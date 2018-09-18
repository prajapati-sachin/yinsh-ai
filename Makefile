#MakeFile
CXX = g++
CXXFLAGS      = -std=c++11 -O3 	

main:  main.cpp Board.o board_convert.o
	$(CXX) $(CXXFLAGS) main.cpp Board.cpp board_convert.cpp

Board.o: Board.cpp board_convert.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp	

board_convert.o: board_convert.cpp Board.cpp
	$(CXX) $(CXXFLAGS) -c board_convert.cpp	

clean: 
	$(RM) main *.o *~
