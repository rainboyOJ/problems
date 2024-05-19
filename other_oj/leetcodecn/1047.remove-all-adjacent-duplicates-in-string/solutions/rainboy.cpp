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
    mystack<char> t;
    string removeDuplicates(string s) {
        for(int i =0;i<s.length();i++){
            char c = s[i];
            
            if( !t.empty() && t.top() == c ){
                t.pop();
            }
            else t.push(c);
        }
        string ret;

        for(int i = 0 ;i < t.head;i++)
            ret += t.sta[i];
        // std::reverse(ret);
        return ret;
    }
};
