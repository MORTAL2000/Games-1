//
//  Square.cpp
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#include "Square.hpp"

void Square::setMyState(state s){
    mystate = s;
}

state Square::getMyState(){
    return mystate;
}

void Square::setMyPiece(Pieces *p){
    mypiece = p;
}

void Square::setSquarecolor(block_color c){
    mycolor = c;
}

block_color Square::getSquarecolor(void){
    return mycolor;
}

Pieces *Square::getMypiece(){
    return mypiece;
}