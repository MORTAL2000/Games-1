//
//  Pieces.cpp
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#define SIZE 8

#include "Pieces.hpp"
#include <stdio.h>


bool Elephant::valid_move(int cur, int des){
    
    
    
    return true;
}

std::string Elephant::display_char(){
    
    return "E";
}

pcolor Elephant::getMyPColor(){
    return mypcolor;
}



bool Horse::valid_move(int cur, int des){
    
    
    return true;
}

std::string Horse::display_char(){
    
    return "H";
}

pcolor Horse::getMyPColor(){
    return mypcolor;
}


bool Camel::valid_move(int cur, int des){
    
    
    return true;
}
std::string Camel::display_char(){
    
    return "C";
}

pcolor Camel::getMyPColor(){
    return mypcolor;
}

bool Mantri::valid_move(int cur, int des){
    
    
    
    return true;
}

std::string Mantri::display_char(){
    
    return "M";
}

pcolor Mantri::getMyPColor(){
    return mypcolor;
}

bool King::valid_move(int cur, int des){
    
    
    
    return true;
}



std::string King::display_char(){
    
    return "K";
}

pcolor King::getMyPColor(){
    return mypcolor;
}

bool Pius::valid_move(int cur, int des){
    
    
    return true;
}

std::string Pius::display_char(){
    
    return "P";
}

pcolor Pius::getMyPColor(){
    return mypcolor;
}
