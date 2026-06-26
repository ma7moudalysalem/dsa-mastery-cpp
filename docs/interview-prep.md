# Interview Prep Track

The course teaches the material. This track teaches you to perform under interview conditions, which is a separate skill. You can know every pattern cold and still freeze when a stranger is watching you type. The fix is reps in the exact format you will face, with feedback, before it counts. That is what the two mock rounds and the final-weeks plan below are for.

This page covers how the timed mocks work, a repeatable way to talk through a problem, how to manage 45 minutes, how to communicate complexity without bluffing, the follow-ups interviewers reach for, a short note on behavioral prep, and a study plan for the last few weeks.

---

## The two mock rounds

Both mocks are live, 1:1, 45 minutes, on a shared editor, think-aloud. They mirror a real technical screen at a strong company: you read the problem, ask questions, talk through an approach, write C++ that compiles, test it by hand, and state its complexity. The interviewer is graded on a rubric, not on whether you got a clean accept.

The rubric has five dimensions, each scored 1 to 5:

| Dimension | What a 5 looks like |
|-----------|--------------------|
| Communication | Thinks out loud, narrates the plan before coding, takes hints gracefully |
| Problem-solving approach | Finds the pattern, considers brute force then improves, justifies the choice |
| Correctness | Code runs on the examples and the edge cases, bugs are caught by self-review |
| Complexity analysis | States tight time and space bounds and can defend them |
| Code quality | Readable, named steps, handles empty/single/overflow without being told |

### Mock 1 — end of Week 10 (formative, ungraded)

One medium problem drawn from the patterns in weeks 1 through 10: typically a sliding-window, two-pointer, hashing, linked-list, or tree-BFS problem, plus a complexity discussion at the end. Nothing here counts toward anything. The point is to feel the format while the stakes are zero, find out where you stall, and get a written note on what to drill in the back half of the course.

Most people discover the same thing in Mock 1: the gap is not the algorithm, it is the silence. They go quiet for four minutes, solve it in their head, then start typing with no narration. That reads as a low Communication score even when the code is correct. Mock 1 exists so you learn that before it matters.

### Mock 2 — Week 16 (graded)

One medium and one hard in 45 minutes. The hard problem is usually a graph or DP question, the kind that separates "studied" from "ready." You get a written feedback report with concrete next steps.

Pass bar: average rubric score at least 3.0 out of 5, with no single dimension below 2. Distinction-level is a 4.0 average. The two-problem format is deliberate. It forces time management, which is the thing a single-problem mock never tests. If you spend 35 minutes perfecting the medium, you fail the round even with two correct answers, because you never showed you could move.

---

## How to talk through a problem

Use the same method the course drills all 16 weeks: **UPSCR** (Understand, Pattern, Strategy, Code, Review). The order is the whole point. Beginners jump to Code and get stuck. Strong candidates spend the first third of the interview not typing.

**1. Understand.** Restate the problem in your own words and confirm it back. Pin down input types, output, constraints, and what happens on the empty or degenerate case. Ask about ranges, because `n <= 10^5` and `n <= 10^9` are different problems. Work one small example by hand, out loud, before you touch the keyboard. A surprising fraction of failed interviews are correct solutions to the wrong problem.

Good questions to ask here:
- Can the input be empty? Can it have duplicates? Can values be negative?
- Are we optimizing for time, space, or is one already constrained?
- Is the array sorted? Can I sort it, or does that break a requirement?
- Should I return the value, the index, or all of them?

**2. Pattern.** Say out loud what the problem reminds you of. "Sorted array and a target, so I'm thinking two pointers or binary search." "We want a window of consecutive elements, that's sliding window." "All combinations, so backtracking." Naming the pattern is half the interview. It signals you have seen the shape before, and it gives you a starting structure instead of a blank page.

**3. Strategy.** State the brute force first, even if it is obviously too slow. It shows you can always produce something, and it gives you a baseline to improve. Then describe the better approach in plain words, name the data structure, and state the target complexity before you write a line. If your planned complexity is already too slow for the constraints, you fix it here, where it costs nothing, not after 40 lines of code. Get the interviewer to nod at the plan before you start typing. "Does that approach sound reasonable to you?" is a fine thing to say.

**4. Code.** Translate the plan into clean C++ in small, named steps. Narrate as you go, but lightly. You do not need to read every semicolon aloud. Say what each block does: "Now I'm building the frequency map," "this loop shrinks the window from the left." Use real variable names. If you blank on STL syntax, say so and write pseudocode for that line rather than going silent.

**5. Review.** Do not announce you are done and lean back. Trace your code on the original example by hand, out loud. Then hit the edge cases you found in step 1: empty input, single element, all duplicates, integer overflow, the largest allowed `n`. Fix what you find before the interviewer does. Catching your own bug scores higher than writing bug-free code, because real engineering is mostly catching your own bugs.

The thing that ties this together: keep talking. A wrong idea spoken aloud gives the interviewer a place to drop a hint. A correct idea kept silent gives them nothing to grade.

---

## Time management in 45 minutes

A rough budget for a single-problem round:

| Phase | Time | What you're doing |
|-------|------|-------------------|
| Understand + clarify | 3–5 min | Restate, ask questions, one hand example |
| Pattern + strategy | 5–8 min | Brute force, better approach, state complexity, get a nod |
| Code | 15–20 min | Write it, narrate lightly |
| Review + test | 5–8 min | Trace by hand, hit edge cases, fix bugs |
| Follow-up / buffer | remainder | Optimization, follow-up question, "what if the input were huge" |

For Mock 2's two-problem round, treat the medium as a ~18 minute problem and protect time for the hard one. If you are 20 minutes in and still debugging the medium, say "let me get this to a working state and move on," then move on. An interviewer would far rather see two reasonable attempts than one polished answer and one blank screen.

Watch for the two classic time sinks. The first is over-clarifying: asking five questions when one would do, to delay the moment you have to commit. The second is silent debugging: staring at a bug for three minutes without saying anything. If you are stuck, say what you expected, what you got, and where you think the gap is. That is both how you actually find the bug and how you keep scoring Communication points while you do.

If you genuinely stall, ask for a hint. It costs less than you think. "I'm considering a hashmap here but I'm worried about the space, am I overcomplicating it?" is a strong sentence. It shows your reasoning and invites a nudge without giving up.

---

## Communicating complexity

State complexity at two moments: when you propose the approach (the target you are aiming for) and when you finish (the bound you actually hit). Confirm they match. Drift between the two is a common, avoidable miss.

Be precise about a few things interviewers listen for:

- **Time and space, both, every time.** People remember time and forget space. Recursion has a space cost from the call stack; a recursive tree traversal is O(h) space for the stack, O(n) in the worst case of a skewed tree. Say it.
- **In terms of what.** "O(n)" is meaningless until you say what `n` is. For a string problem it might be the length; for a graph it is usually O(V + E). For two arrays say O(n + m), not a vague O(n).
- **Tight bounds.** If the answer is Θ(n), do not hedge with "it's at most O(n²)." A loose-but-true bound reads as not knowing the real cost. State the tight one and be ready to defend it.
- **Amortized when it applies.** `push_back` on a vector is O(1) amortized because of doubling, not O(1) worst case. If you build a result by appending, the right phrase is "O(1) amortized per push, O(n) total." Saying "amortized" correctly is a strong signal.
- **Average vs worst case.** Hash map lookup is O(1) average, O(n) worst case under adversarial collisions. Quicksort is O(n log n) average, O(n²) worst case with a bad pivot. Name which you mean.

Do not bluff a complexity you cannot justify. If asked "why is that O(n log n)," you should be able to point at the sort, or the n iterations each doing a log-n binary search or heap operation. If you cannot trace the cost, you do not know it yet, and a follow-up will expose that fast. It is better to say "let me count this carefully" and actually count.

A clean closing line sounds like: "This is O(n) time, since we make one pass and each element is pushed and popped from the stack at most once, and O(n) space for the stack in the worst case." Specific, defensible, done.

---

## Common follow-ups

Interviewers rarely stop at the first correct answer. They probe to see how deep the understanding goes. Expect some version of these, and have an answer ready before they ask.

- **"Can you do better on time?"** Usually there is a way: a hashmap to drop an O(n²) to O(n), sorting to enable two pointers, a heap for top-K, binary search on a sorted structure. Know the standard upgrade for each brute force.
- **"Can you do it in less space?"** Convert recursion to iteration to drop stack space. Reuse the input array in place. Use two variables instead of a full DP table for a 1D recurrence (Fibonacci-style problems go from O(n) to O(1) space this way).
- **"What if the input doesn't fit in memory?"** Now they want streaming, external sort, or a fixed-size structure like a heap of size K for top-K over a stream. Reservoir sampling and the two-heaps median pattern live here.
- **"What if it's sorted / nearly sorted / has a bounded range?"** Sorted unlocks binary search and two pointers. A bounded value range unlocks counting sort or a fixed-size frequency array, turning O(n log n) into O(n).
- **"What if there are duplicates?"** Half of two-pointer and backtracking problems get a twist version where you must skip duplicates to avoid repeated results. Know how (sort, then skip equal neighbors in the loop).
- **"What if it's a stream and you can't see the whole input?"** Maintain running state: a running heap, a sliding window, a monotonic deque, a running prefix sum.
- **"How would you test this?"** Name the categories, not random examples: empty, single element, all same, already sorted, reverse sorted, max size, overflow boundary. This is the same edge-case list from UPSCR's Review step.
- **"Walk me through it on this new input."** They hand you a fresh example to check you actually understand your own code rather than having pattern-matched a memorized solution. Trace it honestly; if you find a bug, fix it, that is a point in your favor.

The meta-skill: when you finish, you can often preempt the first follow-up yourself. "This is O(n²); if the array were sorted I could do this in O(n) with two pointers, want me to assume that?" That moves you from answering questions to driving the interview.

---

## Behavioral prep (short note)

Technical rounds are not the only rounds. Most loops include a behavioral conversation, and strong technical candidates lose offers by treating it as a formality. Prepare for it like any other problem.

Keep five or six stories ready, each from real experience: a hard bug you tracked down, a disagreement you resolved, a project you owned end to end, a time you were wrong and corrected course, a time you helped a teammate, a deadline you had to make a tradeoff for. Structure each one with STAR: Situation, Task, Action, Result. Lead with the result so the listener knows where the story is going, then fill in how you got there. Keep each story to about two minutes spoken. Be specific about what *you* did, not what the team did.

Have honest answers for "why this company" and "why are you looking." Have a real question or two for them, because "do you have questions for me" is part of the evaluation. The bar here is sincerity and specificity, not polish. One concrete story beats three vague ones.

This course does not run mock behavioral interviews; that is outside its scope. But the cohort channel is a fine place to swap stories and practice, and your two mock partners can give you five minutes of behavioral practice at the end of a technical mock if you ask.

---

## Final-weeks study plan

The last three to four weeks are about retention and recognition speed, not learning new topics. By now you have seen everything. The job is to make recall automatic and to close the gaps the checkpoints exposed. Do not try to grind 50 new problems in the last week. Review what you have already solved, on a schedule that fights forgetting.

### Spaced review of the pattern bank

Work the 28 core patterns on a spaced schedule so each one resurfaces just as it starts to fade. A simple rotation:

- **Day 1:** review the pattern, re-solve two problems you have already done from it, from a blank file, no notes.
- **Day 3:** re-solve one of them again, plus one new problem in the same pattern.
- **Day 7:** one cold problem in the pattern, timed, talking out loud as if in an interview.

Cycle the patterns so that across a week you touch every one at least once, and the weaker ones twice. "Re-solve from blank" matters. Reading your old solution feels productive and teaches almost nothing. Reproducing it cold is the only thing that proves you own it.

Track each pattern with a simple status: green (solve it cold without thinking), yellow (get there but slowly), red (still have to look it up). Spend your time on yellow and red. Do not keep re-solving the greens because they feel good.

### A curated top list

In the final two weeks, do a focused pass over a tight list of high-yield problems, one per major pattern, timed and out loud. This is the "if I only had time for one problem per pattern" set. Suggested anchors, all in the problem bank:

| Pattern | Anchor problem |
|---------|----------------|
| Two pointers | 3Sum (15) |
| Sliding window | Longest Substring Without Repeating Characters (3) |
| Fast & slow pointers | Linked List Cycle II (142) |
| Prefix sums + hashing | Subarray Sum Equals K (560) |
| In-place reversal | Reverse Nodes in k-Group (25) |
| Monotonic stack | Daily Temperatures (739) |
| Tree BFS | Binary Tree Level Order Traversal (102) |
| Tree DFS | Lowest Common Ancestor of a Binary Tree (236) |
| Top-K / heaps | Kth Largest Element in an Array (215) |
| Two heaps | Find Median from Data Stream (295) |
| K-way merge | Merge k Sorted Lists (23) |
| Modified binary search | Search in Rotated Sorted Array (33) |
| Binary search on the answer | Koko Eating Bananas (875) |
| Backtracking | Combination Sum (39) |
| Subsets | Subsets (78) |
| Topological sort | Course Schedule II (210) |
| Graph BFS/DFS | Number of Islands (200) |
| Dijkstra | Network Delay Time (743) |
| Union-find | Number of Provinces (547) |
| Tries | Implement Trie (208) |
| 1D DP | House Robber (198) |
| 0/1 knapsack | Partition Equal Subset Sum (416) |
| Unbounded knapsack | Coin Change (322) |
| LCS / string DP | Longest Common Subsequence (1143) |
| Edit distance | Edit Distance (72) |
| Bitwise XOR | Single Number (136) |

If you can solve every row on that list cold, under time, narrating as you go, you are ready for Mock 2 and for the real thing it imitates.

### A sample final-three-weeks schedule

- **Week 14 (before Mock content gets heavy):** finish the graph material, then start the spaced pattern rotation on the patterns from weeks 1 through 10. One full mock with a cohort partner.
- **Week 15:** rotate through the search, backtracking, greedy, and bit patterns; keep the older patterns alive with one cold problem each. Run the curated top list at half pace, two or three rows a day. Do one timed two-problem mock with a partner to rehearse the Mock 2 format.
- **Week 16:** the whole curated top list, timed and out loud, plus targeted re-solves of anything still yellow or red. Light volume the day before Mock 2. You are not cramming; you are arriving rested and sharp, which beats arriving exhausted and over-prepared.

The day of Mock 2, do one easy warmup problem you have solved before, to get your hands and your voice moving. The round itself is just UPSCR under a clock, which by then you will have run dozens of times.
