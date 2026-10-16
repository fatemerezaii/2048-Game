# 2048 - Console Edition

A console-based implementation of the classic **2048 puzzle game**, built with C++.

Combine matching tiles to reach 2048 while managing the board using keyboard controls. The game features colored console visuals, player profiles, a leaderboard, and game saving functionality.

## Features

- **Classic 2048 Gameplay** — Combine matching numbered tiles to create larger values.
- **Keyboard Controls** — Navigate the board using the arrow keys.
- **Colored Console Interface** — Different tile values are displayed in different colors.
- **Player Profiles** — Sign in with a username and keep track of your results.
- **Leaderboard** — View player rankings based on wins and losses.
- **Save and Continue** — Save your current board and continue a saved game later.
- **Game Statistics** — Track the number of moves and elapsed time.
- **Win and Lose Conditions** — Reach 2048 to win or run out of valid moves to lose.

## Requirements

- Windows operating system
- A C++ compiler supporting C++11 or later
- A terminal that supports ANSI escape codes

## Getting Started

### 1. Clone the Repository

```bash
git clone <YOUR-REPOSITORY-URL>
cd <YOUR-REPOSITORY-NAME>
```

### 2. Compile

Using g++:

```bash
g++ main.cpp -o 2048
```

Replace `main.cpp` with the name of your source file if necessary.

### 3. Run

```bash
./2048
```

On Windows, run:

```bash
2048.exe
```

## How to Play

1. Select **New Game** from the main menu.
2. Enter a username to create or access your player profile.
3. Use the arrow keys to move the tiles.
4. Combine matching tiles and try to reach **2048**.
5. Save your progress and continue later if needed.
6. Check the scoreboard to compare your results with other players.

## Data Files

The game uses local text files to store data:

- `scoreboard.txt` — Stores player records and leaderboard information.
- `savedgame.txt` — Stores the saved game board and move count.

## Technologies

- C++
- Standard Template Library (STL)
- File Handling
- Structs and Arrays
- Console Input and Output
- Random Number Generation

## Future Improvements

- Improve tile movement and merging logic.
- Prevent invalid moves from increasing the move counter.
- Support multiple save slots.
- Improve save/load handling for player statistics and elapsed time.
- Add a more polished terminal interface.

## License

This project is available for educational and personal use.
