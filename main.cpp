#include <iostream>
#include "board_convert.h"
#include "Board.h"

using namespace std;

int board[11][11];
board_convert b;
vector<pair<int, int> > rings1;
vector<pair<int, int> > rings2;
vector<pair<int, int> > rings[2];

/*
Not in board: -1
Empty Position: 0
Orange Marker: 1 -> playerid 1
Blue Marker: 2 -> playerid 2
Orange Ring: 3 -> playerid 1
Blue Ring: 4  -> playerid 2
*/






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

void remove_rings(Board &tempBoard , pair < pair <int,int>, pair <int,int> > removing_marker_pair){
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

void place_ring_in_board(pair<int,int> coordinates_in_board,int player_id, Board &tempBoard, string str){
    if(tempBoard.get_at_position(coordinates_in_board.first,coordinates_in_board.second)==0){
        tempBoard.set_at_position(coordinates_in_board.first,coordinates_in_board.second,player_id+2) ;
        
        //output the string
    }else{
        cout << "Invalid Move" << "\n";
    }
}

void move_ring_in_board(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, Board &tempBoard, string str){
    if(tempBoard.get_at_position(coordinates_for_marker.first,coordinates_for_marker.second)==player_id+2 && tempBoard.get_at_position(coordinates_for_ring.first,coordinates_for_ring.second)==0){
        tempBoard.set_at_position(coordinates_for_marker.first,coordinates_for_marker.second,player_id);
        tempBoard.set_at_position(coordinates_for_ring.first,coordinates_for_ring.second,player_id+2);
        // int find = find_in_vector(temp_rings[player_id-1], coordinates_for_marker);
        // if(find!=-1){
        //     rings1.erase(rings1.begin() + find);
        // }
        // else{
        //     cout << "Invalid Move" << "\n";       
        // }
        // temp_rings[player_id-1].push_back(coordinates_for_ring);

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
        //checking if ring would be removed or not
            
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempBoard,player_id);//markers to be removed
        //cout<<"size: "<<removing_markers.size()<<endl;
        while(removing_markers.size()!=0){
    		//cout<<(removing_markers[0].first).first<<","<<(removing_markers[0].first).second<<":"<<(removing_markers[0].second).first<<","<<(removing_markers[0].second).second<<endl;
            remove_rings(tempBoard,removing_markers[0]);
            vector<pair <int,int> > temp_rings = tempBoard.get_rings(player_id);
            pair <int,int> temp_ring = temp_rings[0];

            tempBoard.set_at_position(temp_ring.first,temp_ring.second,0);
                //output the string

            removing_markers = find_removing_markers(tempBoard,player_id);
        }


    }
    else{
        cout << "Invalid Move" << "\n";
    }
}



void make_move(string move, int player_id){
    if(move.at(0)=='P'){
        // place a ring..initial steps
        int hexagon= move.at(2)-'0';
        int points_in_hexagon= move.at(4)-'0';
        pair<int, int> coordinates_in_board = b.get_2dpoint(hexagon, points_in_hexagon);
        int value_at_board = board[coordinates_in_board.first][coordinates_in_board.second];        
        if(value_at_board==0){
            if(player_id==1){
                // Ring of player 1
                board[coordinates_in_board.first][coordinates_in_board.second] = 3;
                rings1.push_back(coordinates_in_board);
            }
            else if(player_id==2){
                // Ring of player 2
                board[coordinates_in_board.first][coordinates_in_board.second] = 4;
                rings2.push_back(coordinates_in_board);
            }
            else{
                cout << "Invalid Move" << "\n";    
            }
        }
        else{
            cout << "Invalid Move" << "\n";
        }
    }
    else if(move.at(0)=='S'){
        if(move.length()<12){
            //place a marker at position -> move a ring to new position     
            int hexagon_marker = move.at(2)-'0';
            int point_in_hexagon_for_marker = move.at(4)-'0';
            int hexagon_ring = move.at(8)-'0';
            int point_in_hexagon_for_ring = move.at(10)-'0';
            pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
            pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);
            if(player_id==1){
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==3 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    board[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                // ALSO HAVE TO FLIP THE RINGS
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
            }
            
            else if(player_id==2){
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==4 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]=2;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]=4;
                    //change the position in rings1
                    int find = find_in_vector(rings2, coordinates_for_marker);
                    if(find!=-1){
                        rings2.erase(rings2.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings2.push_back(coordinates_for_ring);
                }
                // ALSO HAVE TO FLIP THE RINGS
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
            }
            
            else{
                cout << "Invalid Move" << "\n";    
            }

        }
        
        else{
            //place a marker at a position -> move a ring to a given position -> remove a row of 5 markers -> remove a ring 
            int hexagon_marker = move.at(2)-'0';
            int point_in_hexagon_for_marker = move.at(4)-'0';
            int hexagon_ring = move.at(8)-'0';
            int point_in_hexagon_for_ring = move.at(10)-'0';
            int hexagon_marker_removal_start= move.at(12)-'0';
            int point_in_hexagon_marker_removal_start= move.at(14)-'0';
            int hexagon_marker_removal_end= move.at(18)-'0';
            int point_in_hexagon_marker_removal_end= move.at(20)-'0';
            int hexagon_ring_removal = move.at(24)-'0';
            int points_in_hexagon_ring_removal = move.at(26)-'0';
            
            pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
            pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);

            pair<int, int> coordinates_marker_removal_start = b.get_2dpoint(hexagon_marker_removal_start, point_in_hexagon_marker_removal_start);
            pair<int, int> coordinates_marker_removal_end = b.get_2dpoint(hexagon_marker_removal_end, point_in_hexagon_marker_removal_end);

            pair<int, int> final_ring_removal = b.get_2dpoint(hexagon_ring_removal, points_in_hexagon_ring_removal);

            if(player_id==1){
                //MOVE THE RING AND PLACE THE MARKER
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==3 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                //
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
                // REMOVE THE ROW
                    if(coordinates_marker_removal_start.first==coordinates_marker_removal_end.first){
                        //x coordinates of both are same hence remove along y direction
                        if(coordinates_marker_removal_start.second>coordinates_marker_removal_end.second){
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                board[coordinates_marker_removal_start.first][counter]=0;
                                counter--;
                            }
                            board[coordinates_marker_removal_start.first][counter]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                board[coordinates_marker_removal_start.first][counter]=0;
                                counter++;
                            }
                            board[coordinates_marker_removal_start.first][counter]=0;
                        }
                    }
                    else if(coordinates_marker_removal_start.second==coordinates_marker_removal_end.second){
                        //y coordinates of both are same hence remove along x direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                board[counter][coordinates_marker_removal_start.second]=0;
                                counter--;
                            }
                            board[counter][coordinates_marker_removal_start.second]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                board[counter][coordinates_marker_removal_start.second]=0;
                                counter++;
                            }
                            board[counter][coordinates_marker_removal_start.second]=0;
                        }
                    }
                    else{
                        //remove along third direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                board[counter1][counter2]=0;
                                counter1--;
                                counter2++;
                            }
                            board[counter1][counter2]=0;
                        }
                        else{
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                board[counter1][counter2]=0;
                                counter1++;
                                counter2--;
                            }
                            board[counter1][counter2]=0;
                        }
                    }
                //
                // REMOVE THE RING
                    if(board[final_ring_removal.first][final_ring_removal.second]==3){
                        board[final_ring_removal.first][final_ring_removal.second]=0;
                    }
                    else{
                        cout << "Remove Ring Error" << "\n";
                    }
                //
            }
            
            else if(player_id==2){
                //MOVE THE RING AND PLACE THE MARKER
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==3 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                //
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(board[coordinates_for_marker.first][i]==1){
                                board[coordinates_for_marker.first][i]=2;
                            }
                            else if(board[coordinates_for_marker.first][i]==2){
                                board[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(board[i][coordinates_for_marker.second]==1){
                                board[i][coordinates_for_marker.second]=2;
                            }
                            else if(board[i][coordinates_for_marker.second]==2){
                                board[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(board[i][start2]==1){
                                board[i][start2]=2;
                            }
                            else if(board[i][start2]==2){
                                board[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
                // REMOVE THE ROW
                    if(coordinates_marker_removal_start.first==coordinates_marker_removal_end.first){
                        //x coordinates of both are same hence remove along y direction
                        if(coordinates_marker_removal_start.second>coordinates_marker_removal_end.second){
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                board[coordinates_marker_removal_start.first][counter]=0;
                                counter--;
                            }
                            board[coordinates_marker_removal_start.first][counter]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                board[coordinates_marker_removal_start.first][counter]=0;
                                counter++;
                            }
                            board[coordinates_marker_removal_start.first][counter]=0;
                        }
                    }
                    else if(coordinates_marker_removal_start.second==coordinates_marker_removal_end.second){
                        //y coordinates of both are same hence remove along x direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                board[counter][coordinates_marker_removal_start.second]=0;
                                counter--;
                            }
                            board[counter][coordinates_marker_removal_start.second]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                board[counter][coordinates_marker_removal_start.second]=0;
                                counter++;
                            }
                            board[counter][coordinates_marker_removal_start.second]=0;
                        }
                    }
                    else{
                        //remove along third direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                board[counter1][counter2]=0;
                                counter1--;
                                counter2++;
                            }
                            board[counter1][counter2]=0;
                        }
                        else{
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                board[counter1][counter2]=0;
                                counter1++;
                                counter2--;
                            }
                            board[counter1][counter2]=0;
                        }
                    }
                //
                // REMOVE THE RING
                    if(board[final_ring_removal.first][final_ring_removal.second]==4){
                        board[final_ring_removal.first][final_ring_removal.second]==0;
                    }
                    else{
                        cout << "Remove Ring Error" << "\n";
                    }
                //
            }
            
            else{
                cout << "Invalid Move" << "\n";    
            }


        }
    }
    else{
        cout << "Invalid move" << endl;
    }
}



vector<pair<int,int> > neighbour( int player_id ){
    vector<pair<int,int> > ans;
    if(player_id==1){
        for(int i=0;i<rings1.size();i++){
            pair<int,int> curr_ring = rings1[i];
            int x_change[] = {1,-1, 0, 0, 1,-1};
            int y_change[] = {0, 0, 1,-1,-1, 1};

            for(int j=0;j<6;j++){
                int x_cordinate=curr_ring.first+x_change[j];
                int y_cordinate=curr_ring.second+y_change[j];
                int c=0;
                while(board[x_cordinate][y_cordinate]!=-1 && x_cordinate>=0 && x_cordinate<11 && y_cordinate>=0 && y_cordinate<11 ){
                    if(board[x_cordinate][y_cordinate]==0){
                        if(c==0){
                            ans.push_back(make_pair(x_cordinate, y_cordinate));
                            x_cordinate+=x_change[j];
                            y_cordinate+=y_change[j];
                        }else{
                            ans.push_back(make_pair(x_cordinate, y_cordinate));
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
    }
    else if(player_id==2){
        for(int i=0;i<rings2.size();i++){
            pair<int,int> curr_ring = rings2[i];
            int x_change[] = {1,-1,0,0,1,-1};
            int y_change[] = {0,0,1,-1,-1,1};

            for(int j=0;j<6;j++){
                int x_cordinate=curr_ring.first+x_change[j];
                int y_cordinate=curr_ring.second+y_change[j];
                int c=0;
                while(board[x_cordinate][y_cordinate]!=-1 && x_cordinate>=0 && x_cordinate<11 && y_cordinate>=0 && y_cordinate<11 ){
                    if(board[x_cordinate][y_cordinate]==0){
                        if(c==0){
                            ans.push_back(make_pair(x_cordinate, y_cordinate));
                            x_cordinate+=x_change[j];
                            y_cordinate+=y_change[j];
                        }else{
                            ans.push_back(make_pair(x_cordinate, y_cordinate));
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
    }
    return ans;
}

// Sample C++ Code 
int main(int argc, char** argv) {
    
    // cout << sizeof(b) << "\n";
    // cout << "num of hexagons"<< b.no_of_hexagons() << "\n";
    // cout << "num of points in hex 2" << b.points_in_hexagon_i(2) << "\n";

    
    // int player_id, board_size, time_limit;
    // // Get input from server about game specifications
    // cin >> player_id >> board_size >> time_limit;

    // int player_id=1;
    // if(player_id == 2) {
    //     // Get other player's move
    //     getline(cin, move); 
        
    //     while(true) {
    //         cout<<"P 1 0"<<endl;
    //         cin>>move;
    //     }
    // }   
    // else if(player_id == 1) {
    //     while(true) {
    //         // cout<<"P 0 0"<<endl;
    //         // /cin>>move;
    //         getline(cin, move);
    //         make_move(move, 1); 
    //     }
    // }

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

    pair<int,int> p = make_pair(5,5);
    pair<int,int> q = make_pair(9,5);
    string str="as";
    // p = make_pair(5,5);
    // place_ring_in_board(p,1,board, rings, str);
    // cout<<(rings[0]).size()<<endl;
    // board[6][5]=2;
    // board[7][5]=2;
    // board[8][5]=2;
    // board[4][5]=1;
    Board board = Board();
    p = make_pair(5,5);
    place_ring_in_board(p,1,board,str);
    p = make_pair(9,5);
    place_ring_in_board(p,2,board,str);
    // cout<<"board[5][5] : "<<board.get_at_position(5,5)<<endl;
    p = make_pair(5,5);q = make_pair(6,5);
    move_ring_in_board(p,q,1,board,str);
    p = make_pair(6,5);q = make_pair(7,5);
    move_ring_in_board(p,q,1,board,str);
    p = make_pair(7,5);q = make_pair(8,5);
    move_ring_in_board(p,q,1,board,str);
    p = make_pair(8,5);q = make_pair(8,6);
    move_ring_in_board(p,q,1,board,str);
    p = make_pair(9,5);q = make_pair(4,5);
    move_ring_in_board(p,q,2,board,str);
    // p = make_pair(5,5);
    // q = make_pair(9,5);
    // move_ring_in_board(p,q,1,board,rings, str);

    // for(int i=0;i<6;i++){
    // 	cout<<"board[4+i][5] : "<<board.get_at_position(4+i,5)<<endl;
    // }






    return 0;
}