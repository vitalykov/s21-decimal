CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -I.
GCOV_FLAG=--coverage
CHECK_LIB_FLAGS=$(shell pkg-config --cflags --libs check)

SRC_DIR=.
DECIMAL_LIB_DIR=decimal_lib
BIG_LIB_DIR=big_lib
BIG_BIG_LIB_DIR=bigbig_lib
TEST_DIR=tests

S21_DECIMAL_SRC=$(shell find $(SRC_DIR) -name "s21_*.c") \
                $(SRC_DIR)/util.c \
                $(shell find $(DECIMAL_LIB_DIR) -name "*.c") \
								$(shell find $(BIG_LIB_DIR) -name "*.c") \
								$(shell find $(BIG_BIG_LIB_DIR) -name "*.c")
S21_DECIMAL_OBJ=$(S21_DECIMAL_SRC:.c=.o)
S21_DECIMAL_LIB=s21_decimal.a

TEST_SRC=$(shell find $(TEST_DIR) -type f -name "test*.c")
TEST_OBJ=$(TEST_SRC:.c=.o)
TEST_EXEC=test

GCOV_DIR=gcov
GCOV_TEST_EXEC=$(addprefix $(GCOV_DIR)/,coverage)
GCOV_COVERAGE_INFO=$(addprefix $(GCOV_DIR)/,full_coverage.info)
GCOV_S21_STRING_INFO=$(addprefix $(GCOV_DIR)/,s21_string_coverage.info)
GCOV_HTML_DIR=html_report

.PHONY: all

all: $(S21_DECIMAL_LIB)

.PHONY: test

$(TEST_EXEC): $(TEST_OBJ) $(S21_DECIMAL_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CHECK_LIB_FLAGS)

$(S21_DECIMAL_LIB): $(S21_DECIMAL_OBJ)
	ar rc $@ $^

.PHONY: gcov_report

gcov_report: $(S21_DECIMAL_SRC) $(TEST_SRC)
	mkdir -p $(GCOV_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAG) -o $(GCOV_TEST_EXEC) $^ $(CHECK_LIB_FLAGS)
	./$(GCOV_TEST_EXEC)
	lcov -t "$(GCOV_TEST_EXEC)" -o $(GCOV_COVERAGE_INFO) -c -d . 
	lcov --extract $(GCOV_COVERAGE_INFO) "*/*_lib/*.c" "*/s21_*.c" "*/util.c" -o $(GCOV_S21_STRING_INFO)
	genhtml $(GCOV_S21_STRING_INFO) -o $(GCOV_HTML_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: rebuild

rebuild: clean all

.PHONY: clean

clean: 
	rm -f $(S21_DECIMAL_OBJ) $(TEST_OBJ) $(TEST_EXEC) $(S21_DECIMAL_LIB)
	rm -rf $(GCOV_DIR) $(GCOV_HTML_DIR)

.PHONY: clang-format

clang-format:
	find . -type f -name "*.[ch]" -exec clang-format -i {} +

.PHONY: cppcheck

cppcheck:
	cppcheck . --enable=all --std=c11 -I . --suppress=missingIncludeSystem
