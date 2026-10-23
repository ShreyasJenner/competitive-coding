# Recursive descent: the cursor contract, and who owns the separator

The learner solved LC 1106 with a shared `int&` cursor and one helper that branches on the first character. It passes 14/14, including 6666-deep nesting and 3000 random cases, and is clean under ASan/UBSan. They did not short-circuit early, so the cursor always gets past every child.

**Misconceptions corrected on the way.** Their first draft had all of these:
- It mixed up `cursor += 2` (moving the pointer) with moving the position (`int*`).
- Leaves consumed the trailing `,`, so the leaf did the parent's job of handling separators.
- It counted a `depth` variable by hand, although the recursion already matches brackets.
- The `!` branch returned before stepping past `)`.

All four were pointed out by line, with no code given, and the learner rewrote the helper unaided. Before that, they couldn't answer "first index after the expr at s[k]". After bracket matching was explained with an index ruler, they answered the transfer questions (s[4]→5, s[0]→14) correctly.

**Evidence**: `usr/src/leetcode/1106.cpp` (2026-10-20), Lesson 4.

**Implications**:
- When teaching a new recursive shape, ask "which call owns this character?" explicitly. Ownership of the separator, not the recursion itself, was where they slipped.
- Small leftovers: `!` still uses a loop, `== true ? false : true` stands in for `!`, and the `|`/`&` branches are duplicated. These are cleanups, not misunderstandings.
- Next options: the explicit-stack rewrite (bridge to 301's BFS), or LC 394 solved cold.

**Update 2026-10-22 (spaced check, 3 days later)**: traced `&(t,f)` cold with no notes. Got t→3, f→5, &→6. The leaf stops right after itself, and the parent steps over `,`/`)`. Their ambiguous 2026-10-21 wording was a phrasing slip, not the old misconception. Ownership is settled, so no re-drill is needed.
