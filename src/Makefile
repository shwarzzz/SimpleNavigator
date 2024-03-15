CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
S21_GRAPH_SRC = ./graph/*.cc ./modules/matrix.cc 
S21_ALGORITHM_SRC = ./graph_algorithms/*.cc
TEST_SRC = ./tests/graph_tests.cc
CONSOLE_SRC = ./model/*.cc ./controller/*.cc ./view/*.cc  main.cc
OBJ = *.o
LFLAGS = -lgtest
TARGET = maze
GCOV_FLAGS = --no-external

ifeq ($(shell uname), Linux) 
	LFLAGS += -lpthread
endif

ifeq ($(shell uname), Darwin)
	TARGET = maze.app
	GCOV_FLAGS += --ignore-errors mismatch 
endif

all: s21_navigator

s21_navigator: clean s21_graph.a s21_graph_algorithms.a
	@$(CC) $(CFLAGS) -c $(CONSOLE_SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L. s21_graph.a s21_graph_algorithms.a -o main
	
tests: remove_generated_files s21_graph.a s21_graph_algorithms.a
	@$(CC) $(CFLAGS) -c $(TEST_SRC)
	@$(CC) graph_tests.o $(CFLAGS) $(LFLAGS) -L. s21_graph.a s21_graph_algorithms.a -o test
	@mkdir tests/generated_files
	@chmod a-w tests/test_data/inaccessible.dot
	./test

s21_graph.a:
	$(CC) $(CFLAGS) -c $(S21_GRAPH_SRC)
	ar rcs s21_graph.a $(OBJ)
	ranlib s21_graph.a
	rm -rf *.o

s21_graph_algorithms.a: 
	$(CC) $(CFLAGS) -c $(S21_ALGORITHM_SRC)
	ar rcs s21_graph_algorithms.a $(OBJ) 
	ranlib s21_graph_algorithms.a
	rm -rf *.o 

add_coverage:
	$(eval CFLAGS += --coverage)

gcov_report: clean add_coverage tests
	lcov -t "test" -o test.info -c -d . $(GCOV_FLAGS)
	genhtml -o report test.info
	open report/index.html

check_format:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format -n --style=Google --verbose

formatting:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format -i --style=Google --verbose 

valgrind: clean tests
	valgrind --tool=memcheck --leak-check=full --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

clean: remove_generated_files
	rm -rf *.o *.a *.gcno *.gcda test test.info report main

remove_generated_files:
	rm -rf ./tests/generated_files

PHONY: all tests clean valgrind