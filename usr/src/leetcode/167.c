// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *numbers, int target, int l, int r) {
  if (l > r) {
    return -1;
  }

  int mid;
  mid = (l + r) / 2;
  if (numbers[mid] == target) {
    return mid;
  } else if (numbers[mid] > target) {
    return binarySearch(numbers, target, l, mid - 1);
  } else {
    return binarySearch(numbers, target, mid + 1, r);
  }
}

int *twoSum_O_N(int *numbers, int numbersSize, int target, int *returnSize) {
  int i, idx;
  int *ans = malloc(sizeof(int) * 2);
  *returnSize = 2;

  for (i = 0; i < numbersSize; i++) {
    idx = binarySearch(numbers, target - numbers[i], i + 1, numbersSize - 1);
    if (idx != -1) {
      ans[0] = i + 1;
      ans[1] = idx + 1;
      return ans;
    }
  }

  return NULL;
}

int *twoSum_O_log_N(int *numbers, int numbersSize, int target,
                    int *returnSize) {
  int i, j;
  int *ans = malloc(sizeof(int) * 2);
  *returnSize = 2;

  i = 0;
  j = numbersSize - 1;
  while (i < j) {

    if (numbers[i] + numbers[j] == target) {
      ans[0] = i + 1;
      ans[1] = j + 1;
      break;
    } else if (numbers[i] + numbers[j] > target) {
      j--;
    } else {
      i++;
    }
  }

  return ans;
}

int main() {
  int numbersSize, target, returnSize;

  int numbers[] = {-10, -2, 1, 2, 5, 6, 8};
  numbersSize = 7;
  target = 0;
  int *ans = twoSum_O_log_N(numbers, numbersSize, target, &returnSize);

  printf("[%d, %d]\n", ans[0], ans[1]);

  free(ans);

  return 0;
}
