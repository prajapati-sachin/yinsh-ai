#include "Board.h"

using namespace std;

Board::Board(){
	for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            this->board[i][j]=-1;
        }
    }
    int num_hex=b.no_of_hexagons();

    for(int i=0;i<num_hex;i++){
        int num_points=b.points_in_hexagon_i(i);
        for(int j=0;j<num_points;j++){
            pair<int, int> a = b.get_2dpoint(i, j);
            if(a.first!=-1 && a.second!=-1)
                this->board[a.first][a.second]=0;
        }
    }


    this->ring_count[0]=0;
    this->marker_count[0]=0;
    this->ring_count[1]=0;
    this->marker_count[1]=0;
}

Board::Board(Board copy){
	for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            this->board[i][j]=copy.at_position(i,j);
        }
    }

    this->ring_count[0]=copy.get.ring_count[0];
    this->marker_count[0]=copy.get.marker_count[0];
    this->ring_count[1]=copy.get.ring_count[0];
    this->marker_count[1]=copy.get.ring_count[0];
    this->rings[0]=copy.get.rings[0];
    this->rings[1]=copy.get.rings[1];
}

int Board::get_ring_count(int player){
	return this->ring_count[player];
}

int Board::get_marker_count(int player){
	return this->marker_count[player];
}

vector<pair<int, int> > Board::get_ring(int player){
	return rings[player];
}

int Board::at_position(int i,int j){
	return this->board[i][j];
}