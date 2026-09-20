# Graph Representation Comparison – Social Network

## 1. Aim
To implement the given social network using an adjacency matrix and an adjacency list, perform BFS and DFS from vertex A, search for vertex E, compare the two graph representations, and determine their suitability for a sparse social network.

## 2. Given Input
Vertices: A, B, C, D, E, F

Connections: A-B, A-C, B-D, B-E, C-F, E-F

Starting vertex: A

Search target: E

Edge checked: E-F

The graph is undirected, so every connection is stored in both directions.

## 3. Adjacency Matrix

```text
    A B C D E F
A   0 1 1 0 0 0
B   1 0 0 1 1 0
C   1 0 0 0 0 1
D   0 1 0 0 0 0
E   0 1 0 0 0 1
F   0 0 1 0 1 0
```

## 4. Adjacency List

```text
A -> B -> C -> NULL
B -> A -> D -> E -> NULL
C -> A -> F -> NULL
D -> B -> NULL
E -> B -> F -> NULL
F -> C -> E -> NULL
```

## 5. Traversal Results

### BFS from A
Order for both representations:

```text
A -> B -> C -> D -> E -> F
```

### DFS from A
Order for both representations:

```text
A -> B -> D -> E -> F -> C
```

The traversal order is the same because both representations examine neighbours in the same A-to-F / insertion order.

## 6. Search Result

A BFS-based search is used to locate vertex E starting from A.

- Adjacency Matrix: E found after 11 neighbour checks.
- Adjacency List: E found after 5 neighbour checks.

## 7. Edge-Checking Result

The edge E-F was checked.

- Adjacency Matrix: 1 check.
- Adjacency List: 2 checks, because E's list is B -> F and F is the second neighbour.

## 8. Trace Tables

### 8.1 BFS Trace

| Step | Vertex removed from queue | New vertices added | Queue after step | Visited order |
|---:|:---:|:---|:---|:---|
| 1 | A | B, C | B, C | A, B, C |
| 2 | B | D, E | C, D, E | A, B, C, D, E |
| 3 | C | F | D, E, F | A, B, C, D, E, F |
| 4 | D | None | E, F | A, B, C, D, E, F |
| 5 | E | None | F | A, B, C, D, E, F |
| 6 | F | None | Empty | A, B, C, D, E, F |

### 8.2 DFS Trace

| Step | Current vertex | Action | Traversal order |
|---:|:---:|:---|:---|
| 1 | A | Visit B | A, B |
| 2 | B | Visit D | A, B, D |
| 3 | D | No unvisited neighbour | A, B, D |
| 4 | B | Visit E | A, B, D, E |
| 5 | E | Visit F | A, B, D, E, F |
| 6 | F | Visit C | A, B, D, E, F, C |
| 7 | C | No unvisited neighbour | A, B, D, E, F, C |

### 8.3 Search Trace for E from A

#### Matrix

| Step | Vertex processed | Matrix positions checked | Result |
|---:|:---:|:---|:---|
| 1 | A | A, B, C, D, E, F | B and C discovered |
| 2 | B | A, B, C, D, E | E discovered; search stops |

Total neighbour checks = 6 + 5 = **11**.

#### List

| Step | Vertex processed | Neighbours checked | Result |
|---:|:---:|:---|:---|
| 1 | A | B, C | B and C discovered |
| 2 | B | A, D, E | E found; search stops |

Total neighbour checks = 2 + 3 = **5**.

### 8.4 Edge Check for E-F

| Representation | Checks | Reason |
|:---|---:|:---|
| Matrix | 1 | Directly access matrix[E][F] |
| List | 2 | Check E's neighbours B, then F |

## 9. Execution Results

| Operation | Adjacency Matrix | Adjacency List |
|:---|---:|---:|
| BFS neighbour checks | 36 | 12 |
| DFS neighbour checks | 36 | 12 |
| Search for E from A | 11 | 5 |
| Edge check E-F | 1 | 2 |

The traversal orders are identical, but the adjacency list examines only existing edges while the matrix scans all six possible neighbour positions for every visited vertex.

## 10. Complexity Analysis

Let V be the number of vertices and E be the number of edges.

### Adjacency Matrix

- Space: O(V²)
- Edge checking: O(1)
- BFS: O(V²)
- DFS: O(V²)

### Adjacency List

- Space: O(V + E)
- Edge checking: O(deg(u)) in the worst case O(V)
- BFS: O(V + E)
- DFS: O(V + E)

For the given graph, V = 6 and E = 6.

The matrix therefore contains 36 cells. Since the graph is undirected, the adjacency list stores 12 adjacency entries (one for each direction of the 6 edges) plus 6 vertex-head pointers.

## 11. Comparison

| Feature | Adjacency Matrix | Adjacency List |
|:---|:---|:---|
| Storage | O(V²) | O(V+E) |
| Given graph storage form | 36 matrix cells | 6 head pointers + 12 adjacency nodes |
| BFS | O(V²) | O(V+E) |
| DFS | O(V²) | O(V+E) |
| Edge check | O(1) | O(deg(u)) worst case O(V) |
| Actual BFS checks | 36 | 12 |
| Actual DFS checks | 36 | 12 |
| Actual E search checks | 11 | 5 |
| Actual E-F edge checks | 1 | 2 |

## 12. Conclusion

For a sparse social network, the adjacency list uses space proportional to the number of vertices and actual connections, O(V+E), rather than reserving a V x V matrix. In this execution, it also required fewer neighbour checks for BFS, DFS and the BFS-based search. The adjacency matrix still has an important advantage for direct edge checking because an edge can be tested in O(1) time. Therefore, for the stated sparse-network use case, the adjacency-list representation matches the required storage and traversal behaviour more closely, while the matrix is useful when frequent direct edge-existence checks are the main operation.
