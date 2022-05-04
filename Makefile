# compiler
CC = g++

# compiler flags
# -g	debugging information
# -Wall compiler warnings	
CFLAGS = -g -Wall

# build target
TARGET = Response

# build the enhanced Astiri project
all: Response TestSuite

Response: $(TARGET).cpp Request.cpp Request.hpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp Request.cpp Request.hpp

TestSuite: Test1 Test2 Test3 Test4

Test1: $(TARGET)
	$(TARGET) 5 "uri1" 10

Test2: $(TARGET)
	$(TARGET) 10 "uri1" 25

Test3: $(TARGET)
	$(TARGET) 15 "uri2" 50

Test4: $(TARGET)
	$(TARGET) 20 "uri2" 100

# delete compiled program
# NOTE: clean recipe is for windows machines, linux machines should use:
# $(RM) $(TARGET)
clean:
	del $(TARGET).exe

