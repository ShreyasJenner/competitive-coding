# Dedup by building one canonical representative, not filtering

The learner replaced 301's `std::set` with a `std::vector` and a pruning rule, and passed all 13 cases, including 3000 random strings against a brute force. Instead of the taught rule ("no delete if `s[i]==s[i-1]` and `s[i-1]` was kept"), they found the other valid one: "no delete if the last *kept* character (`path.back()`) equals `s[i]`". That rule needs no extra parameter. Both are verified correct, so they understood the *idea* (one representative per equivalence class) and didn't just copy the condition.

**Slip:** they guarded `*path.rbegin()` with `i > 0`, a guard copied from the `s[i-1]` form. When every earlier character was deleted, `path` is empty at `i > 0` (e.g. `"))"`), so the read is UB. Tests, ASan and `_GLIBCXX_DEBUG` all missed it, because libstdc++'s SSO byte before the buffer reads as 0. It was pointed out without a fix, and the learner fixed it unaided by guarding on `path.size() > 0`. Verified.

**Evidence**: `usr/src/leetcode/301.cpp` (2026-10-19), Lesson 3.

**Implications**: When a learner adapts a pattern, check that each guard still protects the thing it now indexes. Prompt: "what exactly does this guard protect?" Edge cases like "everything before was deleted / empty path" deserve a mention when teaching state-based rules. Ready for step (2) of the 301 plan (cheaper state). LC 90 is pending as interleaved practice for the loop-form skip.
