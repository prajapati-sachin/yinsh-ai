#include <board_convert.h>

using namespace std;

board_convert::board_convert(){
	vector<pair<int, int> > v ;
	v.pushback(make_pair(5,5));
	hex_data.pushback(v);
	v.clear();
	v.pushback(make_pair(5,6));
	v.pushback(make_pair(6,5));
	v.pushback(make_pair(6,4));
	v.pushback(make_pair(5,4));
	v.pushback(make_pair(4,5));
	v.pushback(make_pair(4,6));
	hex_data.pushback(v);
	v.clear();
	v.pushback(make_pair(5,7));
	v.pushback(make_pair(6,6));
	v.pushback(make_pair(7,5));
	v.pushback(make_pair(7,4));
	v.pushback(make_pair(7,3));
	v.pushback(make_pair(6,3));
	v.pushback(make_pair(5,3));
	v.pushback(make_pair(4,4));
	v.pushback(make_pair(3,5));
	v.pushback(make_pair(3,6));
	v.pushback(make_pair(3,7));
	v.pushback(make_pair(4,7));
	hex_data.pushback(v);
	v.clear();
	v.pushback(make_pair(5,8));
	v.pushback(make_pair(6,7));
	v.pushback(make_pair(7,6));
	v.pushback(make_pair(8,5));
	v.pushback(make_pair(8,4));
	v.pushback(make_pair(8,3));
	v.pushback(make_pair(8,2));
	v.pushback(make_pair(7,2));
	v.pushback(make_pair(6,2));
	v.pushback(make_pair(5,2));
	v.pushback(make_pair(4,3));
	v.pushback(make_pair(3,4));
	v.pushback(make_pair(2,5));
	v.pushback(make_pair(2,6));
	v.pushback(make_pair(2,7));
	v.pushback(make_pair(2,8));
	v.pushback(make_pair(3,8));
	v.pushback(make_pair(4,8));
	hex_data.pushback(v);
	v.clear();
	v.pushback(make_pair(5,9));
	v.pushback(make_pair(6,8));
	v.pushback(make_pair(7,7));
	v.pushback(make_pair(8,6));
	v.pushback(make_pair(9,5));
	v.pushback(make_pair(9,4));
	v.pushback(make_pair(9,3));
	v.pushback(make_pair(9,2));
	v.pushback(make_pair(9,1));
	v.pushback(make_pair(8.1));
	v.pushback(make_pair(7,1));
	v.pushback(make_pair(6,1));
	v.pushback(make_pair(5.1));
	v.pushback(make_pair(4,2));
	v.pushback(make_pair(3,3));
	v.pushback(make_pair(2,4));
	v.pushback(make_pair(1,5));
	v.pushback(make_pair(1,6));
	v.pushback(make_pair(1,7));
	v.pushback(make_pair(1,8));
	v.pushback(make_pair(1,9));
	v.pushback(make_pair(2.9));
	v.pushback(make_pair(3,9));
	v.pushback(make_pair(4,9));
	hex_data.pushback(v);
	v.clear();
	v.pushback(make_pair(-1,-1));//
	v.pushback(make_pair(6,9));
	v.pushback(make_pair(7,8));
	v.pushback(make_pair(8.7));
	v.pushback(make_pair(9,6));
	v.pushback(make_pair(-1,-1));//
	v.pushback(make_pair(10,4));
	v.pushback(make_pair(10,3));
	v.pushback(make_pair(10,2));
	v.pushback(make_pair(10,1));
	v.pushback(make_pair(-1,-1));//
	v.pushback(make_pair(9,0));
	v.pushback(make_pair(8,0));
	v.pushback(make_pair(7,0));
	v.pushback(make_pair(6,0));
	v.pushback(make_pair(-1.-1));//
	v.pushback(make_pair(4,1));
	v.pushback(make_pair(3,2));
	v.pushback(make_pair(2,3));
	v.pushback(make_pair(1,4));
	v.pushback(make_pair(-1,-1));//
	v.pushback(make_pair(0,6));
	v.pushback(make_pair(0,7));
	v.pushback(make_pair(0,8));
	v.pushback(make_pair(0,9));
	v.pushback(make_pair(-1,-1));//
	v.pushback(make_pair(1,10));
	v.pushback(make_pair(2,10));
	v.pushback(make_pair(3,10));
	v.pushback(make_pair(4,10));
	hex_data.pushback(v);
	v.clear();





}

pair<int,int> board_convert::get_2dpoint(int hexagon_no, int point_no ){
	return hex_data[hexagon_no][point_no];
}

pair<int,int> board_convert::get_hexagon_point(int x, int y ){
	return 2d_data[x][y];
}