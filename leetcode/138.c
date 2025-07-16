#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node *next;
  struct Node *random;
};

int index_of(struct Node *ptr, int size) {
  if (ptr == NULL) {
    return -1;
  }

  int count;

  count = 0;
  while (ptr != NULL) {
    count++;
    ptr = ptr->next;
  }

  return size - count;
}

struct Node *copyRandomList(struct Node *head) {
  if (head == NULL) {
    return NULL;
  }

  int size, idx;
  struct Node *ptr, *head2, *ptr2;
  struct Node *itr, *itr2;

  size = 0;
  ptr = head;
  while (ptr != NULL) {
    size++;
    ptr = ptr->next;
  }

  ptr = head;
  head2 = malloc(sizeof(struct Node));
  ptr2 = head2;
  while (ptr != NULL) {
    ptr2->val = ptr->val;
    if (ptr->next == NULL) {
      ptr2->next = NULL;
    } else {
      ptr2->next = malloc(sizeof(struct Node));
      ptr2 = ptr2->next;
    }

    ptr = ptr->next;
  }

  ptr = head;
  ptr2 = head2;
  while (ptr != NULL) {
    itr = ptr->random;
    if (itr == NULL) {
      ptr2->random = NULL;
    } else {
      idx = index_of(itr, size);
      itr2 = head2;
      while (idx--) {
        itr2 = itr2->next;
      }
      ptr2->random = itr2;
    }
    ptr = ptr->next;
    ptr2 = ptr2->next;
  }

  return head2;
}

void print_linked_list(struct Node *head) {
  struct Node *ptr;
  int idx, size;

  size = 0;
  ptr = head;
  while (ptr != NULL) {
    size++;
    ptr = ptr->next;
  }

  ptr = head;
  while (ptr != NULL) {
    idx = index_of(ptr->random, size);
    if (idx == -1) {
      printf("(%d, NULL), ", ptr->val);
    } else {
      printf("(%d, %d), ", ptr->val, idx);
    }

    ptr = ptr->next;
  }

  printf("\n");
}

int main() {
  struct Node n1, n2, n3, n4, n5;
  struct Node *ans;

  n1.val = 7;
  n2.val = 13;
  n3.val = 11;
  n4.val = 10;
  n5.val = 1;

  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n5;
  n5.next = NULL;

  n1.random = NULL;
  n2.random = &n1;
  n3.random = &n5;
  n4.random = &n3;
  n5.random = &n1;

  print_linked_list(&n1);

  ans = copyRandomList(&n1);

  print_linked_list(ans);

  return 0;
}
