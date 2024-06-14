CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
CHECKFLAGS = -lgtest -pthread

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(CXX) $(CXXFLAGS) -c s21_matrix_oop.cc -o s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_matrix_oop.o

test: clean s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) s21_matrix_oop.cc test.cc $(CHECKFLAGS) -o test
	./test

gcov_report: clean
	$(CXX) --coverage test.cc s21_matrix_oop.cc $(CXXFLAGS) $(CHECKFLAGS) -o test
	./test
	lcov -t "test" -o  test.info --no-external -c -d  .
	genhtml -o report test.info

clean:
	rm -rf *.o *.a *.g* *.txt
	rm -rf s21_matrix_oop
	rm -rf test.info coverage.info test report

rebuild: clean all

style:
	clang-format -style=google -i *.cc *.h
	clang-format -style=google -n *.cc *.h

21: 
	$(CXX) $(CXXFLAGS) s21_matrix_oop.cc -o s21_matrix_oop
	./s21_matrix_oop
