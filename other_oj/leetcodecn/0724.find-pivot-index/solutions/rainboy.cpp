
const int maxn = 1e5+5;
class Solution {
public:
    int a[maxn]; //前缀和
    int pivotIndex(vector<int>& nums) {
        int len = nums.size();
        for(int i =0 ;i<len;i++){
            a[i+1] = a[i] + nums[i]; // 注意这里,想一想为什么a从下标1开始?
        }
        for(int i =1;i<=len;i++){
            int left = a[i-1];
            int right = a[len] - a[i];
            if( left == right)
                return i-1;
        }
        return -1;
    }
};
