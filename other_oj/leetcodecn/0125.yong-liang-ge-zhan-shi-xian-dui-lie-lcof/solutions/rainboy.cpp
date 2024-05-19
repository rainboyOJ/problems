#include <stack>
class CQueue {
public:
    std::stack<int> s1,s2;
    CQueue() {

    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if( s2.empty()) {

            while( !s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }

        if( s2.empty())
            return -1;
        else {
            int t= s2.top();
            s2.pop();
            return t;
        }
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
