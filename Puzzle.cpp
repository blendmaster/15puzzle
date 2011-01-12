//Puzzle class function implementation
#include <cstdlib>
#include <iostream>
#include "Puzzle.h" //can't forget this

//NOTE! THIS WAS CODED WHERE HEIGHT IS ACTUALLY A WIDTH, AND WIDTH IS ACTUALLY A HEIGHT
// sodday ;_;

//creates a 4x4 puzzle
Puzzle::Puzzle() {
    setDimensions(4, 4);
} 

//creates a dimension x dimension puzzle
Puzzle::Puzzle(int dimension) { //user provides dimentions
    setDimensions(dimension, dimension);
} 

//creates a width x height puzzle
Puzzle::Puzzle(int newWidth, int newHeight) {
    setDimensions(newWidth, newHeight);
} 
//This function sets the new dimentions of the puzzle and re-shuffles it.
void Puzzle::setDimensions( int newWidth, int newHeight) {
    width = newWidth ;
    height = newHeight ;  //It's not a square, so each dimention must be named
    turns = 0 ;
    do { //initialize it and shuffle it again until you come across a solvable one
        initPuzzle() ;
        shufflePuzzle() ;
        
        //cout << "Shuffled puzzle: \n";
        //output(cout);                             }this was used in debugging, but is no longer needed
        //system("PAUSE");
        
    } while ( !isSolvable() ) ;  //do it until it's solved
}

int Puzzle :: getWidth() const { //return the width. pretty simple
    return width ;
}
int Puzzle :: getHeight() const { //return the height. pretty simple
    return height ;
}

 //returns tile at the board index specified
int Puzzle::getBoard(int x,int y) const {
    return board[x][y] ;
}
 //returns the current number of turns
int Puzzle::getTurns() const {
    return turns;
}
//returns blankX
int Puzzle::getBlankX() const {
    return blankX ; //Remember, blankX is only an index. it is not an actual value
} 
 //returns blankY
int Puzzle::getBlankY() const {
    return blankY ;  //Remember, blankX is only an index. it is not an actual value
}

//swaps the tile at position x,y with the blank space, if possible
void Puzzle::swap(int x, int y) {
    //cout << "swapping (" << blankX << "," << blankY << ") with ("
    //     << x << "," << y << ")...\n";
    //system("PAUSE");
    
    //Check to make sure that the user wants to move a valid space
    if ( x >= width || y >= height || x < 0 || y < 0 ) { //you can't move here
        cout << "Error. You can't move off the board!" << endl ;
        system("PAUSE") ;
        return ;
    } 
    board[blankX][blankY] = board[x][y]; //move tile to the blank space
    board[x][y] = width*height ; //change moved tile to a blank space
    //update blankX and Y to the new blank space
    blankX = x;
    blankY = y;
    turns++ ; //both swap functions increment "turns" by 1
} 

//swaps the tile with "tile" on it with the blank space, if possible
void Puzzle::swap(int tile) {
    int x = -1; //initialize a few integers that will be used later
    int y = -1;
    
    //Go throught array and look for the "tile" that was specified
    for ( int a = 0 ; a < width ; a++ ) {
        for ( int b = 0 ; b < height ; b++ ) {
            if ( board[a][b] == tile ) { //once you find the tile that was specified,
                x = a ; //save those values
                y = b ;
                break ; //once you've found what you're looking for, quit looking and do the swap
            }
        }
    }
    //Base the swap function that will now go
    swap(x,y); //both swap functions increment "turns" by 1
} 

// returns true if the puzzle is solved, i.e. in order
bool Puzzle::isSolved() const {
    int prevtile = 0 ; //initialize an integer to store the previous tile
    //Go throught array and make sure every tile is greater than the last tile
    for ( int a = 0 ; a < width ; a++ ) {
        for ( int b = 0 ; b < height ; b++ ) {
            if ( board[a][b] < prevtile ) { //If the tile after is greater than the tile before, it isn't solved
                return false ;
            }
            prevtile = board[a][b] ; //the previous tile is now the one that you just fixed
        }
    }
    return true ; //if you never hit a spot where it's wrong, it's right.
} 

//outputs the board in a pretty format to os
ostream& Puzzle::output(ostream& os) const {
    //output underscores
    for(int i = 0; i < height; i++) {
            os << " ____";
    }
    os << " \n";
    for ( int a = 0 ; a < width ; a++ ) {
        //output pipes |
        for( int i = 0; i < height; i++) {
            os << "|    ";    
        }
        os << "|\n";
        for ( int b = 0 ; b < height ; b++ ) { //also account for the numbers that take up the space of two digits
            if( board[a][b] < width*height && board[a][b] < 10 ) {
                os << "| " << board[a][b] << "  ";
            } else if( board[a][b] < width*height && board[a][b] >= 10 ) { //anything above ten takes up extra space
                os << "| " << board[a][b] << " ";
            } else { //blank space
                os << "|    ";
            }
        }
        os << "|\n";
        //output pipes |
        for( int i = 0; i < height; i++) {
            os << "|    ";    
        }
        os << "|\n";
        //output base
        for(int i = 0; i < height; i++) {
            os << "|____";
        }
        os << "|\n";
    }
    return os ; //return the ostream
}

//outputs the puzzle to os in a plain format
ostream& operator << (ostream& os, const Puzzle& p) {
    os << p.turns << endl; //The order of this part doesn't matter as long as you keep it consistant
    os << p.width << endl;
    os << p.height << endl;
    os << p.blankX << endl;
    os << p.blankY << endl;
    //go through the array and print each number, followed by a space
    //the space makes the istream function easier to write
    for ( int a = 0 ; a < p.width ; a++ ) {
        for ( int b = 0 ; b < p.height ; b++ ) {
            os << p.board[a][b] << " ";
        }
    }
    os << endl;
    return os; //return that ostream
} 


//changes board state from input, i.e. a savefile
istream& operator >> (istream& is, Puzzle& p) {
    //It's important to keep the order consistant with the ostream function
    is >> p.turns;
    if( p.turns < 0 ) { //Check to make sure this particular input is valid
        cout << "Invalid turns value. Defaulting to 0";
        p.turns = 0;
        is.setstate(ios::failbit); //this is only if the input fails and is not as expected
        return is ;
    }
    is >> p.width;
    if( p.width < 0 ) { //Check to make sure this particular input is valid
        cout << "Invalid width value. Defaulting to 4";
        p.width = 4;
        is.setstate(ios::failbit);//this is only if the input fails and is not as expected
        return is ;
    }
    is >> p.height ;
    if( p.height < 0 ) { //Check to make sure this particular input is valid
        cout << "Invalid height value. Defaulting to 4";
        p.height = 4;
        is.setstate(ios::failbit);//this is only if the input fails and is not as expected
        return is ;
    }
    is >> p.blankX;
    if( p.blankX < 0 || p.blankX >= p.width ) { //Check to make sure this particular input is valid
        cout << "Invalid blankX value. Defaulting to 0";
        p.blankX = 0;
        is.setstate(ios::failbit);//this is only if the input fails and is not as expected
        return is ;
    }
    is >> p.blankY;
    if( p.blankY < 0 || p.blankY >= p.height ) { //Check to make sure this particular input is valid
        cout << "Invalid turns value. Defaulting to 0";
        p.blankY = 0;
        is.setstate(ios::failbit);//this is only if the input fails and is not as expected
        return is ;
    }

    for ( int a = 0 ; a < p.width ; a++ ) { //read in the array values too
        for ( int b = 0 ; b < p.height ; b++ ) {
            is >> p.board[a][b] ;
            if( p.board[a][b] > p.width*p.height ) { //Check to make sure this particular input is valid
                cout << "Invalid board value. Defaulting to 0";
                p.board[a][b] = 0;
                is.setstate(ios::failbit);//this is only if the input fails and is not as expected
                return is ;
            }
        }
    } 
    //yey, everthing read correctly
    return is ;
}

//fils the puzzle, in order, with the tiles neccesary
void Puzzle::initPuzzle() {
    for ( int a = 0 ; a < width ; a++ ) {
        for ( int b = 0 ; b < height ; b++ ) {//go through the array, and as you do...
            //cout << "putting " << (b+1) + height*a << " at (" << a << "," << b << ")...\n";
            
            board[a][b] = (b+1) + height*a ; //fill in the array with appropriate numbers
            //(above) '+1' accounts for array indexing, width*a acounts for where in the array you are
        }
    }
    blankX = width-1 ; //the blank index will be the bottom right of the puzzle. 
    blankY = height-1 ; //subtract one for the array indexing
    
    //cout << "puzzle init!\n";
} 

// randomly shuffles the tiles of the puzzle with FisherYates
void Puzzle::shufflePuzzle() {
    //this is how to use a fisheryates to shuffle a 2D array
    for ( int i = width*height-1 ; i > 0 ; i-- ) {
        int r = rand() % i; //0 <= r < 1 before the current tile
        //cout << "switching " << i << " and " << r << "...\n";
        int buffer = board[i/height][i%height]; //the buffer is created as a means of temporarily holding the extra value 
        board[i/height][i%height] = board[r/height][r%height];
        board[r/height][r%height] = buffer;
    }
    
    //update blankX and blankY
    for ( int a = 0 ; a < width ; a++ ) { //read in the array values too
        for ( int b = 0 ; b < height ; b++ ) {
            if( board[a][b] == width*height ) {
                blankX = a;
                blankY = b;
                break;    
            }        
        }
    }
    
    //cout << "puzzle shuffled!\n";
} 

//returns true if the current puzzle is solvable to the ascending order state
//according to the algorithm at
// http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
bool Puzzle::isSolvable() {
    int inversions = 0;
    //check every tile against each tile after it
    //counting inversions as we go
    for ( int a = 0 ; a < width ; a++ ) {
        for ( int b = 0 ; b < height ; b++ ) {
            //for each tile after the current
            for ( int i = a ; i < width ; i++ ) {
                //skip blank space
                if( board[a][b] != width*height ) {
                    for ( int j = 0 ; j < height ; j++ ) {
                        //if this tile is less than the tile we started on
                        if( !(i == a && j <= b ) && (board[i][j] < board[a][b]) ) {
                            //cout << board[i][j] << " is less than " << board[a][b] << "! incrementing inversions...\n";
                            
                            inversions++;
                        }
                    }
                }
            }
        }
    }
    
    //cout << "there are " << inversions << " inversions in this puzzle.\n";
    
    //If solvable, return true
    //If the grid width is odd, then the number of inversions in a solvable solution is even
    if ( inversions % 2 == 0 && height % 2 == 1 ) {
        //cout << "puzzle solvable!\n";
        return true ;
    }
    //If the grid width is even and the blank is on an odd row counting from the bottom,
    //then the number of inversions in a solvable situation is even
    if ( ( width - blankX ) % 2 == 1 && height % 2 == 0 && inversions % 2 == 0 ) {
        //cout << "puzzle solvable!\n";
        return true ;
    }
    //If width is even and blank is on an even row from bottom, then inversions must be odd
    if ( ( width - blankX ) % 2 == 0 && height % 2 == 0 && inversions % 2 == 1 ) {
        //cout << "puzzle solvable!\n";
        return true ;
    }
    
    //cout << "puzzle not solvable!\n";
    return false ; //if none of the right situations arise, it isn't solvable
} 
