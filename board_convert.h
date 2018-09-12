#ifndef BOARDCONVERT_H
#define	BOARDCONVERT_H

#include <bits/stdc++.h>
using namespace std;


class board_convert {
// private:
public:
	vector<vector<pair<int,int > > > hex_data;

	pair<int,int> data_2d[11][11];

// public:	
	board_convert();

	pair<int,int> get_2dpoint(int hexagon_no, int point_no );

	pair<int,int> get_hexagon_point(int x, int y );

	int no_of_hexagons();

	int points_in_hexagon_i(int i);


};

#endif