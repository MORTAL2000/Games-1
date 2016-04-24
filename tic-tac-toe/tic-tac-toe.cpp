//
//  main.cpp
//  Tic-Tac-toe
//
//  Created by Bibek Ghimire on 4/20/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#include <iostream>

using namespace std;


struct Box{
    int position;
    int state;
};


class Board{

private:
    Box box[3][3];
    bool game_state;
    int won;
    
public:
    Board(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                box[i][j].state = 0;
            }
        }
    }
    int get_game_state(){
        return game_state;
    }
    void set_game_state(int state){
        game_state = state;
    }
    // check who won
    int game_logic(){
        
        if(box[0][0].state == 1 && box[1][1].state == 1 && box[2][2].state == 1) return 1; // diagonal
        if(box[0][2].state == 1 && box[1][1].state == 1 && box[2][0].state == 1) return 1; // another diagonal
        
        if(box[0][0].state == 2 && box[1][1].state == 2 && box[2][2].state == 2) return 2; // diagonal
        if(box[0][2].state == 2 && box[1][1].state == 2 && box[2][0].state == 2) return 2; // another diagonal
        
        // row
        if(box[0][0].state == 1 && box[0][1].state == 1 && box[0][2].state == 1) return 1;
        if(box[1][0].state == 1 && box[1][1].state == 1 && box[1][2].state == 1) return 1;
        if(box[2][0].state == 1 && box[2][1].state == 1 && box[2][2].state == 1) return 1;
        
        // row
        if(box[0][0].state == 2 && box[0][1].state == 2 && box[0][2].state == 2) return 2;
        if(box[1][0].state == 2 && box[1][1].state == 2 && box[1][2].state == 2) return 2;
        if(box[2][0].state == 2 && box[2][1].state == 2 && box[2][2].state == 2) return 2;
        
        // colum
        if(box[0][0].state == 1 && box[1][0].state == 1 && box[2][0].state == 1) return 1;
        if(box[0][1].state == 1 && box[1][1].state == 1 && box[2][1].state == 1) return 1;
        if(box[0][2].state == 1 && box[1][2].state == 1 && box[2][2].state == 1) return 1;
        
        // colum
        if(box[0][0].state == 2 && box[1][0].state == 2 && box[2][0].state == 2) return 2;
        if(box[0][1].state == 2 && box[1][1].state == 2 && box[2][1].state == 2) return 2;
        if(box[0][2].state == 2 && box[1][2].state == 2 && box[2][2].state == 2) return 2;

        return 0;
          
    }
    
    bool game_finished(){
        int count = 0;
        if(game_logic() == 1 || game_logic() == 2) return true;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
            
                if(box[i][j].state == 1 || box[i][j].state == 2)count++;
            }
        }
        if(count == 9) return true;
        else return false;
    }
    
    void display_board(){
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(box[i][j].state == 0){
                    cout << "  | " ;
                }else if(box[i][j].state == 1){
                    cout << " X| ";
                }else if(box[i][j].state == 2){
                    cout << " O| ";
                }
            }
            cout<<endl<<endl;
        }
    }
    
    bool set_doard(int x, int y, int turn){
        if(turn == 1 && box[x][y].state == 0){
            box[x][y].state = 2;
            return true;
        }else if(turn == 2 && box[x][y].state == 0){
            box[x][y].state = 1;
            return true;
        }
        else {
            cout << "This state is already chosen" <<endl;
            return false;
        }
    }
};



int main(int argc, const char * argv[]) {
    
    int x,y;
    int logic_val;
    int turn;
    
    std::cout << "Please enter position as x y c co-ordinates and state of box as 'X' or 'O' \n";

    Board obj;
    turn = 1;
    
    while (!obj.game_finished()) {
        obj.display_board();
        if(turn == 1){
            cout<<"Player 1 enter your input" <<endl;
            turn = 2;
        }else if(turn == 2){
            cout<<"Player 2 enter your input" <<endl;
            turn = 1;
        }
        cin>> x >> y;
        if(obj.set_doard(x, y, turn)){
            logic_val = obj.game_logic();
            if(logic_val == 1) {
                cout<<"Player 1 won"<<endl;
                break;
            }else if(logic_val == 2){
                cout<<"Player 2 won"<<endl;
                break;
            }
        }
    }
    
    if(obj.game_logic() == 0)cout <<"Game Draw" << endl;
    
    obj.display_board();
   
    return 0;
}
