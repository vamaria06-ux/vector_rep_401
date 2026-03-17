CXXFLAGS += -Wall -Wextra -std=c++14 -MMD
-include main.d
main: main.cpp
	$(CXX) $^ -o $@