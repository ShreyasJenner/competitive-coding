# LC 236: path comparison first, then the "return your own answer" contract after the lesson

On 2026-10-23 the learner solved LC 236 (18/18 under ASan/UBSan, including a 65535-node complete tree, a 30000-node vine and 3000 random trees). They **attempted it cold before reading Lesson 6**, because they felt they already had the solution.

**Attempt 1 (their own idea):** find the root→p and root→q paths with a recursive `findNode`, then take the last common node of the two paths. The algorithm is valid (it is the same idea as the test's reference). It passed 16/16 once the vine cases were skipped. But `path` was passed **by value**, and each frame also created two more vectors to hold the children's paths, so the work was O(n·h). That makes it O(n²) on a vine, and it hit an ASan stack-overflow at depth 30000. It also compared `val` instead of pointers. Pointers given: line 25 (by value) and the copies per frame; "what did 301 do with a growing path?"

**Attempt 2 (after reading the lesson):** the one-pass post-order contract: null → null, `root == p || root == q` → root, both sides non-null → root, else whichever is non-null. It compares pointers. There is one redundant branch (both null).

**Evidence**: `usr/src/leetcode/236.cpp` (2026-10-23). Retrieval right after: "only p → returns p" was correct. "Both → returns itself" was **imprecise**: for p=7, q=4, `f(5)` returns 2 (passed up), not 5. I corrected it to "both → returns their LCA, which may be deep below t".

**Implications**:
- Record 0007's question ("will they pick 'return your own answer' unprompted?") is answered **no, not yet**. Unprompted, they reached for search → collect paths → compare, which is two passes plus extra storage. They can apply the contract once it is shown. The next unprompted test is LC 198 (DP), or a cold tree problem such as LC 543 Diameter.
- The "both → myself" wording suggests they think of the return value as "which node am I" rather than "what my subtree found". Recheck with a spaced question: "f(5) with p=7, q=4 returns?" (want 2).
- Value vs reference is still a blind spot under recursion (`std::vector` by value). 301 step (2) in NOTES targets the same habit. Consider pairing them.
- Pattern: they like to try first, then read. Lessons could open with a timed "attempt it cold" step, and the contract box serves as the reveal.
