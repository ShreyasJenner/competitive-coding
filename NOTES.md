# Teaching notes

- Language: C++ for all lesson code. Repo style is `class Solution` plus a `main` that prints results.
- Workflow (since 2026-10-14): the learner's code lives in `usr/src/<platform>/N.cpp`, with `main` wrapped in `#ifndef TEST`. Tests go in `usr/test/<platform>/N.cpp`, which `#include "../../src/<platform>/N.cpp"` and has `main` return non-zero on failure. Run with `./test.sh N`, `./build.sh N` and `./clean.sh`; binaries land in `usr/bin`. For each lesson problem, ship the test file and a starter (not the solution).
- Learner likes to drive by naming a specific problem to crack ("teach me via LC 301"). Build lessons around the problem, and don't hand over full solutions: use progressive hints plus a local PASS/FAIL harness.
- Weak areas self-reported: DP, graphs, trees/recursion, and optimising from brute force.
- Natural next steps after 301: the BFS formulation of 301 (bridge to graphs), then tree recursion.
