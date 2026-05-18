# Twixt - CLI Edition

A complete Command Line Interface (CLI) implementation of the classic strategy board game **Twixt**, written entirely in C. 

The game involves two players (Red and Black) taking turns placing pegs and links on a 24x24 grid. The objective is to create a continuous connected path of your color from one side of the board to the other (left-to-right for Red, top-to-bottom for Black) before your opponent does.

###  Learn to Play
* **Rules of the game:** [Watch the tutorial here](https://youtu.be/dIyuVS3xRQ0?si=_qYFqihhfrxKRBRq)
* **Try the web version:** [Play online here](https://twixtlive.com/Play.aspx) to get familiarized with the mechanics.

---

##  Project Architecture

The codebase is highly modular, separating the game state, board mechanics, and core execution into distinct files to optimize memory storage and execution time.

* **`main.c`**: The entry point of the program. Handles the main game loop, CLI command parsing (`r c` for moves, `help`, `quit`), and turn alternation between Red and Black players.
* **`game.c` & `game.h`**: Contains the core game mathematics and state logic. This manages the automatic generation of knight-move connections, the geometric math to ensure edges do not intersect, and the pathfinding algorithm to determine a winner.
* **`board.c` & `board.h`**: Manages the underlying 24x24 grid. It handles storing the board state, rendering the grid to the terminal, and validating moves (e.g., preventing peg placement in corners or restricted enemy end-rows).
* **`Makefile`**: Automates the compilation process, linking the `.c` files and their respective `.o` object files into the final executable.

---

##  Technical Highlights

* **Pathfinding & Win Detection:** The logic to check if a player has won relies on a custom **Breadth-First Search (BFS)** algorithm. It utilizes a `visited` matrix and a custom `Node` queue to efficiently traverse the network of connected pegs and verify if a path reaches the opposite end of the board.
* **Geometric Edge Intersection:** Implements advanced mathematical orientation (cross-product calculation) to verify line segments. When a player places a peg, the program calculates all possible knight-moves and strictly rejects any links that would cross an existing edge.
* **Memory Optimization:** Built with strict space and time complexity considerations, ensuring no wasted memory storage. Edges are stored in a contiguous array rather than complex graphs.

---

##  How to Build and Run

**For Mac/Linux:**
compile using : `make`
*(press enter/return)*
run using : `./a.out`
*(press enter/return)*
for recompilation use: `make clean`
*(and then enter)*

**For Windows:**
compile using : `mingw32-make`
*(then enter)*
run using : `./a.out.exe` or `a.out.exe`
*(press enter)*
for recompilation : `mingw32-make clean`
