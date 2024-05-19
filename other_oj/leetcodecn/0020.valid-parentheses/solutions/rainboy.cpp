const int maxn = 1e5+5;
template<typename T = int,int siz = maxn>
struct mystack{
    T sta[siz+5];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}

    int size() { return head;}
};

class Solution {
public:
    mystack<char> sta;
    bool isValid(string s) {

        for(int i = 0 ;i<s.length();i++){
            char c = s[i];

            if( c == '(' || c == '[' || c == '{')
                sta.push(c);
            else  {
                if( sta.empty()) return 0;
                char t = sta.top();
                if( t == '(' && c == ')')
                {
                    sta.pop();
                    continue;
                }
                if( t == '[' && c == ']')
                {
                    sta.pop();
                    continue;
                }
                if( t == '{' && c == '}')
                {
                    sta.pop();
                    continue;
                }
                return 0;

            }
        }
        return sta.empty();

    }
};
