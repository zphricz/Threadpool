CXXFLAGS = -std=c++11 -Ofast -Wall -Werror
OS = $(shell uname -s)
SRC = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, objs/%.o, $(SRC))
HEADERS = $(patsubst %.cpp, %.h, $(SRC))
DEPS = $(patsubst %.cpp, objs/%.d, $(SRC))
ELFNAME = threadpool_test

ifeq ($(OS), Darwin)
	CXX = clang++
endif
ifeq ($(OS), Linux)
  CXXFLAGS+= -Wl,--no-as-needed
	CXX = g++
	LDFLAGS = -lpthread
endif

all: $(ELFNAME)

$(ELFNAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o$@ $^ $(LDFLAGS) 

objs/%.o: %.cpp objs
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

objs:
	    mkdir -p objs

-include $(DEPS)

clean:
	rm -f objs/*.o
	rm -f objs/*.d
	rm -f $(ELFNAME)
