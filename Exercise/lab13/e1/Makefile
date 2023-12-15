CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = l13e1.out

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean:
	rm -f $(OBJS) $(EXEC)