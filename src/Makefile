CM = gcc
CFLAGS=-Wall -Werror -Wextra  -std=c11 -O3
GCOV_FLAGS=--coverage #--fprofile-arcs --ftest-coverage
NCURSE= -lncurses

# all, install, uninstall, clean, dvi, dist, test, gcov_report.

DIR= ./game_lib/tetris
DIR_GUI= ./gui/cli

SOURCE= $(foreach dir, $(DIR), $(wildcard $(dir)/*.c))
SOURCE_H=$(foreach dir, $(DIR), $(wildcard $(dir)/*.h))

SOURCE_OBJECTS = $(patsubst %.c, %.o, $(SOURCE))

SOURCE_GUI= $(foreach dir, $(DIR_GUI), $(wildcard $(dir)/*.c))
SOURCE_GUI_H= $(foreach dir, $(DIR_GUI), $(wildcard $(dir)/*.h))
GUI_OBJ= $(patsubst %.c, %.o, $(SOURCE_GUI))

EXECUTABLE_NAME= Tetris_CLI.a

GAME_NAME_EX= Tetris

TEST_DIR= ./tests

TEST_SOURCE= $(foreach dir, $(TEST_DIR), $(wildcard $(dir)/*.c))
TEST_OBJECTS=$(patsubst %.c,%.o, ${TEST_SOURCE})

TEST_EXECUTABLE_NAME=s21_Tetris_CLI_test
ADD_TEST_LIB= -lcheck

GCOV_REPORT_NAME=$(TEST_EXECUTABLE_NAME)_gcovr
REPORT_LIB = gcov_report

ifeq ($(shell uname -s),Linux) # Linux
	ADD_LIB = -lrt -pthread -lsubunit -lm
else
	ADD_LIB =
endif


all: $(EXECUTABLE_NAME) $(TEST_EXECUTABLE_NAME) gcov_report

install: ${EXECUTABLE_NAME} $(GUI_OBJ)
	$(CM) $(CFLAGS) -o $(GAME_NAME_EX)  $(GUI_OBJ) ${EXECUTABLE_NAME} $(NCURSE) 

uninstall:
	rm -rf $(GAME_NAME_EX)

clean_obj:
	rm -rf ${SOURCE_OBJECTS}
	rm -rf ${TEST_OBJECTS}
	rm -rf ${GUI_OBJ}

clean_gcov_test:
	lcov -z -d gcov_report/.
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.gcda
	rm -rf gcov_report/*
	rm -rf $(GCOV_REPORT_NAME)

clean: clean_obj clean_gcov_test
	rm -rf ${EXECUTABLE_NAME}
	rm -rf ${GAME_NAME_EX}
	rm -rf $(TEST_EXECUTABLE_NAME)
	rm -rf doxygen
	rm -rf *.tar
	clear

dvi:
	doxygen
	open doxygen/html/index.html

dist: install
	tar -cf C7_BrickGame_v1.0.tar ${GAME_NAME_EX}


$(EXECUTABLE_NAME): clean_obj $(SOURCE_OBJECTS)
	ar rcs $@ ${SOURCE_OBJECTS}
	ranlib $@

$(SOURCE_OBJECTS):
	$(CM) $(CFLAGS) -c $(patsubst %.o,%.c, $@) -o $@  ${ADD_LIB} 

$(GUI_OBJ):
	$(CM) $(CFLAGS) -c $(patsubst %.o,%.c, $@) -o $@  ${ADD_LIB} 

$(TEST_EXECUTABLE_NAME): $(EXECUTABLE_NAME) ${TEST_OBJECTS}
	${CM} ${CFLAGS}  -o $@  ${TEST_OBJECTS} $(EXECUTABLE_NAME) ${ADD_TEST_LIB} ${ADD_LIB} $(NCURSE) 
	${clean_obj}

${TEST_OBJECTS}:
	$(CM) $(CFLAGS) -c $(patsubst %.o,%.c, $@) -o $@  ${ADD_LIB}

test: clean ${EXECUTABLE_NAME} $(TEST_EXECUTABLE_NAME)
	clear
	./$(TEST_EXECUTABLE_NAME)

gcov_report:
	${CM} ${CFLAGS} ${GCOV_FLAGS} ${SOURCE} ${TEST_SOURCE}  -o ${GCOV_REPORT_NAME} ${ADD_TEST_LIB} ${ADD_LIB} $(NCURSE)
	./${GCOV_REPORT_NAME}
	lcov --capture --test-name "${GCOV_REPORT_NAME}" --output-file ${GCOV_REPORT_NAME}.info --directory .
	genhtml --output-directory $(REPORT_LIB) ${GCOV_REPORT_NAME}.info
	open $(REPORT_LIB)/index.html

format_check: 
	clang-format -n -style=google $(SOURCE) $(SOURCE_GUI_H) $(SOURCE_GUI) $(TEST_SOURCE) tests/*.h

valgrind: test
	clear
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXECUTABLE_NAME)

docker: ../docker
	sh ../docker/run.sh

.PHONY: all install uninstall clean dvi dist test gcov_report ${TEST_OBJECTS} $(TEST_EXECUTABLE_NAME) $(SOURCE_OBJECTS) $(EXECUTABLE_NAME) clean_gcov_test format_check