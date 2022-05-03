# compiler
CC = g++

# compiler flags
# -g	debugging information
# -Wall compiler warnings	
CFLAGS = -g -Wall

# build target
TARGET = Response

# build the enhanced Astiri project
all: $(TARGET)

$(TARGET): $(TARGET).cpp Request.cpp Request.hpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp Request.cpp Request.hpp

# delete compiled program
# NOTE: clean recipe is for windows machines, linux machines should use:
# $(RM) $(TARGET)
clean:
	del $(TARGET).exe
