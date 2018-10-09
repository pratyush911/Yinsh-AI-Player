#include "board.h"    

float Board::all_utlity()
{
    int two,three,four,two_opp,three_opp,four_opp;int h=0;int v=0;int h_opp=0;int v_opp=0;
    two=three=four=two_opp=three_opp=four_opp=0;
    for(int i=0;i<=10;i++)
    {
        for(int j=0;j<=10;j++)
        {
            if(mapping[j][i]=="M")
            {
                h++;
            }
            else
            {
                if(h==2) two++;
                if(h==3) three++;
                if(h==4) four++;
                h=0;
            }
            if(mapping[j][i]=="MO")
            {
                h_opp++;
            }
            else
            {
                if(h_opp==2) two_opp++;
                if(h_opp==3) three_opp++;
                if(h_opp==4) four_opp++;
                h_opp=0;
            }
            if(mapping[i][j]=="M")
            {
                v++;
            }
            else
            {
                if(v==2) two++;
                if(v==3) three++;
                if(v==4) four++;
                v=0;
            }
            if(mapping[i][j]=="MO")
            {
                v_opp++;
            }
            else
            {
                if(v_opp==2) two_opp++;
                if(v_opp==3) three_opp++;
                if(v_opp==4) four_opp++;
                v_opp=0;
            }

        }
    }
    v=0;v_opp=0;
  for(int delta =-5;delta<=5;delta++)
    {
        int x,y;
        for(int i=std::max(0,-delta) ; i<=10; i++)
           {
               y = i;
               x = i + delta;
               if (x >10 ||y >10 || x<0 || y<0){
                   break;
               }
               if(mapping[y][x]=="M")
               {
                   v++;
               }
               else
                {
                    if(v==2) two++;
                    if(v==3) three++;
                    if(v==4) four++;
                    v=0;
                }
                if(mapping[y][x]=="MO")
               {
                   v_opp++;
               }
               else
                {
                    if(v_opp==2) two_opp++;
                    if(v_opp==3) three_opp++;
                    if(v_opp==4) four_opp++;
                    v_opp=0;
                }
           }
      }
      return std::pow(2,two)+std::pow(2,three)+std::pow(2,four) -std::pow(2,two_opp)-std::pow(2,three_opp)-std::pow(2,four_opp);
}
float Board::edge_utility()
{
    int edge1 = 0;
    int edge2 = 0;
    int  edge3 = 0;
    int  edge4 = 0;
    int  edge5 = 0;
    int edge6  = 0;
    for (int i=1;i<=4;i++)
    {
        if(mapping[i][0]=="M" || mapping[i][0]=="R")
        {
            edge1++;
        }
        if(mapping[0][i]=="M" || mapping[0][i]=="R")
        {
            edge2++;
        }
        if(mapping[i+5][10]=="M" || mapping[i+5][10]=="R")
        {
            edge3++;
        }
        if(mapping[10][i+5]=="M" || mapping[10][i+5]=="R")
        {
            edge4++;
        }
        if(mapping[i+5][i]=="M" || mapping[i+5][i]=="R")
        {
            edge5++;
        }
        if(mapping[i][i+5]=="M" || mapping[i][i+5]=="R")
        {
            edge6++;
        }
        
    }
    return pow(edge1 - 1,4) + pow(edge2 - 1,4) + pow(edge3 - 1,4) + pow(edge4-1, 4) + pow(edge5 - 1, 4) + pow(edge6 - 1, 4);
}
float Board::rings_utility()
{
    int counter=0;
    for (int i=0;i<RingPos.size(); i++){
        int x1 = RingPos[i].x;
        int y1 = RingPos[i].y;
        if (x1 < 10 && mapping[y1][x1+1] == "M"){
            counter ++;
        }
        if (y1 < 10 && mapping[y1+1][x1] == "M"){
            counter ++;
        }
        if (x1 > 0 && mapping[y1][x1-1] == "M"){
            counter ++;
        }
        if (y1 > 0 && mapping[y1-1][x1] == "M"){
            counter ++;
        }
        if (x1 < 10 && y1 < 10 && mapping[y1+1][x1+1] == "M"){
            counter ++;
        }
        if (x1 > 0 && y1 > 0 && mapping[y1-1][x1-1] == "M"){
            counter ++;
        }
    }
    int counter_opp = 0;
    for (int i=0;i<RingPosOpp.size(); i++){
        int x1 = RingPosOpp[i].x;
        int y1 = RingPosOpp[i].y;
        if (x1 < 10 && mapping[y1][x1+1] == "MO"){
            counter_opp ++;
        }
        if (y1 < 10 && mapping[y1+1][x1] == "MO"){
            counter_opp ++;
        }
        if (x1 > 0 && mapping[y1][x1-1] == "MO"){
            counter_opp ++;
        }
        if (y1 > 0 && mapping[y1-1][x1] == "MO"){
            counter_opp ++;
        }
        if (x1 < 10 && y1 < 10 && mapping[y1+1][x1+1] == "MO"){
            counter_opp ++;
        }
        if (x1 > 0 && y1 > 0 && mapping[y1-1][x1-1] == "MO"){
            counter_opp ++;
        }
    }
    float util = (counter-counter_opp) *2;
    return util;
}
float Board::find_utility()
{
    float utils = 0;
   
    int delta_markers = markersMy - markersOpp;
    // int delta_rings = RingPos.size() - RingPosOpp.size();
    // utils += markersMy * (std::pow(10,delta_rings))/100;
    float balance[6] = {200,200, 200, 70, 20, 0};
    float balance_opp[6] = {300,300, 300, 100, 50, 0};
    utils += balance[RingPos.size()];
    utils -= balance[RingPosOpp.size()];
    // utils -= (RingPos.size() - RingPosOpp.size())*10000;
    utils += markersMy;
    utils -= markersOpp;
    // utils += (float)delta_markers;
    // utils += rings_utility();
    // utils+=all_utlity();
    // utils-=all_utlity_opp();
    // utils-= 2* edge_utility();

    return utils;

}
vector<Tup3> Board::check_row_vertical_my( int init_pos_x,int init_pos_y,bool my_turn )
{
    int x1=init_pos_x;int y1=init_pos_y;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    for(int i=0;i<=10;i++)
    {
        if(mapping[i][x1]==marker_check) 
            {
                v++;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i-4;Cart c2;c2.x=x1;c2.y=i;
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
        else{v=0;}
    }
    return output;

}
vector<Tup3> Board::check_row_vertical_opp( int init_pos_x,int init_pos_y,bool my_turn )
{

    int x1=init_pos_x;int y1=init_pos_y;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    for(int i=0;i<=10;i++)
    {
        if(mapping[i][x1]==marker_check) 
            {
                v++;
                if(v==5)
                {

                    Cart c1;c1.x=x1;c1.y=i-4;Cart c2;c2.x=x1;c2.y=i;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
        else{v=0;}
    }
    return output;

}

vector<Tup3> Board::check_row_vertical( int init_pos_x,int init_pos_y ,bool my_turn)
{

    if (my_turn) return check_row_vertical_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_vertical_opp(init_pos_x, init_pos_y, my_turn);

}

vector<Tup3> Board::check_row_horizontal_my( int init_pos_x,int init_pos_y,bool my_turn )
{

    int x1=init_pos_x;int y1=init_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    string marker_check;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]==marker_check) 
            {
                h++;
                if(h==5)
                {
                    Cart c1;c1.x=i-4;c1.y=y1;Cart c2;c2.x=i;c2.y=y1;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;}
    }
    return output;

}
vector<Tup3> Board::check_row_horizontal_opp( int init_pos_x,int init_pos_y,bool my_turn )
{

    int x1=init_pos_x;int y1=init_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    string marker_check;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]==marker_check) 
            {
                h++;
                if(h==5)
                {
                    Cart c1;c1.x=i-4;c1.y=y1;Cart c2;c2.x=i;c2.y=y1;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;}
    }
    return output;

}

vector<Tup3> Board::check_row_horizontal( int init_pos_x,int init_pos_y,bool my_turn )
{

    if (my_turn) return  check_row_horizontal_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_horizontal_opp(init_pos_x, init_pos_y, my_turn);

}

vector<Tup3> Board::check_row_diagonal_my( int init_pos_x,int init_pos_y,bool my_turn)
{

    int x1=init_pos_x;int y1=init_pos_y;
    int delta = x1-y1;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    int x,y;
    for(int i=std::max(0,-delta) ; i<=10; i++)
        {
            y = i;
            x = i + delta; 
            if (x >10 ||y >10 || x<0 || y<0){
                break;
            }
            if(mapping[y][x]==marker_check) 
            {
                h++;;
                if(h==5)
                {
                    
                    Cart c1;
                    c1.x = x - 4;
                    c1.y = y - 4;
                    Cart c2;
                    c2.x = x;
                    c2.y = y;
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;}
            
        }
    return output;

}
vector<Tup3> Board::check_row_diagonal_opp( int init_pos_x,int init_pos_y,bool my_turn)
{


    int x1=init_pos_x;int y1=init_pos_y;
    int delta = x1-y1;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    int x,y;
    for(int i=std::max(0,-delta) ; i<=10; i++)
        {
            y = i;
            x = i + delta; 
            if (x >10 ||y >10 || x<0 || y<0){
                break;
            }
            if(mapping[y][x]==marker_check) 
            {
                h++;;
                if(h==5)
                {
                    
                    Cart c1;
                    c1.x = x - 4;
                    c1.y = y - 4;
                    Cart c2;
                    c2.x = x;
                    c2.y = y;
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;}
            
        }
    return output;

}
vector<Tup3> Board::check_row_diagonal( int init_pos_x,int init_pos_y,bool my_turn )
{

    if (my_turn) return check_row_diagonal_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_diagonal_opp(init_pos_x, init_pos_y, my_turn);

}
vector<Tup3> Board::check_row_all_points_each( int init_pos_x,int init_pos_y,int check, bool my_turn )
{

    int x1=init_pos_x;int y1=init_pos_y;
    vector<Tup3> non_intersecting_rows;
    if(check==0)
    {
        vector<Tup3> temp1=check_row_horizontal(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,my_turn);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else if(check==1)
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,my_turn);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_horizontal(x1,y1,my_turn);

        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());   
    }
    return non_intersecting_rows;    

}

int Board::check_if_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y, int ring_x, int ring_y, bool my_turn)
{

    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int check=0;

    string rings_check = "RO";
    string marker_check = "MO";
    if (my_turn){
        rings_check = "R";
        marker_check = "M";
    }

    if (mapping[ring_y][ring_x] != rings_check){
        return 1;
    }
        if(x1==x2)
    {
        for(int i=y1;i<=y2;i++)
        {
            if(mapping[i][x1]!=marker_check)
            {
                check=1;break;
            }
        }
    }
    else if(y1==y2)
    {
        for(int i=x1;i<=x2;i++)
        {
            if(mapping[y1][i]!=marker_check)
            {
                check=1;break;
            }
        }
    }
    else
    {
        if(x1<x2)
        {
            while(x1<x2 && y1<y2)
            {
                if(mapping[y1][x1]!=marker_check)
                {
                    check=1;break;
                }
                x1++;y1++;        
            }
        }
        if(x1>x2)
        {
            while(x1>x2 && y1>y2)
            {
                if(mapping[y1][x1]!=marker_check)
                {
                    check=1;break;
                }
                x1--;y1--;        
            }
        }
    }

    return check;

}

vector<Tup3> Board::check_row_all_points( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y,bool my_turn )
{

    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    vector<Tup3> non_intersecting_rows;
    if(x1==x2)
    {
        for(int y=std::min(y1,y2);y<=std::max(y1,y2);y++)
        {
            vector<Tup3> temp1=check_row_all_points_each(x1,y,0,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());
        }
    }
    else if(y1==y2)
    {
        for(int x=std::min(x1,x2);x<=std::max(x1,x2);x++)
        {
            vector<Tup3> temp1=check_row_all_points_each(x,y1,1,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());
        }
    }
    else
    {
        for(int i=std::min(x1,x2);i<=std::max(x1,x2);i++)
        {
            vector<Tup3> temp1=check_row_all_points_each(i,i+y1-x1,2,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());   
        }
    }
    return non_intersecting_rows;    

}

vector<MoveVal> Board::find_neighbours( Cart c, int dir, bool my_turn)//c--> position of ring to be moved
 {

    int x,y;
    if(dir==1)
    {
        x=c.x;
        y=c.y+1;
    }
    else if(dir==2)
    {
        x=c.x;
        y=c.y-1;
    }
    else if(dir==3)
    {
        x=c.x+1;
        y=c.y;
    }
    else if(dir==4)
    {
        x=c.x -1 ;
        y=c.y;
    }
    else if(dir==5) 
    {
        x=c.x+ 1;
        y=c.y+1;
    }
    else if(dir==6)
    {
        x=c.x-1;
        y=c.y-1;
    }

    int t=0; //t=1--> a marker has been encountered
    
    Children ch;
    if ((x< 0|| y<0 || x>10 || y>10)){
    
        return ch.neighbours;
    }

    MoveVal mvl;
    while(!(mapping[y][x]=="R" || mapping[y][x]=="RO" ||mapping[y][x]=="I"))
    {
         
        if(mapping[y][x]=="E" && t==0)
        {
            vector<string> m;
            vector<Cart> ct;

            vector<string> m_temp;
            vector<Cart> ct_temp;
            
            Cart r;
            r.x=x;
            r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);

            m_temp.push_back("S");
            m_temp.push_back("M");
            ct_temp.push_back(c);
            ct_temp.push_back(r);
            execute_move_sequence(ct,m,my_turn);
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_vertical(c.x,c.y, my_turn);
            }
            else if(y==c.y)
            {
                t_vec = check_row_horizontal(c.x,c.y, my_turn);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y, my_turn);
            }

            // for()
            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y,my_turn);

            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
             

            if(non_intersecting_rows.size() > 0)
                {
                    
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        vector<string> m_temp_1;
                        vector<Cart> ct_temp_1;
                        vector<string> m_first;
                        vector<Cart> ct_first;

                        m_first.push_back("RS");
                        m_first.push_back("RE");
                        m_first.push_back("X");
                        m.push_back("RS");
                        m.push_back("RE");
                        m.push_back("X");

                        ct.push_back(non_intersecting_rows[i].carts[0]);
                        ct.push_back(non_intersecting_rows[i].carts[1]);
                        ct.push_back(non_intersecting_rows[i].carts[2]);
                        ct_first.push_back(non_intersecting_rows[i].carts[0]);
                        ct_first.push_back(non_intersecting_rows[i].carts[1]);
                        ct_first.push_back(non_intersecting_rows[i].carts[2]);
                        execute_move_sequence(ct_first,m_first, my_turn);

                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            vector<string> m_temp_2;
                            vector<Cart> ct_temp_2;
                            if(check_if_row(non_intersecting_rows[j].carts[0].x, 
                                            non_intersecting_rows[j].carts[0].y, 
                                            non_intersecting_rows[j].carts[1].x, 
                                            non_intersecting_rows[j].carts[1].y,
                                            non_intersecting_rows[j].carts[2].x, 
                                            non_intersecting_rows[j].carts[2].y,
                                            my_turn) ==0)
                            {

                                m.push_back("RS");
                                m.push_back("RE");
                                m.push_back("X");
                                ct.push_back(non_intersecting_rows[j].carts[0]);
                                ct.push_back(non_intersecting_rows[j].carts[1]);
                                ct.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_1.push_back("RS");
                                m_temp_1.push_back("RE");
                                m_temp_1.push_back("X");
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_2.push_back("RS");
                                m_temp_2.push_back("RE");
                                m_temp_2.push_back("X");
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[2]);



                                if(my_turn)
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPos.size()- 2)) break;
                                }
                                else
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPosOpp.size()- 2)) break;   
                                }

                                execute_move_sequence(ct_temp_2, m_temp_2, my_turn);
                                
                            }                                                      
                        }
                        // execute_move_sequence(ct_temp_1, m_temp_1, my_turn);
                        mvl.movetype = m;
                        mvl.cart_xy = ct;
                        ch.neighbours.push_back(mvl);

                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn); 

                        undo_move_sequence(ct_first,m_first, my_turn);

                        int len = m_temp_1.size();
                        for (int d = 0 ; d<len + 3; d++){//<= as 1 extra for initial
                            m.pop_back();
                            ct.pop_back();
                        }

                    }
                }
  
                else
                {
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }

                undo_move_sequence(ct_temp,m_temp, my_turn);

                
            if(dir==1)
            {
                y++;
            }
            else if(dir==2)
            {
                y--;
            }
            else if(dir==3)
            {
                x++;
            }
            else if(dir==4)
            {
                x--;
            }
            else if(dir==5)
            {
                x++; y++;
            }
            else if(dir==6)
            {
                x--; y--;
            }

        }
        else if(mapping[y][x]=="M" || mapping[y][x]=="MO")
        {
            t=1;
            if(dir==1)
            {
                y++;
            }
            else if(dir==2)
            {
                y--;
            }
            else if(dir==3)
            {
                x++;
            }
            else if(dir==4)
            {
                x--;
            }
            else if(dir==5)
            {
                x++; y++;
            }
            else if(dir==6)
            {
                x--; y--;
            }
        }
        else if(mapping[y][x]=="E" && t==1)
        {
            vector<string> m;
            vector<Cart> ct;

            vector<string> m_temp;
            vector<Cart> ct_temp;
            
            Cart r;
            r.x=x;
            r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);

            m_temp.push_back("S");
            m_temp.push_back("M");
            ct_temp.push_back(c);
            ct_temp.push_back(r);

            execute_move_sequence(ct,m,my_turn);
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_vertical(c.x,c.y,my_turn);
            }
            else if(y==c.y)
            {
                t_vec = check_row_horizontal(c.x,c.y,my_turn);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y,my_turn);
            }


            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
            if(non_intersecting_rows.size() > 0)
                {
                    
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        vector<string> m_temp_1;
                        vector<Cart> ct_temp_1;
                        vector<string> m_first;
                        vector<Cart> ct_first;

                        m_first.push_back("RS");
                        m_first.push_back("RE");
                        m_first.push_back("X");
                        m.push_back("RS");
                        m.push_back("RE");
                        m.push_back("X");

                        ct.push_back(non_intersecting_rows[i].carts[0]);
                        ct.push_back(non_intersecting_rows[i].carts[1]);
                        ct.push_back(non_intersecting_rows[i].carts[2]);
                        ct_first.push_back(non_intersecting_rows[i].carts[0]);
                        ct_first.push_back(non_intersecting_rows[i].carts[1]);
                        ct_first.push_back(non_intersecting_rows[i].carts[2]);
                        execute_move_sequence(ct_first,m_first, my_turn);
                        
                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            vector<string> m_temp_2;
                            vector<Cart> ct_temp_2;
                            if(check_if_row(non_intersecting_rows[j].carts[0].x, 
                                            non_intersecting_rows[j].carts[0].y, 
                                            non_intersecting_rows[j].carts[1].x, 
                                            non_intersecting_rows[j].carts[1].y,
                                            non_intersecting_rows[j].carts[2].x, 
                                            non_intersecting_rows[j].carts[2].y,
                                            my_turn) ==0)
                            {

                                m.push_back("RS");
                                m.push_back("RE");
                                m.push_back("X");
                                ct.push_back(non_intersecting_rows[j].carts[0]);
                                ct.push_back(non_intersecting_rows[j].carts[1]);
                                ct.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_1.push_back("RS");
                                m_temp_1.push_back("RE");
                                m_temp_1.push_back("X");
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_2.push_back("RS");
                                m_temp_2.push_back("RE");
                                m_temp_2.push_back("X");
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[2]);



                                if(my_turn)
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPos.size()- 2)) break;
                                }
                                else
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPosOpp.size()- 2)) break;   
                                }
                                execute_move_sequence(ct_temp_2, m_temp_2, my_turn);
                                
                            }                                                      
                        }
                        // execute_move_sequence(ct_temp_1, m_temp_1, my_turn);
                        mvl.movetype = m;
                        mvl.cart_xy = ct;
                        ch.neighbours.push_back(mvl);
                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn); 
                        undo_move_sequence(ct_first,m_first, my_turn);
                        int len = m_temp_1.size();
                        for (int d = 0 ; d<len+3; d++){//<= as 1 extra for initial
                            m.pop_back();
                            ct.pop_back();
                        }

                    }
                }
                
                else
                {
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }

            undo_move_sequence(ct_temp,m_temp, my_turn);
            break;  
        }
        if ((x<0 || y<0 || x>10 || y>10)){
            break;
        }
    }
    return ch.neighbours;
}

vector<MoveVal> Board::moveRing(bool my_turn)
{


    vector<MoveVal> padosi;

    vector<Cart> myCopyRing (RingPos);
    vector<Cart> oppCopyRing (RingPosOpp);

    if (my_turn){

        for (int i=0; i < RingPos.size(); i++) 
        {
            for(int j=1;j<=6;j++)
            {
                // printConfig();
                vector<MoveVal> p1= find_neighbours(myCopyRing[i],j, my_turn);
                padosi.insert(padosi.end(),p1.begin(),p1.end());  
            }
        }
    } 
    else{
        for (int i=0; i < RingPosOpp.size(); i++) 
        {
            for(int j=1;j<=6;j++)
            {
                // printConfig();

                vector<MoveVal> p1= find_neighbours(oppCopyRing[i],j, my_turn);
                padosi.insert(padosi.end(),p1.begin(),p1.end());

            }
        }
    } 
    
    return padosi; 
}


vector<MoveVal> Board::placeRing(bool my_turn){
 /**/
  vector<MoveVal> all_possible_moves;
  int rings_temp = RingPos.size();
  
  if( rings_temp==0 || rings_temp==1 || rings_temp==2 || rings_temp==3)
  {
       MoveVal move;
       if(mapping[5][5]=="E")
       {
           Cart c;
           c.x=5;
           c.y=5;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[6][5] == "E")
       {
           Cart c;
           c.x=5;
           c.y=6;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[6][6] == "E")
       {
           Cart c;
           c.x=6;
           c.y=6;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[5][6] == "E")
       {
           Cart c;
           c.x=6;
           c.y=5;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[4][5] == "E")
       {
           Cart c;
           c.x=5;
           c.y=4;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[4][4] == "E")
       {
           Cart c;
           c.x=4;
           c.y=4;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[5][4] == "E")
       {
           Cart c;
           c.x=4;
           c.y=5;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[7][5] == "E")
       {
           Cart c;
           c.x=5;
           c.y=7;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
    }

  else
  {
      for(int y=0;y<=3;y++)
      {

          if(mapping[y+6][10]=="E")
          {
              MoveVal move;
              Cart c;
              c.x=10;
              c.y=y+6;
              move.movetype.push_back("P");
              move.cart_xy.push_back(c);
              // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
              all_possible_moves.push_back(move);
              return all_possible_moves;;
          }
          if(mapping[y+1][0]=="E")
          {
              MoveVal move;
              Cart c;
              c.x=0;
              c.y=y+1;
              move.movetype.push_back("P");
              move.cart_xy.push_back(c);
              // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
              all_possible_moves.push_back(move);
              return all_possible_moves;;
          }
      }
  }
  
}

     //------------------------------------Checkin rows made by opponent----------------------------------------------------            
Tup3 Board::CheckRowsMadeByOpp(Cart opp_c_in, Cart opp_c_fin, bool my_turn){


    vector<Tup3> non_intersecting_rows_by_opp = check_row_all_points(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y,my_turn);
     Tup3 t;
    for(int j=0;j<non_intersecting_rows_by_opp.size();j++)
        {
            if(check_if_row(non_intersecting_rows_by_opp[j].carts[0].x,
                            non_intersecting_rows_by_opp[j].carts[0].y,
                            non_intersecting_rows_by_opp[j].carts[1].x,
                            non_intersecting_rows_by_opp[j].carts[1].y,
                            non_intersecting_rows_by_opp[j].carts[2].x,
                            non_intersecting_rows_by_opp[j].carts[2].y,
                            my_turn) == 0)

            {
                t.moves.push_back("RS");
                t.moves.push_back("RE");
                t.moves.push_back("X");
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[0]);
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[1]);
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[2]);
                // if(t.moves.size()/3 == RingPos.size()- 2) break; //REMOVING BREAK CONDITION
            }                       
        }

    // execute_move_sequence(t.carts,t.moves,my_turn);
    return t;
}

Children Board::find_children(int playerstate, bool my_turn)
{
    Children my_children;
    vector<MoveVal> p = moveRing(my_turn);
    my_children.neighbours = p;
    my_children.next_state = 2;
    return my_children;

}

    