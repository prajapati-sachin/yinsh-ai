#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include "board_convert.h"

using namespace std;
#include "board_convert.h"

class Board {
public:

    int board[11][11];
    board_convert b;
    vector<pair<int, int> > rings[2];
    int ring_count[2];
    int marker_count[2];

    //empty constructor
    Board();

    //copy
    Board(const Board& copy);

    int get_ring_count(int player);

    int get_marker_count(int player);

    vector<pair<int, int> > get_rings(int player);

    int get_at_position(int i,int j);

    // void set_ring_count(int player,int value);

    // void set_marker_count(int player,int value);

    // void insert_ring(int player);

    // void delete_ring(int player);

    void set_at_position(int i,int j,int value);

    vector<pair<pair<int,int>,pair<int,int> > > neighbour( int player_id );

};

int find_in_vector(vector<pair<int, int> > rings, pair<int, int> findit);


#endif