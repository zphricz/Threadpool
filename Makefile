CXXFLAGS = -std=c++14 -Ofast -Wall -Werror
OS = $(shell uname -s)
SRC = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))
DEPS = $(patsubst %.cpp, $(OBJDIR)/%.d, $(SRC))
OBJDIR = objs
ELFNAME = test_threadpool

ifeq ($(OS), Darwin)
	CXX = clang++
endif
ifeq ($(OS), Linux)
	CXX = g++-5
	LDFLAGS += -Wl,--no-as-needed -lpthread
endif

all: $(ELFNAME)

$(ELFNAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o$@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

-include $(DEPS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.d
	rm -f $(ELFNAME)
