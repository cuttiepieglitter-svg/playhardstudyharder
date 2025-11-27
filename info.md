# AI Lab Assignments (1–8)
## Time & Space Complexities + Simple Algorithm Steps

---

# ✅ **ASSIGNMENT 1 — 8-Puzzle (BFS + DFS)**
_Source: LAB1_BD_8PUZZLE.cpp_

### **Algorithm Steps**
1. Read initial puzzle state.
2. Define goal state (1–8 with blank = 0).
3. Insert start into queue (BFS) or stack (DFS).
4. Loop:
   - Pop node.
   - If goal → stop.
   - Find blank position.
   - Generate up to 4 moves.
   - If not visited, push to frontier.
5. End if frontier empty.

### **Time Complexity**
- **BFS:** O(b^d)  
- **DFS:** O(b·d)  
b ≈ 4 moves, d ≈ 31 for 8-puzzle.

### **Space Complexity**
- **BFS:** O(b^d)  
- **DFS:** O(b·d)

---

# ✅ **ASSIGNMENT 2 — Map Coloring (Forward Checking)**
_Source: LAB2_MAP_CONSTRAINT.cpp_

### **Algorithm Steps**
1. Define regions, colors, and adjacency.
2. Start from region 0.
3. Try each color for region:
   - Check if neighbors have same color.
   - If valid → assign → recurse for next region.
   - Else backtrack.
4. Continue until all regions colored.

### **Time Complexity**
Worst case: **O(kⁿ)**  
n = 7 regions, k = 3 colors → 3⁷ = 2187.

### **Space Complexity**
Recursion depth n → **O(n)**

---

# ✅ **ASSIGNMENT 3 — Family Tree**
_Source: LAB3_FAMTREE.cpp_

### **Algorithm Steps**
1. Create Person nodes.
2. Link children to parents.
3. Print tree using recursion (DFS).
4. For queries:
   - Search entire tree.
   - Print all children of given person.

### **Time Complexity**
- Building tree: O(n)  
- Printing tree: O(n)  
- Query: O(n)

### **Space Complexity**
- Store all nodes: O(n)  
- Recursion depth: O(h)

---

# ✅ **ASSIGNMENT 4 — A\* Search (Pune → Mumbai)**
_Source: LAB4_ASTAR_OPTIMAL.cpp_

### **Algorithm Steps**
1. Define graph and heuristic values.
2. Push start node to priority queue (min-heap).
3. Loop:
   - Pop node with smallest f = g + h.
   - If goal → reconstruct path.
   - Expand neighbors and update costs.
4. Continue until goal is found.

### **Time Complexity**
A* worst case: **O(E log V)**

### **Space Complexity**
Open + closed lists → **O(V)**

---

# ✅ **ASSIGNMENT 5 — Minimax for Tic-Tac-Toe**
_Source: LAB5_MinMax_TTT.cpp_

### **Algorithm Steps**
1. Human = X, AI = O.
2. After human move:
   - AI runs minimax on all empty cells.
   - AI chooses move with highest score.
3. Evaluate board for win/loss/draw.
4. Continue until terminal state.

### **Time Complexity**
Worst case: **O(9!) ≈ 362,880**  
(Full minimax tree)

### **Space Complexity**
Recursion depth ≤ 9 → **O(d)**  
Board: O(1)

---

# ✅ **ASSIGNMENT 6 — N-Queens (Backtracking)**
_Source: LAB6_8QUEEN_Backtracking.cpp_

### **Algorithm Steps**
1. Start from column 0.
2. For each row:
   - Check if safe (row, upper-left diagonal, lower-left diagonal).
   - If safe → place queen.
   - Recurse to next column.
   - If fail → backtrack.
3. Stop after one valid solution.

### **Time Complexity**
Worst case: **O(N!)**

### **Space Complexity**
Board: **O(N²)**  
Recursion depth: **O(N)**

---

# ✅ **ASSIGNMENT 7 — Forward Chaining (Medical Diagnosis)**
_Source: LAB7_ForwardChain.cpp_

### **Algorithm Steps**
1. Start with basic symptoms (fever, cough, body ache).
2. Apply rules sequentially:
   - Fever & Cough → ViralInfection  
   - ViralInfection & BodyAche → FluSymptoms  
   - FluSymptoms → Flu  
3. Mark inferred facts as true.
4. Print final result.

### **Time Complexity**
Rules R = 3 → **O(R)**

### **Space Complexity**
Facts + rules → **O(R + F)**

---

# ✅ **ASSIGNMENT 8 — Backward Chaining**
_Source: LAB8_BackwardChain.cpp_

### **Algorithm Steps**
1. Goal = prove "Flu".
2. If "Flu" is not a fact:
   - Find rule with "Flu" as consequent.
   - Recursively prove its antecedents:
     - FluSymptoms
     - ViralInfection
     - Fever, Cough, BodyAche
3. If all antecedents true → Flu proven.
4. Else → fail.

### **Time Complexity**
Worst case: **O(R × F)**  
R = rules, F = facts.

### **Space Complexity**
Recursion depth = rules triggered → **O(R)**

---

# ✅ **SUMMARY TABLE**

| Assignment | Topic | Time Complexity | Space Complexity |
|-----------|--------|----------------|------------------|
| 1 | 8-Puzzle (BFS/DFS) | BFS: O(b^d), DFS: O(bd) | BFS: O(b^d), DFS: O(bd) |
| 2 | Map Coloring | O(kⁿ) | O(n) |
| 3 | Family Tree | O(n) | O(n) |
| 4 | A* | O(E log V) | O(V) |
| 5 | Minimax TTT | O(9!) | O(d) |
| 6 | N-Queens | O(N!) | O(N²) |
| 7 | Forward Chaining | O(R) | O(R+F) |
| 8 | Backward Chaining | O(R×F) | O(R) |

