#include <stdio.h>

int minSubArrayLen(int target, int *nums, int numsSize) {
  int sw_l, sw_r, sw_val, k;

  sw_l = sw_r = 0;
  sw_val = nums[0];
  while (sw_val < target && ++sw_r < numsSize) {
    sw_val += nums[sw_r];
  }

  if (sw_val < target) {
    return 0;
  }

  k = sw_r - sw_l + 1;
  while (sw_r < numsSize) {
    while (sw_val >= target) {
      if (sw_val - nums[sw_l] >= target) {
        sw_val -= nums[sw_l++];
      } else {
        break;
      }
    }

    if (sw_r - sw_l + 1 < k) {
      k = sw_r - sw_l + 1;
    }

    if (++sw_r < numsSize) {
      sw_val += nums[sw_r];
    }
  }

  return k;
}

int main() {
  int nums[] = {12, 28, 83, 4, 25, 26, 25, 2, 25, 25, 25, 12};
  int numsSize = 12;
  int target = 213;

  printf("%d\n", minSubArrayLen(target, nums, numsSize));

  return 0;
}
