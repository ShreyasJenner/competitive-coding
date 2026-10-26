# Algorithmic Problem Solving Resources

## Knowledge

- [Book: _Competitive Programmer's Handbook_ by Antti Laaksonen (free PDF, CSES)](https://cses.fi/book/book.pdf)
  Concise, rigorous, C++-based. Use for: the theory behind any core topic. Ch. 5 covers complete search/backtracking; later chapters cover graphs, trees and DP.
- [USACO Guide](https://usaco.guide/)
  Curated modules with graded practice problems. Use for: practice sets after a lesson. Bronze "Complete Search with Recursion" (https://usaco.guide/bronze/complete-rec) covers subsets, permutations and backtracking.
- [walkccc LeetCode solutions](https://walkccc.me/LeetCode/)
  Clean C++ reference solutions with complexity notes. Use for: checking a solution *after* solving, and links between related problems (e.g. 301 ↔ 921).
- [doocs LeetCode](https://leetcode.doocs.org/en/)
  Problem statements and constraints mirror, with multiple solutions. Use for: confirming constraints.

- [USACO Guide: Flood Fill](https://usaco.guide/silver/flood-fill)
  Short module with an example and a graded problem list. Defines flood fill as labelling "the connected component that a particular cell belongs to". Warns that the recursive version can overflow the stack. Use for: grid DFS/BFS (200, 695, 733, 130).
- CPH graph chapters (same PDF as above): ch. 11 Basics of graphs (printed p. 109, PDF p. 119); ch. 12 Graph traversal (printed p. 117, PDF p. 127), with DFS code on PDF p. 128 and "Connectivity check" on PDF p. 131. In-book links use `book.pdf#page=N` with the PDF page.

- CPH tree chapters (same PDF): ch. 14 Tree algorithms (printed p. 133, PDF p. 143). Subtree DP `count[s]` is on PDF p. 145, binary-tree pre/in/post-order on PDF p. 149, and ch. 18's LCA definition ("the lowest node whose subtree contains both the nodes") on PDF p. 177. Use for: tree recursion that returns values (236, 104, 543, 124). Ch. 18's binary-lifting/Euler-tour methods are for many queries, which LeetCode rarely needs.

- CPH DP chapter (same PDF): ch. 7 Dynamic programming (printed p. 65, PDF p. 75). The coin problem takes the full path: recursive formulation (PDF p. 76) → plain recursion is exponential, then memoization with `ready[]`/`value[]` (PDF p. 77) → iterative table, "most competitive programmers prefer this implementation" (PDF p. 78). Use for: the primary DP source (198, 322, 213).
- [USACO Guide: Intro to DP (Gold)](https://usaco.guide/gold/intro-dp)
  Links CPH ch. 7 and a graded problem list (CSES DP section, AtCoder DP Contest). Its worked example is Frog 1 (`dp[i]` = min cost to reach stone i), with push and pull versions. Use for: DP practice sets after a lesson.
- [Errichto, "Dynamic Programming lecture #1: Fibonacci, iteration vs recursion" (YouTube)](https://www.youtube.com/watch?v=YBSt1jYwVfU)
  USACO Guide calls it a "Great introduction video". #2 covers coin change. Use for: a video on the same recursion → memo → loop path.

- [_Crafting Interpreters_ by Robert Nystrom, ch. 6 "Parsing Expressions" (free online)](https://craftinginterpreters.com/parsing-expressions.html)
  The clearest free explanation of recursive descent: each grammar rule becomes a function, and a `current` cursor marks the next token. Use for: parsing/expression problems (1106, 394, 224, 726). §6.2 is the core; §6.3 covers error handling, which LeetCode rarely needs.

## Wisdom (Communities)

- [Codeforces blogs](https://codeforces.com/blog/)
  The most active CP community. Use for: "how do I think about X" questions and editorials.
- [LeetCode Discuss](https://leetcode.com/discuss/)
  Per-problem discussion threads. Use for: comparing your approach with others' after an AC.

## Gaps
- Graphs: CPH ch. 11–12 and USACO Flood Fill so far. Still need a source for BFS shortest paths and topological sort (USACO Silver/Gold modules are candidates).
