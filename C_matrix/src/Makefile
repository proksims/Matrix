CC = gcc
FLAGS = -Wall -Werror -Wextra 

all: clean s21_matrix.a

s21_matrix.a: 
	$(CC) $(FLAGS) -c "s21_matrix.c" "s21_matrix.h"
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

# for linux: -lrt -lm -lsubunit
test: clean s21_matrix.a
	$(CC) $(FLAGS) s21_matrix.c test.c -lcheck  -o test
	./test
	
gcov_report: clean
	$(CC) --coverage test.c s21_matrix.c $(FLAGS) -lcheck -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o *.a *.g* 
	rm -rf s21_matrix
	rm -rf test.info test report test1 test2

rebuild: clean all

style:
	clang-format -style=google -i ./s21_matrix.c
	clang-format -style=google -i ./s21_matrix.h
	clang-format -style=google -i ./test.c
	clang-format -style=google -n ./s21_matrix.c
	clang-format -style=google -n ./s21_matrix.h
	clang-format -style=google -n ./test.c

21: 
	$(CC) $(FLAGS) s21_matrix.c -lm -o s21_matrix
	./s21_matrix