# The Problem-Solving Framework (UPSCR)

Most people who freeze on an interview problem do not freeze because they lack knowledge. They freeze because they have no procedure. They stare at the prompt, hope a clever idea arrives, and when it doesn't, they panic and start typing something. The typing makes it worse.

The fix is a method you run on every problem, the same way every time, until it is automatic. This course uses one. We call it **UPSCR**: Understand, Pattern, Strategy, Code, Review. Five steps, always in that order. You will see it applied on camera to every problem across all 16 weeks, so by the end you run it without thinking about it.

The point of a fixed procedure is that it moves the hard work to the front, where it is cheap. Thinking before you type costs you a few minutes. Typing before you think costs you the whole problem.

## The five steps

### 1. Understand

Restate the problem in your own words. Out loud if you can. If you cannot restate it cleanly, you do not understand it yet, and any code you write is a guess.

Pin down four things:

- **Inputs.** Types, ranges, can they be empty, can they be negative, are there duplicates, is the input sorted.
- **Outputs.** Exact format. Return a value or modify in place? Return an index or the element? One answer or all of them?
- **Constraints.** Read the size of `n`. This single number usually tells you the target complexity before you have any idea of the algorithm. More on that below.
- **Edge cases.** Empty input, one element, all elements equal, already sorted, reverse sorted, the maximum allowed size, values that overflow `int`.

Then work one small example by hand, on paper, before writing anything. Most wrong solutions come from confidently solving a slightly different problem than the one that was asked.

**Reading the constraints to guess the target complexity.** The maximum value of `n` is a strong hint. Rough guide, assuming a one-second time budget:

| Max `n` | Target complexity | What it usually means |
|---|---|---|
| n ≤ 20 | O(2ⁿ), O(n!) | Backtracking, brute-force subsets/permutations is fine |
| n ≤ 5,000 | O(n²) | A nested loop is acceptable |
| n ≤ 10⁶ | O(n) or O(n log n) | One pass, sorting, or a hash map |
| n ≤ 10⁹ | O(log n) or O(√n) | Binary search on the answer, or math, no array scan |

If `n` can be a billion, you are not allowed to even look at every element. That tells you the shape of the answer before you know the answer.

### 2. Pattern

Ask which of the core interview patterns this problem resembles. This course teaches roughly 20 of them, and almost every medium-difficulty problem is one pattern lightly disguised. A few triggers:

- Sorted array and a target value → two pointers or modified binary search.
- A contiguous subarray or substring with some property → sliding window.
- A linked list and you suspect a cycle, or you need the middle → fast and slow pointers.
- Many range-sum queries over a fixed array → prefix sums.
- "Find all combinations / subsets / permutations" with small `n` → backtracking.
- "Next greater element" or a span/histogram problem → monotonic stack.
- Top-K or a running median → a heap, or two heaps.

Pattern recognition is the skill that separates people who start from people who stall. It is also learnable. You learn it by solving many problems and consciously naming the pattern each time, which is exactly what the problem bank in this repo is built to drill. The [pattern reference](patterns.md) lists the trigger for each one.

### 3. Strategy

Pick the data structure and the algorithm before you type a single line. Write the approach in plain words or short pseudocode, then state the expected time and space complexity.

This is the checkpoint. If your planned complexity is already too slow for the constraint you read in step 1, you fix it here, in your head or in two lines of pseudocode, not after you have written 40 lines of C++ and gotten attached to them. A brute force is a perfectly good first strategy as long as you say so out loud and know its cost. Get a correct idea first, then improve it. Never optimize a solution you do not yet have.

### 4. Code

Translate the strategy into clean C++. Small, named steps. Good variable names. Handle the edge cases you already listed in step 1.

If the first three steps were done well, this step is almost mechanical, and that is the entire point of doing them first. When coding feels hard, it is usually a sign that the strategy was vague. Stop and go back to step 3 rather than fighting the keyboard.

Watch the usual C++ traps while you type:

- `int` overflows around 2.1 billion. If a sum or product can exceed that, use `long long`. This is the single most common avoidable bug.
- `vector::size()` is unsigned. `size() - 1` on an empty vector wraps to a huge number.
- Pass large containers by `const&`, not by value, or you pay a silent O(n) copy.

### 5. Review

Do not assume it works because it compiled.

Trace your finished code on the example you built in step 1, by hand, line by line. Then run it against the edge cases you listed: empty input, one element, duplicates, the largest case, anything that could overflow. Finally, confirm that the actual time and space complexity matches what you claimed in step 3, and state it out loud the way you would to an interviewer. If the real complexity is worse than your claim, you either miscounted or there is a hidden cost (a `substr` in a loop, a copy you forgot), and you want to find that now, not in the interview.

## Why the order is the lesson

Beginners jump straight to step 4. They read the prompt, get an idea, and start coding. Sometimes it works. Often they are 30 lines deep before they realize the approach is wrong or too slow, and now they are debugging a bad plan instead of fixing a good one.

The framework forces the thinking up front, where mistakes cost seconds instead of minutes. Understand so you solve the right problem. Find the pattern so you do not reinvent it. Settle the strategy and its complexity so the code is just transcription. By the time you are typing, the hard part is already done.

## A worked example, end to end

Let's run all five steps on one problem.

> **Two Sum.** Given an array of integers `nums` and an integer `target`, return the indices of the two numbers that add up to `target`. Exactly one valid pair exists. You may not use the same element twice.

### Step 1 — Understand

Restated: find two different positions `i` and `j` such that `nums[i] + nums[j] == target`, and return `{i, j}`.

- **Input:** a `vector<int>` and an `int` target. Values can be negative. Duplicates are allowed (two equal values at different indices is a valid pair).
- **Output:** the two indices, not the values themselves.
- **Constraints:** assume `n` can be up to about 10⁵. From the table above, 10⁵ means I want O(n) or O(n log n). An O(n²) double loop would be borderline and is the thing to beat.
- **Edge cases:** the pair could be the first and last elements; the array could contain negatives; two equal values could form the pair (for example `target = 6` with `nums = [3, 3]`).

Quick example by hand: `nums = [2, 7, 11, 15]`, `target = 9`. The answer is indices `0` and `1`, because `2 + 7 == 9`.

### Step 2 — Pattern

I need to find, for each element `x`, whether its complement `target - x` exists somewhere else in the array. "Does this value exist, in O(1)?" is the signal for a hash map. So this is the **hashing for lookup** pattern: trade space for time by remembering what I have seen.

### Step 3 — Strategy

The brute force is two nested loops over all pairs: O(n²) time, O(1) space. Correct, but I already said I want better.

Better strategy: one pass. Keep a hash map from value to the index where I saw it. For each element `nums[i]`, compute `need = target - nums[i]`. If `need` is already in the map, I have found the pair and return the stored index together with `i`. Otherwise record `nums[i] -> i` and move on.

Checking the map before inserting the current element guarantees the two indices are different, which handles the duplicate case cleanly.

Expected cost: **O(n) time** (each element handled once, hash operations O(1) average) and **O(n) space** for the map. That fits the constraint, so I am done planning and can code.

### Step 4 — Code

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> seen;          // value -> index
    for (int i = 0; i < (int)nums.size(); ++i) {
        int need = target - nums[i];
        auto it = seen.find(need);
        if (it != seen.end()) {
            return {it->second, i};        // found the earlier index, plus i
        }
        seen[nums[i]] = i;                 // record only after the check
    }
    return {};                             // no pair (problem guarantees one exists)
}
```

Notes on the choices:

- `nums` is passed by `const&`, so there is no O(n) copy of the input.
- I cast `nums.size()` to `int` for the loop because `size()` is unsigned and mixing it with a signed `int i` produces compiler warnings and, in subtraction, wraparound bugs.
- The map lookup happens before the insert, so element `i` can never pair with itself.

### Step 5 — Review

Trace the example `nums = [2, 7, 11, 15]`, `target = 9`:

- `i = 0`: `need = 9 - 2 = 7`. `7` is not in the map. Insert `2 -> 0`.
- `i = 1`: `need = 9 - 7 = 2`. `2` *is* in the map at index `0`. Return `{0, 1}`. Correct.

Edge cases:

- Duplicate pair, `nums = [3, 3]`, `target = 6`. At `i = 0`, `need = 3` is not yet in the map; insert `3 -> 0`. At `i = 1`, `need = 3` is in the map at index `0`; return `{0, 1}`. Correct, and the two indices differ.
- Negatives, `nums = [-1, -2, -3, -4]`, `target = -6`. The pair is `-2` and `-4` at indices `1` and `3`. At `i = 3`, `need = -6 - (-4) = -2`, which was stored at index `1`; return `{1, 3}`. Correct.
- One element or empty input cannot contain a pair; the loop returns `{}` without ever indexing out of bounds.

Complexity check against the claim: one pass over `n` elements, each doing O(1) average-case hash work, so **O(n) time**. The map can hold up to `n` entries, so **O(n) space**. Matches what I said in step 3. Stated for an interviewer: "Linear time, linear space, one pass with a hash map; I check for the complement before inserting so I never reuse an index."

That is the whole loop. Understand, Pattern, Strategy, Code, Review. The brute force was O(n²); naming the pattern pointed straight at the hash map; the strategy fixed the complexity on paper before any code existed; the coding was a transcription of the plan; and the review proved it on the cases that break naive solutions.

The framework earns its keep on both ends of the difficulty range: on easy problems it catches the carelessness that costs points, and on hard ones the first two steps are usually where the foothold turns up. After a few hundred problems it stops being a checklist and becomes the way you think.

## Where to go next

- The pattern triggers referenced in step 2 live in the [`patterns.md`](patterns.md) reference.
- The graded problem bank to drill all of this is in [`problems/`](../problems/).
- The week-by-week schedule that introduces each pattern in order is in [`weeks/`](../weeks/).
