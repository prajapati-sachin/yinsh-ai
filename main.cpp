#include <bits/stdc++.h>
#include "board_convert.h"
#include "Board.h"

using namespace std;

int board[11][11];
board_convert b;
vector<pair<int, int> > rings1;
vector<pair<int, int> > rings2;
vector<pair<int, int> > rings[2];
stack<string> initial_moves;
long long node;
// std::ofstream ofs ("te.txt", std::ofstream::out);
std::ofstream ofs ("test.txt", std::ofstream::out);

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

string make_string(pair<pair<int,int>, pair<int,int> > removing_markers ,pair<int,int> remove_ring ,int n);

vector<pair<pair<int,int>,pair<int,int> > > find_removing_markers(Board tempBoard,int player_id,int n,int s){
    vector< pair < pair <int,int>, pair <int,int> > > removing_markers;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};

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

    for(int i=0;i<=2;i++){
        for (int j=st;j<en;j++)
        {
            pair<int,int> corner_point = b.get_corner_point(i,j,n);
            int count=0;
            pair <int,int> start;
            pair <int,int> end;
            int x_const = corner_point.first;
            int y_const = corner_point.second;
            while(tempBoard.get_at_position(x_const,y_const)!=-1&&x_const<lim&&x_const>=0&&y_const<lim&&y_const>=0){

                if(tempBoard.get_at_position(x_const,y_const)==player_id){
                    count++;
                    if(count==1){
                        start=make_pair(x_const,y_const);
                    }
                    if(count==s){
                        end=make_pair(x_const,y_const);
                        removing_markers.push_back(make_pair(start,end));
                        x_const-=s*x_change[i];
                		y_const-=s*y_change[i];
                        
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

void remove_markers(Board &tempBoard , pair < pair <int,int>, pair <int,int> > removing_marker_pair,int n,int s){
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

void place_ring_in_board(Board &tempBoard, pair<int,int> coordinates_in_board,int player_id){
    if(tempBoard.get_at_position(coordinates_in_board.first,coordinates_in_board.second)==0){
        tempBoard.set_at_position(coordinates_in_board.first,coordinates_in_board.second,player_id+2) ;
        
        //output the string
    }else{
        cout << "Invalid Move" << "\n";
    }
}

string move_ring_in_board(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, Board &tempBoard, string &str,bool myMove,int n,int s){
    string st="";
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        tempBoard.set_at_position(coordinates_for_marker.first,coordinates_for_marker.second,player_id);
        tempBoard.set_at_position(coordinates_for_ring.first,coordinates_for_ring.second,player_id+2);
        
        st+="S ";
        pair<int,int> p = b.get_hexagon_point(coordinates_for_marker.first,coordinates_for_marker.second,n);
        st+=to_string(p.first);
        st+=" ";
        st+=to_string(p.second);
        st+=" ";
        st+="M ";
        p=b.get_hexagon_point(coordinates_for_ring.first,coordinates_for_ring.second,n);
        st+=to_string(p.first);
        st+=" ";
        st+=to_string(p.second);
        st+=" ";


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
	        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
	        //cout<<"size: "<<removing_markers.size()<<endl;
	        while(removing_markers.size()!=0){
	    		//cout<<(removing_markers[0].first).first<<","<<(removing_markers[0].first).second<<":"<<(removing_markers[0].second).first<<","<<(removing_markers[0].second).second<<endl;
	            remove_markers(tempBoard,removing_markers[0],n,s);
	            vector<pair <int,int> > temp_rings = tempBoard.get_rings(player_id);
	            pair <int,int> temp_ring = temp_rings[0];
	            remove_ring(tempBoard,temp_ring);

	            tempBoard.set_at_position(temp_ring.first,temp_ring.second,0);
	                //output the string

	            removing_markers = find_removing_markers(tempBoard,player_id,n,s);
	        }

	    }

    }
    else{
        cout << "Invalid Move" << "\n";
    }
    //cout<<s<<endl;
    return st;
}

void make_move(Board &tempBoard, string move, int player_id,int n,int s){
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
        pair<int, int> coordinates_in_board = b.get_2dpoint(hexagon, points_in_hexagon,n);
        string st="aa";//useless
        place_ring_in_board(tempBoard,coordinates_in_board,player_id);

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
                pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker,n);
                pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring,n);
                string st="aa";//useless
                string str = move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,st,false,n,s);


                i+=6;
            }
            else if (tokens[i]=="RS"){
                int hexagon_marker_removal_start= stoi(tokens[i+1]);
                int point_in_hexagon_marker_removal_start= stoi(tokens[i+2]);
                int hexagon_marker_removal_end= stoi(tokens[i+4]);
                int point_in_hexagon_marker_removal_end= stoi(tokens[i+5]);
                int hexagon_ring_removal = stoi(tokens[i+7]);
                int points_in_hexagon_ring_removal = stoi(tokens[i+8]);

                pair<int, int> coordinates_marker_removal_start = b.get_2dpoint(hexagon_marker_removal_start, point_in_hexagon_marker_removal_start,n);
                pair<int, int> coordinates_marker_removal_end = b.get_2dpoint(hexagon_marker_removal_end, point_in_hexagon_marker_removal_end,n);

                pair<int, int> final_ring_removal = b.get_2dpoint(hexagon_ring_removal, points_in_hexagon_ring_removal,n);

                remove_markers(tempBoard,make_pair(coordinates_marker_removal_start,coordinates_marker_removal_end),n,s);
                remove_ring(tempBoard,final_ring_removal);

                i+=9;

            }
        }
    }
}

bool initial_removal(Board &tempBoard,int player_id,string &str,int n,int s){
    vector< pair < pair <int,int>, pair <int,int> > > removing_markers1 = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
    if(removing_markers1.size()==0)
        return false;
    else{
        remove_markers(tempBoard,removing_markers1[0],n,s);
        vector<pair <int,int> > temp_rings1 = tempBoard.get_rings(player_id);
        pair <int,int> temp_ring1 = temp_rings1[0];
        remove_ring(tempBoard,temp_ring1);
        string s1= make_string(removing_markers1[0],temp_ring1,n);
        if(tempBoard.get_ring_count(player_id)==2){
            //Board copy_tempBoard = Board(tempBoard);
            str = s1;
            return true;

        }else{
            vector< pair < pair <int,int>, pair <int,int> > > removing_markers2 = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
            if(removing_markers2.size()==0){
                str = s1;
                return true;
            }
            else{
                remove_markers(tempBoard,removing_markers2[0],n,s);
                vector<pair <int,int> > temp_rings2 = tempBoard.get_rings(player_id);
                pair <int,int> temp_ring2 = temp_rings2[0];
                remove_ring(tempBoard,temp_ring2);
                string s2= make_string(removing_markers2[0],temp_ring2,n);
                if(tempBoard.get_ring_count(player_id)==2){
                    //Board copy_tempBoard = Board(tempBoard);
                    str = s1+s2;
                    return true;
                }else{
                    vector< pair < pair <int,int>, pair <int,int> > > removing_markers3 = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
                    if(removing_markers3.size()==0){
                        str = s1+s2;
                        return true;
                    }
                    else{
                        remove_markers(tempBoard,removing_markers3[0],n,s);
                        vector<pair <int,int> > temp_rings3 = tempBoard.get_rings(player_id);
                        pair <int,int> temp_ring3 = temp_rings3[0];
                        remove_ring(tempBoard,temp_ring3);
                        string s3= make_string(removing_markers3[0],temp_ring3,n);
                        str = s1+s2+s3;
                        return true;
                    }
                }

            }
        }        


        return true;
    }
}

string Max_value_action(Board &tempBoard, int alpha, int beta, int player_id,double remaining_time,int n,int s);
int Max_value(Board &tempBoard, int alpha, int beta, int depth, int player_id,int player_id_for_eval,int n,int s);
int Min_value(Board tempBoard, int alpha, int beta, int depth, int player_id,int player_id_for_eval,int n,int s);
void move_ring_in_board_max(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id,int player_id_for_eval, Board &tempBoard, string &str,int &v,int &alpha,int &beta,int depth,int n,int s);
void move_ring_in_board_min(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id,int player_id_for_eval, Board &tempBoard, string &str,int &v,int &alpha,int &beta,int depth,int n,int s);

string alpha_beta_search(Board &tempBoard,int player_id,double remaining_time,int n,int s){
	
	return Max_value_action(tempBoard,INT_MIN,INT_MAX,player_id,remaining_time,n,s);
}


string Max_value_action(Board &tempBoard, int alpha, int beta, int player_id,double remaining_time,int n,int s){
	int v = INT_MIN;
	string move="";
    int depth = 0;
	vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id,n);
    int size = successors.size();
    // ofs<<"size: "<<size<<endl;
    if(tempBoard.get_marker_count(player_id)+tempBoard.get_marker_count(3-player_id)<4){
        depth=2;
    }else{
        if(n==5){
            if(size>55)
                depth = 3;
            else if(size>33)
                depth = 4;
            else
                depth = 5;
        }else{
            if(s==5){
                if(size>60)
                    depth = 3;
                else if(size>35)
                    depth = 4;
                else
                    depth = 5;
            }else{
                if(size>65)
                    depth = 3;
                else if(size>35)
                    depth = 4;
                else
                    depth = 5;
            }
        }
    }   
    if(remaining_time<30)
        depth=3;
    else if(remaining_time<10)
        depth=2;
    else if(remaining_time<2)
        depth=1;
    //depth = 2;
    ofs<<"depth: "<<depth<<endl;
    ofs<<"size: "<<successors.size()<<endl;
	for(int i=0;i<successors.size();i++){
		Board copy = Board(tempBoard);
		//cout<<successors[i].first.first<<","<<successors[i].first.second <<endl;
		//cout<<copy.get_at_position(5,5)<<endl;
		pair<int,int> coordinates_for_marker = successors[i].first;
		pair<int,int> coordinates_for_ring = successors[i].second;
		move_ring_in_board_max(coordinates_for_marker,coordinates_for_ring,player_id,player_id,copy,move,v,alpha,beta,depth,n,s);
		//cout<<copy.get_at_position(5,5)<<endl;
		if(v >= beta)
			return move;
	}
	return move;
}

int Max_value(Board &tempBoard, int alpha, int beta, int depth, int player_id,int player_id_for_eval,int n,int s){
    node++;
	if(depth==0||tempBoard.isTerminal(n)){
        
		return tempBoard.evaluation(player_id_for_eval,n,s);
    }
	else{
		int v = INT_MIN;
		string str = "";
		vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id,n);
		for(int i=0;i<successors.size();i++){
			Board copy = Board(tempBoard);
			
			pair<int,int> coordinates_for_marker = successors[i].first;
			pair<int,int> coordinates_for_ring = successors[i].second;
			move_ring_in_board_max(coordinates_for_marker,coordinates_for_ring,player_id,player_id_for_eval,copy,str,v,alpha,beta,depth,n,s);
			//v = max(v,Min_value(copy,alpha,beta,depth-1,3-player_id));
			if(v >= beta)
				return v;
			// alpha = max(alpha,v);
		}
		return v;
	}
}

int Min_value(Board tempBoard, int alpha, int beta, int depth, int player_id,int player_id_for_eval,int n,int s){
    node++;
	if(depth==0||tempBoard.isTerminal(n)){
        
		return tempBoard.evaluation(player_id_for_eval,n,s);
    }
	else{
		int v = INT_MAX;
		string str = "";
		vector<pair<pair<int,int>,pair<int,int> > > successors = tempBoard.neighbour(player_id,n);
		for(int i=0;i<successors.size();i++){
			Board copy = Board(tempBoard);
			
			pair<int,int> coordinates_for_marker = successors[i].first;
			pair<int,int> coordinates_for_ring = successors[i].second;
			move_ring_in_board_min(coordinates_for_marker,coordinates_for_ring,player_id,player_id_for_eval,copy,str,v,alpha,beta,depth,n,s);
			//v = min(v,Min_value(copy,alpha,beta,depth-1,3-player_id));
			if(v <= alpha)
				return v;
			//beta = min(beta,v);
		}
		return v;
	}
}

void move_ring_in_board_max(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id,int player_id_for_eval, Board &tempBoard, string &str,int &v,int &alpha,int &beta,int depth,int n,int s){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        // std::ofstream ofs ("test.txt", std::ofstream::out);
        // ofs<<"size: "<<removing_markers1.size()<<endl;
        string a="";
        string s1=move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,a,false,n,s);
        //checking if ring would be removed or not if it is my move
   		//s1="aa";
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers1 = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
        
        //ofs << "lorem ipsum";
        int value=0;
        if(removing_markers1.size()==0){
        	value = Min_value(tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
        	if(v<value){
        		str=s1;
        		v=value;
        	}
            // v = max(v,Min_value(tempBoard,alpha,beta,depth-1,3-player_id));
			if(v >= beta)
				return ;
			alpha = max(alpha,v);
        }
        else{
            if(tempBoard.get_ring_count(player_id)==n-3){
                string s2="";
                Board copy_tempBoard = Board(tempBoard);
                remove_markers(copy_tempBoard,removing_markers1[0],n,s);
                vector<pair <int,int> > temp_rings1 = copy_tempBoard.get_rings(player_id);
                pair <int,int> temp_ring1 = temp_rings1[0];
                remove_ring(copy_tempBoard,temp_ring1);
                s2= make_string(removing_markers1[0],temp_ring1,n);
                value = Min_value(copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
                if(v<value){
                    str=s1+s2;
                    v=value;
                }
                if(v >= beta)
                    return ;
                alpha = max(alpha,v);

            }
            else{
    	        for(int i=0;i<removing_markers1.size();i++){
    	        	for(int j=0;j<tempBoard.get_ring_count(player_id);j++){
    	        		string s2="";
    	        		Board copy_tempBoard = Board(tempBoard);
    	        		remove_markers(copy_tempBoard,removing_markers1[i],n,s);
    	        		vector<pair <int,int> > temp_rings1 = copy_tempBoard.get_rings(player_id);
    		            pair <int,int> temp_ring1 = temp_rings1[j];
    		            remove_ring(copy_tempBoard,temp_ring1);
    		            s2= make_string(removing_markers1[i],temp_ring1,n);
                        vector< pair < pair <int,int>, pair <int,int> > > removing_markers2 = find_removing_markers(copy_tempBoard,player_id,n,s);//markers to be removed
                        if(removing_markers2.size()==0){
                            if(depth > 3)
                                depth = 3;
    			            value = Min_value(copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
    			            if(v<value){
    			            	str=s1+s2;
    			            	v=value;
    			            }
    						if(v >= beta)
    							return ;
    						alpha = max(alpha,v);
    					}
    					else{
                            if(copy_tempBoard.get_ring_count(player_id)==n-3){
                                string s3="";
                                Board copy_copy_tempBoard = Board(copy_tempBoard);
                                remove_markers(copy_copy_tempBoard,removing_markers2[0],n,s);
                                vector<pair <int,int> > temp_rings2 = copy_copy_tempBoard.get_rings(player_id);
                                pair <int,int> temp_ring2 = temp_rings2[0];
                                remove_ring(copy_copy_tempBoard,temp_ring2);
                                s3= make_string(removing_markers2[0],temp_ring2,n);
                                value = Min_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
                                if(v<value){
                                    str=s1+s2+s3;
                                    v=value;
                                }
                                if(v >= beta)
                                    return ;
                                alpha = max(alpha,v);

                            }
                            else{
        					    for(int i=0;i<removing_markers2.size();i++){
        			        		for(int j=0;j<copy_tempBoard.get_ring_count(player_id);j++){
        			        			string s3="";
        				        		Board copy_copy_tempBoard = Board(copy_tempBoard);
        				        		remove_markers(copy_copy_tempBoard,removing_markers2[i],n,s);
        				        		vector<pair <int,int> > temp_rings2 = copy_copy_tempBoard.get_rings(player_id);
        					            pair <int,int> temp_ring2 = temp_rings2[j];
        					            remove_ring(copy_copy_tempBoard,temp_ring2);
        					            s3= make_string(removing_markers2[i],temp_ring2,n);
        			                    vector< pair < pair <int,int>, pair <int,int> > > removing_markers3 = find_removing_markers(copy_copy_tempBoard,player_id,n,s);//markers to be removed
                                        if(removing_markers3.size()==0){
                                            if(depth > 3)
                                                depth = 3;
        						            value=Min_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
        						            if(v<value){
        						            	str=s1+s2+s3;
        						            	v=value;
        						            }
        									if(v >= beta)
        										return ;
        									alpha = max(alpha,v);
        								}else{
        									
											string s4="";
											Board copy_copy_copy_tempBoard = Board(copy_copy_tempBoard);
											remove_markers(copy_copy_copy_tempBoard,removing_markers3[0],n,s);
											vector<pair <int,int> > temp_rings3 = copy_copy_copy_tempBoard.get_rings(player_id);
									        pair <int,int> temp_ring3 = temp_rings3[0];
									        remove_ring(copy_copy_copy_tempBoard,temp_ring3);
									        s4=make_string(removing_markers3[0],temp_ring3,n);
						                    value = Min_value(copy_copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
						        			if(v<value){
						        				str=s1+s2+s3+s4;
						        				v=value;
						        			}
						        			if(v >= beta)
						        				return ;
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

void move_ring_in_board_min(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id,int player_id_for_eval, Board &tempBoard, string &str,int &v,int &alpha,int &beta,int depth,int n,int s){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        string a="";
        string s1=move_ring_in_board(coordinates_for_marker,coordinates_for_ring,player_id,tempBoard,a,false,n,s);
        s1="aa";
        //checking if ring would be removed or not if it is my move
   		//cout<<s1<<endl;
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers1 = find_removing_markers(tempBoard,player_id,n,s);//markers to be removed
        //cout<<"size: "<<removing_markers.size()<<endl;
        int value=0;
        if(removing_markers1.size()==0){
        	value = Max_value(tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
        	if(v>value){
        		str=s1;
        		v=value;
        	}
			if(v <= alpha)
				return ;
			beta = min(beta,v);
        }
        else{
            if(tempBoard.get_ring_count(player_id)==n-3){
                string s2="";
                Board copy_tempBoard = Board(tempBoard);
                remove_markers(copy_tempBoard,removing_markers1[0],n,s);
                vector<pair <int,int> > temp_rings1 = copy_tempBoard.get_rings(player_id);
                pair <int,int> temp_ring1 = temp_rings1[0];
                remove_ring(copy_tempBoard,temp_ring1);
                s2= make_string(removing_markers1[0],temp_ring1,n);
                value = Max_value(copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
                if(v>value){
                    str=s1+s2;
                    v=value;
                }
                if(v <= alpha)
                    return ;
                beta = min(beta,v); 

            }
            else{
    	        for(int i=0;i<removing_markers1.size();i++){
    	        	for(int j=0;j<tempBoard.get_ring_count(player_id);j++){
    	        		string s2="";
    	        		Board copy_tempBoard = Board(tempBoard);
    	        		remove_markers(copy_tempBoard,removing_markers1[i],n,s);
    	        		vector<pair <int,int> > temp_rings1 = copy_tempBoard.get_rings(player_id);
    		            pair <int,int> temp_ring1 = temp_rings1[j];
    		            remove_ring(copy_tempBoard,temp_ring1);
    		            s2= make_string(removing_markers1[i],temp_ring1,n);
                        vector< pair < pair <int,int>, pair <int,int> > > removing_markers2 = find_removing_markers(copy_tempBoard,player_id,n,s);//markers to be removed
                        if(removing_markers2.size()==0){
                            if(depth > 3)
                                depth = 3;
                            value = Max_value(copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
                            if(v>value){
                            	str=s1+s2;
                            	v=value;
                            }
                			if(v <= alpha)
                				return ;
                			beta = min(beta,v);
    					}
    					else{
                            if(copy_tempBoard.get_ring_count(player_id)==n-3){
                                string s3="";
                                Board copy_copy_tempBoard = Board(copy_tempBoard);
                                remove_markers(copy_copy_tempBoard,removing_markers2[0],n,s);
                                vector<pair <int,int> > temp_rings2 = copy_copy_tempBoard.get_rings(player_id);
                                pair <int,int> temp_ring2 = temp_rings2[0];
                                remove_ring(copy_copy_tempBoard,temp_ring2);
                                s3= make_string(removing_markers2[0],temp_ring2,n);
                                value = Max_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
                                if(v>value){
                                    str=s1+s2+s3;
                                    v=value;
                                }
                                if(v <= alpha)
                                    return ;
                                beta = min(beta,v);

                            }
                            else{
        					    for(int i=0;i<removing_markers2.size();i++){
        			        		for(int j=0;j<copy_tempBoard.get_ring_count(player_id);j++){
        				        		string s3="";
        				        		Board copy_copy_tempBoard = Board(copy_tempBoard);
        				        		remove_markers(copy_copy_tempBoard,removing_markers2[i],n,s);
        				        		vector<pair <int,int> > temp_rings2 = copy_copy_tempBoard.get_rings(player_id);
        					            pair <int,int> temp_ring2 = temp_rings2[j];
        					            remove_ring(copy_copy_tempBoard,temp_ring2);
        					            s3= make_string(removing_markers2[i],temp_ring2,n);
        			                    vector< pair < pair <int,int>, pair <int,int> > > removing_markers3 = find_removing_markers(copy_copy_tempBoard,player_id,n,s);//markers to be removed
                                        if(removing_markers3.size()==0){
        			                        if(depth > 3)
                                                depth = 3;
                                            value = Max_value(copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
        			                        if(v>value){
        			                        	str=s1+s2+s3;
        			                        	v=value;
        			                        }
        			            			if(v <= alpha)
        			            				return ;
        			            			beta = min(beta,v);
        								}else{

											string s4="";
											Board copy_copy_copy_tempBoard = Board(copy_copy_tempBoard);
											remove_markers(copy_copy_copy_tempBoard,removing_markers3[0],n,s);
											vector<pair <int,int> > temp_rings3 = copy_copy_copy_tempBoard.get_rings(player_id);
									        pair <int,int> temp_ring3 = temp_rings3[0];
									        remove_ring(copy_copy_copy_tempBoard,temp_ring3);
									        s4=make_string(removing_markers3[0],temp_ring3,n);
						                    value = Max_value(copy_copy_copy_tempBoard,alpha,beta,depth-1,3-player_id,player_id_for_eval,n,s);
						        			if(v>value){
						        				str=s1+s2+s3+s4;
						        				v=value;
						        			}
			                    			if(v <= alpha)
			                    				return ;
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

string make_string(pair<pair<int,int>, pair<int,int> > removing_markers ,pair<int,int> remove_ring,int n){
	string st="";
	st+="RS ";
	pair<int,int> p = b.get_hexagon_point(removing_markers.first.first,removing_markers.first.second,n);
    st+=to_string(p.first);
    st+=" ";
    st+=to_string(p.second);
    st+=" ";
    st+="RE ";
	p = b.get_hexagon_point(removing_markers.second.first,removing_markers.second.second,n);
    st+=to_string(p.first);
    st+=" ";
    st+=to_string(p.second);
    st+=" ";
	st+="X ";
	p = b.get_hexagon_point(remove_ring.first,remove_ring.second,n);
    st+=to_string(p.first);
    st+=" ";
    st+=to_string(p.second);
    st+=" ";
    return st;

}

// Sample C++ Code 
int main(int argc, char** argv) {
    // std::ofstream ofs ("test.txt", std::ofstream::out);

    //ofs << "lorem ipsum";

  	clock_t start = clock();
    // cout << sizeof(b) << "\n";
    // cout << "num of hexagons"<< b.no_of_hexagons(n) << "\n";
    // cout << "num of points in hex 2" << b.points_in_hexagon_i(2,n) << "\n";
    // initialize_board();
    inital_moves_initialize();
    double time_taken_by_other_player;

    // // cout << "alright" << "\n";
    
    int player_id, n, time_limit, s;
    string move;
    // // Get input from server about game specifications
    cin >> player_id >> n >> time_limit >> s;

    Board board = Board(n);
    if(player_id == 2) {
        // Get other player's move        
        move.clear();
        clock_t start1 = clock();
        while(move.size()==0){
        	getline(cin, move);
    	}
        clock_t end1 = clock();
        time_taken_by_other_player  += double(end1-start1)/CLOCKS_PER_SEC;
        make_move(board, move, 1,n,s);   
        int ring_move=0;
        while(true) {
            //OUTPUT YOUR MOVE
            string s_out="";
            if(ring_move<n){
               // cout << "I am here\n"; 
                string temp = initial_moves.top();
                initial_moves.pop();

                vector<string> tokens;
			    stringstream stream1(temp);
			    string tempo;
			    while(stream1 >> tempo){
			        tokens.push_back(tempo);
			    }

                pair<int, int> inposition = make_pair(stoi(tokens[1]), stoi(tokens[2]));
                pair<int, int> inboard = b.get_2dpoint(inposition.first, inposition.second,n);
                if(board.get_at_position(inboard.first, inboard.second)==0){
                    // place the ring
                    board.set_at_position(inboard.first, inboard.second, 4);
                    //output
                    // cerr<<temp << "\n";
                    cout << temp << "\n";

                }
                else{
                    //ring_move--;
                    continue;
                }
                //SIMPLY PLACE A RING                
                ring_move++;
            }
            else{
                clock_t current = clock();
                double elapsed_time = double(current-start)/CLOCKS_PER_SEC;
                double remaining_time = time_limit-(elapsed_time- time_taken_by_other_player) ;
                // cout << "Elapsed Time: " << elapsed_time << "Remaining Time" << remaining_time << endl;
                ofs<<"remaining_time: "<<remaining_time<<endl;
                //OUTPUT MAIN MOVE
                string s_initial ="";
                bool initial_remove = initial_removal(board,player_id,s_initial,n,s);
                s_out = alpha_beta_search(board,player_id,remaining_time,n,s);
                s_out.pop_back();//delete last space
                if(initial_remove && !board.isTerminal(n)){
                    cout<<s_initial<<s_out<<endl;
                }
                else if(initial_remove && board.isTerminal(n)){
                	cout<<s_initial<<endl;	
                }
                else{
                    cout<<s_out<<endl;
                }
                //std::ofstream ofs ("test.txt", std::ofstream::out);
                ofs<<"node: "<<node<<endl;
                node=0;
                
            	///////////////////////////////////////////////////////////////////////////////////////// 
		        //MAKE THAT MOVE IN YOUR BOARD
		        make_move(board, s_out, player_id,n,s);
		        if(board.isTerminal(n))
            		break;
            }
            
            /////////////////////////////////////////////////////////////////////////////////////////
            //GET OTHER PLAYERS MOVE
            start1 = clock();
            getline(cin, move);
            end1 = clock();
            time_taken_by_other_player  += double(end1-start1)/CLOCKS_PER_SEC;
            make_move(board, move, 1,n,s);
            if(ring_move==n){
            	if(board.isTerminal(n)){
            		break;
            	}
            }
        }
    }   
    else if(player_id == 1) {
        int ring_move=0;
        // cout << "I am here\n"; 

        while(true){
            //OUTPUT YOUR MOVE
            string s_out="";
            if(ring_move<n){
                // cout << "I am here\n"; 
                string temp = initial_moves.top();
                initial_moves.pop();

                vector<string> tokens;
			    stringstream stream1(temp);
			    string tempo;
			    while(stream1 >> tempo){
			        tokens.push_back(tempo);
			    }

                pair<int, int> inposition = make_pair(stoi(tokens[1]), stoi(tokens[2]));
                pair<int, int> inboard = b.get_2dpoint(inposition.first, inposition.second,n);
                if(board.get_at_position(inboard.first, inboard.second)==0){
                    // place the ring
                    board.set_at_position(inboard.first, inboard.second, 3);
                    //output
                    // cerr<<temp << "\n";
                    cout << temp << endl;
                }
                else{
                    // ring_move--;
                    continue;
                }
                //SIMPLY PLACE A RING                
                ring_move++;
            }
            else{
                clock_t current = clock();
                double elapsed_time = double(current-start)/CLOCKS_PER_SEC;
                double remaining_time = time_limit-(elapsed_time - time_taken_by_other_player) ;
                // cout << "Elapsed Time: " << elapsed_time << "Remaining Time" << remaining_time << endl;
                ofs<<"remaining_time: "<<remaining_time<<endl;
                //OUTPUT MAIN MOVE
                string s_initial ="";
                bool initial_remove = initial_removal(board,player_id,s_initial,n,s);
                s_out = alpha_beta_search(board,player_id,remaining_time,n,s);
                s_out.pop_back();//delete last space
                if(initial_remove && !board.isTerminal(n)){
                    cout<<s_initial<<s_out<<endl;
                }
                else if(initial_remove && board.isTerminal(n)){
                	cout<<s_initial<<endl;	
                }
                else{
                    cout<<s_out<<endl;
                }
                ofs<<"node: "<<node<<endl;
                node=0;
            	///////////////////////////////////////////////////////////////////////////////////////// 
	            //MAKE THAT MOVE IN YOUR BOARD
	            make_move(board, s_out, player_id,n,s);
	            if(board.isTerminal(n))
	            	break;

            }
            
            /////////////////////////////////////////////////////////////////////////////////////////
            //GET OTHER PLAYERS MOVE
            move.clear();
            clock_t start1 = clock();
            while(move.size()==0){
            	getline(cin, move);
        	}
            clock_t end1 = clock();
            time_taken_by_other_player  += double(end1-start1)/CLOCKS_PER_SEC;
            make_move(board, move, 3-player_id,n,s); 
            if(ring_move==n){
            	if(board.isTerminal(n))
            		break;
            }
            
        }
    }


    return 0;
}