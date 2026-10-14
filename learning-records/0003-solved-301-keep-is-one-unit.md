# Solved LC 301 with backtracking; "keep" must be one unit

The learner wrote a correct pruned keep/delete DFS for LC 301. It passed all 7 local tests and matched a brute-force BFS on 20,000 random inputs. It needed two pointer-style hints and no code was handed over. Both bugs were the same misconception: treating a **keep** as separable pieces rather than one atomic push → recurse(updated state) → pop unit.

1. They split keep into two calls: one updated `open` without pushing, the other pushed without updating `open`. That produced three children per bracket.
2. Their letter branch pushed but never recursed or popped, so the search dead-ended at the first letter.

**Evidence**: `usr/src/leetcode/301.cpp` (2026-10-14). The warm-up `usr/src/warmup/subsequences.cpp` passed first time, so the plain unpruned DFS was fine. Errors appeared only when pruning conditions were mixed into the branches.

**Implications**: DFS over choices is now usable (supersedes the gap noted in [[0002-dfs-as-implicit-tree-is-new]]). In future backtracking problems, check that every branch is "one child = one complete state transition". A useful self-check prompt is "how many `dfs` calls can one node make?" Next candidates: the dedup skip-rule stretch goal (pruning equal siblings), or the BFS formulation of 301 as the bridge into graphs.
