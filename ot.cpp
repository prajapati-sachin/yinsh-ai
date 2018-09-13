#include <iostream>
#include "board_convert.h"


using namespace std;

int board[11][11];

/*
Not in board: -1
Empty Position: 0
Orange Marker: 1 -> playerid 1
Blue Marker: 2 -> playerid 2
Orange Ring: 3 -> playerid 1
Blue Ring: 4  -> playerid 2
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