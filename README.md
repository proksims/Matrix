# s21_matrix

Implementation of the matrix.h library.

In this project you will implement your own library for processing numerical matrices in the C/C++ programming language. Matrices are one of the basic data structures in programming, e.g. they are used to represent table values, for computational tasks and neural networks. As part of the project you will learn more about matrices and solidify knowledge of structured programming.

## Matrix

A matrix is a collection of numbers arranged into a fixed number of rows and columns.

Matrix A is a rectangular table of numbers arranged in m rows and n columns

```
    1 2 3
A = 4 5 6
    7 8 9
```

```
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

You can get the desired element with the help of indices, as follows
A[1,1] = 1, where the first index is the row number, the second is the column number.

Matrix A will have elements with the following indices:

```
    (1,1) (1,2) (1,3)
A = (2,1) (2,2) (2,3)
    (3,1) (3,2) (3,3)
```

The order of a matrix is the number of its rows or columns. \
The main diagonal of a square matrix is the diagonal from the upper left to the lower right corner. \
A rectangular matrix (B) is a matrix with the number of rows not equal to the number of columns. \
A square matrix (A) is a matrix with the number of rows equal to the number of columns.

A column matrix is a matrix with only one column:

```
    (1,1)
A = (2,1)
    (n,1)
```

A row matrix is a matrix that has only one row:

```
A = (1,1) (1,2) (1,m)
```

Tip: A column matrix and a row matrix are also often called vectors.

A diagonal matrix is a square matrix in which all elements outside the main diagonal are zero. \
An identity matrix is a diagonal matrix with all diagonal elements equal to one:

```
    1 0 0
A = 0 1 0
    0 0 1
```

A triangular matrix is a square matrix with all elements on one side of the main diagonal equal to zero.

```
    1 2 3
A = 0 4 5
    0 0 6
```
