# Matrix Class

A C++ implementation of a matrix class designed for 3D transformation matrices, used in a 3D Viewer project. The class supports basic matrix operations such as addition, subtraction, multiplication, transposition, determinant calculation, and matrix inversion.

## Features
- **Matrix Operations**: Addition (`+`), subtraction (`-`), multiplication (`*`), scalar multiplication, and equality comparison (`==`).
- **Transformation Support**: Designed for 3D Viewer transformations (e.g., rotation, scaling, translation).
- **Error Handling**: Throws `std::invalid_argument` for invalid inputs (e.g., negative dimensions, incompatible matrix sizes).
- **Efficient Memory Management**: Uses `std::vector` for dynamic memory and `std::move` for efficient assignment.
- **Accessors**: Provides safe access to elements via `operator()(int r, int c)` (const and non-const versions).

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/matrix.git
   ```
2. Include xmatrix.h and xmatrix.cc in your C++ project.
3. Compile with a C++11 or later compiler (e.g., g++ -std=c++11).

## Usage
```C++
#include "xmatrix.h"
#include <iostream>

int main() {
  xMatrix::Matrix mat(2, 3);
  mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
  mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

  std::cout << "Original matrix:\n";
  mat.PrintMatrix();

  xMatrix::Matrix transposed = mat.Transpose();
  std::cout << "Transposed matrix:\n";
  transposed.PrintMatrix();

  return 0;
}
```

### Example Output
```C++
Original matrix:
1 2 3
4 5 6

Transposed matrix:
1 4
2 5
3 6
```

## Building and Testing
* Dependencies: Requires a C++11-compliant compiler (e.g., g++, clang++).
* Tests: Unit tests are provided using Google Test (see tests/ directory).
* Build: Use cmake to compile the project (see CMakeLists.txt for details).

Project Structure
* src/xmatrix.h: Header file with class declaration.
* src/xmatrix.cc: Implementation of matrix operations.
* tests/: Unit tests for validating functionality.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for suggestions.

## Licence
MIT License (see LICENSE file).