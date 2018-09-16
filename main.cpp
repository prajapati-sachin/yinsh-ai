#include <iostream>
#include "board_convert.h"
#include "Board.h"

using namespace std;

int board[11][11];
board_convert b;
vector<pair<int, int> > rings1;
vector<pair<int, int> > rings2;
vector<pair<int, int> > rings[2];
stack<string> initial_moves;
/*
Not in board: -1
Empty Position: 0
Orange Marker: 1 -> playerid 1
Blue Marker: 2 -> playerid 2
Orange Ring: 3 -> playerid 1
Blue Ring: 4  -> playerid 2
*/



void inital_moves_initialize(){
    initial_moves.push("P 1 5");
    initial_moves.push("P 1 1");
    initial_moves.push("P 1 4");
    initial_moves.push("P 1 3");
    initial_moves.push("P 1 0");
    initial_moves.push("P 2 11");
    initial_moves.push("P 2 9");
    initial_moves.push("P 2 7");
    initial_moves.push("P 2 5");
    initial_moves.push("P 2 3");
    initial_moves.push("P 2 1");
    initial_moves.push("P 0 0");
}


vector<pair<pair<int,int>,pair<int,int> > > find_removing_markers(Board tempBoard,int player_id){
    vector< pair < pair <int,int>, pair <int,int> > > removing_markers;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};
    for(int i=0;i<2;i++){
        for (int j=1;j<10;j++)
        {
            pair<int,int> corner_point = b.get_corner_point(i,j);
            int count=0;
            pair <int,int> start;
            pair <int,int> end;
            int x_const = corner_point.first;
            int y_const = corner_point.second;
            while(tempBoard.get_at_position(x_const,y_const)!=-1&&x_const<11&&x_const>=0&&y_const<11&&y_const>=0){

                if(tempBoard.get_at_position(x_const,y_const)==player_id){
                    count++;
                    if(count==1){
                        start=make_pair(x_const,y_const);
                    }
                    if(count==5){
                        end=make_pair(x_const,y_const);
                        removing_markers.push_back(make_pair(start,end));
                        x_const-=5*x_change[i];
                		y_const-=5*y_change[i];
                        
                    }
                }else{
                    count=0;
                }

                x_const+=x_change[i];
                y_const+=y_change[i];
                }

        }
    }
    return removing_markers;
}

void remove_markers(Board &tempBoard , pair < pair <int,int>, pair <int,int> > removing_marker_pair){
    pair<int,int> start=removing_marker_pair.first;
    pair<int,int> end = removing_marker_pair.second;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};
    int j,k=1;
    if(start.first==end.first){
        j=1;
        if(start.second<end.second)
            k=0;
    }
    else if(start.second==end.second){
        j=0;
        if(start.first<end.first)
            k=0;
    }
    else{
        j=2;
        if(start.first<end.first)
            k=0;
    }
    //cout<<"new j: "<<j<<" k: "<<k<<endl;
    int counter1 = start.first;
    int counter2 = start.second;
    while(!(counter1==end.first&&counter2==end.second)){
        tempBoard.set_at_position(counter1,counter2,0);
        if(k==0){
            counter1+=x_change[j];
            counter2+=y_change[j];
        }else{
            counter1-=x_change[j];
            counter2-=y_change[j];
        }                      
    }
    tempBoard.set_at_position(counter1,counter2,0);

}

void remove_ring(Board &tempBoard , pair <int,int>  removing_ring){
	tempBoard.set_at_position(removing_ring.first,removing_ring.second,0);
}

void place_ring_in_board(pair<int,int> coordinates_in_board,int player_id, Board &tempBoard, string str){
    if(tempBoard.get_at_position(coordinates_in_board.first,coordinates_in_board.second)==0){
        tempBoard.set_at_position(coordinates_in_board.first,coordinates_in_board.second,player_id+2) ;
        
        //output the string
    }else{
        cout << "Invalid Move" << "\n";
    }
}

void move_ring_in_board(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, Board &tempBoard, string str,bool myMove){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        tempBoard.set_at_position(coordinates_for_marker.first,coordinates_for_marker.second,player_id);
        tempBoard.set_at_position(coordinates_for_ring.first,coordinates_for_ring.second,player_id+2);


        //flip the markers
        int x_change[] = {1, 0, 1};
        int y_change[] = {0, 1,-1};
        int j,k=1;
        if(coordinates_for_marker.first==coordinates_for_ring.first){
            j=1;
            if(coordinates_for_marker.second<coordinates_for_ring.second)
                k=0;
        }
        else if(coordinates_for_marker.second==coordinates_for_ring.second){
            j=0;
            if(coordinates_for_marker.first<coordinates_for_ring.first)
                k=0;
        }
        else{
            j=2;
            if(coordinates_for_marker.first<coordinates_for_ring.first)
                k=0;
        }

        //cout<<"j: "<<j<<" k: "<<k<<endl;
        int counter1 = coordinates_for_marker.first;
        int counter2 = coordinates_for_marker.second;
        if(k==0){
            counter1+=x_change[j];
            counter2+=y_change[j];
        }else{
            counter1-=x_change[j];
            counter2-=y_change[j];
        } 

        while(!(counter1==coordinates_for_ring.first&&counter2==coordinates_for_ring.second)){
            if(tempBoard.get_at_position(counter1,counter2)==1)
               tempBoard.set_at_position(counter1,counter2,2); 
            else if(tempBoard.get_at_position(counter1,counter2)==2)
            	tempBoard.set_at_position(counter1,counter2,1);
            if(k==0){
                counter1+=x_change[j];
                counter2+=y_change[j];
            }else{
                counter1-=x_change[j];
                counter2-=y_change[j];
            }                      
        }
        //checking if ring would be removed or not if it is my move
        if(myMove){   
	        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempBoard,player_id);//markers to be removed
	        //cout<<"size: "<<removing_markers.size()<<endl;
	        while(removing_markers.size()!=0){
	    		//cout<<(removing_markers[0].first).first<<","<<(removing_markers[0].first).second<<":"<<(removing_markers[0].second).first<<","<<(removing_markers[0].second).second<<endl;
	            remove_markers(tempBoard,removing_markers[0]);
	            vector<pair <int,int> > temp_rings = tempBoard.get_rings(player_id);
	            pair <int,int> temp_ring = temp_rings[0];
	            remove_ring(tempBoard,temp_ring);

	            tempBoard.set_at_position(temp_ring.first,temp_ring.second,0);
	                //output the string

	            removing_markers = find_removing_markers(tempBoard,player_id);
	        }

	    }

    }
    else{
        cout << "Invalid Move" << "\n";
    }
}

void make_move(Board &tempBoard, string move, int player_id){
    vector<string> tokens;
    stringstream stream1(move);
    string temp;
    while(stream1 >> temp){
        tokens.push_back(temp);
    }

    if(tokens[0]=="P"){
        // place a ring..initial steps
        int hexagon= stoi(tokens[1]);
        int points_in_hexagon= stoi(tokens[2]);
        pair<int, int> coordinates_in_board = b.get_2dpoint(hexagon, points_in_hexagon);
        string s="aa";//useless
        place_ring_in_board(coordinates_in_board,player_id,tempBoard,s);

    }  
    else{
        int i=0;
        while(i<tokens.size()){
            if(tokens[i]=="S"){
                //place a marker at position -> move a ring to new position     
                int hexagon_marker = stoi(tokens[i+1]);
                int point_in_hexagon_for_marker = stoi(tokens[i+2]);
                int hexagon_ring = stoi(tokens[i+4]);
                int point_in_hexagon_for_ring =stoi(tokens[i+5]);
                pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
                pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);
                string s="aa";//useless
                move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,s,false);


                i+=6;
            }
            else if (tokens[i]=="RS"){
                int hexagon_marker_removal_start= stoi(tokens[i+1]);
                int point_in_hexagon_marker_removal_start= stoi(tokens[i+2]);
                int hexagon_marker_removal_end= stoi(tokens[i+4]);
                int point_in_hexagon_marker_removal_end= stoi(tokens[i+5]);
                int hexagon_ring_removal = stoi(tokens[i+7]);
                int points_in_hexagon_ring_removal = stoi(tokens[i+8]);

                pair<int, int> coordinates_marker_removal_start = b.get_2dpoint(hexagon_marker_removal_start, point_in_hexagon_marker_removal_start);
                pair<int, int> coordinates_marker_removal_end = b.get_2dpoint(hexagon_marker_removal_end, point_in_hexagon_marker_removal_end);

                pair<int, int> final_ring_removal = b.get_2dpoint(hexagon_ring_removal, points_in_hexagon_ring_removal);

                remove_markers(tempBoard,make_pair(coordinates_marker_removal_start,coordinates_marker_removal_end));
                remove_ring(final_ring_removal);

                i+=9;

            }
        }
    }
}

pair<pair<int,int>,pair<int,int> > alpha_beta_search(Board &tempBoard,int player_id){
	int depth=1;
	return Max_value_action(tempBoard,INT_MIN,INT_MAX,depth,player_id);
}

pair<pair<int,int>,pair<int,int> > Max_value_action(Board &tempBoard, int alpha, int beta, int depth, int player_id){
	int v = INT_MIN;
	pair<pair<int,int>,pair<int,int> > move;
	vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id);
	for(int i=0;i<successors.size();i++){
		Board copy = Board(tempBoard);
		string str = "aa";
		pair<int,int> coordinates_for_marker = successors[i].first;
		pair<int,int> coordinates_for_ring = successors[i].second;
		move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,copy,str,true);
		if(Min_value(copy,alpha,beta,depth-1,3-player_id)>v){
			v=Min_value(copy,alpha,beta,depth-1,3-player_id);
			move=make_pair(coordinates_for_marker,coordinates_for_ring);
		}
		if(v > beta)
			return move;
		alpha = max(alpha,v);
	}
	return move;
}

int Max_value(Board &tempBoard, int alpha, int beta, int depth, int player_id){
	if(depth==0||tempBoard.isTerminal())
		return tempBoard.evaluation_function();
	else{
		int v = INT_MIN;
		vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id);
		for(int i=0;i<successors.size();i++){
			Board copy = Board(tempBoard);
			string str = "aa";
			pair<int,int> coordinates_for_marker = successors[i].first;
			pair<int,int> coordinates_for_ring = successors[i].second;
			move_ring_in_board_max(coordinates_for_marker,coordinates_for_ring,player_id,copy,str,&v,&alpha,&beta,depth);
			//v = max(v,Min_value(copy,alpha,beta,depth-1,3-player_id));
			if(v > beta)
				return v;
			// alpha = max(alpha,v);
		}
		return v;
	}
}

int Min_value(Board tempBoard, int alpha, int beta, int depth, int player_id){
	if(depth==0||tempBoard.isTerminal())
		return tempBoard.evaluation_function();
	else{
		int v = INT_MAX;
		vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id);
		for(int i=0;i<successors.size();i++){
			Board copy = Board(tempBoard);
			string str = "aa";
			pair<int,int> coordinates_for_marker = successors[i].first;
			pair<int,int> coordinates_for_ring = successors[i].second;
			move_ring_in_board_min(coordinates_for_marker,coordinates_for_ring,player_id,copy,str,&v,&alpha,&beta,depth);
			//v = min(v,Min_value(copy,alpha,beta,depth-1,3-player_id));
			if(v < alpha)
				return v;
			//beta = min(beta,v);
		}
		return v;
	}
}

void move_ring_in_board_max(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, Board &tempBoard, string str,int &v,int &alpha,int &beta,int depth){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,str);
        //checking if ring would be removed or not if it is my move
   
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempBoard,player_id);//markers to be removed
        //cout<<"size: "<<removing_markers.size()<<endl;
        if(find_removing_markers.size()==0){
            v = max(v,Min_value(tempBoard,alpha,beta,depth-1,3-player_id));
			if(v > beta)
				return v;
			alpha = max(alpha,v);
        }
        else{
	        for(int i=0;i<removing_markers.size();i++){
	        	for(int j=0;j<tempBoard.get_ring_count(player_id);j++){
	        		Board copy_tempBoard = Board(tempBoard);
	        		remove_markers(copy_tempBoard,removing_markers[i]);
	        		vector<pair <int,int> > temp_rings = copy_tempBoard.get_rings(player_id);
		            pair <int,int> temp_ring = temp_rings[j];
		            remove_ring(copy_tempBoard,temp_ring);
                    removing_markers = find_removing_markers(copy_tempBoard,player_id);//markers to be removed
                    if(find_removing_markers.size()==0){
			            v = max(v,Min_value(copy_tempBoard,alpha,beta,depth-1,3-player_id));
						if(v > beta)
							return v;
						alpha = max(alpha,v);
					}
					else{
					    for(int i=0;i<removing_markers.size();i++){
			        		for(int j=0;j<copy_tempBoard.get_ring_count(player_id);j++){
				        		Board copy_copy_tempBoard = Board(copy_tempBoard);
				        		remove_markers(copy_copy_tempBoard,removing_markers[i]);
				        		vector<pair <int,int> > temp_rings = copy_copy_tempBoard.get_rings(player_id);
					            pair <int,int> temp_ring = temp_rings[j];
					            remove_ring(copy_copy_tempBoard,temp_ring);
			                    removing_markers = find_removing_markers(copy_copy_tempBoard,player_id);//markers to be removed
                                if(find_removing_markers.size()==0){
						            v = max(v,Min_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id));
									if(v > beta)
										return v;
									alpha = max(alpha,v);
								}else{
									for(int i=0;i<removing_markers.size();i++){
										for(int j=0;j<copy_copy_tempBoard.get_ring_count(player_id);j++){
											Board copy_copy_copy_tempBoard = Board(copy_copy_tempBoard);
											remove_markers(copy_copy_copy_tempBoard,removing_markers[i]);
											vector<pair <int,int> > temp_rings = copy_copy_copy_tempBoard.get_rings(player_id);
									        pair <int,int> temp_ring = temp_rings[j];
									        remove_ring(copy_copy_copy_tempBoard,temp_ring);
						                    v = max(v,Min_value(copy_copy_copy_tempBoard,alpha,beta,depth-1,3-player_id));
						        			if(v > beta)
						        				return v;
						        			alpha = max(alpha,v);
									    }
									}

								}
							}
						}

					}
					
	        	}
	        }
	    }

	    

    }
    else{
        cout << "Invalid Move" << "\n";
    }
}

void move_ring_in_board_min(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, Board &tempBoard, string str,int &v,int &alpha,int &beta,int depth){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,str);
        //checking if ring would be removed or not if it is my move
   
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempBoard,player_id);//markers to be removed
        //cout<<"size: "<<removing_markers.size()<<endl;
        if(find_removing_markers.size()==0){
            v = min(v,Max_value(tempBoard,alpha,beta,depth-1,3-player_id));
			if(v < alpha)
				return v;
			beta = min(beta,v);
        }
        else{
	        for(int i=0;i<removing_markers.size();i++){
	        	for(int j=0;j<tempBoard.get_ring_count(player_id);j++){
	        		Board copy_tempBoard = Board(tempBoard);
	        		remove_markers(copy_tempBoard,removing_markers[i]);
	        		vector<pair <int,int> > temp_rings = copy_tempBoard.get_rings(player_id);
		            pair <int,int> temp_ring = temp_rings[j];
		            remove_ring(copy_tempBoard,temp_ring);
                    removing_markers = find_removing_markers(copy_tempBoard,player_id);//markers to be removed
                    if(find_removing_markers.size()==0){
                        v = min(v,Max_value(copy_tempBoard,alpha,beta,depth-1,3-player_id));
            			if(v < alpha)
            				return v;
            			beta = min(beta,v);
					}
					else{
					    for(int i=0;i<removing_markers.size();i++){
			        		for(int j=0;j<copy_tempBoard.get_ring_count(player_id);j++){
				        		Board copy_copy_tempBoard = Board(copy_tempBoard);
				        		remove_markers(copy_copy_tempBoard,removing_markers[i]);
				        		vector<pair <int,int> > temp_rings = copy_copy_tempBoard.get_rings(player_id);
					            pair <int,int> temp_ring = temp_rings[j];
					            remove_ring(copy_copy_tempBoard,temp_ring);
			                    removing_markers = find_removing_markers(copy_copy_tempBoard,player_id);//markers to be removed
                                if(find_removing_markers.size()==0){
			                        v = min(v,Max_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id));
			            			if(v < alpha)
			            				return v;
			            			beta = min(beta,v);
								}else{
									for(int i=0;i<removing_markers.size();i++){
										for(int j=0;j<copy_copy_tempBoard.get_ring_count(player_id);j++){
											Board copy_copy_copy_tempBoard = Board(copy_copy_tempBoard);
											remove_markers(copy_copy_copy_tempBoard,removing_markers[i]);
											vector<pair <int,int> > temp_rings = copy_copy_copy_tempBoard.get_rings(player_id);
									        pair <int,int> temp_ring = temp_rings[j];
									        remove_ring(copy_copy_copy_tempBoard,temp_ring);
			                                v = min(v,Max_value(copy_copy_copy_tempBoard,alpha,beta,depth-1,3-player_id));
			                    			if(v < alpha)
			                    				return v;
			                    			beta = min(beta,v);
									    }
									}

								}
							}
						}

					}
					
	        	}
	        }
	    }

	    

    }
    else{
        cout << "Invalid Move" << "\n";
    }
}



// Sample C++ Code 
int main(int argc, char** argv) {
    
    // cout << sizeof(b) << "\n";
    // cout << "num of hexagons"<< b.no_of_hexagons() << "\n";
    // cout << "num of points in hex 2" << b.points_in_hexagon_i(2) << "\n";
    initialize_board();
    inital_moves_initialize();

    // cout << "alright" << "\n";
    
    int player_id, board_size, time_limit;
    string move;
    // // Get input from server about game specifications
    // cin >> player_id >> board_size >> time_limit;

    player_id=1;
    if(player_id == 2) {
        // Get other player's move
        getline(cin, move); 
        make_move(move, 1);   
        int ring_move=0;
        while(true) {
            //OUTPUT YOUR MOVE
            if(ring_move<5){
                string temp = initial_moves.top();
                initial_moves.pop();
                pair<int, int> inposition = make_pair(temp.at(2)-'0', temp.at(4)-'0');
                pair<int, int> inboard = b.get_2dpoint(inposition.first, inposition.second);
                if(board[inboard.first][inboard.second]==0){
                    // place the ring
                    board[inboard.first][inboard.second]=4;
                    //output
                    cout << temp << "\n";
                }
                else{
                    ring_move--;
                }
                //SIMPLY PLACE A RING                
                ring_move++;
            }
            else{
                //OUTPUT MAIN MOVE
            }
            ///////////////////////////////////////////////////////////////////////////////////////// 
            //MAKE THAT MOVE IN YOUR BOARD
            
            /////////////////////////////////////////////////////////////////////////////////////////
            //GET OTHER PLAYERS MOVE
            getline(cin, move);
            make_move(move, 1);
        }
    }   
    else if(player_id == 1) {
        int ring_move=0;
                        // cout << "I am here\n"; 

        while(true){
            //OUTPUT YOUR MOVE
            if(ring_move<5){
                // cout << "I am here\n"; 
                string temp = initial_moves.top();
                initial_moves.pop();
                pair<int, int> inposition = make_pair(temp.at(2)-'0', temp.at(4)-'0');
                pair<int, int> inboard = b.get_2dpoint(inposition.first, inposition.second);
                if(board[inboard.first][inboard.second]==0){
                    // place the ring
                    board[inboard.first][inboard.second]=3;
                    //output
                    cout << temp << "\n";
                }
                else{
                    // ring_move--;
                    continue;
                }
                //SIMPLY PLACE A RING                
                ring_move++;
            }
            else{
                //OUTPUT MAIN MOVE
                
            }
            ///////////////////////////////////////////////////////////////////////////////////////// 
            //MAKE THAT MOVE IN YOUR BOARD
            
            /////////////////////////////////////////////////////////////////////////////////////////
            //GET OTHER PLAYERS MOVE
            getline(cin, move);
            make_move(move, 2); 
            
        }
    }

    // make_move("P 0 0", 1);
    // make_move("S 0 0 M 1 1", 1);
    // cout << "No. of player1 rings: "<<rings1.size() << "\n";
    // cout << "Position: " << rings1[0].first << " " << rings1[0].second << "\n";
    // vector<pair<int,int> > n = neighbour(1);
    // cout << "No. of neighbours: "<<n.size() << "\n";
    // for(int i=0;i<n.size();i++){
    //     cout << "Neighbour " << i+1 << ": "<< "Hexagon: "<<b.get_hexagon_point(n[i].first, n[i].second).first << " - Point: "<<b.get_hexagon_point(n[i].first, n[i].second).second <<"\n";
    // }

    // cout << "At center: " << board[5][5] << "\n";
    // cout << "Ring: " << board[6][5] << "\n";

    return 0;
}