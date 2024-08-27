# Colors for `echo -e`
# WARN : don't put " and use the echo command, not echo -e
LIGHT_ORANGE_COLOR=\e[38;5;216m
TURQUOISE_COLOR=\e[38;5;43m
LIGHT_BLUE_COLOR=\e[38;5;153m
RED_COLOR=\e[38;5;196m
NO_COLOR=\e[0m

# Paths
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# Params and Flags
PERSONAL_FLAGS= -D NDEBUG # use own flags here
ARCHITECTURE_FLAGS = -march=native
COMPILER=g++
LDLIBS=
FLAGS = -I $(INC_DIR) -O3 -std=c++17 -Wall -Wfatal-errors -fopenmp $(ARCHITECTURE_FLAGS) $(PERSONAL_FLAGS)

# Source and Object files
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Generate executable targets for different sizes
sizes = 128 192 256 320 384 448 512
MAIN = tdtsptw $(foreach size,$(sizes),tdtsptw$(size))
MAIN := $(addprefix $(BIN_DIR)/,$(MAIN)) # prefix all MAIN with BIN_DIR

small: $(firstword $(MAIN))
large: $(lastword $(MAIN))
all: dirs $(MAIN)

# set default target : https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified
.DEFAULT_GOAL := default
.PHONY: default build dirs small large all clean clear

default: build

build: dirs small

#$(MAIN): $(BIN_DIR)/%

# Linking target
$(MAIN): $(OBJS)
	$(COMPILER) -o $@ $(if $(filter tdtsptw%,$*),-DMAX_INSTANCE_SIZE=$(subst tdtsptw,,$*),) $^ $(FLAGS) $(LDLIBS)

# compiling main
obj/%.o: src/%.cpp 
	mkdir -p $(dir $@)
	$(COMPILER) -o $@ -c $^ $(FLAGS)

clean:
	@echo -e "$(RED_COLOR)Cleaning compil. files...$(NO_COLOR)"
	rm -rf $(BIN_DIR) $(OBJ_DIR)

dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

# Aliases
clear: clean
