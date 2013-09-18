OPTIMIZATION?=-O2
CFLAGS?= -std=c99 -Wall 
CFLAGS+= $(OPTIMIZATION)

SRC_DIR=src
TEST_DIR=test
OBJ_DIR=obj

SKADI_TEST_EXE=skadiTest
SKADI_OBJ=skadi.o
TEST_OBJ=test.o tt_test.o

all: test
compile: $(OBJ_DIR)/$(SKADI_OBJ)
compile_test:$(patsubst %,$(OBJ_DIR)/%,$(TEST_OBJ))  

# Compile all & link & execute
test: compile compile_test
	$(CC) -o $(SKADI_TEST_EXE) $(CFLAGS) $(CCLINK) $(OBJ_DIR)/*.o
	./$(SKADI_TEST_EXE)

test-interactif: compile compile_test
	$(CC) -o $(SKADI_TEST_EXE) $(CFLAGS) $(CCLINK) $(OBJ_DIR)/*.o
	./$(SKADI_TEST_EXE) interactif

# Compile src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG) -MMD -c $< -o $@

# Compile test
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG) -MMD -c $< -o $@ -I${TEST_DIR} -I${SRC_DIR}

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm skadiTest
