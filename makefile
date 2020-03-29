CC = g++
CFLAGS = -std=c++17 -Wall -O2 -Iinclude -Ivendor
LFLAGS =
LIB = -fopenmp -lsfml-graphics -lsfml-window -lsfml-system

EXE = build/dendrite

SRC_DIR = src
BUILD_DIR = build

SRC := $(shell find $(SRC_DIR) -name '*.cpp' -exec basename {} \;)
OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LFLAGS) $(LIB) -o $@ $^
  
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)/%.d
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LIB) -c -MT $@ -MM -MP -MF $(BUILD_DIR)/$*.d $<
	$(CC) $(CFLAGS) $(LIB) -c -o $@ $<

$(DEP):
include $(wildcard $(DEP))

clean:
	rm -rf $(BUILD_DIR)
