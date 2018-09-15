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

vector<pair<int, int> > Board::get_rings(int player){
	return rings[player];
}

int Board::get_at_position(int i,int j){
	return this->board[i][j];
}

void set_at_position(int i,int j,int value){
	int prev_value = this->board[i][j];
	if(prev_value==0){
		if(value==1)
			this->marker_count[0]++;
		else if(value==2)
			this->marker_count[1]++;
		else if(value==3){
			this->ring_count[0]++;
			rings[0].push_back(make_pair(i,j));
		}
		else if(value==4){
			this->ring_count[1]++;
			rings[1].push_back(make_pair(i,j));
		}
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==1){
		this->marker_count[0]--;
		if(value==2)
			this->marker_count[1]++;
		else if(value==0)
			continue;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==2){
		this->marker_count[1]--;
		if(value==1)
			this->marker_count[0]++;
		else if(value==0)
			continue;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==3){
		if(value==1){
			this->marker_count[0]++;
			int find = find_in_vector(rings[0], make_pair(i,j));
			if(find!=-1){
            	this->rings[0].erase(rings1.begin() + find);
            	this->ring_count[0]--;
        	}
		}
		else if(value==0)
			this->ring_count[0]--;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==4){
		if(value==2){
			this->marker_count[1]++;
			int find = find_in_vector(rings[1], make_pair(i,j));
			if(find!=-1){
            	this->rings[1].erase(rings1.begin() + find);
            	this->ring_count[1]--;
        	}
		}
		else if(value==0)
			this->ring_count[1]--;
		else
			cout<<"wrong"<<endl;
	}else{
		cout<<"wrong"<<endl;
	}
	this->board[i][j]=value;
}

int find_in_vector(vector<pair<int, int> > rings, pair<int, int> findit){
    int position=-1;
    for(int i=0;i<rings.size();i++){
        if(rings[i]==findit){
            position=i;
            break;
        }
    }
    return position;
}