OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = type2.out

CXX = g++
CFALGS = -c -Wall
CXXFLAGS = $(CFALGS) -O3

LDFLAGE = -L ./lib
LIB = -lmyfun

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LIB) $(LDFLAG)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
