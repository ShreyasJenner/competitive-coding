# Teaching notes

## ▶ RESUME HERE (as of end of session 2026-10-21)

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
- **Lesson layout (learner's request, 2026-10-19):** lessons are grouped by topic in `lessons/<topic>/NNNN-name.html`, and NNNN stays a global sequence number (next free: **0006**). Asset/reference paths from a lesson are `../../assets/` and `../../reference/`. Each lesson's nav is `<nav class="course no-print" data-topic=… data-file=…>`, rendered by `assets/course.js` from its TOPICS list. To add a lesson, add it to TOPICS. To add a topic, add an entry with its reference sheet. `lessons/index.html` is the revision hub listing every topic. The learner wants lessons in a topic to link to each other so they can revise a topic.

## Components (assets/)

- `style.css`: shared styles; colour tokens with a dark mode; print styles.
- `quiz.js`: `.quiz` multiple choice (data-answer, 0-based), `.drill` fill-ins (data-expect) with "Show answer", `.score`, `button.copy`.
- `stepper.js`: step-through for recursive code. `step.tape = {text, pos, from}` handles string+cursor (parsers). `Stepper.recorder()` generates steps.
- `grid.js` (2026-10-21): `Grid.mount(root, {rows, markToggle, maxSteps, algorithm})`. Editable land/water grid, scan+fill stepper (default `Grid.floodDFS`), and a "mark on arrival" toggle that shows the infinite loop. Steps are `{seen, cur, scan, stack, count, note}`.
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
