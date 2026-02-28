# BC CALCULATOR: my_bc

A small arithmetic expression evaluator written in C.

`my_bc` parses and evaluates integer expressions from the command line using:
- A custom dynamic array
- Dijkstra’s Shunting Yard algorithm
- Reverse Polish Notation (RPN) evaluation

---

## Features

- Integer arithmetic (base 10)
- Operators: `+  -  *  /  %`
- Parentheses: `( )`
- Unary `+` and `-`
- Operator precedence & associativity
- Parse error detection
- AddressSanitizer build target

---

## How It Works

Input → Lexer → Shunting Yard → RPN Evaluation → Result

### Lexer (`lexer.c`)
- Converts input string into tokens
- Detects integers, operators, parentheses
- Handles unary `+` and `-`

### Shunting Yard (`shunting.c`)
- Converts infix expressions into Reverse Polish Notation
- Respects precedence and associativity
- Detects mismatched parentheses

### Evaluator (`eval.c`)
- Uses a stack to evaluate RPN expressions
- Prints the final result

### Dynamic Array (`dynarray.c`)
Minimal vector implementation used for:
- Token storage
- Operator stack
- Evaluation stack

---

## Project Structure

```
include/
    my_bc.h

src/
    main.c
    lexer.c
    shunting.c
    eval.c
    dynarray.c
    error.c

Makefile
```

---

## Build

```bash
make
```

Rebuild:

```bash
make re
```

AddressSanitizer:

```bash
make asan
```

---

## Usage

```bash
./my_bc.exe "EXPRESSION"
```

Examples:

```bash
./my_bc.exe "2+2"
4

./my_bc.exe "2+3*4"
14

./my_bc.exe "(2+3)*4"
20
```

---

## Error Handling

Invalid expressions print:

```
parse error
```

Examples:
- Mismatched parentheses
- Invalid characters
- Incorrect operator placement

---

## Concepts Demonstrated

- Tokenization
- Shunting Yard algorithm
- Stack-based evaluation
- Custom dynamic memory management
- Modular C design