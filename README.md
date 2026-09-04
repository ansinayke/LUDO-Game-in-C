# LUDO - Console Board Game in C

[![Language: C](https://img.shields.io/badge/Language-C-A8B9CC?logo=c&logoColor=black)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard: C11](https://img.shields.io/badge/Standard-C11-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Build: cc](https://img.shields.io/badge/Build-cc-2E7D32)](https://clang.llvm.org/)

A terminal-based Ludo game implemented in C. The project models a four-player game with four pieces per player, randomized dice rolls, piece movement, captures, home completion, and final rankings.

This project was built to strengthen my understanding of procedural programming, state management, arrays, control flow, and compiling a multi-file C program on a POSIX system.

## Features

- Four players: Red, Green, Yellow, and Blue
- Four pieces per player
- Randomized opening roll to determine the first player
- Dice rolls from 1 to 6
- Rolling a six gives a player additional rolls, with three consecutive sixes ending the turn
- Movement from base to start, around the track, and into home
- Capture logic that sends an opponent's piece back to base
- Automatic detection of players who bring all four pieces home
- Final finishing order, including the remaining player's fourth-place position
- Console status board showing every piece's current state

## Tech Stack

| Technology | Purpose |
| --- | --- |
| C11 | Core game logic, data modeling, and procedural control flow |
| Standard C library | Input/output, random number generation, and program utilities |
| POSIX `unistd.h` | `sleep()` delays for a more readable terminal experience |
| `cc` / Clang | Compilation and warning checks |
| GitHub | Source control and project presentation |

## Getting Started

### Requirements

- A C compiler such as Clang or GCC
- A POSIX-compatible environment such as macOS or Linux

### Compile

```bash
gcc main.c game_logic.c -o ludo
```

### Run

```bash
./ludo
```

The game is intentionally terminal-based. No external libraries or runtime dependencies are required.

## Project Structure

```text
.
├── main.c          # Program entry point
├── game_logic.c    # Game state, turns, movement, captures, and rankings
├── types.h         # Shared constants, declarations, and public game interface
└── README.md       # Project documentation
```

## Implementation Overview

The game state is represented with a two-dimensional integer array:

```c
int playerPieces[NUM_PLAYERS][NUM_PIECES];
```

Each integer represents a piece position:

- `0`: base
- `1`: starting square
- `2` to `57`: track and home-lane positions
- `58`: home

The main loop advances through players until three players have completed the game. Finished players are skipped, while the last unfinished player receives fourth place. Shared constants such as player and piece counts are kept in `types.h`, making the core logic easier to read and adjust.

## Technical Decisions

### Why C?

C was a deliberate choice for practicing the fundamentals close to the machine: explicit data representation, fixed-size arrays, function boundaries, compilation, and predictable control flow. A game is a useful domain for this because every action changes observable state and can be checked after each turn.

### Why arrays?

The fixed four-by-four player-piece structure maps directly to the rules of this version of Ludo. It keeps state compact and makes iteration over players and pieces straightforward without introducing unnecessary abstractions for a small console application.

### Why a shared header?

`types.h` provides one place for game-wide constants and the `game_ludo()` declaration. This separates the program entry point from the game implementation and demonstrates how multiple C translation units work together.

### Why pseudo-random dice?

`rand()` with a time-based seed creates a different playthrough on each run while keeping the implementation dependency-free. The dice values are constrained to the inclusive range 1 to 6.

### Why POSIX delays?

`sleep()` spaces out the status messages and makes the terminal output easier to follow. This improves the interactive feel, with the tradeoff that the current build targets macOS and Linux rather than every ISO C platform.

## Implementation Guidelines

For anyone extending this project, keep these guidelines in mind:

1. Keep rule changes inside `game_logic.c` and shared configuration in `types.h`.
2. Preserve the position invariants: base is `0`, home is `58`, and a move must never exceed home.
3. Validate movement before changing a piece's position.
4. Keep turn progression and finish tracking synchronized so completed players are not given additional turns.
5. Compile with `-Wall -Wextra` after every rule change.
6. Test edge cases such as an exact roll into home, a move beyond home, a capture, three consecutive sixes, and a player with no valid move.
7. If portability is required, isolate or replace `sleep()` with a platform-neutral timing approach.

## What I Learned

Building this game improved my ability to:

- Translate written game rules into explicit state transitions
- Design and update nested array-based data structures
- Break a small program across a header and multiple source files
- Reason about boundary conditions and invalid moves
- Track multiple simultaneous outcomes, including finishing order
- Use compiler warnings as an early feedback loop
- Think about tradeoffs between simplicity, portability, and user experience

## Future Improvements

- Add interactive piece selection instead of moving the first eligible piece
- Add configurable player names and input validation
- Separate rendering, input, and rules into dedicated modules
- Add automated tests for movement and capture rules
- Improve random number generation and inject a testable dice source
- Add a portable timing abstraction and optional no-delay mode
- Support a saved game state or replay log

## Conclusion

This project demonstrates my approach to learning by building: start with a concrete problem, model the state carefully, validate the behavior, and document the technical decisions behind the implementation.
