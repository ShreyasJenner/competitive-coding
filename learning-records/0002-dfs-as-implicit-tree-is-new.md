# DFS over an implicit tree is new; tree recursion is not

The learner could write the budget scan for LC 301 unaided, but was stuck at "write the DFS" and said they don't know DFS. They have, however, written recursive tree traversal over an explicit `TreeNode*` tree (`count_descendants` in LC 230). The gap is recognising that a recursion over *choices* is the same DFS, with the tree living only in the call stack, plus the choose/explore/un-choose discipline for shared state.

**Evidence**: Message during Lesson 1, step 2; `usr/src/leetcode/230.cpp`; `usr/src/leetcode/301.cpp` scan is correct.

**Also observed**: In the state-tracing check for `"())(()"`, they gave (0,0,0) instead of (0,0,1) after deleting the first `(`. They decremented `rmR` alongside `rmL`, possibly by collapsing the next forced deletion into the same step. Watch for "one node = one decision" slips.

**Implications**: Anchor new search techniques on 230-style tree recursion. Graph DFS (LC 200 territory) should be taught as the same idea with a visited set. Don't assume they can trace call order without a visualiser yet; Lesson 2's drill (predict the leaf order for "abc") is the check.
