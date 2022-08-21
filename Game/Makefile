CXX := clang++
CXXFLAGS := -std=c++20 -I.. -ggdb
WARNING := -Wall -Wextra -pedantic
LDLIBS := ../Lib/CannonLaunchLib.a -lSDL2 -lSDL2_ttf -lSDL2_image

SRCS := $(shell find . -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

cannonlaunch: $(OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)

run: cannonlaunch
	./cannonlaunch

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) cannonlaunch *.log