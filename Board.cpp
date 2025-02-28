#include <bits/stdc++.h>
#include "Board.h"

using namespace std;

Board::Board(int n){



	for(int i=0;i<13;i++){
        for(int j=0;j<13;j++){
            board[i][j]=-1;
        }
    }
    int num_hex=b.no_of_hexagons(n);

    for(int i=0;i<num_hex;i++){
        int num_points=b.points_in_hexagon_i(i,n);
        for(int j=0;j<num_points;j++){
            pair<int, int> a = b.get_2dpoint(i, j,n);
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
	for(int i=0;i<13;i++){
        for(int j=0;j<13;j++){
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
	return ring_count[player-1];
}

int Board::get_marker_count(int player){
	return marker_count[player-1];
}

vector<pair<int, int> > Board::get_rings(int player){

	return rings[player-1];
}

int Board::get_at_position(int i,int j){
	return board[i][j];
}

bool Board::isTerminal(int n){
	bool b1 = this->get_ring_count(1)<=n-3;
	bool b2 = this->get_ring_count(2)<=n-3;
	return b1 || b2;
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
            	rings[0].erase(rings[0].begin()+find);
            	ring_count[0]--;
        	}
		}
		else if(value==0){
			int find = find_in_vector(rings[0], make_pair(i,j));
			if(find!=-1){
            	rings[0].erase(rings[0].begin()+find);
            	ring_count[0]--;
   			}
   		}
		else
			cout<<"wrong"<<endl;
	}else if(prev_value==4){
		if(value==2){
			marker_count[1]++;
			int find = find_in_vector(rings[1], make_pair(i,j));
			if(find!=-1){
            	rings[1].erase(rings[1].begin()+find);
            	ring_count[1]--;
        	}
		}
		else if(value==0){
			int find = find_in_vector(rings[1], make_pair(i,j));
			if(find!=-1){
            	rings[1].erase(rings[1].begin()+find);
            	ring_count[1]--;
        	}
        }
		else
			cout<<"wrong"<<endl;
	}else{
		cout<<"wrong"<<endl;
	}
	board[i][j]=value;
}

vector<pair<pair<int,int>,pair<int,int> > > Board::neighbour( int player_id ,int n){
	int lim;
	if(n==5){
		lim=11;
	}else{
		lim=13;
	}

    vector<pair< pair<int,int> , pair<int,int> > > ans;
    for(int i=0;i<rings[player_id-1].size();i++){
	    pair<int,int> curr_ring = (rings[player_id-1])[i];
	    int x_change[] = {1,-1, 0, 0, 1,-1};
	    int y_change[] = {0, 0, 1,-1,-1, 1};

	    for(int j=0;j<6;j++){
	        int x_cordinate=curr_ring.first+x_change[j];
	        int y_cordinate=curr_ring.second+y_change[j];
	        int c=0;
	        while(board[x_cordinate][y_cordinate]!=-1 && x_cordinate>=0 && x_cordinate<lim && y_cordinate>=0 && y_cordinate<lim ){
	            if(board[x_cordinate][y_cordinate]==0){
	                if(c==0){
	                    ans.push_back(make_pair(curr_ring,make_pair(x_cordinate, y_cordinate)));
	                    x_cordinate+=x_change[j];
	                    y_cordinate+=y_change[j];
	                }else{
	                    ans.push_back(make_pair(curr_ring,make_pair(x_cordinate, y_cordinate)));
	                    break;
	                }
	            }
	            else if(board[x_cordinate][y_cordinate]==1 || board[x_cordinate][y_cordinate]==2){
	                x_cordinate+=x_change[j];
	                y_cordinate+=y_change[j];
	                c=1;
	            }
	            else if(board[x_cordinate][y_cordinate]==3 || board[x_cordinate][y_cordinate]==4){
	                break;
	            }
	        }

	    }

	}

	return ans;

}




int Board::evaluation( int player_id,int n,int s){
    int eval=0;
    eval+= 3000*((ring_count[3-player_id - 1])-(ring_count[player_id - 1]));
    eval+= (marker_count[player_id-1]-marker_count[3-player_id - 1]);
    //int k=0;
    // for(int i=0;i<2;i++){
    // 	for(int j=0;j<10;j++){
    // 		k++;
    // 	}
    // }
    int st,en,lim;
    if(n==5){
        st=1;en=10;lim=11;
    }else{
        if(s==6){
            st=1;en=12;lim=13;
        }
        else{
            st=0;en=13;lim=13;
        }
    }

    int wt1[] = {0,0,2,5,30,200};
    int wt2[] = {0,0,2,5,30,200};
	int count_num = 0;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};
    for(int i=0;i<=2;i++){
        for (int j=st;j<en;j++){
        	pair<int,int> corner_point = b.get_corner_point(i,j,5);
        	int count1=0;
        	int count2=0;
        	int x_const = corner_point.first;
        	int y_const = corner_point.second;
        	while(board[x_const][y_const]!=-1&&x_const<lim&&x_const>=0&&y_const<lim&&y_const>=0){
        		if(board[x_const][y_const]==player_id){
        			count1++;
        			if(count1==s-1){
        				count_num+=wt1[s-1];
        				count1=0;
        			}
        		}else{
        			count_num+=wt1[count1];
        			count1=0;
        		}

        		if(board[x_const][y_const]==3-player_id){
        			count2++;
        			if(count2==s-1){
        				count_num-=wt2[s-1];
        				count2=0;
        			}
        		}else{
        			count_num-=wt2[count2];
        			count2=0;
        		}


        		x_const+=x_change[i];
        		y_const+=y_change[i];
        	}
        }
    }
    eval+= count_num;
    //eval+= this->consecutive_marker(4,player_id)*10;
    // eval-= this->consecutive_marker(4,3-player_id)*10;

    // eval+= this->consecutive_marker(3,player_id)*4;
    // eval-= this->consecutive_marker(3,3-player_id)*4;
    // // srand(time(0)); 
    
    // eval = rand()%100;
    return eval;
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