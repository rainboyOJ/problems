// struct Solution;
impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        for i in 1..nums.len(){
            // println!("{} {}",i,nums[i]);
            for j in 0..i {
                // println!("{} {} ",nums[i],nums[j] );
                if nums[j] + nums[i] == target {
                    return vec![j as i32,i as i32];
                }
            }
        }
        vec![]
    }
}

// fn test() {
//     let nums = vec![2, 7, 11, 15];
//     let target = 9;
//     assert_eq!(Solution::two_sum(nums, target), vec![0, 1]);
// }

// fn main() {
//     test()
// }

