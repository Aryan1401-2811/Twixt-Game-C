# Twixt - CLI Edition

A complete Command Line Interface (CLI) implementation of the classic strategy board game **Twixt**, written entirely in C. 

The game involves two players (Red and Black) taking turns placing pegs and links on a grid. The objective is to create a continuous connected path of your color from one side of the board to the other (top-to-bottom for one player, left-to-right for the other) before your opponent does.

###  Learn to Play
* **Rules of the game:** [Watch the tutorial here](https://youtu.be/dIyuVS3xRQ0?si=_qYFqihhfrxKRBRq)
* **Try the web version:** [Play online here](https://twixtlive.com/Play.aspx) to get familiarized with the mechanics.

---

##  Project Architecture

The codebase is highly modular, separating the game state, board mechanics, and core execution into distinct files to optimize memory storage and execution time.

* **`main.c`**: The entry point of the program. Handles the main game loop, initializing the board, and invoking the CLI interface.
* **`game.c` & `game.h`**: Contains the core game flow logic. This manages alternating turns between the Red and Black players, processing player inputs, and coordinating the overall game state.
* **`board.c` & `board.h`**: Manages the underlying data structures for the grid. It handles storing the board state, validating if two pins can be connected, and executing the pathfinding logic.
* **`Makefile`**: Automates the compilation process, linking the `.c` files and their respective `.o` object files into the final executable.

---

##  Technical Highlights

* **Pathfinding & Win Detection:** The logic to check if a player has won relies on advanced traversal algorithms. It utilizes either recursion or 2D Dynamic Programming (DP) to efficiently check for continuous connected paths across the grid (e.g., verifying if a valid path of pins exists from the top row to a specific coordinate `(i, j)`).
* **Memory Optimization:** Built with strict space and time complexity considerations, ensuring no wasted memory storage during runtime.
* **Custom Data Structures:** Utilizes custom `structs` and `enums` to cleanly represent piece types, connection validity, and coordinate systems.

---

##  How to Build and Run

For Mac/Linux :
compile using : make
(press enter/return)
run using : ./a.out
(press enter/return)
for recompilation use: make clean
(and then enter)

For Windows:
compile using : mingw32-make
(then enter)
run using : ./a.out.exe or a.out.exe
(press enter)
for recompilation : mingw32-make clean
