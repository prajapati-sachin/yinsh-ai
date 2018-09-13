#include <iostream>
#include "board_convert.h"


using namespace std;

int board[11][11];
board_convert b;

/*
Not in board: -1
Empty Position: 0
Orange Marker: 1
Blue Marker: 2
Orange Ring: 3
Blue Ring: 4 
*/
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
    if(move[0]=="P"){
        // place a ring..initial steps
        int hexagon= move[2]-'0';
        int points_in_hexagon= move[4]-'0';
        pair<int, int> coordinates_in_board = b.get_2dpoint(hexagon, points_in_hexagon);
        int value_at_board = board[coordinates_in_board.first][coordinates_in_board.second];        
        if(value_at_board==0){
            if(player_id==1){
                // Ring of player 1
                board[coordinates_in_board.first][coordinates_in_board.second] = 3;
            }
            else if(player_id==2){
                // Ring of player 2
                board[coordinates_in_board.first][coordinates_in_board.second] = 4;
            }
            else{
                cout << "Invalid Move" << "\n";    
            }
        }
        else{
            cout << "Invalid Move" << "\n";
        }

    }
    else if(move[0]=="S"){
        //place a marker at position -> move a ring to new position
        if(move.length()<12){
            int hexagon_marker = move[2]-'0';
            int point_in_hexagon_for_marker = move[4]-'0';
            int hexagon_ring = move[8]-'0';
            int point_in_hexagon_for_ring = move[10]-'0';
            pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
            pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);
            if(player_id==1){
                if(board[coordinates_for_marker.first][coordinates_for_marker.second]==3 && board[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    board[coordinates_for_marker.first][coordinates_for_marker.second]==1;
                    board[coordinates_for_ring.first][coordinates_for_ring.second]==3;
                }

            }
            else if(player_id==2){

            }
            else{
                cout << "Invalid Move" << "\n";    
            }

        }
        //place a marker at a position -> move a ring to a given position -> remove a row of 5 markers -> remove a ring 
        else{
            int hexagon_marker = move[2]-'0';
            int point_in_hexagon_for_marker = move[4]-'0';
            int hexagon_ring = move[8]-'0';
            int point_in_hexagon_for_ring = move[10]-'0';
            int hexagon_marker_removal_start= move[12]-'0';
            int point_in_hexagon_marker_removal_start= move[14]-'0';
            int hexagon_marker_removal_end= move[18]-'0';
            int point_in_hexagon_marker_removal_end= move[20]-'0';
            int hexagon_ring_removal = move[24]-'0';
            int points_in_hexagon_ring_removal = move[26]-'0';



        }
    }
    else{
        cout << "Invalid move" << endl;
    }
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