#MakeFile
CXX = g++
CXXFLAGS      = -std=c++11 -O3 	

main: main.o Board.o board_convert.o
	$(CXX) -o main main.o Board.o board_convert.o

main.o: main.cpp Board.cpp board_convert.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Board.o: Board.cpp board_convert.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp	

board_convert.o: board_convert.cpp Board.cpp
	$(CXX) $(CXXFLAGS) -c board_convert.cpp	

clean: 
	$(RM) main *.o *~
