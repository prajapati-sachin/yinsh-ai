#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include "board_convert.h"

using namespace std;


class Board {
// private:
public:
    int board[11][11];
    board_convert b;
    vector<pair<int, int> > rings[2];
    int ring_count[2];
    int marker_count[2];

    //empty constructor
    Board();

    //copy
    Board(Board copy)();

    int get_ring_count(int player);

    int get_marker_count(int player);

    vector<pair<int, int> > get_ring(int player);

    int at_position(int i,int j);



}