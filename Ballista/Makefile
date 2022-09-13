CXX := clang++
CXXFLAGS := -std=c++20 -I.. -ggdb
WARNING := -Wall -Wextra -pedantic
LDLIBS := -lSDL2 -lSDL2_ttf -lSDL2_image
GAMELIB := ../DynamoEngine/DynamoEngineLib.a

EXE := ballista

SRCS := $(shell find . -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(GAMELIB) $(LDLIBS)

%.o: %.cpp %.hpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE) *.log