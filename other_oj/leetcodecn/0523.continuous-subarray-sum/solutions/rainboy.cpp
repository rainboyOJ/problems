class Solution {
public:
    std::map<int,int> m;
    bool checkSubarraySum(vector<int>& nums, int k) {
        int len = nums.size();
        int pre = 0;
        for(int i =0;i< len;i++) {
            pre += nums[i];
            pre %= k;
            if( pre == 0 && i > 0) {
                return true;
            }
            if( m.find(pre) != m.end()){
                if( i - m[pre] >=2)
                    return true;
            }
            else m[pre] = i; // 没有找到,注意只记录第一个mod为pre的位置
        }
        return 0;
    }
};
