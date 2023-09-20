//一个单文件的simple judge
//用来对一个程序进行评测
// c++17

#include <string>
#include <string_view>
#ifdef DEBUG
#include <cstdio>
#endif
#include <vector>

#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <sys/select.h>
#include <sys/resource.h>

using std::literals::operator""sv;

constexpr uint32_t UNLIMITED = 0;
constexpr uint32_t extra_mem_limit = 16; // 16mb

//评测参数
struct judge_config {
    uint32_t    max_cpu_time{UNLIMITED}; // seconds
    uint32_t    max_real_time{UNLIMITED}; // seconds
    uint64_t    max_memory{UNLIMITED}; // mb
    uint64_t    max_stack{UNLIMITED}; //mb
    std::string_view cwd; // current work directory
    std::string_view exe_path{"1"};
    std::string_view input_path{"/dev/stdin"sv};
    std::string_view output_path{"/dev/stdout"sv};
    std::string_view error_path{"/dev/stderr"sv};
    char * args[32];
    char * env[32];
    std::string_view log_path{"judger_log.txt"sv};
} JCONFIG;

int j_args_tot = 0;
int j_env_tot = 0;


enum judgeResult_id {

    SUCCESS             = 0,  // 运行正常
    CPU_TIME_LIMIT_EXCEEDED  = 1, // 超时
    REAL_TIME_LIMIT_EXCEEDED = 2,// 超时
    MEMORY_LIMIT_EXCEEDED    = 3, // 超内存
    RUNTIME_ERROR            = 4, // 运行错误
    SYSTEM_ERROR             = 5, // 系统错误
    WAIT_FAILED         = 6,
    INVALID_CONFIG      = 7,
    FORK_FAILED         = 8,
    PTHREAD_FAILED      = 9,
    ROOT_REQUIRED       = 10,
    LOAD_SECCOMP_FAILED = 11,
    SETRLIMIT_FAILED    = 12,
    DUP2_FAILED         = 13,
    SETUID_FAILED       = 14,
    EXECVE_FAILED       = 15,
    SPJ_ERROR           = 16,
    COMPILE_FAIL        = 17 // TODO
};


//评测结果
struct judge_result {
    int cpu_time; // millisecond
    int real_time; //millisecond
    long memory; // kb
    int signal; // 退出的信号
    int exit_code; // 程序的退出值
    int error; // 错误值
    int result; // 结果 0
} JRESULT;


//// >>>>>>>>> utils
//转成ms
inline long timeval_to_ms(struct timeval & t) {
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

inline void print_judge_result() {
    printf("cpu_time %d\n",JRESULT.cpu_time);
    printf("real_time %d\n",JRESULT.real_time);
    printf("memory %ld\n",JRESULT.memory);
    printf("signal %d\n",JRESULT.signal);
    printf("exit_code %d\n",JRESULT.exit_code);
    printf("error %d\n",JRESULT.error);
    printf("result %d\n",JRESULT.result);

}
inline void print_judge_result_json() {
    printf("{\n");
    printf("\"cpu_time\": %d,\n",JRESULT.cpu_time);
    printf("\"real_time\": %d,\n",JRESULT.real_time);
    printf("\"memory\": %ld,\n",JRESULT.memory);
    printf("\"signal\": %d,\n",JRESULT.signal);
    printf("\"exit_code\": %d,\n",JRESULT.exit_code);
    printf("\"error\": %d,\n",JRESULT.error);
    printf("\"result\": %d\n",JRESULT.result);
    printf("}\n");
}
//// >>>>>>>>> utils end


int main (int argc, char *argv[]) {
    //1. 进行参数分析
    for(int i = 1;i< argc;i+=2) {
#ifdef  DEBUG
        printf("args %d : %s\n",i,argv[i]);
#endif
        char * endchar;
        if( argv[i] == "--max-cpu-time"sv )
        {
            JCONFIG.max_cpu_time = std::strtoull(argv[i+1],&endchar,10);
        }
        else if ( argv[i] == "--max-real-time"sv)
        {
            JCONFIG.max_real_time = std::strtoull(argv[i+1],&endchar,10);
        }
        else if ( argv[i] == "--max-memory"sv)
        {
            JCONFIG.max_memory = std::strtoull(argv[i+1],&endchar,10);
        }
        else if ( argv[i] == "--max-stack"sv)
        {
            JCONFIG.max_stack = std::strtoull(argv[i+1],&endchar,10);
        }
        else if ( argv[i] == "--cwd"sv)
        {
            JCONFIG.cwd = std::string_view(argv[i+1]);

        }
        else if ( argv[i] == "--exe"sv)
        {
            JCONFIG.exe_path = std::string_view(argv[i+1]);
        }
        else if ( argv[i] == "--input"sv)
        {
            JCONFIG.input_path  = std::string_view(argv[i+1]);
        }
        else if ( argv[i] == "--output"sv)
        {
            JCONFIG.output_path = std::string_view(argv[i+1]);
        }
        else if ( argv[i] == "--error"sv)
        {
            JCONFIG.error_path = std::string_view(argv[i+1]);
        }
        else if ( argv[i] == "--args"sv)
        {
            JCONFIG.args[j_args_tot++] = argv[i+1];
        }
        else if ( argv[i] == "--env"sv)
        {
            JCONFIG.env[j_env_tot++] = argv[i+1];
        }
        else if ( argv[i] == "--log"sv)
        {
            JCONFIG.log_path = std::string_view(argv[i+1]);
        }
        else if(argv[i] == "--help"sv){
            printf("--help TODO");
            return 0;
        }
        else
        {
            printf("error! not recognize arg : %s\nplease check usage by --help",argv[i]);
            return -1;
        }
    }
    
#ifdef  DEBUG
    // debug print JCONFIG
    printf("JCONFIG.max_cpu_time =  %u\n",JCONFIG.max_cpu_time);
    printf("JCONFIG.max_real_time =  %u\n",JCONFIG.max_real_time);
    printf("JCONFIG.max_cpu_time =  %u\n",JCONFIG.max_cpu_time);
    printf("JCONFIG.max_stack=  %lu\n",JCONFIG.max_stack);
    printf("JCONFIG.max_memory=  %lu\n",JCONFIG.max_memory);
    printf("JCONFIG.cwd=  %s\n",JCONFIG.cwd.data());
    printf("JCONFIG.input_path=  %s\n",JCONFIG.input_path.data());
    printf("JCONFIG.output_path=  %s\n",JCONFIG.output_path.data());
    printf("JCONFIG.error=  %s\n",JCONFIG.error_path.data());
    printf("JCONFIG.log =  %s\n",JCONFIG.log_path.data());
    for(int i =  0 ;i < j_args_tot ;i++){
        printf("args[%d] : %s\n",i, JCONFIG.args[i]);
    }
    for(int i =  0 ;i < j_env_tot ;i++){
        printf("env[%d] : %s\n",i, JCONFIG.env[i]);
    }
    // printf("JCONFIG.=  %u\n",JCONFIG.);
#endif


    int child_pid = fork();
    if ( child_pid < 0 ) {
        printf("fork error!\n");
        return -1;
    }

    if( child_pid == 0) { // child process
        //1. cwd
        if( JCONFIG.cwd.length() != 0) {
            chdir(JCONFIG.cwd.data());
        }

        //2. setrlimt
        struct rlimit rlim;
        if( JCONFIG.max_memory != UNLIMITED ) {
            uint32_t memory_limt = (JCONFIG.max_memory+extra_mem_limit) * 1024 * 1024; //转成byte
            rlim.rlim_cur = rlim.rlim_max = memory_limt;
            if( setrlimit(RLIMIT_AS,&rlim) != 0) {
                printf("child error: set RLIMIT_AS failed\n");
                fflush(stderr);
                return SETRLIMIT_FAILED;
            }
        }

        if( JCONFIG.max_stack != UNLIMITED ) {
            uint32_t stack_limt = (JCONFIG.max_stack+extra_mem_limit) * 1024 * 1024; //转成byte
            rlim.rlim_cur = rlim.rlim_max = stack_limt;
            if( setrlimit(RLIMIT_STACK,&rlim) != 0) {
                fprintf(stderr,"child error: set RLIMIT_STACK failed\n");
                fflush(stderr);
                return SETRLIMIT_FAILED;
            }
        }

        if( JCONFIG.max_cpu_time!= UNLIMITED ) {
            rlim.rlim_cur = rlim.rlim_max = JCONFIG.max_cpu_time;
            if( setrlimit(RLIMIT_CPU,&rlim) != 0) {
                fprintf(stderr,"child error: set RLIMIT_CPU failed\n");
                fflush(stderr);
                return SETRLIMIT_FAILED;
            }
        }

        if( JCONFIG.max_real_time!= UNLIMITED ) {
            rlim.rlim_cur = rlim.rlim_max = JCONFIG.max_real_time * 1000 * 1000;
            if( setrlimit(RLIMIT_RTTIME,&rlim) != 0) {
                fprintf(stderr,"child error: set RLIMIT_RTTIME failed\n");
                fflush(stderr);
                return SETRLIMIT_FAILED;
            }
        }

        // dup2
        //// 1. 输入重定向:
        if( JCONFIG.input_path.length() != 0 ) {
            FILE * input_file = fopen(JCONFIG.input_path.data(),"r");
            if( input_file == NULL) {
                fprintf(stderr,"input file %s not existed!", JCONFIG.input_path.data());
                fflush(stderr);
                return DUP2_FAILED;
            }
            dup2(fileno(input_file),0);
            fclose(input_file);
        }

        //// 2. 输出重定向:
        if( JCONFIG.output_path.length() != 0 ) {
            FILE * output_file = fopen(JCONFIG.output_path.data(),"w");
            if( output_file == NULL) {
                fprintf(stderr,"output file %s create failed!", JCONFIG.output_path.data());
                fflush(stderr);
                return DUP2_FAILED;
            }
            dup2(fileno(output_file),1);
            fclose(output_file);
        }

        //// 3. 错误重定向:
        if( JCONFIG.error_path.length() != 0 ) {
            FILE * error_file = fopen(JCONFIG.error_path.data(),"w");
            if( error_file == NULL) {
                fprintf(stderr,"error file %s create failed!", JCONFIG.error_path.data());
                fflush(stderr);
                return DUP2_FAILED;
            }
            dup2(fileno(error_file),2);
            fclose(error_file);
        }

        execve(JCONFIG.exe_path.data(),JCONFIG.args,JCONFIG.env);
        return 0;
    }
    // father pid

    int status;
    waitpid(child_pid,&status,0);
    struct rusage usage;
    // int return_val_getrusage = getrusage(RUSAGE_CHILDREN, &usage);
    getrusage(RUSAGE_CHILDREN, &usage);

    if( WIFSIGNALED(status) != 0) // 子进程是否是被信号退出的
    {
        JRESULT.signal  = WTERMSIG(status); //得到退出的信号
    }

    if(JRESULT.signal == SIGUSR1) // 接受的信号是用户自定义的信号
    {
        JRESULT.result = SYSTEM_ERROR;
    }
    else {
        if( WIFEXITED(status))
            JRESULT.exit_code = WEXITSTATUS(status); //退出的代码

        //得到子进程运行的cpu_time
        JRESULT.cpu_time = timeval_to_ms(usage.ru_utime) + timeval_to_ms(usage.ru_stime);

        JRESULT.memory = usage.ru_maxrss;

        if(JRESULT.exit_code != 0 )
            JRESULT.result = SYSTEM_ERROR;

        if( JRESULT.signal == SIGSEGV) //段错误
        {
            if( JCONFIG.max_memory != UNLIMITED && JCONFIG.max_memory * 1024 <  (uint64_t)JRESULT.memory)
            {
                JRESULT.result = MEMORY_LIMIT_EXCEEDED;
            }
            else
                JRESULT.result = RUNTIME_ERROR;
        }
        else { // 不是被 SEGV错误
            if(JRESULT.signal != 0)
                JRESULT.result = RUNTIME_ERROR;
            if( JCONFIG.max_memory != UNLIMITED && JCONFIG.max_memory * 1024 <  (uint64_t)JRESULT.memory)
            {
                JRESULT.result = MEMORY_LIMIT_EXCEEDED;
            }

            if( JCONFIG.max_cpu_time!= UNLIMITED && JCONFIG.max_cpu_time <  (uint64_t)JRESULT.cpu_time)
            {
                JRESULT.result = CPU_TIME_LIMIT_EXCEEDED;
            }

            if( JCONFIG.max_real_time != UNLIMITED && JCONFIG.max_real_time <  (uint64_t)JRESULT.real_time)
            {
                JRESULT.result = REAL_TIME_LIMIT_EXCEEDED;
            }
        }
    }

    if( isatty(fileno(stdout))) {
        print_judge_result();
    }
    else
        print_judge_result_json();

    return 0;
}
