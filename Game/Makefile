CXX := clang++
CXXFLAGS := -std=c++20 -I.. -ggdb
WARNING := -Wall -Wextra -pedantic
LDLIBS := -lSDL2 -lSDL2_ttf -lSDL2_image
GAMELIB := ../Lib/CannonLaunchLib.a

SRCS := $(shell find . -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

cannonlaunch: $(OBJS) $(GAMELIB)
	$(CXX) -o $@ $^ $(LDLIBS)

%.o: %.cpp %.hpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) cannonlaunch *.log