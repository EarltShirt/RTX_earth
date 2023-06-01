CXX = g++
CXXFLAGS = -Wall -std=c++17
LDLIBS = -lcurl

# name of your executable
TARGET = my_program

# .cpp files
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

clean:
    rm -f $(TARGET)
