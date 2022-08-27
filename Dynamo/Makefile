CXX := clang++
CXXFLAGS := -std=c++20 -I.. -ggdb
WARNING := -Wall -Wextra -pedantic

SRCS := $(shell find . -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

LIBNAME := DynamoLib.a

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIBNAME)

%.o: %.cpp %.hpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -c $< -o $@