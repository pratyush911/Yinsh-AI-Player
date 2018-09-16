//State of the game ://
#include "minimax.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 


//****************NOT UPDATED PREVIOUS MOVE ANYWHERE -- BOARDDDDDDD UTILITY NOT UPDATEDDDD******************************//
//*****ALSO WHAT ABOUT STATE?????***************************//

MoveVal DecisionMaker(Board board, int ply, int my_state){
    MoveVal* temp = new MoveVal(board.utility_board);
    MoveVal mv = MaxVal(board, INT_MIN, INT_MAX, ply, my_state, temp);
    cout << "Checking Decision " << mv.movetype[0] << " " << mv.cart_xy[0].x << " "<< mv.cart_xy[0].y << endl;
    return mv;
}

MoveVal MaxVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal* prev_move){
    cout << "Enter MaxVal" <<endl;
    bool my_turn = true;
    if (ply == 0){
        MoveVal retMove(prev_move -> movetype, prev_move -> cart_xy, prev_move -> utility);
        cout << "return Move utility: " <<retMove.utility<<" movetype: "<<retMove.movetype[0] << " Cartx: " <<retMove.cart_xy[0].x << " Carty: " <<retMove.cart_xy[0].y << endl;        
        return retMove;
    }
    board.find_children( my_state, my_turn);
    cout << "Children Returned, Size: " <<board.children.neighbours.size()<< ", "<<endl;
    if (board.children.neighbours.size() == 0){
        MoveVal retMove(prev_move -> movetype, prev_move -> cart_xy, prev_move -> utility);
        cout << "return Move utility: " <<retMove.utility<<" movetype: "<<retMove.movetype[0] << " Cartx: " <<retMove.cart_xy[0].x << " Carty: " <<retMove.cart_xy[0].y << endl;        
        return retMove;
    }
    MoveVal* ptrMove = new MoveVal(INT_MIN);
    MoveVal my_child;
    for (int i = 0; i < board.children.neighbours.size(); i++){
        board.execute_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype ); 
        cout << "Looping MaxVal ngb" << board.children.neighbours[i].movetype[0] << " " << board.children.neighbours[i].cart_xy[0].x << " " << board.children.neighbours[i].cart_xy[0].y    ;
        MoveVal* prev_ptr = &board.children.neighbours[i];
        my_child = MinVal(board,alpha,beta, ply - 1, board.children.next_state, prev_ptr);//How to find new state??????????????????
        alpha = std::max(alpha,my_child.utility);
        cout << "Alpha: "<<alpha<< " Beta: "<<beta<<endl; 
        board.undo_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta) {
            return my_child;
        }
        cout << "My Child utility" <<my_child.utility<< " movetype: "<<my_child.movetype[0] << " Cartx: " <<my_child.cart_xy[0].x << " Carty: " << my_child.cart_xy[0].y << endl; 
        if (ptrMove->utility <= my_child.utility){
            ptrMove = &my_child;
            cout << "Pointer Move utility: " <<ptrMove -> utility<<" movetype: "<<ptrMove -> movetype[0] << " Cartx: " <<ptrMove -> cart_xy[0].x << " Carty: " <<ptrMove -> cart_xy[0].y << endl;        

        }
    }
    cout << "Out of Loop; Pointer Move utility: " <<ptrMove -> utility<<" movetype: "<<ptrMove -> movetype[0] << " Cartx: " <<ptrMove -> cart_xy[0].x << " Carty: " <<ptrMove -> cart_xy[0].y << endl; 
    MoveVal retMove(ptrMove -> movetype, ptrMove -> cart_xy, ptrMove -> utility);
    cout << "return Move utility: " <<retMove.utility<<" movetype: "<<retMove.movetype[0] << " Cartx: " <<retMove.cart_xy[0].x << " Carty: " <<retMove.cart_xy[0].y << endl;        
    return retMove;
}

MoveVal MinVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal* prev_move){
    cout << "Enter MinVal" <<endl;
    bool my_turn = false;
    cout << "In MinVal" << prev_move -> movetype[0] << " " << prev_move -> cart_xy[0].x <<" "<< prev_move -> cart_xy[0].y <<endl;
    if (ply ==0 ){
        MoveVal retMove(prev_move -> movetype, prev_move -> cart_xy, prev_move -> utility);
        cout << "Ply = 0; return Move utility: " <<retMove.utility<<" movetype: "<<retMove.movetype[0] << " Cartx: " <<retMove.cart_xy[0].x << " Carty: " <<retMove.cart_xy[0].y << endl;        
        return retMove;
    }
    board.find_children(my_state, my_turn);
    if (board.children.neighbours.size() == 0 ){
        MoveVal retMove(prev_move -> movetype, prev_move -> cart_xy, prev_move -> utility);
        cout << "return Move utility: " <<retMove.utility<<" movetype: "<<retMove.movetype[0] << " Cartx: " <<retMove.cart_xy[0].x << " Carty: " <<retMove.cart_xy[0].y << endl;        
        return retMove;
    }
    MoveVal* ptrMove = new MoveVal(INT_MAX);
    MoveVal my_child;
    for (int i = 0; i < board.children.neighbours.size(); i++){        
        board.execute_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype );
        MoveVal* prev_ptr = &board.children.neighbours[i];
        my_child = MaxVal(board,alpha,beta, ply - 1, board.children.next_state, prev_ptr);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        board.undo_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta){
            return my_child;
        }
        if (ptrMove->utility >= my_child.utility){
            ptrMove = &my_child;
        } 
            
    }
    MoveVal retMove(ptrMove -> movetype, ptrMove -> cart_xy, ptrMove -> utility);
    return retMove; 
} 



