#include <iostream>
#include "board_convert.h"


using namespace std;

int board[11][11];

/*
Not in board: -1
Empty Position: 0
Orange Marker: 1
Blue Marker: 2
Orange Ring: 3
Blue Ring: 4 
*/
void initialize_board(board_convert b){
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

void make_move(){



}





// Sample C++ Code 
int main(int argc, char** argv) {
    board_convert b;
    // cout << sizeof(b) << "\n";
    // cout << "num of hexagons"<< b.no_of_hexagons() << "\n";
    // cout << "num of points in hex 2" << b.points_in_hexagon_i(2) << "\n";
    initialize_board(b);

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