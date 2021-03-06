# The project contains 2 folders:
# src: contains all *.cpp source code;
# include: contains all header files.

# Compiler & linker.
CC=g++
# Compile flags.
CFLAGS=-g -c #-std=c++11
# Link flags.
LDFLAGS=
# All header files
HEADERS=$(wildcard include/*.h)
# All source files
SOURCES=$(wildcard src/*.cpp)

# Subsitute every '.cpp' prefix in $(SOURCES) variable with the '.o'.
OBJECTS=$(SOURCES:.cpp=.o)

# The final executable file
EXEC=minbbox

# Build final executable file
all: $(EXEC)
$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# For insurance: if any header file is changed, re-compile the whole project.
%.o:%.cpp $(HEADERS)
	$(CC) $(INCLUDE_PATH) $(CFLAGS) $< -o $@

# Remove executable file and all object files
clean:
	rm -f $(OBJECTS) $(EXEC)