# ------------------------------------------------------------
#  POSCPP - Layered Architecture Example (Makefile)
#  Builds all layers and produces poscpp executable in target/
# ------------------------------------------------------------

# Compiler & flags
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -I.

# Output directory
TARGET_DIR := target
BIN        := $(TARGET_DIR)/poscpp

# Source files
PRES_SRC   := $(wildcard pres/*.cpp)
DOMAIN_SRC := $(wildcard domain/*.cpp)
DATA_SRC   := $(wildcard data/*.cpp)
MAIN			 := main.cpp

SRCS := $(MAIN) $(PRES_SRC) $(DOMAIN_SRC) $(DATA_SRC)

# Convert: pres/a.cpp → target/pres/a.o
OBJS := $(patsubst %.cpp,$(TARGET_DIR)/%.o,$(SRCS))

# ------------------------------------------------------------
# Default target
# ------------------------------------------------------------
all: $(BIN)

# ------------------------------------------------------------
# Link final executable
# ------------------------------------------------------------
$(BIN): $(OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJS)

# ------------------------------------------------------------
# Compile each cpp file to object file inside target/
# Example: pres/pres.cpp → target/pres/pres.o
# ------------------------------------------------------------
$(TARGET_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Clean
# ------------------------------------------------------------
clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean
