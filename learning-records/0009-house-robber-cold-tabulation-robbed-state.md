# LC 198: cold tabulation with a "house i is robbed" state; the exchange argument was missed

On 2026-10-26 the learner solved LC 198 House Robber, their first DP (20/20 under ASan/UBSan, plus a scratchpad stress test of 200,000 random streets of up to 100 houses against the skip/rob DP). They read only §1 of Lesson 7 (the contract `best(i)` = most money from houses i..n−1) and then wrote their own logic, **going straight to a right-to-left loop**. They skipped the plain recursion, the timeout and the memo.

**Their state:** `best[i]` = most money from houses i onward, **given that house i is robbed**. The recurrence is `nums[i] + max(best[i+2], best[i+3])`, the answer is `max(best[0], best[1])`, and n = 1, 2 and the first entries are special-cased. Their contract, in their own words: "the max possible value that can be robbed if one starts robbing from that house and moves only forward". That is correct, and I sharpened it to "house i is robbed".

**Misconception:** asked why `best[i+4]` is never needed, they said "best[i+2] connects to best[i+4] … so best[i+2] would have already considered it". That ignores their own contract, since `best[i+2]` forces robbing i+2. The real reason is an exchange argument: adding house i+2 to a plan that skips 3 houses stays legal and costs nothing, because `nums ≥ 0`. Their code returns 9 instead of 10 on `[5,-1,-1,-1,5]`. I explained this; it hasn't been re-tested.

**Follow-up the same day: top-down memo.** They chose to rewrite it with the lesson's skip/rob state and a memo. Their first version had two bugs: (1) the memo lookup came *before* the `i >= n` base case, so `memo[n]` and `memo[n+1]` were read out of bounds and the vector assertion crashed before case 1; (2) it never stored into the memo, so the lookup could never hit. I pointed at bug 1 by line. For bug 2, I asked them to predict the output and count §4's three changes (array, lookup before, store after). Between the two fixes they ran the tests and saw "still running after 2 s" on the 100-house case, so they have now felt the exponential blow-up directly. They fixed both: base case first, `memo[i] = max(...)`, a `-1` sentinel, and both vectors by reference. 20/20.

**Evidence**: `usr/src/leetcode/198.cpp` (2026-10-26) and their written answers.

**Implications**:
- Record 0007/0008's question ("return your own answer, unprompted?") is a **yes** here, once §1 had stated the contract. They built the table from smaller states without any accumulator. Untested: a cold problem where they must *choose* the state.
- They think bottom-up naturally, filling from the end. The memo was then written top-down after two pointers. **Its two weak points were ordering (base case before lookup) and the forgotten store.** Check both unprompted in the next top-down DP (337).
- Watch for **arguments that silently depend on constraints**: they write a correct but narrower recurrence without seeing what it relies on. Prompt with "what does this rely on?" and an out-of-constraints counterexample.
- Their "robbed / not robbed" state is exactly the per-node pair that LC 337 needs. That makes it a strong bridge.
