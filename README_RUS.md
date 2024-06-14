# s21_matrix

Реализация библиотеки matrix.h.

В данном проекте Вам предстоит реализовать свою библиотеку для обработки числовых матриц на языке программирования С/C++. Матрицы являются одной из базовых структур данных в программировании, например, они применяются для представления табличных значений, для вычислительных задач и нейронных сетей. В рамках этого проекта предполагается более детальное знакомство с матрицами и закрепление структурного подхода.

## Матрица

Матрица - это набор чисел, расположенных в фиксированном количестве строк и столбцов.
Матрица A - прямоугольная таблица чисел, расположенных в m строках и n столбцах

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

Получить нужный элемент можно при помощи индексов, так
A[1,1] = 1, где первый индекс - номер строки, второй - номер столбца.

Матрица А будет иметь элементы с следующими индексами:

```
    (1,1) (1,2) (1,3)
A = (2,1) (2,2) (2,3)
    (3,1) (3,2) (3,3)
```

Порядок матрицы — это число ее строк или столбцов. \
Главная диагональ квадратной матрицы — это диагональ, идущая из левого верхнего в правый нижний угол. \
Прямоугольная матрица (В) — это матрица, у которой число строк не равно числу столбцов. \
Квадратная матрица (А) — это матрица у которой число строк равно числу столбцов.

Матрица-столбец — это матрица, у которой всего один столбец:

```
    (1,1)
A = (2,1)
    (n,1)
```

Матрица-строка — это матрица, у которой всего одна строка:

```
A = (1,1) (1,2) (1,m)
```

Tip: матрицу-столбец и матрицу-строку ещё часто называют векторами.

Диагональная матрица — это квадратная матрица, у которой все элементы, стоящие вне главной диагонали, равны нулю. \
Единичная матрица — это диагональная матрица, у которой все диагональные элементы равны единице:

```
    1 0 0
A = 0 1 0
    0 0 1
```

Треугольная матрица — это квадратная матрица, у которой все элементы, расположенные по одну сторону главной диагонали, равны нулю.

```
    1 2 3
A = 0 4 5
    0 0 6
```