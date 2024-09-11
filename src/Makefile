CC=g++ -std=c++17
CFLAGS=-Wall -Wextra -Werror
FLAG_COV=--coverage -fprofile-arcs -ftest-coverage
TESTS_TETRIS=tests/tetris/*_test.cc
TESTS_SNAKE=tests/snake/*_test.cc
VALGRIND_FLAGS=--tool=memcheck --track-origins=yes
NCURSES=-lncurses
DOCS_FOLDER=doxygen
CLI=gui/cli/
BUILDER=qmake

SOURCES_COMMON=brick_game/common/*.cc
SOURCES_TETRIS=brick_game/tetris/model/*.cc $(SOURCES_COMMON)
SOURCES_SNAKE=brick_game/snake/model/*.cc brick_game/snake/controller.cc $(SOURCES_COMMON)

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	TEST_LIBS_C=-lcheck -lsubunit -pthread -lrt -lm -lrt
	TEST_LIBS_CC=-lgtest -lgtest_main -lpthread
else
	TEST_LIBS_C=`pkg-config --cflags --libs check` -lm
	TEST_LIBS_CC=-lgtest -lgtest_main -pthread
endif

.PHONY: all mkdir_build install install_cli install_desktop tertis.a snake.a uninstall dvi dist test test_snake test_tetris gcov_report format clean

all: clean install

mkdir_build:
	mkdir build
	touch build/snake_record.txt
	touch build/tetris_record.txt

install: clean mkdir_build tetris.a snake.a install_cli install_desktop

install_cli:
	$(CC) $(CFLAGS) main.cc $(CLI)*.cc -o build/brickgame_cli $(NCURSES) -L./build -ltetris -lsnake

install_desktop:
	mkdir gui/desktop/build/
	cd gui/desktop/build && $(BUILDER) ../desktop.pro && $(MAKE)
	mv gui/desktop/build/desktop.app build/

cli:
	@./build/brickgame_cli

snake.a:
	$(CC) $(CFLAGS) -c $(SOURCES_SNAKE)
	ar rc libsnake.a *.o
	rm *.o
	mv libsnake.a build/

tetris.a:
	$(CC) $(CFLAGS) -c $(SOURCES_TETRIS)
	ar rc libtetris.a *.o 
	rm *.o
	mv libtetris.a build/

uninstall:
	rm -rf build/

dvi:
	@doxygen
	@open $(DOCS_FOLDER)/html/index.html

dist: clean
	mkdir -p dist
	tar -czvf brick_game.tar Makefile Doxyfile ./brick_game/* ./gui/* ./img/* ../README.md ./tests/* main.cc
	mv brick_game.tar dist/

test: clean mkdir_build test_tetris test_snake

test_snake:
	$(CC) $(CFLAGS) -o test_snake tests/snake/test_entry.cc $(TESTS_SNAKE) $(SOURCES_SNAKE) $(FLAG_COV) $(TEST_LIBS_CC)
	leaks -atExit -- ./test_snake

test_tetris:
	$(CC) $(CFLAGS) -o test_tetris tests/tetris/main.cc $(TESTS_TETRIS) $(SOURCES_TETRIS) $(FLAG_COV) $(TEST_LIBS_C)
	leaks -atExit -- ./test_tetris

gcov_report: test
	lcov --no-external -c -d . -o gcov.info --ignore-errors inconsistent,inconsistent --filter range
	genhtml gcov.info -o gcov_report --ignore-errors inconsistent,inconsistent
	open gcov_report/index.html

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i $(TESTS_TETRIS) $(TESTS_SNAKE) tests/tetris/*.h tests/snake/*.h $(SOURCES_TETRIS) $(SOURCES_SNAKE) brick_game/tetris/*.h brick_game/tetris/model/*.h brick_game/snake/*.h brick_game/snake/model/*.h gui/cli/*.h gui/cli/*.cc gui/desktop/*.cpp gui/desktop/*.h main.cc
	@clang-format -n $(TESTS_TETRIS) $(TESTS_SNAKE) tests/tetris/*.h tests/snake/*.h $(SOURCES_TETRIS) $(SOURCES_SNAKE) brick_game/tetris/*.h brick_game/tetris/model/*.h brick_game/snake/*.h brick_game/snake/model/*.h gui/cli/*.h gui/cli/*.cc gui/desktop/*.cpp gui/desktop/*.h main.cc
	@rm .clang-format

clean: uninstall
	rm -rf gcov_report/ doxygen/ dist/
	rm -f *.info test_*
	rm -f *.gcda *.gcno *.gcov *.o *.a *.out
	rm -rf gui/desktop/build/ gui/build-desktop-Desktop_arm_darwin_generic_mach_o_64bit-Debug
	rm -f gui/desktop/qrc_application.cpp gui/desktop/desktop.pro.user gui/desktop/BrickGameButton.ui