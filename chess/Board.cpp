//
//  Board.cpp
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#include "Board.hpp"
#include <stdio.h>



Board::Board(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            fill_pieces(i,j);
        }
    }
    

}

void Board::display(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            
            if(sq[i][j].getMyState() == occupied){
                if(sq[i][j].getSquarecolor() == block_white){
                    std::cout<<"[W," <<sq[i][j].getMypiece()->display_char()<<",("<<i<<","<<j<<")"<<"]";
                }else{
                    std::cout<<"[B," <<sq[i][j].getMypiece()->display_char()<<",("<<i<<","<<j<<")"<<"]";
                }
            }
            else{
                if(sq[i][j].getMyState() == clean){
                    if(sq[i][j].getSquarecolor() == block_white){
                        std::cout<<"[W, "<<",("<<i<<","<<j<<")"<<"]";
                    }else if(sq[i][j].getSquarecolor() == block_black){
                        std::cout<<"[B, "<<",("<<i<<","<<j<<")"<<"]";
                    }
                }

            }
        }
        std::cout<<std::endl;
    }
}

void Board::fill_pieces(int i, int j){
    
    // piusa
    if(i == 1){
        if(j%2 == 0){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Pius(pblack));
            sq[i][j].setSquarecolor(block_black);
        }else {
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Pius(pblack));
            sq[i][j].setSquarecolor(block_white);
        }
    }//piusa
    else if(i == 6){
        if(j%2 == 0){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Pius(pwhite));
            sq[i][j].setSquarecolor(block_white);
        }else {
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Pius(pwhite));
            sq[i][j].setSquarecolor(block_black);
        }
    }// others
    else if(i == 0){
      
        if(j == 0){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Elephant(pblack));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 1){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Horse(pblack));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 2){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Camel(pblack));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 3){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new King(pblack));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 4){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Mantri(pblack));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 5){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Camel(pblack));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 6){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Horse(pblack));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 7){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Elephant(pblack));
            sq[i][j].setSquarecolor(block_black);
        }
    }// others
    else if(i == 7){
        
        if(j == 0){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Elephant(pwhite));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 1){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Horse(pwhite));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 2){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Camel(pwhite));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 3){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new King(pwhite));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 4){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Mantri(pwhite));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 5){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Camel(pwhite));
            sq[i][j].setSquarecolor(block_white);
        }else if(j == 6){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Horse(pwhite));
            sq[i][j].setSquarecolor(block_black);
        }else if(j == 7){
            sq[i][j].setMyState(occupied);
            sq[i][j].setMyPiece(new Elephant(pwhite));
            sq[i][j].setSquarecolor(block_white);
        }
        
    }else{
        if(i%2 == 0){
            if(j%2 == 0){
                sq[i][j].setMyState(clean);
                sq[i][j].setSquarecolor(block_white);
            }else{
                sq[i][j].setMyState(clean);
                sq[i][j].setSquarecolor(block_black);

            }
        }else if(i%2 == 1){
            if(j%2 == 1){
                sq[i][j].setMyState(clean);
                sq[i][j].setSquarecolor(block_white);
            }else{
                sq[i][j].setMyState(clean);
                sq[i][j].setSquarecolor(block_black);
                
            }
        }
    }
}