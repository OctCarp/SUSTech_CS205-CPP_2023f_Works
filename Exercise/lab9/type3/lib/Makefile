OBJ = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = libfunction.so
CXX = g++
LIB_DIR = /usr/lib

$(TARGET): $(OBJ)
	$(CXX) -shared -fPIC $^ -o $@

	sudo cp $(TARGET) $(LIB_DIR)

%.o : %.cpp
	$(CXX) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
	sudo rm -f $(LIB_DIR)/libfunction.so
