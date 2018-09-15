#include "Board.h"

using namespace std;

Board::Board(){
	for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            board[i][j]=-1;
        }
    }
    int num_hex=b.no_of_hexagons();

    for(int i=0;i<num_hex;i++){
        int num_points=b.points_in_hexagon_i(i);
        for(int j=0;j<num_points;j++){
            pair<int, int> a = b.get_2dpoint(i, j);
            if(a.first!=-1 && a.second!=-1)
                board[a.first][a.second]=0;
        }
    }


    ring_count[0]=0;
    marker_count[0]=0;
    ring_count[1]=0;
    marker_count[1]=0;
}

Board::Board(const Board& copy){
	for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            board[i][j]=copy.board[i][j];//get_at_position(i,j);
        }
    }

    ring_count[0]=copy.ring_count[0];
    marker_count[0]=copy.marker_count[0];
    ring_count[1]=copy.ring_count[1];
    marker_count[1]=copy.ring_count[1];
    rings[0]=copy.rings[0];
    rings[1]=copy.rings[1];
}

int Board::get_ring_count(int player){
	return ring_count[player];
}

int Board::get_marker_count(int player){
	return marker_count[player];
}

vector<pair<int, int> > Board::get_rings(int player){
	return rings[player];
}

int Board::get_at_position(int i,int j){
	return board[i][j];
}

void Board::set_at_position(int i,int j,int value){
	int d=0;
	int prev_value = board[i][j];
	if(prev_value==0){
		if(value==1)
			marker_count[0]++;
		else if(value==2)
			marker_count[1]++;
		else if(value==3){
			ring_count[0]++;
			rings[0].push_back(make_pair(i,j));
		}
		else if(value==4){
			ring_count[1]++;
			rings[1].push_back(make_pair(i,j));
		}
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==1){
		marker_count[0]--;
		if(value==2)
			marker_count[1]++;
		else if(value==0)
			d=1;//continue;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==2){
		marker_count[1]--;
		if(value==1)
			marker_count[0]++;
		else if(value==0)
			d=1;//continue;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==3){
		if(value==1){
			marker_count[0]++;
			int find = find_in_vector(rings[0], make_pair(i,j));
			if(find!=-1){
            	rings[0].erase(rings[0].begin() + find);
            	ring_count[0]--;
        	}
		}
		else if(value==0)
			ring_count[0]--;
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==4){
		if(value==2){
			marker_count[1]++;
			int find = find_in_vector(rings[1], make_pair(i,j));
			if(find!=-1){
            	rings[1].erase(rings[1].begin() + find);
            	ring_count[1]--;
        	}
		}
		else if(value==0)
			ring_count[1]--;
		else
			cout<<"wrong"<<endl;
	}else{
		cout<<"wrong"<<endl;
	}
	board[i][j]=value;
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