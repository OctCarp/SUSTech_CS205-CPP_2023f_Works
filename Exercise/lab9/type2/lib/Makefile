OBJ = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = libmyfun.a

CXX = g++
CFALGS = -c -Wall

$(TARGET): $(OBJ)
	ar -r $(TARGET) $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ) $(TARGET)
