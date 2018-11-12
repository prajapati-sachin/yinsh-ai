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




	vector<pair<int, int> > u1 ;
	u1.push_back(make_pair(6,6));
	big_hex_data.push_back(u1);
	// u.clear();
	vector<pair<int, int> > u2 ;
	u2.push_back(make_pair(6,7));
	u2.push_back(make_pair(7,6));
	u2.push_back(make_pair(7,5));
	u2.push_back(make_pair(6,5));
	u2.push_back(make_pair(5,6));
	u2.push_back(make_pair(5,7));
	big_hex_data.push_back(u2);
	// u.clear();
	vector<pair<int, int> > u3 ;
	u3.push_back(make_pair(6,8));
	u3.push_back(make_pair(7,7));
	u3.push_back(make_pair(8,6));
	u3.push_back(make_pair(8,5));
	u3.push_back(make_pair(8,4));
	u3.push_back(make_pair(7,4));
	u3.push_back(make_pair(6,4));
	u3.push_back(make_pair(5,5));
	u3.push_back(make_pair(4,6));
	u3.push_back(make_pair(4,7));
	u3.push_back(make_pair(4,8));
	u3.push_back(make_pair(5,8));
	big_hex_data.push_back(u3);
	// // u.clear();
	vector<pair<int, int> > u4 ;
	u4.push_back(make_pair(6,9));
	u4.push_back(make_pair(7,8));
	u4.push_back(make_pair(8,7));
	u4.push_back(make_pair(9,6));
	u4.push_back(make_pair(9,5));
	u4.push_back(make_pair(9,4));
	u4.push_back(make_pair(9,3));
	u4.push_back(make_pair(8,3));
	u4.push_back(make_pair(7,3));
	u4.push_back(make_pair(6,3));
	u4.push_back(make_pair(5,4));
	u4.push_back(make_pair(4,5));
	u4.push_back(make_pair(3,6));
	u4.push_back(make_pair(3,7));
	u4.push_back(make_pair(3,8));
	u4.push_back(make_pair(3,9));
	u4.push_back(make_pair(4,9));
	u4.push_back(make_pair(5,9));
	big_hex_data.push_back(u4);
	// // u.clear();
	vector<pair<int, int> > u5 ;
	u5.push_back(make_pair(6,10));
	u5.push_back(make_pair(7,9));
	u5.push_back(make_pair(8,8));
	u5.push_back(make_pair(9,7));
	u5.push_back(make_pair(10,6));
	u5.push_back(make_pair(10,5));
	u5.push_back(make_pair(10,4));
	u5.push_back(make_pair(10,3));
	u5.push_back(make_pair(10,2));
	u5.push_back(make_pair(9,2));
	u5.push_back(make_pair(8,2));
	u5.push_back(make_pair(7,2));
	u5.push_back(make_pair(6,2));
	u5.push_back(make_pair(5,3));
	u5.push_back(make_pair(4,4));
	u5.push_back(make_pair(3,5));
	u5.push_back(make_pair(2,6));
	u5.push_back(make_pair(2,7));
	u5.push_back(make_pair(2,8));
	u5.push_back(make_pair(2,9));
	u5.push_back(make_pair(2,10));
	u5.push_back(make_pair(3,10));
	u5.push_back(make_pair(4,10));
	u5.push_back(make_pair(5,10));
	big_hex_data.push_back(u5);
	// // u.clear();
	vector<pair<int, int> > u6 ;
	u6.push_back(make_pair(6,11));
	u6.push_back(make_pair(7,10));
	u6.push_back(make_pair(8,9));
	u6.push_back(make_pair(9,8));
	u6.push_back(make_pair(10,7));
	u6.push_back(make_pair(11,6));
	u6.push_back(make_pair(11,5));
	u6.push_back(make_pair(11,4));
	u6.push_back(make_pair(11,3));
	u6.push_back(make_pair(11,2));
	u6.push_back(make_pair(11,1));
	u6.push_back(make_pair(10,1));
	u6.push_back(make_pair(9,1));
	u6.push_back(make_pair(8,1));
	u6.push_back(make_pair(7,1));
	u6.push_back(make_pair(6,1));
	u6.push_back(make_pair(5,2));
	u6.push_back(make_pair(4,3));
	u6.push_back(make_pair(3,4));
	u6.push_back(make_pair(2,5));
	u6.push_back(make_pair(1,6));
	u6.push_back(make_pair(1,7));
	u6.push_back(make_pair(1,8));
	u6.push_back(make_pair(1,9));
	u6.push_back(make_pair(1,10));
	u6.push_back(make_pair(1,11));
	u6.push_back(make_pair(2,11));
	u6.push_back(make_pair(3,11));
	u6.push_back(make_pair(4,11));
	u6.push_back(make_pair(5,11));
	big_hex_data.push_back(u6);

	vector<pair<int, int> > u7 ;
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(7,11));
	u7.push_back(make_pair(8,10));
	u7.push_back(make_pair(9,9));
	u7.push_back(make_pair(10,8));
	u7.push_back(make_pair(11,7));
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(12,5));
	u7.push_back(make_pair(12,4));
	u7.push_back(make_pair(12,3));
	u7.push_back(make_pair(12,2));
	u7.push_back(make_pair(12,1));
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(11,0));
	u7.push_back(make_pair(10,0));
	u7.push_back(make_pair(9,0));
	u7.push_back(make_pair(8,0));
	u7.push_back(make_pair(7,0));
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(5,1));
	u7.push_back(make_pair(4,2));
	u7.push_back(make_pair(3,3));
	u7.push_back(make_pair(2,4));
	u7.push_back(make_pair(1,5));
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(0,7));
	u7.push_back(make_pair(0,8));
	u7.push_back(make_pair(0,9));
	u7.push_back(make_pair(0,10));
	u7.push_back(make_pair(0,11));
	u7.push_back(make_pair(-1,-1));
	u7.push_back(make_pair(1,12));
	u7.push_back(make_pair(2,12));
	u7.push_back(make_pair(3,11));
	u7.push_back(make_pair(4,12));
	u7.push_back(make_pair(5,12));
	big_hex_data.push_back(u7);


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

	for(int i=0;i<13;i++){
		for(int j=0;j<13;j++){
			big_data_2d[i][j]=make_pair(-1, -1);
		}
	}

	for(int i=0;i<big_hex_data.size();i++){
		for(int j=0;j<big_hex_data[i].size();j++){
			pair<int, int> a =big_hex_data[i][j];
			if(a.first!=-1 && a.second !=-1){	
				big_data_2d[a.first][a.second]=make_pair(i, j);
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


	big_corner_points[0][0]=make_pair(1,12);
	big_corner_points[0][1]=make_pair(0,11);
	big_corner_points[0][2]=make_pair(0,10);
	big_corner_points[0][3]=make_pair(0,9);
	big_corner_points[0][4]=make_pair(0,8);
	big_corner_points[0][5]=make_pair(0,7);
	big_corner_points[0][6]=make_pair(1,6);
	big_corner_points[0][7]=make_pair(1,5);
	big_corner_points[0][8]=make_pair(2,4);
	big_corner_points[0][9]=make_pair(3,3);
	big_corner_points[0][10]=make_pair(4,2);
	big_corner_points[0][11]=make_pair(5,1);
	big_corner_points[0][12]=make_pair(7,0);

	big_corner_points[1][0]=make_pair(0,7);
	big_corner_points[1][1]=make_pair(1,5);
	big_corner_points[1][2]=make_pair(2,4);
	big_corner_points[1][3]=make_pair(3,3);
	big_corner_points[1][4]=make_pair(4,2);
	big_corner_points[1][5]=make_pair(5,1);
	big_corner_points[1][6]=make_pair(6,1);
	big_corner_points[1][7]=make_pair(7,0);
	big_corner_points[1][8]=make_pair(8,0);
	big_corner_points[1][9]=make_pair(9,0);
	big_corner_points[1][10]=make_pair(10,0);
	big_corner_points[1][11]=make_pair(11,0);
	big_corner_points[1][12]=make_pair(12,1);


	big_corner_points[2][0]=make_pair(7,11);
	big_corner_points[2][1]=make_pair(5,12);
	big_corner_points[2][2]=make_pair(4,12);
	big_corner_points[2][3]=make_pair(3,12);
	big_corner_points[2][4]=make_pair(2,12);
	big_corner_points[2][5]=make_pair(1,12);
	big_corner_points[2][6]=make_pair(1,11);
	big_corner_points[2][7]=make_pair(0,11);
	big_corner_points[2][8]=make_pair(0,10);
	big_corner_points[2][9]=make_pair(0,9);
	big_corner_points[2][10]=make_pair(0,8);
	big_corner_points[2][11]=make_pair(0,7);
	big_corner_points[2][12]=make_pair(1,5);


}

pair<int,int> board_convert::get_2dpoint(int hexagon_no, int point_no,int n ){
	if(n==5)
		return hex_data[hexagon_no][point_no];
	else
		return big_hex_data[hexagon_no][point_no];
}

pair<int,int> board_convert::get_hexagon_point(int x, int y ,int n){
	if(n==5)
		return data_2d[x][y];
	else
		return big_data_2d[x][y];
}

pair<int,int> board_convert::get_corner_point(int i, int j ,int n ){
	if(n==5)
		return corner_points[i][j];
	else
		return big_corner_points[i][j];
}

int board_convert::no_of_hexagons(int n){
	if(n==5)
		return hex_data.size();
	else
		return big_hex_data.size();
}

int board_convert::points_in_hexagon_i(int i,int n){
	if(n==5)
		return hex_data[i].size();
	else
		return big_hex_data[i].size();
}


