一个simple judge,提供简单的可用的本地使用评测器

- 评测给定的程序
- 重定义输入输出
- 限制时间与内存的大小
- 得到运行的后的资源的使用


用到的linux下的系统调用

如果你想要学习如何编写这个代码,你可以查看[learn](./learn/)文件夹下的相关代码

## rlimit

根据[这里][1],可以学习rlimit的使用

我们需要的内容

- `RLIMIT_AS`
- `RLIMIT_CPU`
- `RLIMIT_RTTIME`

## dup2

- 查看手册`man 2 dup2`

## waitpid


## signalfd的使用

- [Linux fd 系列 — signalfd 是什么 ？ - 知乎](https://zhuanlan.zhihu.com/p/418256266)
 - 创建`int signalfd(int fd, const sigset_t *mask, int flags);`
 - 清空`sigemptyset(&mask);`
 - 添加`sigaddset(&mask, SIGINT);`
 - sigprocmask
- `man 2 signalfd`


## 参考的文章

- [1]: https://www.geeksforgeeks.org/get-set-process-resource-limits-in-c/ "GetSet process resource limits in C - GeeksforGeeks"
- [2]: https://insidelinuxdev.net/article/a0cnmn.html "signalfd, pidfd 实现poll等待子进程退出 - ILD"
