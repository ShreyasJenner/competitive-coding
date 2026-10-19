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

- [_Crafting Interpreters_ by Robert Nystrom, ch. 6 "Parsing Expressions" (free online)](https://craftinginterpreters.com/parsing-expressions.html)
  The clearest free explanation of recursive descent: each grammar rule becomes a function, and a `current` cursor marks the next token. Use for: parsing/expression problems (1106, 394, 224, 726). §6.2 is the core; §6.3 covers error handling, which LeetCode rarely needs.

## Wisdom (Communities)

- [Codeforces blogs](https://codeforces.com/blog/)
  The most active CP community. Use for: "how do I think about X" questions and editorials.
- [LeetCode Discuss](https://leetcode.com/discuss/)
  Per-problem discussion threads. Use for: comparing your approach with others' after an AC.

## Gaps
- No trusted, structured source picked yet for DP intuition (candidates to evaluate: CPH ch. 7, USACO Guide Gold DP, Errichto's DP lectures).
- No graph resource beyond CPH yet.
