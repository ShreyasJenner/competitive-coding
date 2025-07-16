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

  struct Node *ptr, *new_node, *head2;

  ptr = head;
  while (ptr != NULL) {
    new_node = malloc(sizeof(struct Node));
    new_node->val = ptr->val;

    new_node->next = ptr->next;
    ptr->next = new_node;

    ptr = ptr->next->next;
  }

  ptr = head;
  while (ptr != NULL) {
    if (ptr->random != NULL) {
      ptr->next->random = ptr->random->next;
    } else {
      ptr->next->random = NULL;
    }

    ptr = ptr->next->next;
  }

  ptr = head->next;
  head2 = head->next;
  while (ptr != NULL) {
    if (ptr->next != NULL) {
      ptr->next = ptr->next->next;
    }

    ptr = ptr->next;
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
