OBJS = $(patsubst %.cpp, %.o , $(wildcard ./*.cpp))
TARGET = type3.out
CXX = g++

LDFLAG = -L./lib
lib = -lfunction

$(TARGET) : $(OBJS)
	$(CXX) $^ $(lib) $(LDFLAG) -o $@

%.o : %.cpp
	$(CXX) -c $^ -o $@

.PHONY : clean
clean:
	rm -rf *.o $(TARGET)
