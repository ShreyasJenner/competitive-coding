# A fill that returns a value: accumulator vs "return your own answer"

The learner solved LC 695 cold (no lesson, no hints) on 2026-10-22. It passes 16/16 under ASan/UBSan, including the 50x50 snake and 3000 random grids vs union-find. The scan/fill split carried over from 200, and they marked on arrival again.

**Their contract:** `dfsFlood(grid, r, c, f)` threads a running total. It returns `f` plus the number of cells this call sinks, and each child receives the total so far. After each child they wrote `flooded = max(tmp, flooded)`. Asked "can `tmp` ever be smaller than `flooded`?", they answered "no" correctly, but the reason was "it's larger if it lands on an island bigger than the current value". That is a comparison framing, when in fact it is a sum. A scratchpad check confirmed the four `max` lines are always `flooded = tmp`.

**Evidence**: `usr/src/leetcode/695.cpp` (2026-10-22). Spaced checks the same session: grid DFS mark-on-arrival (needed one prompt), 1106 ownership 3/5/6 correct.

**Implications**:
- They reach for "pass state down" by default. The "return my own answer, parent combines children" contract (`1 + sum(children)`) is not yet their first instinct. That contract underlies tree recursion (236) and DP (198), so it's the next thing to make deliberate.
- Transfer from 200 to 695 was clean at Medium. Stay at Medium.
- **Same-day rewrite:** prompted only with "return `1 + sum of the four calls`", they dropped the parameter and wrote `return 1 + dfsFlood(...) + ...` with the `max` only in the scan. Still 16/16. They can apply the contract when it's named. Whether they pick it unprompted is what 236/198 will test.
- Minor: `if (grid[r][c] == 1)` after the guard is always true. `max_flooded` is set twice and doesn't need to be a member. Still four hand-written calls rather than a `dr`/`dc` loop.
