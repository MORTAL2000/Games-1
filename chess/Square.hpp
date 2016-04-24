//
//  Square.hpp
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <iostream>
#include "Pieces.hpp"

enum state { clean, occupied };
enum block_color { block_black, block_white};

class Square{

private:
    block_color mycolor;
    state mystate;
    Pieces* mypiece;
    
    
public:
    void setMyState(state s);
    state getMyState(void);
    
    void setMyPiece(Pieces *p);
    
    void setSquarecolor(block_color c);
    
    block_color getSquarecolor(void);
    
    Pieces * getMypiece();
};

#endif /* Square_hpp */
