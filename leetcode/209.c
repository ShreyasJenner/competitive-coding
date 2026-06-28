// https : // leetcode.com/problems/minimum-size-subarray-sum/

#include <stdio.h>

/*
 * Pseudo Code:
 * Set the min size to size of array + 1
 * Expand sliding window to right till it reaches end of array:
 *    Add rightmost element in sliding window to sum
 *    While sum of elements in sliding window >= target:
 *       Replace min size if it is greater than size of sliding window
 *       Shrink sliding window from left
 * Return 0 if min size is still set to size of array + 1, else return min size
 */

int minSubArrayLen(int target, int *nums, int numsSize) {
  int sum, min_size, i, j;

  i = j = 0;
  sum = 0;
  min_size = numsSize + 1;

  for (j = 0; j < numsSize; j++) {
    sum += nums[j];

    while (sum >= target) {
      min_size = j - i + 1 < min_size ? j - i + 1 : min_size;
      sum -= nums[i];
      i++;
    }
  }

  return min_size == numsSize + 1 ? 0 : min_size;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5};
  int numsSize = 5;
  int target = 15;

  printf("%d\n", minSubArrayLen(target, nums, numsSize));
}
