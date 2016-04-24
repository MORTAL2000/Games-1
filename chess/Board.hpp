//
//  Board.h
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//



#ifndef Board_h
#define Board_h

#define SIZE 8


#include "Square.hpp"

class Board{
   
private:
    Square sq[8][8];
    
public:

    Board();
    
    void display();
    void fill_pieces(int i, int j);
};

#endif /* Board_h */
