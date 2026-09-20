# Social Network Graph Representation Comparison

## Problem
Consider a small social network with the connections:
- A-B
- A-C
- B-D
- B-E
- C-F
- E-F

The graph is implemented using an adjacency matrix and an adjacency list. BFS and DFS are performed from vertex A, and vertex E is searched from A using BFS. Edge E-F is also checked to compare edge-checking operations.

## Files
- `graph_comparison.c` - C source code for both graph representations, BFS, DFS and search.
- `input.txt` - Input data used for the assignment.
- `output.txt` - Output produced by the C program.
- `report.md` - Assignment report including trace tables, complexity analysis, comparison and conclusion.

## How to run
```bash
gcc -std=c11 -Wall -Wextra -pedantic graph_comparison.c -o graph_comparison
./graph_comparison
```
