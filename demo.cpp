
void make_move_in_board(string move, int player_id, int tempboard[][],str){
    if(move.at(0)=='P'){
        // place a ring..initial steps
        int hexagon= move.at(2)-'0';
        int points_in_hexagon= move.at(4)-'0';
        pair<int, int> coordinates_in_board = b.get_2dpoint(hexagon, points_in_hexagon);
        int value_at_board = tempboard[coordinates_in_board.first][coordinates_in_board.second];        
        if(value_at_board==0){
            if(player_id==1){
                // Ring of player 1
                tempboard[coordinates_in_board.first][coordinates_in_board.second] = 3;
                rings1.push_back(coordinates_in_board);
            }
            else if(player_id==2){
                // Ring of player 2
                tempboard[coordinates_in_board.first][coordinates_in_board.second] = 4;
                rings2.push_back(coordinates_in_board);
            }
            else{
                cout << "Invalid Move" << "\n";    
            }
        }
        else{
            cout << "Invalid Move" << "\n";
        }
    }
    else if(move.at(0)=='S'){

        if(move.length()<12){
            vector<pair<int,int> > flipped;//to store markers that have been flipped
            //place a marker at position -> move a ring to new position     
            int hexagon_marker = move.at(2)-'0';
            int point_in_hexagon_for_marker = move.at(4)-'0';
            int hexagon_ring = move.at(8)-'0';
            int point_in_hexagon_for_ring = move.at(10)-'0';
            pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
            pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);
            if(player_id==1){
                if(tempboard[coordinates_for_marker.first][coordinates_for_marker.second]==3 && tempboard[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    tempboard[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    flipped.push_back(coordinates_for_marker);
                    tempboard[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                // ALSO HAVE TO FLIP THE RINGS
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                                flipped.push_back(make_pair(i,start2));
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                                flipped.push_back(make_pair(i,start2));
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                                flipped.push_back(make_pair(i,start2));
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                                flipped.push_back(make_pair(i,start2));
                            }
                            start2--;
                        }
                    }
                }
                //
            }
            
            else if(player_id==2){
                if(tempboard[coordinates_for_marker.first][coordinates_for_marker.second]==4 && tempboard[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    tempboard[coordinates_for_marker.first][coordinates_for_marker.second]=2;
                    flipped.push_back(coordinates_for_marker);          
                    tempboard[coordinates_for_ring.first][coordinates_for_ring.second]=4;
                    //change the position in rings1
                    int find = find_in_vector(rings2, coordinates_for_marker);
                    if(find!=-1){
                        rings2.erase(rings2.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings2.push_back(coordinates_for_ring);
                }
                // ALSO HAVE TO FLIP THE RINGS
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                                flipped.push_back(make_pair(coordinates_for_marker.first,i));
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));;
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                                flipped.push_back(make_pair(i,coordinates_for_marker.second));
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                                flipped.push_back(make_pair(i,start2));
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                                flipped.push_back(make_pair(i,start2));
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                                flipped.push_back(make_pair(i,start2));
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                                flipped.push_back(make_pair(i,start2));
                            }
                            start2--;
                        }
                    }
                }
                //
            }
            
            else{
                cout << "Invalid Move" << "\n";    
            }
            int ring_remove=0;
            
            vector< pair < pair <int,int>, pair <int,int> > > removing_markers//markers to be removed
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



            
                
            if(ring_remove!=0){

            }

        }
        
        else{
            //place a marker at a position -> move a ring to a given position -> remove a row of 5 markers -> remove a ring 
            int hexagon_marker = move.at(2)-'0';
            int point_in_hexagon_for_marker = move.at(4)-'0';
            int hexagon_ring = move.at(8)-'0';
            int point_in_hexagon_for_ring = move.at(10)-'0';
            int hexagon_marker_removal_start= move.at(12)-'0';
            int point_in_hexagon_marker_removal_start= move.at(14)-'0';
            int hexagon_marker_removal_end= move.at(18)-'0';
            int point_in_hexagon_marker_removal_end= move.at(20)-'0';
            int hexagon_ring_removal = move.at(24)-'0';
            int points_in_hexagon_ring_removal = move.at(26)-'0';
            
            pair<int, int> coordinates_for_marker = b.get_2dpoint(hexagon_marker, point_in_hexagon_for_marker);
            pair<int, int> coordinates_for_ring = b.get_2dpoint(hexagon_ring, point_in_hexagon_for_ring);

            pair<int, int> coordinates_marker_removal_start = b.get_2dpoint(hexagon_marker_removal_start, point_in_hexagon_marker_removal_start);
            pair<int, int> coordinates_marker_removal_end = b.get_2dpoint(hexagon_marker_removal_end, point_in_hexagon_marker_removal_end);

            pair<int, int> final_ring_removal = b.get_2dpoint(hexagon_ring_removal, points_in_hexagon_ring_removal);

            if(player_id==1){
                //MOVE THE RING AND PLACE THE MARKER
                if(tempboard[coordinates_for_marker.first][coordinates_for_marker.second]==3 && tempboard[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    tempboard[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    tempboard[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                //
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
                // REMOVE THE ROW
                    if(coordinates_marker_removal_start.first==coordinates_marker_removal_end.first){
                        //x coordinates of both are same hence remove along y direction
                        if(coordinates_marker_removal_start.second>coordinates_marker_removal_end.second){
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                tempboard[coordinates_marker_removal_start.first][counter]=0;
                                counter--;
                            }
                            tempboard[coordinates_marker_removal_start.first][counter]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                tempboard[coordinates_marker_removal_start.first][counter]=0;
                                counter++;
                            }
                            tempboard[coordinates_marker_removal_start.first][counter]=0;
                        }
                    }
                    else if(coordinates_marker_removal_start.second==coordinates_marker_removal_end.second){
                        //y coordinates of both are same hence remove along x direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                tempboard[counter][coordinates_marker_removal_start.second]=0;
                                counter--;
                            }
                            tempboard[counter][coordinates_marker_removal_start.second]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                tempboard[counter][coordinates_marker_removal_start.second]=0;
                                counter++;
                            }
                            tempboard[counter][coordinates_marker_removal_start.second]=0;
                        }
                    }
                    else{
                        //remove along third direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                tempboard[counter1][counter2]=0;
                                counter1--;
                                counter2++;
                            }
                            tempboard[counter1][counter2]=0;
                        }
                        else{
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                tempboard[counter1][counter2]=0;
                                counter1++;
                                counter2--;
                            }
                            tempboard[counter1][counter2]=0;
                        }
                    }
                //
                // REMOVE THE RING
                    if(tempboard[final_ring_removal.first][final_ring_removal.second]==3){
                        tempboard[final_ring_removal.first][final_ring_removal.second]=0;
                    }
                    else{
                        cout << "Remove Ring Error" << "\n";
                    }
                //
            }
            
            else if(player_id==2){
                //MOVE THE RING AND PLACE THE MARKER
                if(tempboard[coordinates_for_marker.first][coordinates_for_marker.second]==3 && tempboard[coordinates_for_ring.first][coordinates_for_ring.second]==0){
                    //could also include check for a single line
                    tempboard[coordinates_for_marker.first][coordinates_for_marker.second]=1;
                    tempboard[coordinates_for_ring.first][coordinates_for_ring.second]=3;
                    //change the position in rings1
                    int find = find_in_vector(rings1, coordinates_for_marker);
                    if(find!=-1){
                        rings1.erase(rings1.begin() + find);
                    }
                    else{
                        cout << "Invalid Move" << "\n";       
                    }
                    rings1.push_back(coordinates_for_ring);
                }
                //
                // ALSO HAVE TO FLIP THE RINGS------------------------------------------
                if(coordinates_for_marker.first==coordinates_for_ring.first){
                    //first coordinates x's are equal so change is in y direction
                    if(coordinates_for_marker.second>coordinates_for_ring.second){
                        int start = coordinates_for_marker.second-1;
                        for(int i=start;i>coordinates_for_ring.second;i--){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.second+1;
                        for(int i=start;i<coordinates_for_ring.second;i++){
                            if(tempboard[coordinates_for_marker.first][i]==1){
                                tempboard[coordinates_for_marker.first][i]=2;
                            }
                            else if(tempboard[coordinates_for_marker.first][i]==2){
                                tempboard[coordinates_for_marker.first][i]=1;
                            }
                        }
                    }
                }
                else if(coordinates_for_marker.second==coordinates_for_ring.second){
                    //second coordinates y's are equal so change is in x direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start = coordinates_for_marker.first-1;
                        for(int i=start;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                    else{
                        int start = coordinates_for_marker.first+1;
                        for(int i=start;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][coordinates_for_marker.second]==1){
                                tempboard[i][coordinates_for_marker.second]=2;
                            }
                            else if(tempboard[i][coordinates_for_marker.second]==2){
                                tempboard[i][coordinates_for_marker.second]=1;
                            }
                        }
                    }
                }
                else{
                    //flips in third direction
                    if(coordinates_for_marker.first>coordinates_for_ring.first){
                        int start1 = coordinates_for_marker.first-1;
                        int start2 = coordinates_for_marker.second+1;
                        for(int i=start1;i>coordinates_for_ring.first;i--){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                            }
                            start2++;
                        }
                    }
                    else{
                        int start1 = coordinates_for_marker.first+1;
                        int start2 = coordinates_for_marker.second-1;
                        for(int i=start1;i<coordinates_for_ring.first;i++){
                            if(tempboard[i][start2]==1){
                                tempboard[i][start2]=2;
                            }
                            else if(tempboard[i][start2]==2){
                                tempboard[i][start2]=1;
                            }
                            start2--;
                        }
                    }
                }
                //
                // REMOVE THE ROW
                    if(coordinates_marker_removal_start.first==coordinates_marker_removal_end.first){
                        //x coordinates of both are same hence remove along y direction
                        if(coordinates_marker_removal_start.second>coordinates_marker_removal_end.second){
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                tempboard[coordinates_marker_removal_start.first][counter]=0;
                                counter--;
                            }
                            tempboard[coordinates_marker_removal_start.first][counter]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.second;
                            while(counter!=coordinates_marker_removal_end.second){
                                tempboard[coordinates_marker_removal_start.first][counter]=0;
                                counter++;
                            }
                            tempboard[coordinates_marker_removal_start.first][counter]=0;
                        }
                    }
                    else if(coordinates_marker_removal_start.second==coordinates_marker_removal_end.second){
                        //y coordinates of both are same hence remove along x direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                tempboard[counter][coordinates_marker_removal_start.second]=0;
                                counter--;
                            }
                            tempboard[counter][coordinates_marker_removal_start.second]=0;
                        }
                        else{
                            int counter = coordinates_marker_removal_start.first;
                            while(counter!=coordinates_marker_removal_end.first){
                                tempboard[counter][coordinates_marker_removal_start.second]=0;
                                counter++;
                            }
                            tempboard[counter][coordinates_marker_removal_start.second]=0;
                        }
                    }
                    else{
                        //remove along third direction
                        if(coordinates_marker_removal_start.first>coordinates_marker_removal_end.first){
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                tempboard[counter1][counter2]=0;
                                counter1--;
                                counter2++;
                            }
                            tempboard[counter1][counter2]=0;
                        }
                        else{
                            int counter1 = coordinates_marker_removal_start.first;
                            int counter2 = coordinates_marker_removal_start.second;
                            while(counter1!=coordinates_marker_removal_end.first){
                                tempboard[counter1][counter2]=0;
                                counter1++;
                                counter2--;
                            }
                            tempboard[counter1][counter2]=0;
                        }
                    }
                //
                // REMOVE THE RING
                    if(tempboard[final_ring_removal.first][final_ring_removal.second]==4){
                        tempboard[final_ring_removal.first][final_ring_removal.second]==0;
                    }
                    else{
                        cout << "Remove Ring Error" << "\n";
                    }
                //
            }
            
            else{
                cout << "Invalid Move" << "\n";    
            }


        }
    }
    else{
        cout << "Invalid move" << endl;
    }
}