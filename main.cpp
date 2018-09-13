#include <iostream>
#include "board_convert.h"


using namespace std;

int board[11][11];
board_convert b;
vector<pair<int, int> > rings1;
vector<pair<int, int> > rings2;


/*
Not in board: -1
Empty Position: 0
Orange Marker: 1 -> playerid 1
Blue Marker: 2 -> playerid 2
Orange Ring: 3 -> playerid 1
Blue Ring: 4  -> playerid 2
*/

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

void initialize_board(){
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
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]==1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]==3;
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
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
                //
            }
            
            else if(player_id==2){
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==4 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]==2;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]==4;
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
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
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

            pair<int, int> final_ring_removal = b.get_2dpoint(hexagon_ring_removal, point_in_hexagon_ring_removal);

            if(player_id==1){
                //MOVE THE RING AND PLACE THE MARKER
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==3 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]==1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]==3;
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
                        board[final_ring_removal.first][final_ring_removal.second]==0;
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
                    board[coordinates_for_marker.first][coordinates_for_marker.second]==1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]==3;
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
            int x_change[] = {1,-1,0,0,1.-1};
            int y_change[] = {0,0,1,-1,-1.1};

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
            int x_change[] = {1,-1,0,0,1.-1};
            int y_change[] = {0,0,1,-1,-1.1};

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
    initialize_board();

    cout << "alright" << "\n";
    
    // int player_id, board_size, time_limit;
    // string move;
    // // Get input from server about game specifications
    // cin >> player_id >> board_size >> time_limit;

    // if(player_id == 2) {
    //     // Get other player's move
    //     cin>>move; 
        
    //     while(true) {
    //         cout<<"P 1 0"<<endl;
    //         cin>>move;
    //     }
    // }   
    // else if(player_id == 1) {
    //     while(true) {
    //         cout<<"P 0 0"<<endl;
    //         cin>>move; 
    //     }
    // }
    return 0;
}