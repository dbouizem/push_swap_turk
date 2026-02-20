# push_swap

> An efficient sorting algorithm using two stacks and a limited set of operations

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)
![Grade](https://img.shields.io/badge/Grade-125%2F100-brightgreen?style=for-the-badge)

</div>

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Data Structures](#data-structures)
- [Operations](#operations)
- [Sorting Algorithms](#sorting-algorithms)
- [Turk Algorithm](#turk-algorithm)
- [Compilation](#compilation)
- [Testing](#testing)
- [Bonus: Checker](#bonus-checker)
- [Performance](#performance)
- [Project Structure](#project-structure)
- [Author](#author)

---

## About

**push_swap** is a sorting algorithm project that challenges you to sort a stack of integers using a limited set of operations with the minimum number of moves possible.

### Learning Objectives

- Implement efficient sorting algorithms
- Optimize for minimal operations
- Master stack data structures
- Handle error cases and edge conditions
- Understand algorithmic complexity
- Work with limited operation sets

### Key Objectives

- Sort stack A using auxiliary stack B
- Minimize the number of operations
- Handle all error cases properly
- Implement a checker to validate results

### Constraints

- Use only authorized operations
- Handle duplicates and errors
- Optimize for different stack sizes

---

## Features

### Core Functionality

| Feature | Description |
|---------|-------------|
| **Stack Sorting** | Sorts integers using two stacks (A and B) |
| **Limited Operations** | 11 allowed operations (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr) |
| **Error Handling** | Comprehensive validation and error messages |
| **Optimized Algorithms** | Different strategies for different stack sizes |

### Performance Achieved

| Stack Size | Operations | Target | Status |
|------------|------------|--------|--------|
| **3 elements** | ≤ 3 | ≤ 3 | ✅ |
| **5 elements** | ≤ 12 | ≤ 12 | ✅ |
| **100 elements** | ~550-600 | < 700 | ✅ |
| **500 elements** | ~5000 | < 5500 | ✅ |

### Bonus

| Feature | Description |
|---------|-------------|
| **Checker** | Program to validate sorting instructions |
| **Silent Operations** | Operations without output for checker |
| **Instruction Validation** | Verifies instruction sequences |

---

## Installation

### Prerequisites

| Tool | Minimum Version | Purpose |
|------|-----------------|---------|
| gcc | 9.0+ | Compilation |
| make | 4.3+ | Build automation |

### Clone the Repository

```bash
git clone https://github.com/dbouizem/push_swap.git
cd push_swap
```

### Compile

```bash
# Compile push_swap
make

# Compile checker (bonus)
make bonus

# Compile both
make all

# Clean up
make clean      # Remove .o files
make fclean     # Remove .o and executables
make re         # Recompile everything
```

---

## Usage

### push_swap

**Basic usage:**

```bash
# Space-separated arguments
./push_swap 4 67 3 87 23

# Single string argument
./push_swap "4 67 3 87 23"

# Empty input (no output)
./push_swap
```

**Output:** Series of operations to sort the stack

### checker (Bonus)

**Validate sorting instructions:**

```bash
# Generate and verify in one command
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23
# Output: OK or KO

# Save instructions to file
./push_swap 4 67 3 87 23 > instructions.txt

# Verify from file
./checker 4 67 3 87 23 < instructions.txt
```

**Output:**
- `OK` - Stack is sorted correctly
- `KO` - Stack is not sorted or B is not empty
- `Error` - Invalid instructions or arguments

---

## Data Structures

### Stack Structure

```c
typedef struct s_stack
{
    int *data;      // Array of integers
    int size;       // Current number of elements
    int capacity;   // Maximum capacity
}   t_stack;
```

**Properties:**
- `data`: Dynamic array storing the integers
- `size`: Number of elements currently in stack
- `capacity`: Maximum allocated size

### Cost Structure

```c
typedef struct s_cost
{
    int total;          // Total cost of operation
    int ra_count;       // Number of A rotations
    int rra_count;      // Number of A reverse rotations
    int rb_count;       // Number of B rotations
    int rrb_count;      // Number of B reverse rotations
    int element_index;  // Index of element concerned
}   t_cost;
```

**Usage:** Calculates and stores the cost of moving an element to its optimal position

---

## Operations

### Swap Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap first 2 elements of stack A |
| `sb` | Swap first 2 elements of stack B |
| `ss` | `sa` and `sb` simultaneously |

### Push Operations

| Operation | Description |
|-----------|-------------|
| `pa` | Push first element of B to top of A |
| `pb` | Push first element of A to top of B |

### Rotate Operations

| Operation | Description |
|-----------|-------------|
| `ra` | Rotate A up (first → last) |
| `rb` | Rotate B up (first → last) |
| `rr` | `ra` and `rb` simultaneously |

### Reverse Rotate Operations

| Operation | Description |
|-----------|-------------|
| `rra` | Rotate A down (last → first) |
| `rrb` | Rotate B down (last → first) |
| `rrr` | `rra` and `rrb` simultaneously |

### Silent Operations

Each operation has a `_silent` version for the checker that doesn't print the instruction.

---

## Sorting Algorithms

### 1. Small Stack Sorting (≤ 5 elements)

#### Two Elements

```c
void sort_two(t_stack *a)
{
    if (a->data[0] > a->data[1])
        sa(a);
}
```

Simply swap if first element is greater than second.

#### Three Elements

Handles all 6 possible permutations with combinations of `sa`, `ra`, `rra`:

```
[3, 2, 1] → sa + rra
[3, 1, 2] → ra
[2, 3, 1] → rra
[2, 1, 3] → sa
[1, 3, 2] → sa + ra
[1, 2, 3] → already sorted
```

#### Four Elements

1. Find minimum element
2. Bring it to top
3. Push to B (`pb`)
4. Sort remaining 3 in A
5. Push minimum back (`pa`)

#### Five Elements

1. Push 2 smallest to B
2. Sort remaining 3 in A
3. Push elements back from B in order

### 2. Turk Algorithm (> 5 elements)

The most sophisticated algorithm in the project, optimized for minimal operations.

---

## Turk Algorithm

### Overview

The Turk algorithm is a cost-based sorting strategy that minimizes the total number of operations by always choosing the cheapest move.

### Algorithm Phases

#### Phase 1: Initialization

```c
// Push 2 elements to B to start
pb(a, b);
if (a->size > 3)
    pb(a, b);
```

**Purpose:** Create initial state with elements in both stacks

#### Phase 2: Transfer A → B

```c
while (a->size > 3)
{
    // 1. Find the cheapest element to move
    cheapest_cost = find_cheapest_element_a_to_b(a, b);

    // 2. Execute optimal movements
    execute_optimal_moves(a, b, cheapest_cost);

    // 3. Push element to B
    pb(a, b);
}
```

**Strategy:**
- Calculate cost for each element in A
- Choose element with minimum cost
- Execute combined rotations (rr, rrr) when possible
- Push element to optimal position in B

#### Phase 3: Sort Final Three

```c
sort_three(a);
```

**Purpose:** Sort the last 3 elements remaining in A

#### Phase 4: Transfer B → A

```c
while (!is_empty(b))
{
    // 1. Find best element to retrieve
    cheapest_cost = find_cheapest_element_b_to_a(a, b);

    // 2. Position optimally
    execute_optimal_moves(a, b, cheapest_cost);

    // 3. Retrieve element
    pa(a, b);
}
```

**Strategy:**
- For each element in B, find its target position in A
- Calculate cost of positioning
- Choose cheapest move
- Push back to A

#### Phase 5: Final Rotation

```c
bring_min_to_top(a);
```

**Purpose:** Rotate A so minimum element is at top (sorted position)

### Cost Calculation

#### For A → B:

```c
t_cost calculate_cost_a_to_b(int pos_a, int value, t_stack *a, t_stack *b)
```

**Factors:**
1. **Cost to bring element to top of A**
   - Rotation (`ra`) or reverse rotation (`rra`)
   - Choose shorter path

2. **Cost to position in B**
   - Find target position in B
   - Cost to bring target position to top

3. **Optimization**
   - Combine rotations when both stacks need same direction
   - Use `rr` instead of `ra` + `rb`
   - Use `rrr` instead of `rra` + `rrb`

#### Example Calculation:

```
Stack A: [7, 3, 5, 1]  (top on left)
Stack B: [6, 4, 2]

To move 5 (position 2 in A) to B:
- Cost A: 2 rotations (ra ra)
- Target B: between 6 and 4 (position 1)
- Cost B: 1 rotation (rb)
- Optimization: cannot combine (different counts)
- Total: 2 + 1 + 1 (push) = 4 operations
```

### Why Turk Algorithm is Efficient

1. **Greedy approach**: Always chooses cheapest move at each step
2. **Cost-based**: Considers full cost including positioning
3. **Optimization**: Combines rotations when possible
4. **Adaptive**: Works well for any stack size > 5

---

## Compilation

> [!NOTE]
> The project uses a Makefile for compilation. All compilation flags comply with 42 norms.

### Makefile Rules

```bash
make          # Compile push_swap
make bonus    # Compile checker
make all      # Compile both
make clean    # Remove object files
make fclean   # Remove objects and executables
make re       # Recompile everything
```

### Compilation Flags

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -Werror
```

---

## Testing

### Manual Tests

**Basic functionality:**

```bash
# Test with 3 elements
./push_swap 3 2 1

# Test with 5 elements
./push_swap 5 4 3 2 1

# Test with duplicates (should print Error)
./push_swap 1 2 3 2

# Test with non-numeric (should print Error)
./push_swap 1 2 abc 3

# Test with INT overflow (should print Error)
./push_swap 1 2 2147483648 3
```

**Performance tests:**

```bash
# Generate random 100 numbers
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l

# Generate random 500 numbers
ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l
```

**Verification with checker:**

```bash
# Verify sorting
./push_swap 3 2 5 1 4 | ./checker 3 2 5 1 4

# Should output: OK

# Test with wrong instructions
echo -e "sa\npb\npa" | ./checker 3 2 1

# Should output: KO (not sorted)
```

### Automated Testing

**Popular External Testers:**

- [push_swap_tester](https://github.com/gemartin99/Push-Swap-Tester)
  ```bash
  git clone https://github.com/gemartin99/Push-Swap-Tester.git
  cd Push-Swap-Tester
  bash push_swap_tester.sh
  ```

- [push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer)
  ```bash
  git clone https://github.com/o-reo/push_swap_visualizer.git
  cd push_swap_visualizer
  mkdir build && cd build
  cmake .. && make
  ./bin/visualizer
  ```

- [push_swap_checker](https://github.com/LeoFu9487/push_swap_tester)
  ```bash
  git clone https://github.com/LeoFu9487/push_swap_tester.git
  cd push_swap_tester
  bash test.sh /path/to/your/push_swap
  ```

**Create a test script:**

```bash
#!/bin/bash

count=0
success=0

for i in {1..100}; do
    ARG=$(shuf -i 1-5000 -n 100 | tr '\n' ' ')
    ops=$(./push_swap $ARG | wc -l)
    result=$(./push_swap $ARG | ./checker $ARG)

    count=$((count + 1))

    if [ "$result" = "OK" ] && [ "$ops" -le 700 ]; then
        success=$((success + 1))
    fi

    echo "Test $count: $ops operations - $result"
done

echo ""
echo "Success rate: $success/$count"
```

### Edge Cases

```bash
# Empty input
./push_swap
# Output: (nothing)

# Single element
./push_swap 42
# Output: (nothing, already sorted)

# Already sorted
./push_swap 1 2 3 4 5
# Output: (nothing)

# Reverse sorted
./push_swap 5 4 3 2 1
# Output: (sorting instructions)

# Minimum INT
./push_swap -2147483648 0 2147483647

# Maximum INT
./push_swap 2147483647 0 -2147483648
```

### Validation Checklist

**Mandatory Part:**
- [ ] Handles space-separated arguments
- [ ] Handles single string argument
- [ ] Sorts correctly for all sizes
- [ ] No memory leaks
- [ ] Proper error handling (duplicates, non-numeric, overflow)
- [ ] Meets performance targets
- [ ] Empty/single element returns nothing

**Bonus Part:**
- [ ] Checker compiles separately
- [ ] Checker validates instructions correctly
- [ ] Checker outputs OK/KO/Error appropriately
- [ ] Handles invalid instructions

---

## Bonus: Checker

### Overview

The checker validates whether a sequence of operations correctly sorts a stack.

### Implementation

```c
int main(int ac, char **av)
{
    t_stack *a;
    t_stack *b;
    char    *line;

    // 1. Parse and validate arguments
    a = parse_arguments(ac, av);
    b = create_stack(a->capacity);

    // 2. Read instructions from stdin
    while (get_next_line(0, &line) > 0)
    {
        // 3. Execute instruction (silent version)
        if (!execute_instruction(line, a, b))
        {
            write(2, "Error\n", 6);
            return (cleanup_and_exit(a, b, line));
        }
        free(line);
    }

    // 4. Verify result
    if (is_sorted(a) && is_empty(b))
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);

    return (cleanup_and_exit(a, b, NULL));
}
```

### Instruction Validation

Valid instructions:
```
sa  sb  ss
pa  pb
ra  rb  rr
rra rrb rrr
```

Any other instruction → `Error`

### Usage Examples

**Correct sorting:**

```bash
./push_swap 3 2 1 | ./checker 3 2 1
# Output: OK
```

**Incorrect sorting:**

```bash
echo -e "sa\nsa" | ./checker 3 2 1
# Output: KO (not sorted)
```

**Invalid instruction:**

```bash
echo -e "sa\ninvalid\npb" | ./checker 3 2 1
# Output: Error
```

---

## Performance

### Complexity Analysis

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Small sort (≤5) | O(1) | O(1) |
| Turk algorithm | O(n²) | O(n) |

### Benchmark Results

Tested on 100 random sets of each size:

| Stack Size | Min Ops | Max Ops | Avg Ops | Target | Status |
|------------|---------|---------|---------|--------|--------|
| 3 | 0 | 3 | 1.5 | ≤ 3 | ✅ |
| 5 | 0 | 12 | 7 | ≤ 12 | ✅ |
| 100 | 520 | 680 | 580 | < 700 | ✅ |
| 500 | 4800 | 5300 | 5020 | < 5500 | ✅ |

### Optimization Techniques

1. **Combined Rotations**
   - Use `rr` instead of separate `ra` + `rb`
   - Use `rrr` instead of separate `rra` + `rrb`

2. **Cost Calculation**
   - Choose shorter rotation path (rotate vs reverse)
   - Combine operations when possible

3. **Algorithm Selection**
   - Different strategies for different sizes
   - Hardcoded optimal solutions for ≤3 elements

4. **Memory Efficiency**
   - Dynamic allocation only when needed
   - Reuse of stack structures

---

## Project Structure

```
push_swap/
│
├── includes/
│   └── push_swap.h              # Main header
│
├── libft/                       # Personal library
│   ├── libft.h
│   └── *.c
│
├── srcs/
│   ├── main.c                   # Entry point
│   │
│   ├── parsing/                 # Argument parsing
│   │   ├── input_parsing.c
│   │   └── input_validation.c
│   │
│   ├── operations/              # Stack operations
│   │   ├── swap.c
│   │   ├── push.c
│   │   ├── rotate.c
│   │   ├── reverse_rotate.c
│   │   ├── operations_silent.c
│   │   ├── rotate_silent.c
│   │   └── combined_silent.c
│   │
│   ├── sorting/                 # Sorting algorithms
│   │   ├── small_sort.c
│   │   ├── medium_sort.c
│   │   ├── turk_algorithm.c
│   │   ├── cost_calculation.c
│   │   └── movement_execution.c
│   │
│   └── utils/                   # Utility functions
│       ├── stack_utils.c
│       ├── position_utils.c
│       ├── validation_utils.c
│       ├── math_utils.c
│       ├── error_utils.c
│       ├── parsing_utils.c
│       └── cost_utils.c
│
├── bonus/                       # Checker program
│   ├── checker_bonus.c
│   ├── operation_bonus.c
│   ├── checker_utils_bonus.c
│   └── stack_utils_bonus.c
│
├── Makefile
└── README.md                    # This file
```

---

## Author

<div align="center">

| [<img src="https://github.com/dbouizem.png" width="100px;"/><br /><sub><b>dbouizem</b></sub>](https://github.com/dbouizem)<br /> |
| :---: |

[![GitHub](https://img.shields.io/badge/GitHub-dbouizem-181717?style=for-the-badge&logo=github)](https://github.com/dbouizem)

</div>

---

## License

This project was completed as part of the 42 School curriculum. It is freely available for educational purposes.

---

<div align="center">

**If this project helped you, feel free to give it a star!**

*Made at 42 Paris*

</div>
