#include <bits/stdc++.h>
#include "board_convert.h"

using namespace std;

board_convert::board_convert(){
//	initializing hex_data
	vector<pair<int, int> > v1 ;
	v1.push_back(make_pair(5,5));
	hex_data.push_back(v1);
	// v.clear();
	vector<pair<int, int> > v2 ;
	v2.push_back(make_pair(5,6));
	v2.push_back(make_pair(6,5));
	v2.push_back(make_pair(6,4));
	v2.push_back(make_pair(5,4));
	v2.push_back(make_pair(4,5));
	v2.push_back(make_pair(4,6));
	hex_data.push_back(v2);
	// v.clear();
	vector<pair<int, int> > v3 ;
	v3.push_back(make_pair(5,7));
	v3.push_back(make_pair(6,6));
	v3.push_back(make_pair(7,5));
	v3.push_back(make_pair(7,4));
	v3.push_back(make_pair(7,3));
	v3.push_back(make_pair(6,3));
	v3.push_back(make_pair(5,3));
	v3.push_back(make_pair(4,4));
	v3.push_back(make_pair(3,5));
	v3.push_back(make_pair(3,6));
	v3.push_back(make_pair(3,7));
	v3.push_back(make_pair(4,7));
	hex_data.push_back(v3);
	// // v.clear();
	vector<pair<int, int> > v4 ;
	v4.push_back(make_pair(5,8));
	v4.push_back(make_pair(6,7));
	v4.push_back(make_pair(7,6));
	v4.push_back(make_pair(8,5));
	v4.push_back(make_pair(8,4));
	v4.push_back(make_pair(8,3));
	v4.push_back(make_pair(8,2));
	v4.push_back(make_pair(7,2));
	v4.push_back(make_pair(6,2));
	v4.push_back(make_pair(5,2));
	v4.push_back(make_pair(4,3));
	v4.push_back(make_pair(3,4));
	v4.push_back(make_pair(2,5));
	v4.push_back(make_pair(2,6));
	v4.push_back(make_pair(2,7));
	v4.push_back(make_pair(2,8));
	v4.push_back(make_pair(3,8));
	v4.push_back(make_pair(4,8));
	hex_data.push_back(v4);
	// // v.clear();
	vector<pair<int, int> > v5 ;
	v5.push_back(make_pair(5,9));
	v5.push_back(make_pair(6,8));
	v5.push_back(make_pair(7,7));
	v5.push_back(make_pair(8,6));
	v5.push_back(make_pair(9,5));
	v5.push_back(make_pair(9,4));
	v5.push_back(make_pair(9,3));
	v5.push_back(make_pair(9,2));
	v5.push_back(make_pair(9,1));
	v5.push_back(make_pair(8,1));
	v5.push_back(make_pair(7,1));
	v5.push_back(make_pair(6,1));
	v5.push_back(make_pair(5,1));
	v5.push_back(make_pair(4,2));
	v5.push_back(make_pair(3,3));
	v5.push_back(make_pair(2,4));
	v5.push_back(make_pair(1,5));
	v5.push_back(make_pair(1,6));
	v5.push_back(make_pair(1,7));
	v5.push_back(make_pair(1,8));
	v5.push_back(make_pair(1,9));
	v5.push_back(make_pair(2,9));
	v5.push_back(make_pair(3,9));
	v5.push_back(make_pair(4,9));
	hex_data.push_back(v5);
	// // v.clear();
	vector<pair<int, int> > v6 ;
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(6,9));
	v6.push_back(make_pair(7,8));
	v6.push_back(make_pair(8,7));
	v6.push_back(make_pair(9,6));
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(10,4));
	v6.push_back(make_pair(10,3));
	v6.push_back(make_pair(10,2));
	v6.push_back(make_pair(10,1));
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(9,0));
	v6.push_back(make_pair(8,0));
	v6.push_back(make_pair(7,0));
	v6.push_back(make_pair(6,0));
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(4,1));
	v6.push_back(make_pair(3,2));
	v6.push_back(make_pair(2,3));
	v6.push_back(make_pair(1,4));
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(0,6));
	v6.push_back(make_pair(0,7));
	v6.push_back(make_pair(0,8));
	v6.push_back(make_pair(0,9));
	v6.push_back(make_pair(-1,-1));
	v6.push_back(make_pair(1,10));
	v6.push_back(make_pair(2,10));
	v6.push_back(make_pair(3,10));
	v6.push_back(make_pair(4,10));
	hex_data.push_back(v6);
	// // v.clear();


//	initializing data_2d
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++){
			data_2d[i][j]=make_pair(-1, -1);
		}
	}

	for(int i=0;i<hex_data.size();i++){
		for(int j=0;j<hex_data[i].size();j++){
			pair<int, int> a =hex_data[i][j];
			if(a.first!=-1 && a.second !=-1){	
				data_2d[a.first][a.second]=make_pair(i, j);
			}
		}
	}

// initializing corner points
	corner_points[0][0]=make_pair(1,10);
	corner_points[0][1]=make_pair(0,9);
	corner_points[0][2]=make_pair(0,8);
	corner_points[0][3]=make_pair(0,7);
	corner_points[0][4]=make_pair(0,6);
	corner_points[0][5]=make_pair(1,5);
	corner_points[0][6]=make_pair(1,4);
	corner_points[0][7]=make_pair(2,3);
	corner_points[0][8]=make_pair(3,2);
	corner_points[0][9]=make_pair(4,1);
	corner_points[0][10]=make_pair(6,0);

	corner_points[1][0]=make_pair(0,6);
	corner_points[1][1]=make_pair(1,4);
	corner_points[1][2]=make_pair(2,3);
	corner_points[1][3]=make_pair(3,2);
	corner_points[1][4]=make_pair(4,1);
	corner_points[1][5]=make_pair(5,1);
	corner_points[1][6]=make_pair(6,0);
	corner_points[1][7]=make_pair(7,0);
	corner_points[1][8]=make_pair(8,0);
	corner_points[1][9]=make_pair(9,0);
	corner_points[1][10]=make_pair(10,1);

	corner_points[2][0]=make_pair(6,9);
	corner_points[2][1]=make_pair(4,10);
	corner_points[2][2]=make_pair(3,10);
	corner_points[2][3]=make_pair(2,10);
	corner_points[2][4]=make_pair(1,10);
	corner_points[2][5]=make_pair(1,9);
	corner_points[2][6]=make_pair(0,9);
	corner_points[2][7]=make_pair(0,8);
	corner_points[2][8]=make_pair(0,7);
	corner_points[2][9]=make_pair(0,6);
	corner_points[2][10]=make_pair(1,4);


}

pair<int,int> board_convert::get_2dpoint(int hexagon_no, int point_no ){
	return hex_data[hexagon_no][point_no];
}

pair<int,int> board_convert::get_hexagon_point(int x, int y ){
	return data_2d[x][y];
}

pair<int,int> board_convert::get_corner_point(int i, int j ){
	return corner_points[i][j];
}

int board_convert::no_of_hexagons(){
	return hex_data.size();
}

int board_convert::points_in_hexagon_i(int i){
	return hex_data[i].size();
}


