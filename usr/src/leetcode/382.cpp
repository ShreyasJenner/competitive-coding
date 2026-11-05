#include <iostream>
#include <vector>

/*
LC 382 Linked List Random Node

Given a singly linked list, return a random node's value from it. Each node
must have the same probability of being chosen.
  Solution(ListNode* head)  sets up the object with the head of the list.
  int getRandom()           picks a node at random and returns its value.
1 <= number of nodes <= 1e4, -1e4 <= Node.val <= 1e4,
at most 1e4 calls to getRandom.

Follow up: what if the list is extremely large and its length is unknown to
you? Could you solve it efficiently without using extra space?
*/

// LeetCode supplies this struct; don't change it.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
    ListNode *head;
    Solution(ListNode* head) {
        this->head = head;
    }

    int getRandom() {
        ListNode *ptr = this->head;
        int ans, probs;

        probs = 1;
        while(ptr != nullptr) {
            if(!(std::rand() % probs)) {
                ans = ptr->val;
            }

            probs++;
            ptr = ptr->next;
        }

        return ans;
    }
};

#ifndef TEST
int main() {
    // 1 -> 2 -> 3
    ListNode *a = new ListNode(1), *b = new ListNode(2), *c = new ListNode(3);
    a->next = b, b->next = c;

    {
        Solution sol(a);
        // Each of 1, 2, 3 should come up about a third of the time.
        for (int i = 0; i < 10; i++) std::cout << sol.getRandom() << ' ';
        std::cout << '\n';
    }
    // The list belongs to the caller (here, main), so main frees it.
    delete a, delete b, delete c;
    return 0;
}
#endif
