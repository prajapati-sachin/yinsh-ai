#ifndef BOARDCONVERT_H
#define	BOARDCONVERT_H

#include <vector>
using namespace std;


class boardconvert {
private:
	vector<vector<pair<int,int > > > hex_data;

	pair<int,int> 2d_data[11][11];

public:
	boardconvert();

	pair<int,int> get_2dpoint(int hexagon_no, int point_no );

	pair<int,int> get_hexagon_point(int x, int y );


};

#endif