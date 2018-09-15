
void place_ring_in_board(pair<int,int> coordinates_in_board,int player_id, int tempboard[][], vector<pair<int,int> > temp_rings[2], string str){
    if(tempboard[coordinates_in_board.first][coordinates_in_board.second]==0){
        tempboard[coordinates_in_board.first][coordinates_in_board.second] = player_id+2;
        temp_rings[player_id-1].push_back(coordinates_in_board);
        //output the string
    }else{
        cout << "Invalid Move" << "\n";
    }
}

void move_ring_in_board(pair<int, int> coordinates_for_marker,pair<int, int> coordinates_for_ring,int player_id, int tempboard[][], vector<pair<int,int> > temp_rings[2], string str){
    if(tempboard[coordinates_for_marker.first][coordinates_for_marker.second]==player_id+2 && tempboard[coordinates_for_ring.first][coordinates_for_ring.second]==0){
        tempboard[coordinates_for_marker.first][coordinates_for_marker.second]=player_id;
        tempboard[coordinates_for_ring.first][coordinates_for_ring.second]=player_id+2;
        int find = find_in_vector(temp_rings[player_id], coordinates_for_marker);
        if(find!=-1){
            rings1.erase(rings1.begin() + find);
        }
        else{
            cout << "Invalid Move" << "\n";       
        }
        temp_rings[player_id].push_back(coordinates_for_ring);

        //flip the markers
        int x_change[] = {1, 0, 1};
        int y_change[] = {0, 1,-1};
        int j,k=1;
        if(coordinates_for_marker.first==coordinates_for_ring.first){
            j=1;
            if(coordinates_for_marker.second<coordinates_for_ring.second)
                k=0;
        }
        else if(coordinates_for_marker.second==coordinates_for_ring.second){
            j=0;
            if(coordinates_for_marker.first<coordinates_for_ring.first)
                k=0;
        }
        else{
            j=2;
            if(coordinates_for_marker.first<coordinates_for_ring.first)
                k=0;
        }


        int counter1 = coordinates_for_marker.first;
        int counter2 = coordinates_for_marker.second;
        if(k==0){
            counter1+=x_change[j];
            counter2+=y_change[j];
        }else{
            counter1-=x_change[j];
            counter2-=y_change[j];
        } 

        while(counter1!=coordinates_for_ring.first&&counter2!=coordinates_for_ring.second){
            if(tempboard[counter1][counter2]==1||tempboard[counter1][counter2]==2)
               tempboard[counter1][counter2]=3-tempboard[counter1][counter2]; 
            if(k==0){
                counter1+=x_change[j];
                counter2+=y_change[j];
            }else{
                counter1-=x_change[j];
                counter2-=y_change[j];
            }                      
        }
        //checking if ring would be removed or not

            
        vector< pair < pair <int,int>, pair <int,int> > > removing_markers = find_removing_markers(tempboard);//markers to be removed
        
        if(removing_markers.size()!=0){
            if(removing_markers.size()==1){
                remove_rings(tempboard,removing_markers[0]);
                //output the string
            }

        }

        
    }
    else{
        cout << "Invalid Move" << "\n";
    }
}

vector< pair < pair <int,int>, pair <int,int> > > find_removing_markers(int tempboard[][]){
    vector< pair < pair <int,int>, pair <int,int> > > removing_markers;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};
    for(int i=0;i<2;i++){
        for (int j=1;j<10;j++)
        {
            pair<int,int> corner_point = b.get_corner_point(i,j);
            int count=0;
            pair <int,int> start;
            pair <int,int> end;
            int x_const = corner_point.first;
            int y_const = corner_point.second;
            while(tempboard[x_const][y_const]!=-1){

                if(tempboard[x_const][y_const]==player_id){
                    count++;
                    if(count==1){
                        start=make_pair(x_const,y_const);
                    }
                    if(count==5){
                        end=make_pair(x_const,y_const);
                        removing_markers.push_back(make_pair(start,end))
                        ring_remove=1;
                    }
                }else{
                    count=0;
                }

                x_const+=x_change[i];
                y_const+=y_change[i];
                }

        }
    }
    return removing_markers;
}

void remove_rings(int tempboard , pair < pair <int,int>, pair <int,int> > removing_marker_pair){
    pair<int,int> start=removing_marker_pair.first;
    pair<int,int> end = removing_marker_pair.second;
    int x_change[] = {1, 0, 1};
    int y_change[] = {0, 1,-1};
    int j,k=1;
    if(start.first==end.first){
        j=1;
        if(start.second<end.second)
            k=0;
    }
    else if(start.second==end.second){
        j=0;
        if(start.first<end.first)
            k=0;
    }
    else{
        j=2;
        if(start.first<end.first)
            k=0;
    }

    int counter1 = start.first;
    int counter2 = start.second;
    while(counter1!=end.first&&counter2!=end.second){
        tempboard[counter1][counter2]=0;
        if(k==0){
            counter1+=x_change[j];
            counter2+=y_change[j];
        }else{
            counter1-=x_change[j];
            counter2-=y_change[j];
        }                      
    }
    tempboard[counter1][counter2]=0;




}

