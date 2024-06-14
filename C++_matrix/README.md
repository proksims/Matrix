# s21_matrix+

Implementation of the s21_matrix_oop.h library.

In this project, you will implement the matrix library that you already know from the **s21_matrix** project, but this time you will be using the object-oriented approach (see materials). The object-oriented approach allows to implement a library for matrices as a separate class whose objects have defined operations, that can be represented both as methods and as standard operators +, -, \*, etc.

### C++ and C

C++ is a programming language based on the C language for implementing programs using an object-oriented approach. This means that the C++ syntax rules are directly derived from C, and so, most of the C code can be copied into programs with C++ and successfully compiled.
For the most part, C++ only adds new opportunities for the programmer or modifies them rather than removes something, so when it comes to C++, it's easier to talk about the differences (see materials) than the similarities.

### An example of a matrix class in C++

```cpp
class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix();              // Default constructor
        ~S21Matrix();             // Destructor

        void SumMatrix(const S21Matrix& other);
        // Other methods..
}
```

## Matrix operations

There is a brief description of the matrix operations below that need to be implemented in the developing library.
They are similar to the operations you performed earlier in «structured programming», so you can see a more detailed description of them there.
Note that some operations have exceptional situations that require special handling using the exception mechanism.

| Operation                                | Description                                                                | Exceptional situations                                                                            |
| ---------------------------------------- | -------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| `bool EqMatrix(const S21Matrix& other)`  | Checks matrices for equality with each other                               |                                                                                                   |
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one                                  | different matrix dimensions                                                                       |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one                              | different matrix dimensions                                                                       |
| `void MulNumber(const double num) `      | Multiplies the current matrix by a number                                  |                                                                                                   |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix                         | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `S21Matrix Transpose()`                  | Creates a new transposed matrix from the current one and returns it        |                                                                                                   |
| `S21Matrix CalcComplements()`            | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square                                                                          |
| `double Determinant()`                   | Calculates and returns the determinant of the current matrix               | the matrix is not square                                                                          |
| `S21Matrix InverseMatrix()`              | Calculates and returns the inverse matrix                                  | matrix determinant is 0                                                                           |

Apart from those operations, you also need to implement constructors and destructors:

| Method                              | Description                                                                |
| ----------------------------------- | -------------------------------------------------------------------------- |
| `S21Matrix()`                       | A basic constructor that initialises a matrix of some predefined dimension |
| `S21Matrix(int rows, int cols) `    | Parametrized constructor with number of rows and columns                   |
| `S21Matrix(const S21Matrix& other)` | Copy constructor                                                           |
| `S21Matrix(S21Matrix&& other)`      | Move constructor                                                           |
| `~S21Matrix()`                      | Destructor                                                                 |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator         | Description                                                 | Exceptional situations                                                                           |
| ---------------- | ----------------------------------------------------------- | ------------------------------------------------------------------------------------------------ |
| `+`              | Addition of two matrices                                    | different matrix dimensions                                                                      |
| `-`              | Subtraction of one matrix from another                      | different matrix dimensions                                                                      |
| `*`              | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`             | Checks for matrices equality (`EqMatrix`)                   |                                                                                                  |
| `=`              | Assignment of values from one matrix to another one         |                                                                                                  |
| `+=`             | Addition assignment (`SumMatrix`)                           | different matrix dimensions                                                                      |
| `-=`             | Difference assignment (`SubMatrix`)                         | different matrix dimensions                                                                      |
| `*=`             | Multiplication assignment (`MulMatrix`/`MulNumber`)         | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)` | Indexation by matrix elements (row, column)                 | index is outside the matrix                                                                      |
