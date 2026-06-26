# Getting Started

This guide gets your machine ready, explains how the repo is laid out, and shows you how to actually use it during the 16 weeks of **DSA in C++**. Read it once, set things up, then keep it open as a reference for the first week.

If you only do one thing today: install a C++ compiler and compile a single file end to end. Everything else builds on that loop.

## What you need to know first

This is not a "learn to program" course. You should already be comfortable with the basics of C++ syntax:

- variables, types (`int`, `double`, `char`, `bool`), and arithmetic
- `if`/`else`, `for`, and `while`
- writing and calling functions, including passing arguments and returning values
- plain arrays and `std::vector` at a beginner level
- reading and printing with `std::cin` / `std::cout`

You do **not** need to know recursion, pointers, templates, or any of the STL containers beyond `vector`. We teach those. The first two weeks (complexity and recursion) deliberately come before any data structure, and they assume nothing more than the list above.

If a few of those bullets are shaky, that is fine. Brush up as you go. If most of them are new, spend a weekend on a C++ syntax primer first, then come back.

## Install a C++ toolchain

You need a C++ compiler that supports C++17. The two standard choices are **g++** (GCC) and **clang++** (LLVM). Either works for every file in this repo. Pick one.

### Windows

The cleanest option is **MSYS2**, which gives you a real GCC.

1. Install MSYS2 from [msys2.org](https://www.msys2.org/) and follow its setup steps.
2. Open the "MSYS2 UCRT64" terminal and install the toolchain:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
3. Add the compiler to your PATH. With a default install that is `C:\msys64\ucrt64\bin`. Add it through System Properties → Environment Variables, or your shell profile.
4. Open a fresh terminal and confirm it works:
   ```bash
   g++ --version
   ```

If you prefer Microsoft's compiler, the **Visual Studio Build Tools** (MSVC, `cl.exe`) also support C++17. The commands below use g++ syntax; if you go the MSVC route you will translate the flags yourself, so g++ via MSYS2 is the smoother path for following along.

### macOS

Install the Command Line Tools, which include `clang++`:

```bash
xcode-select --install
```

Then check it:

```bash
clang++ --version
```

On macOS, `g++` is usually an alias for `clang++`. That is fine. If you specifically want real GCC, install it with Homebrew (`brew install gcc`), which gives you a versioned binary like `g++-14`.

### Linux

Use your package manager. On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential
```

`build-essential` pulls in g++. On Fedora use `sudo dnf install gcc-c++`; on Arch use `sudo pacman -S gcc`. Confirm:

```bash
g++ --version
```

### Editor or IDE

Use whatever lets you edit text and run a terminal. A few that work well:

- **VS Code** with the C/C++ extension. Lightweight, runs everywhere, integrated terminal. This is the most common choice in the cohort.
- **CLion** if you want a full IDE with a debugger built in. It is paid, but free for students.
- **Vim, Neovim, or Emacs** if that is already your home.

Whatever you pick, the rule is the same: you compile and run from the terminal. Do not rely on a magic "Run" button you do not understand. Knowing the exact command matters, because half of debugging is reading what the compiler tells you.

## Compile and run one file

Every file in this repo is standalone. There is no build system, no Makefile, no CMake. Each `.cpp` file has its own `main()` and compiles on its own. That is intentional: one concept, one file, one command.

Here is the command to compile a single file. Memorize it.

```bash
g++ -std=c++17 -O2 -Wall file.cpp -o out
```

Then run the program:

```bash
./out
```

On Windows the output is `out.exe`, and you run it with `./out` or `./out.exe` depending on your shell.

You can chain both steps so a single line compiles and, if compilation succeeded, runs:

```bash
g++ -std=c++17 -O2 -Wall file.cpp -o out && ./out
```

What each flag does:

| Flag | Meaning |
| --- | --- |
| `-std=c++17` | Compile against the C++17 standard. Use this on every command in the course. |
| `-O2` | Optimize. Makes timing experiments realistic. Be aware it can delete code with no observable effect, which matters when you benchmark loops. |
| `-Wall` | Turn on the common warnings. Read them. They catch real bugs, like comparing signed and unsigned values. |
| `-o out` | Name the output file `out`. Without it you get a default name (`a.out`). |

If you are chasing a memory bug in a later week, add `-g -fsanitize=address,undefined` while you debug. The sanitizers catch use-after-free, out-of-bounds access, and signed overflow at runtime, and they will save you hours once we start writing linked lists and trees by hand. They slow the program down, so drop them again for timing experiments.

A quick sanity check before you go further. Create a file called `hello.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "toolchain works\n";
    return 0;
}
```

Compile and run it:

```bash
g++ -std=c++17 -O2 -Wall hello.cpp -o hello && ./hello
```

If you see `toolchain works`, you are ready.

## How this repo is organized

This repository is the public study companion for the course: the syllabus, the schedule, the problem bank, the pattern reference, and the projects. It is not the video lectures themselves. Use it to know what to study, in what order, and which problems to drill.

```
dsa-mastery-cpp/
├── docs/         Course documentation. You are here.
│   └── patterns/   The interview-pattern reference (two pointers, sliding window, etc.)
├── weeks/        One folder per week. The week-by-week curriculum and lecture notes.
├── problems/     The problem bank, grouped by topic and pattern, tagged by difficulty.
└── projects/     Larger build-it-yourself projects that tie several topics together.
```

The course runs 16 weeks, 4 lectures per week, 64 lectures total. Each `weeks/` folder maps to one of those weeks and tells you which lectures it covers, what to read, and which problems to solve.

The two front-loaded weeks are worth calling out, because the ordering is a deliberate teaching decision:

- **Week 1 — Complexity analysis.** Big-O, Big-Omega, Big-Theta, how to analyze loops, best/worst/average case, space complexity, and amortized analysis. This is the yardstick you use to compare every structure and algorithm for the rest of the course.
- **Week 2 — Recursion.** The call stack, base and recursive cases, recurrence relations, converting recursion to iteration, and a first look at memoization. This is the control structure behind trees, graphs, divide and conquer, backtracking, and dynamic programming.

We teach both before any data structure, on purpose. You cannot honestly say a hash map is faster than a list, or that merge sort beats insertion sort, without complexity in hand. And trees in Week 5 are unteachable to anyone who still fears the call stack. Resist the urge to skip ahead to the "real" data structures. These two weeks are the lenses every later topic depends on.

## Using the repo week by week

The course is built around solving problems, not watching lectures. The watching is the setup; the solving is where you learn. Plan to spend most of your time with a `.cpp` file open and a problem half-solved.

A workable rhythm for each week:

1. **Open that week's folder in `weeks/`.** Read the overview. It lists the lectures, the concepts, and the problem set for the week.
2. **Watch the lectures for the concept, then stop.** Do not binge a week of video and then try to do all the problems from memory. One concept, then practice it, then the next.
3. **Solve the warmups first.** Problems in `problems/` are tagged Warmup, Core, and Challenge. Warmups lock in the mechanics. Skipping them to look smart on the Challenges is a false economy.
4. **Write each solution in its own file and compile it with the command above.** Run your own tests. Use `assert()` to encode the invariants you expect to hold, and run through an edge-case checklist every time: empty input, a single element, duplicates, already-sorted and reverse-sorted input, negatives and zero, the maximum allowed size, and integer overflow. Most wrong answers in interviews are an edge case, not a wrong idea.
5. **State the complexity of every solution out loud.** Time and space. Before you optimize, get one correct solution and name its cost. After you optimize, name the new cost. This habit is the whole point of Week 1, and it compounds.
6. **Name the pattern.** When a problem clicks, ask which interview pattern it belongs to: two pointers, sliding window, fast and slow pointers, monotonic stack, tree BFS, tree DFS, backtracking, and so on. The pattern reference lives in [`docs/patterns.md`](./patterns.md). Pattern recognition is what makes a problem you have never seen feel like one you have.

A note on memory bugs, since you will start writing node-based structures from Week 3. When something crashes or behaves randomly, recompile with `-g -fsanitize=address,undefined` and run again. The sanitizer usually points straight at the line. That feedback loop is faster than staring at the code.

Use `projects/` when a week's overview points you there. The projects are bigger than a single problem and combine several topics, which is closer to how the material shows up in real work and in onsite interviews.

## Quick reference

```bash
# Compile and run one file
g++ -std=c++17 -O2 -Wall file.cpp -o out && ./out

# Same, but with runtime checks while debugging
g++ -std=c++17 -g -fsanitize=address,undefined -Wall file.cpp -o out && ./out

# Check your compiler version
g++ --version
```

That command and the edge-case checklist are the two things you will reach for every single day.

When you are set up, head to [`weeks/`](../weeks/) and start with Week 1.
