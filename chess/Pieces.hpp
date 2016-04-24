//
//  Pieces.h
//  Chess
//
//  Created by Bibek Ghimire on 4/23/16.
//  Copyright © 2016 Bibek Ghimire. All rights reserved.
//

#ifndef Pieces_h
#define Pieces_h

#include <string>

enum pcolor { pblack, pwhite};

class Pieces{

protected:
    pcolor mypcolor;
    
public:
    virtual bool valid_move(int cur, int des) = 0;
    virtual std::string display_char()=0;
    
    virtual pcolor getMyPColor() = 0;

    
};

class Elephant:public Pieces{
    
public:
    Elephant( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();

};

class Horse:public Pieces{
    
    
public:
    Horse( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();
};

class Camel:public Pieces{
    
public:
    Camel( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();
};
class Mantri:public Pieces{
    
public:
    Mantri( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();
};
class King:public Pieces{
    
public:
    King( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();
};
class Pius:public Pieces{
    
public:
    Pius( pcolor p){
        mypcolor = p;
    }
    
    bool valid_move(int cur, int des);
    std::string display_char();
    pcolor getMyPColor();
};



#endif /* Pieces_h */
