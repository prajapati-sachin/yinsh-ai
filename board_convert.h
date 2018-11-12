#ifndef BOARDCONVERT_H
#define	BOARDCONVERT_H

#include <bits/stdc++.h>
using namespace std;


class board_convert {
// private:
public:
	vector<vector<pair<int,int > > > hex_data;

	pair<int,int> data_2d[11][11];

	vector<vector<pair<int,int > > > big_hex_data;

	pair<int,int> big_data_2d[13][13];

	pair<int,int> corner_points[3][11];

	pair<int,int> big_corner_points[3][13];

// public:	
	board_convert();

	pair<int,int> get_2dpoint(int hexagon_no, int point_no ,int n );

	pair<int,int> get_hexagon_point(int x, int y ,int n);

	pair<int,int> get_corner_point(int i, int j ,int n);

	int no_of_hexagons(int n);

	int points_in_hexagon_i(int i,int n);




};

#endif