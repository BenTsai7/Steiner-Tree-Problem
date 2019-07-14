#Running on Windows 10, Mingw-32
CXX = g++
CXXFLAGS = -std=c++11 -g
HEADER_DIR = include
SRC_DIR = src
MAIN = ./bin/main
Graph = Graph.o
ILS = ILS.o
Solution = Solution.o
Union_Find_Set = Union_Find_Set.o
MAINO = main.o
$(MAIN) : $(Graph) $(MAINO) $(ILS) $(Solution) $(Union_Find_Set)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) $^ -o $@
	del /f /s /q *.o
$(Graph) : $(SRC_DIR)/Graph.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(ILS) : $(SRC_DIR)/ILS.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(Solution) : $(SRC_DIR)/Solution.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(Union_Find_Set) : $(SRC_DIR)/Union_Find_Set.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(MAINO) : $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
clean:
	del /s /q *.o
	del /s /q bin