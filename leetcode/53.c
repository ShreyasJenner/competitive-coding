// https://leetcode.com/problems/maximum-subarray/description/

#include <stdio.h>

int max(int a, int b) { return a > b ? a : b; }

int maxSubArray(int *nums, int numsSize) {
  int i, j, curr_sum, max_sum;

  curr_sum = max_sum = nums[0];
  for (i = 1; i < numsSize; i++) {
    curr_sum = max(nums[i], curr_sum + nums[i]);
    max_sum = max(curr_sum, max_sum);
  }

  return max_sum;
}

int main() {
  int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int numsSize = 9;
  printf("%d\n", maxSubArray(nums, numsSize));
}
