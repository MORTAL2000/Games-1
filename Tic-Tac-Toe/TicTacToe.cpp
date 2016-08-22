#include "TicTacToe.hpp"
#include "Tree.hpp"

#define RED_TEXT    "\e[31;1m"
#define YELLOW_TEXT "\e[33;1m"
#define DEFAULT     "\e[0m"

TicTacToe::TicTacToe():turn(true),cur_state(size){
    for(auto &it : cur_state){
        it.resize(size,EMPTY);
    }
    //my_tree = new Tree;
    my_tree = std::make_shared<Tree>();
}


int TicTacToe::print(){
     
    int count      = 0;
    int a          = 0;
    int length     = 3*size; 
    int endl_count = 0;

    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            
            if (count == 0){
                for(a = 0; a < length; a++){
                    if( (a+1)%3 == 0) std::cout << " |";
                    else std::cout << " ";
                }
                count++;
                endl_count++;
                std::cout << std::endl;
            }
            if (count == 1){
                for( a = 0; a < 3; a++){      
                    if(a == 1){
                        if(cur_state[i][j] == HASX) 
                            std::cout << "X";
                        else if(cur_state[i][j] == HASO)    
                            std::cout << "O"; 
                        else std::cout << " ";
                    }
                    else if( (a+1)%3 == 0) std::cout << " |";
                    else std::cout << " ";
        
                }
                if( j == 2 ){
                    count++;
                    endl_count++;
                    std::cout << std::endl;
                } 
            }
            if (count == 2){
                for(a = 0; a < length; a++){
                    if( i < 2){  
                        if((a+1)%3 == 0) std::cout << "_|";
                        else std::cout << "_";
                    }else{
                        if((a+1)%3 == 0) std::cout << " |";
                        else std::cout << " ";
                    }
                }
            }
        }
        count = 0;
        endl_count++;
        std::cout << std::endl;
    }
    return endl_count;
}

void TicTacToe::parse_value(std::string s, int& x, int& y){
    
    int i = 0;
    int count = 0;
    while ( s[i] != '\0' ){
        if(s[i] == ' ') {
            i++;
            continue;
        }else{
            //std::cout << "In else : i = " << i <<": s[i] = " << s[i] << std::endl;
            // Major logic failure here 
            if(s[i+1] != ' ' && s[i+1] != '\0' )
                throw std::invalid_argument(" Please Enter x and y in range of 0-2           "); 
            if(count == 0){
                count++;    
                x = s[i] - '0';
              //  std::cout << "x = " << x << std::endl;
                if((x > 2) || (x < 0)) 
                    throw std::invalid_argument(" Please Enter x in range of 0-2             ");
                i++;
                continue;
            }else if(count == 1){
                count++;
                y = s[i] - '0';
              //  std::cout << "y = " << y << std::endl;
                if((y > 2) || (y < 0)) 
                    throw std::invalid_argument(" Please Enter y in range of 0-2              ");
                break;
            }
            
        }
    }
}

// This function sets the state of the i j index. 
// If the i and j  already contains state other then empty throw exception prompting to 
// enter different index 
    
void TicTacToe::set_state(int i, int j, state s){
    
    if( cur_state[i][j] != EMPTY) 
        throw std::invalid_argument("The index you entered already taken            ");
    cur_state[i][j] = s;
}

void TicTacToe::run(){
    int x;
    int y;
    int step  = 0;//size*size + 1;
    int state = 0;
    std::string my_string;

    std::cout << YELLOW_TEXT;
    std::cout << "                  Welcom to TicTacToe           \n";
    std::cout << "     Please enter input via X and Y cordinate:   " << std::endl;
    std::cout << "eg: 1 2 if you enter 1 and 2 the X co-ordinate and Y co-ordinate" << std::endl;
    std::cout << DEFAULT;
    std::cout << std::endl;
    while(state == 0){
        step = print();
       // print_state();
        //std::cout << "Please enter co-ordinates seperated by space            \n";
        if(turn){ 
            step++;
            std::cout << "Its X turn >>  "  << " : ";
            // google : wiki ANSI escape code for more detail
            // zero (or missing), clear from cursor to the end of the line.
            std::cout << "\033[0K";
            std::getline(std::cin,my_string);
        }    
        else{ 
            //std::cout << "Its O turn >> ";
            // google : wiki ANSI escape code for more detail
            // zero (or missing), clear from cursor to the end of the line.
            std::cout << "\033[0K";
        }

        //if(step > 12) step = 12;
        try{
            parse_value(my_string,x,y);
            if(turn){
                try{
                    set_state(x,y, HASX);
                    turn = give_turn(); // This is nor proper place for this
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    step++;
                }
            }
            else{
                try{
                //set_state(x, y, HASO);
                // This is machine turn now
                 machine_set_state(HASO);
                turn = give_turn(); // This is nor proper place for this
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    step++;
                }
            }
            //std::cout << " You Entered  " << x << " , " <<  y <<"                  "<< std::endl;
            //std::cout << "\033[2k";
        } catch( std::invalid_argument& e){
            std::cout << e.what() << std::endl;
        }
        roll_back(step);
        state = game_state();
    }
    step = print();
    std::cout << std::endl;
    std::cout << RED_TEXT;
    if ( state == 1) std::cout << "HUMAN WON: Congratulaton Your Sneaky Baster " << std::endl;
    else if ( state == 2) std::cout << "Computer WON .. Now I head for world domination "<< std::endl;
    else if ( state == 3) std::cout << "There was a DRAW!!  " << std::endl;
    std::cout << DEFAULT;

}

void TicTacToe::minimax(int& x, int& y){
    // latter I could ask user for algorithm that they want 
    // and use switch to select the proper 
    // algorithm 
    my_tree->minimax(x, y, cur_state);

}
    
// this function calls set_state by providing 
// appropriate x and y
void TicTacToe::machine_set_state(state s){

    int x;
    int y;
    
    //std::cout << "entering machine setting for  x  = " << x << " ,  y = " << y << std::endl;
    minimax(x, y); 

    //std::cout << "got machine setting of x  = " << x << " ,  y = " << y << std::endl;
    set_state(x, y, s);
}

int TicTacToe::game_state(){
 
    // use for loop here 

    int mcount = 0;    
    // if x win return 1 
    if( (cur_state[0][0] == HASX) && (cur_state[0][1] == HASX) && (cur_state[0][2] == HASX))
        return 1;
    else if( (cur_state[1][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[1][2] == HASX))
        return 1;
    else if( (cur_state[2][0] == HASX) && (cur_state[2][1] == HASX) && (cur_state[2][2] == HASX))
        return 1;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][2] == HASX))
        return 1;
    else if( (cur_state[2][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[0][2] == HASX))
        return 1;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][0] == HASX) && (cur_state[2][0] == HASX))
        return 1;
    else if( (cur_state[0][1] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][1] == HASX))
        return 1;
    else if( (cur_state[0][2] == HASX) && (cur_state[1][2] == HASX) && (cur_state[2][2] == HASX))
        return 1;
 
  //  if o win return 2   
    else if( (cur_state[0][0]  == HASO) && (cur_state[0][1]  == HASO) && (cur_state[0][2]  == HASO))
        return 2;
    else if( (cur_state[1][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[1][2]  == HASO))
        return 2;
    else if( (cur_state[2][0]  == HASO) && (cur_state[2][1]  == HASO) && (cur_state[2][2]  == HASO))
        return 2;
    else if( (cur_state[0][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[2][2]  == HASO))
        return 2;
    else if( (cur_state[2][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[0][2]  == HASO))
        return 2;
    else if( (cur_state[0][0] == HASO) && (cur_state[1][0] == HASO) && (cur_state[2][0] == HASO))
        return 2;
    else if( (cur_state[0][1] == HASO) && (cur_state[1][1] == HASO) && (cur_state[2][1] == HASO))
        return 2;
    else if( (cur_state[0][2] == HASO) && (cur_state[1][2] == HASO) && (cur_state[2][2] == HASO))
        return 2;
 
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            if( (cur_state[i][j] == HASO) || (cur_state[i][j] == HASX))
                mcount++;
        }
    }
    if (mcount == (size*size)) return 3;

    else return 0;
}

bool TicTacToe::give_turn(){
    // we can use bit toggle here 
    // true means turn of X
    if(turn) {
        turn = false;
        return turn;       
    }
    else {
        turn = true;
        return turn;
    }   
}


void TicTacToe::roll_back(int step){
    for(size_t i = 0; i < step; i++)std::cout << "\e[A";
}

void TicTacToe::print_state(){

    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            
            std::cout << cur_state[i][j] << "  ";
    
        }
        std::cout << std::endl;
    }

}
