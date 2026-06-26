# Assessments & Grading

**Course:** *Data Structures & Algorithms in C++ — From Fundamentals to Interview-Ready*
**Format:** Live cohort · 4 lectures/week · 16 weeks · 64 lectures · ~30 students · $200 lifetime access

This page is the contract. It tells you exactly what you'll be graded on, how the bars are set, and what it takes to earn the certificate. Nothing here is a surprise on exam day. Read it once at the start of the cohort and again at week 8.

The grading philosophy is simple: we measure mastery, not attendance. You can show up to every lecture and still not pass if you don't solve problems. You can also miss a few quizzes and still finish strong, because almost every bar drops your worst scores. The point is to push you toward being interview-ready, not to play a points game.

---

## What gets assessed

There are five separate tracks. Each has its own bar. The certificate requires clearing all five.

| Track | What it is | How often | Counts toward certificate |
|-------|-----------|-----------|---------------------------|
| Weekly homework (Graded Sets) | 10-problem problem sets | 16 sets, one per week | Yes |
| Weekly quizzes | 10-question concept checks | 16 quizzes, one per week | Yes |
| Milestone checkpoints | 90-minute proctored mini-exams | 4, at weeks 4/8/12/16 | Yes |
| Mock interviews | Live 1:1 timed screens | 2, at weeks 10 and 16 | Yes (Mock 2) |
| Projects | Standalone C++17 builds | 6 offered, 2 required | Yes |

Quizzes and checkpoints test whether you *recognize* the right tool fast. Homework and projects test whether you can *build* the solution cleanly. Mock interviews test whether you can do both out loud, under time, with someone watching. Real interviews demand all three, so we grade all three.

---

## Weekly homework

Each week ships one **Graded Set (GS)** and one **Optional Stretch (OS)**.

The Graded Set is 10 problems, due before the first lecture of the following week. The Optional Stretch is 3 to 5 harder problems that never affect your grade but count toward finishing "with Distinction." Both come out of the [problem bank](../problems/README.md), tagged by week and pattern.

There's also in-lecture drilling (3 to 4 warmup problems we solve live), but that's participation only. It isn't graded.

### Per-week volume

| Component | Count/week | Difficulty mix | Graded? | Time budget |
|-----------|-----------|----------------|---------|-------------|
| Live drill | 3–4 | Warmup | No (participation) | during class |
| **Graded Set (GS)** | **10** | 3 Warmup · 5 Core · 2 Challenge | **Yes** | ~5–7 hrs |
| Optional Stretch (OS) | 3–5 | Challenge only | No (distinction credit) | open-ended |

Weeks 1 and 2 run lighter (an 8-problem GS) because they're conceptual: complexity analysis and recursion. Weeks 4, 8, 13, and 16 are the heavy ones, where the patterns stack up fastest.

### How a Graded Set is scored

Each problem is worth 10 points, broken down so that a correct answer isn't automatically a full answer. Getting the right output is most of the grade, but not all of it. Interviewers don't stop at "it works," and neither do we.

| Criterion | Points | What we're checking |
|-----------|:------:|---------------------|
| Correct, passes all tests | 6 | The solution actually solves the problem on every test case |
| Optimal complexity | 2 | You hit the best known time/space bound *and* state it with a one-line justification |
| Clean code + edge cases | 1 | Empty input, single element, overflow, and other boundaries are handled |
| Names the pattern | 1 | A 2–3 line note: which pattern this is and why it fits |

That last point matters more than its weight suggests. Being able to say "this is a sliding window because the constraint is a contiguous range with a monotonic cost" is the skill that transfers to problems you've never seen. We grade it on every set to force the habit.

### Passing a Graded Set

A set **passes at 70%**. The seven graded-quality problems (3 Warmup + 4 of the Core/Challenge) carry the bar at 49 of 70 points. The two Challenge problems are graded for effort and partial credit, so an honest attempt on a hard problem never sinks an otherwise solid week, and a student who's wrestling with the stretch material doesn't get capped out for it.

If you miss the bar, you get one resubmission per week, due within 7 days, worth up to 90% credit. Use it. The resubmission window is deliberate: it's how the schedule absorbs a bad week without anyone falling permanently behind. There are no separate "catch-up weeks" because this is the catch-up mechanism, available every week.

---

## Weekly quizzes

One quiz per week, 16 total. Ten questions, about 20 minutes, auto-graded so you get your score immediately.

The questions are short by design:

- **Big-O identification** — read a code snippet, choose the tight bound.
- **Pattern recognition** — read a problem statement, name the pattern that applies.
- **Trace the algorithm** — walk a few steps of heapify, a DSU after a sequence of unions, or a Dijkstra relaxation, and report the state.
- **Spot the bug** — one short snippet with a single defect; find it.

Quizzes exist to drill vocabulary and reflexes. In an interview you don't have time to rediscover that a problem is two-heaps; you need to feel it in the first thirty seconds. The quiz is how you build that reflex cheaply, week over week.

**Bar:** 70% average. Your lowest quiz is dropped, so the bar is computed over your best 15 of 16.

---

## Milestone checkpoints

Four checkpoints, at the end of weeks 4, 8, 12, and 16. Each is a 90-minute proctored mini-exam over the block that preceded it. This is the first place you solve problems under real time pressure with no resubmission, which is exactly the gap most self-taught candidates have.

| Checkpoint | Week | Covers | Problems |
|:----------:|:----:|--------|:--------:|
| 1 | 4 | Complexity, recursion, arrays/prefix sums, two pointers, sliding window | 4 (1 Warmup · 2 Core · 1 Challenge) |
| 2 | 8 | Hashing, linked lists, stacks/queues/monotonic stack, trees/BST | 4 |
| 3 | 12 | Heaps/top-K, tries, union-find, sorting, binary search (incl. on the answer), divide & conquer | 4 |
| 4 | 16 | Graphs (both weeks), backtracking, greedy, bit manipulation, dynamic programming | 5 |

**Bar:** 60% on each checkpoint. The threshold is lower than the homework bar on purpose, because these are timed and unaided. One checkpoint may be retaken once if you miss it.

---

## Mock interviews

Two rounds, live and 1:1, run to look and feel like a real technical screen at a strong company. Forty-five minutes, shared editor, think out loud the whole way. You're scored on a five-dimension rubric, each rated 1 to 5:

| Dimension | What a 5 looks like |
|-----------|---------------------|
| Communication | States assumptions, narrates the plan before coding, asks clarifying questions |
| Problem-solving approach | Reaches a working idea methodically; recognizes the pattern; doesn't flail |
| Correctness | Code runs on the examples and the edge cases, not just the happy path |
| Complexity analysis | States time and space, justifies them, knows where the cost lives |
| Code quality | Readable, well-named, no dead branches, sane structure |

### Mock 1 — end of Week 10

One medium problem drawn from the weeks 1–10 patterns (think sliding window, tree BFS, or a linked-list reversal), plus a complexity discussion. This round is **formative**: you get a full rubric breakdown and written feedback, but it does not count toward the certificate. The goal is to find your weak dimension while there's still six weeks to fix it. Most people discover it's communication, not algorithms.

### Mock 2 — Week 16

One medium and one hard problem in 45 minutes (typically a graph or a DP problem for the hard slot). This round is **graded** and required for the certificate. You get a written feedback report with concrete next steps regardless of outcome.

**Bar (Mock 2):** rubric average ≥ 3.0 out of 5, with **no single dimension below 2**. A 4 in correctness can't paper over a 1 in communication, because in a real loop it wouldn't either.

---

## Projects

Six projects are offered across the course. Each is standalone-compilable C++17, validated with a `<cassert>` test harness in the repo's house style. They're spaced so each one lands right after the topics it exercises have been taught. Full specs, milestones, and stretch goals live in [the projects page](../projects/README.md); here's what counts toward the certificate.

| # | Project | Lands after | Required? |
|:-:|---------|:-----------:|-----------|
| 1 | LRU + LFU Cache Library | Week 6 | One of {1, 2} required |
| 2 | Expression Evaluator & Mini Calculator | Week 7 | One of {1, 2} required |
| 3 | Maze / Path-Finder Visualizer | Week 14 | Recommended |
| 4 | In-Memory KV Store with Trie Autocomplete | Week 10 | Recommended |
| 5 | Sparse Matrix Engine | Week 11 | Recommended |
| 6 | **Capstone:** Mini Search & Recommendation Engine | Week 16 | **Required** |

The certificate requires **Project 1 or Project 2** (an early integration project, so you've shipped something real before the midpoint) **and the Capstone**. The Capstone is non-negotiable because it's the one project that pulls in everything: hashing for the inverted index, tries for autocomplete, heaps for top-K ranking, sorting for results, a similarity graph with connected components, edit distance for typo tolerance, and binary search for posting-list intersection. If you can build it, you've used the whole course.

A project counts as complete when its `<cassert>` test harness passes and it ships with a short README explaining how to build and what it does.

Projects 3, 4, and 5 are strongly recommended and feed the Distinction track below.

---

## Certificate of Completion

All five criteria are required. No single track can be skipped or bought back with strength in another.

1. **Homework** — passed at least **13 of 16** Graded Sets (each at ≥70%).
2. **Quizzes** — **≥70% average** across your best 15 weekly quizzes.
3. **Checkpoints** — passed **all 4** milestone checkpoints (≥60% each; one retake allowed).
4. **Projects** — completed **Project 1 or 2** *and* the **Capstone (Project 6)**, each with a passing `<cassert>` harness and a short README.
5. **Mock interview** — **Mock 2** rubric average **≥ 3.0/5**, with no dimension below 2.

### Completion with Distinction

Earned on top of every standard requirement above, plus:

- Graded-Set average **≥ 90%** across the course.
- Completed **any two of Projects 3, 4, and 5**.
- Solved **at least 25 Optional-Stretch problems**.
- **Mock 2** rubric average **≥ 4.0/5**.

Distinction is meant to be hard. In a typical cohort of thirty, a handful earn it. It signals that you didn't just clear the bars, you went after the stretch material and held up under interview conditions.

---

## Quick reference

| Requirement | Standard bar | Distinction bar |
|-------------|--------------|-----------------|
| Graded Sets passed | ≥ 13 of 16 (≥70% each) | ≥ 90% average |
| Weekly quizzes | ≥ 70% avg (best 15) | same |
| Checkpoints | All 4 passed (≥60%) | same |
| Required projects | Project 1-or-2 + Capstone | + any two of Projects 3–5 |
| Optional Stretch problems | — | ≥ 25 solved |
| Mock 2 | ≥ 3.0/5 (none < 2) | ≥ 4.0/5 |

If you're tracking yourself mid-cohort and any one of these is slipping, raise it in office hours early. Every bar here is reachable on the normal schedule; the gaps that become unrecoverable are the ones left unaddressed for weeks.
