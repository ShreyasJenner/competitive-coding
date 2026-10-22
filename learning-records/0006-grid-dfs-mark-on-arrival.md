# Grid DFS: mark on arrival, count in the scan

The learner solved LC 200 (their first graph search) unaided, from Lesson 5 with no hints requested. It passes 16/16 under ASan/UBSan, including a 45k-cell snake and 3000 random grids vs union-find. They marked the cell on arrival by sinking it to `'0'` before recursing, kept the counter in the scan only, and checked bounds at each call site instead of at the top of the callee (valid, just less common).

**Evidence**: `usr/src/leetcode/200.cpp` (2026-10-21), first run green as reported.

**Implications**:
- This was the first problem after the switch to Mediums. It landed easily, which supports staying at Medium while building graph and DP patterns.
- The grid-as-graph idea and the visited rule are now in place. Next steps in the ZPD: a fill that *returns* a value (LC 695), BFS on a grid (shortest steps, e.g. LC 994/1091), then general adjacency-list graphs (LC 207).
- Not yet seen: whether they can handle a direction array (`dr`/`dc`) loop. Their code uses four hand-written `if`s.
