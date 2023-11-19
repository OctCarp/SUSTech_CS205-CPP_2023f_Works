SRC_DIR = ./src
SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCE))

TARGET = type1.out
INCLUDE = -I ./inc

CXX = g++
CFALGS = -c -Wall
CXXFLAGS = $(CFALGS) -O3

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCLUDE)

.PHONY: clean
clean:
	rm -rf $(SRC_DIR)/*.o $(TARGET)
