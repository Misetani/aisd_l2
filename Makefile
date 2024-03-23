CC = g++
CPP_FLAGS = -std=c++20 -g -Wall -Wextra -Werror
LIBS = -lgtest -lgtest_main -lpthread

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)

TEST_DIR = tst
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC:.cpp=.o)))

HEADERS = $(wildcard *.h)

PROGRAM = program
TEST_PROGRAM = test_program

all: run clean

run: $(PROGRAM)
	@./$(PROGRAM) || true

test: clean $(TEST_PROGRAM)
	@./$(TEST_PROGRAM) || true

$(PROGRAM): $(OBJ)
	@$(CC) $(CPP_FLAGS) $(OBJ) -o $(PROGRAM)

$(TEST_PROGRAM): $(TEST_OBJ)
	@$(CC) $(CPP_FLAGS) $(TEST_OBJ) -o $(TEST_PROGRAM) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CPP_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CPP_FLAGS) -c $< -o $@

check: $(OBJ)
	@cppcheck $(SRC) $(HEADERS)

valgrind: $(TEST_PROGRAM)
	@valgrind --leak-check=full ./$(TEST_PROGRAM)

clean:
	@rm -rf $(OBJ_DIR) $(PROGRAM) $(TEST_PROGRAM)