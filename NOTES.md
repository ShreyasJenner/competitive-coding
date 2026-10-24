# Teaching notes

## ▶ RESUME HERE (end of session 2026-10-23)

**LC 236 SOLVED, 18/18** (record 0008). It was attempted cold first with a path-comparison version, which failed on the vine because the path was copied by value. After reading Lesson 6 they wrote the contract version. The template is now in `reference/trees.html`.

**Open the next session with:** (1) a spaced check: "In 236 with p=7, q=4 on the example tree, what does the call on node 5 return, and why?" (Want 2, passed up; they said "both → returns itself" this session.) (2) Offer the next problem with AskUserQuestion. Recommend **LC 198 House Robber** (first DP, an unprompted test of "return your own answer" + overlap). Alternatives: **LC 543 Diameter** cold (tree, return height but track the best: a new twist), **LC 994** grid BFS.
- **New preference/pattern:** they attempt problems cold before reading the lesson. Build future lessons as "attempt cold first (link the tests) → lesson as the reveal", rather than fighting it.
- Optional cleanups (both mentioned, status unknown): drop the redundant `a == NULL && b == NULL` branch, and switch the `//` ASCII art in their main to `/* */` (it triggers `-Wcomment`).
- **Before building the 198 lesson:** close the RESOURCES gap on DP (evaluate CPH ch. 7, USACO Guide Gold DP, Errichto). `assets/tree.js` takes an `algorithm` option if a tree-DP lesson (543/337) comes later.

### Earlier in this session: issuing Lesson 6

**In progress: LC 236 LCA via Lesson 6** (`lessons/trees/0006-ask-your-children.html`), the new **trees** topic. The starter `usr/src/leetcode/236.cpp` returns `root` (8/18 pass by accident). `usr/test/leetcode/236.cpp` has 18 cases: a parent-map reference, a 65535-node complete tree, a 30000-node vine, and a stress test of 3000 random trees. It was verified in the scratchpad: the standard solution and a count+out-param solution both get 18/18, and the "return left early" bug fails 11.
- **Vine depth is 30000, not 1e5**, because ASan frames overflow the 8 MB stack near 1e5 even for correct code (the count-based solution crashed at 1e5 and passed at 50000).
- Spaced check at the start of the session: 695 return/max passed. They said "returns the size of the island"; I sharpened it to the per-call view (0 when rejected, otherwise 1 + sum).
- **What to watch (record 0007):** does their contract comment (step 1 of §5) return their *own* answer, or do they reach for an accumulator/out-param again? A count + out-param solution is correct, so accept it but name the difference. When they're solved: write record 0008 and put their verified template in `reference/trees.html` (placeholder is there).
- Hints only if they're stuck: the lesson's Hint 1–3 ladder, then point at lines.
- Next after 236: **LC 198 House Robber** (first DP), as recommended in the lesson.

## Previous resume (end of session 2026-10-22)

**Open the next session with:** (1) a spaced check from memory: "In 695, what does the fill return, and where does the `max` live?" (Want: 0 for water/seen, otherwise `1 + sum of the 4 neighbours`; the max is only in the scan.) (2) Offer the next problem via AskUserQuestion. Recommend **LC 236 LCA** (a lesson; tests "return your own answer" unprompted); alternatives are LC 198 (first DP) and LC 994 (grid BFS).

### Session log 2026-10-22

- Spaced checks passed. Grid DFS: at first they said only "check visited at the top". When I showed them a fill that checks at the top but marks after recursing, they placed the mark correctly and explained the A↔B loop. 1106: 3/5/6 correct, and record 0005 is updated (ownership is settled).
- **LC 695 SOLVED cold, 16/16** (record 0007). It uses an accumulator-threading contract with redundant `max`es, which the learner confirmed after one question. The template and a "two contracts" table are now in `reference/graphs.html`. The rewrite to `1 + sum(children)` is DONE (16/16). Next: the next problem. **Recommend LC 236 LCA or LC 198 House Robber**, since both rely on "return your own answer". Next session's spaced check: "what does a fill return in 695, and where does the max live?"
- (Original issue note) **LC 695 Max Area of Island issued cold** (learner's choice). `usr/test/leetcode/695.cpp` has 16 cases with a union-find reference and stress test, and it was verified with a scratchpad DFS. The starter `usr/src/leetcode/695.cpp` returns 0 (3/16 pass). There is no lesson. If they get stuck, give hints only: "what should a fill *return*?", then "1 + the sum of the neighbours". When solved, write record 0007 and add the 695 template to `reference/graphs.html`.
- Watch for: counting area in the scan rather than in the fill, and a `max` taken over the wrong thing.

## Previous resume (end of session 2026-10-21)

**Where things stand.** LC 200 Number of Islands is **solved** (record 0006): 16/16 under ASan, unaided, no hints, with Lesson 5 as its lesson. This was the first problem after the switch to Mediums (see Pacing below). Lessons 1–5 exist, and the latest is `lessons/graphs/0005-every-cell-is-a-node.html`. `reference/graphs.html` now has the verified LC 200 template.

**Open the next session with these, in order:**
1. **Spaced retrieval, from memory:** "What's the one rule that keeps grid DFS from looping forever, and where in the fill does it go?" (Want: mark on arrival, before any neighbour call.) Keep it quick.
2. **Unresolved check from Lesson 4:** on 2026-10-21 they stated the cursor contract correctly. On who owns `,`/`)` they said "the call that parsed the sub expression", which is ambiguous between parent (correct) and child (the old misconception). Lesson 5 §0 has a drill to settle it: tracing `&(t,f)`, want `t`→3, `f`→5, `&`→6. **Ask whether they did it and got 3/5/6 without the reveal.** If not, revise record 0005's "ownership" implication and re-drill.
3. **Offer the next problem (Medium).** My recommendation is **LC 695 Max Area of Island, solved cold**: no lesson, just a test file plus a starter. Same scan, but the fill *returns* a size, which tests transfer and a change of contract. Alternatives in other weak areas: **LC 198 House Robber** (first DP: brute-force recursion → remove repeated work), **LC 236 LCA** (tree recursion that returns info upward), **LC 78 Subsets** (backtracking confidence win).
4. **Ask about optional items** (all status unknown): comparing with walkccc 200 (it shows BFS), the `dr`/`dc` loop cleanup in their 200 (they wrote four hand-written `if`s), LC 90 Subsets II cold, walkccc 1106 / 301 comparisons, *Crafting Interpreters* §6.2.

**Graph track after 695:** BFS on a grid (shortest steps, e.g. LC 994 Rotting Oranges / 1091) → general adjacency-list graphs (LC 207 Course Schedule). `assets/grid.js` accepts an `algorithm` option, so a BFS lesson can reuse it. RESOURCES gap: still need a trusted source for BFS shortest paths / topological sort.

**Uncommitted at session end** (the learner commits themselves): 200 solution + test, Lesson 5, `assets/grid.js`, `style.css` grid styles, `course.js` graphs topic, `reference/graphs.html`, record 0006, RESOURCES.md, NOTES.md, and the learner's deletion of the old `200.c`.

## Pacing

- **2026-10-21 (learner's request):** "So far I've only been solving hard problems which I struggle with a lot." They want slightly easier problems (**LC Medium**) that still cover the weak concepts (graphs, DP, trees/recursion). Default to Mediums, and raise the difficulty only when they ask or clearly cruise. The mission's success criterion (an unaided Hard) is unchanged. 200 landed easily, so stay at Medium for now.
- When offering a choice of problems, the AskUserQuestion multiple-choice format worked well (they picked from 200/198/236/78).

## Learner preferences & conventions

- Language: C++ for all lesson code. Repo style is `class Solution` plus a `main` that prints results.
- Workflow (since 2026-10-14): the learner's code lives in `usr/src/<platform>/N.cpp`, with `main` wrapped in `#ifndef TEST`. Tests go in `usr/test/<platform>/N.cpp`, which `#include "../../src/<platform>/N.cpp"` and `"../testlib.hpp"`, call `testlib::record(ok, input, got, want)` once per case, and end `main` with `return testlib::summary();`. test.sh totals cases across files; the learner wants per-case counts, not per-file. Run with `./test.sh N`, `./build.sh N` and `./clean.sh`; binaries land in `usr/bin`. Builds use ASan/UBSan. For each lesson problem, ship the test file and a starter (not the solution).
- Learner likes to drive by naming a specific problem to crack ("teach me via LC 301"). Build lessons around the problem, and don't hand over full solutions: use progressive hints plus a local PASS/FAIL harness.
- Weak areas self-reported: DP, graphs, trees/recursion, and optimising from brute force.
- Don't reuse one variable name for two roles across phases. In Lesson 1, `rmR` meant both "scan counter going up" and "search budget going down", and the learner was rightly confused by `r=1` at the tree's root. Name the phases explicitly, or use distinct names.
- Debugging help style that worked: run `./test.sh`, then point at the exact lines and the failure pattern (e.g. "every failing test contains a letter") without writing the fix. The learner fixed both 301 bugs from pointers alone.
- Before declaring a solution done, stress-test it against a brute force in the scratchpad.
- Reference sheets hold back the C++ template until the learner has solved the problem (a placeholder comment marks the spot), then add it, verified against the tests.
- **Lesson design rule (2026-10-20):** every self-check must have a way to reveal the answer (quiz.js drills show a "Show answer" button after a wrong check), and position/index questions need an index ruler.
- Spacing: start each session with a quick cold retrieval check on the previous topic before new work.
- **Lesson layout (learner's request, 2026-10-19):** lessons are grouped by topic in `lessons/<topic>/NNNN-name.html`, and NNNN stays a global sequence number (next free: **0007**). Asset/reference paths from a lesson are `../../assets/` and `../../reference/`. Each lesson's nav is `<nav class="course no-print" data-topic=… data-file=…>`, rendered by `assets/course.js` from its TOPICS list. To add a lesson, add it to TOPICS. To add a topic, add an entry with its reference sheet. `lessons/index.html` is the revision hub listing every topic. The learner wants lessons in a topic to link to each other so they can revise a topic.

## Components (assets/)

- `style.css`: shared styles; colour tokens with a dark mode; print styles.
- `quiz.js`: `.quiz` multiple choice (data-answer, 0-based), `.drill` fill-ins (data-expect) with "Show answer", `.score`, `button.copy`.
- `stepper.js`: step-through for recursive code. `step.tape = {text, pos, from}` handles string+cursor (parsers). `Stepper.recorder()` generates steps.
- `grid.js` (2026-10-21): `Grid.mount(root, {rows, markToggle, maxSteps, algorithm})`. Editable land/water grid, scan+fill stepper (default `Grid.floodDFS`), and a "mark on arrival" toggle that shows the infinite loop. Steps are `{seen, cur, scan, stack, count, note}`.
- `tree.js` (2026-10-23): `Tree.draw(fig, levelOrder, {labels, marks})` draws a static SVG figure. `Tree.mount(div, {values, p, q, algorithm, pick})` is a stepper with p/q selects (default `Tree.lca`). Steps are `{cur, stack, ret:{id:label}, note}`, so a size/height/DP-on-tree algorithm can reuse it. Classes are `tr-*` in style.css. Check a lesson's rendering with `firefox --headless --no-remote --profile <scratch dir> --screenshot`.
- A static index ruler can reuse `.st-tape` / `.st-cell` / `.st-idx` markup (see Lesson 5 §0).
- Test-file pattern worth reusing: embed a reference (brute force or a *different* algorithm, e.g. union-find for 200, a stack evaluator for 1106) plus a seeded random `stress(runs)` that records one case and reports the first mismatch.

## Parked: LC 301 optimisation plan (not dropped)

- Agreed plan (learner's choice, 2026-10-14): (1) dedup skip-rule to drop `std::set` — **DONE** (record 0004); (2) cheaper state; (3) the BFS formulation (bridge to graphs).
- **Step (2) when resumed:** a short lesson in `lessons/backtracking/`. Targets in `usr/src/leetcode/301.cpp`: `getDeleteBudget(std::string s)` takes `s` by value (should be `const std::string&`, or use the member), and `removeInvalidParentheses` returns a needless copy `std::vector<std::string>(out.begin(), out.end())` (could return/move `out`). Also consider `this->` noise and `s_len`. It should be quick, since they already used `const std::string&` in 1106.
- **Step (3)** fits naturally after a grid-BFS lesson on the graph track.
- Also parked from 1106: an explicit-stack rewrite of 1106, and LC 394 Decode String cold (would now be a Medium-level interleaving option).

## History

- 2026-10-14: LC 301 solved (record 0003). Before that: records 0001 (prior sliding window / two pointers) and 0002 (DFS as an implicit tree is new).
- 2026-10-19: Lesson 3 (skip equal siblings) for 301 step (1). Two rules were verified correct (40k random cases each): "no delete child if s[i]==s[i-1] and s[i-1] kept" (taught), and "no delete child if path.back()==s[i]" (also valid, so don't mark it wrong). The learner used the path.back() rule and fixed the empty-path guard themselves; 13/13 pass. The taught `prevKept` version was shown for comparison afterwards. Optional cleanup was suggested (merge the empty `if {} else`).
- 2026-10-19/20: LC 1106 via Lesson 4 (recursive descent, cursor contract). Got stuck on drill Qs 3–4 (index after an expr), which led to the "Show answer" + index ruler fix. Solved 14/14 under ASan (record 0005), with misconceptions fixed by line pointers only: leaf ate the `,`, a hand-counted depth, `!` not stepping past `)`, and `int*` vs position. The template is in `reference/recursive-descent.html`. Optional cleanups mentioned: `!` uses a loop, `==true?false:true`, duplicate `|`/`&` branches.
- 2026-10-21: switched to Mediums. Lesson 5 (LC 200) issued and solved the same session (record 0006). Their style: sink to `'0'` on arrival, bounds checked at the call site, count in the scan only. Scratchpad checks: mark-after-recurse → ASan stack-overflow on case 1; 8 directions → 5 failures.
