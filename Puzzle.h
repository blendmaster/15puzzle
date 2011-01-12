//Puzzle class header
//describes a slide puzzle of
//specified length and width

#pragma once
#include <cstdlib>
#include <iostream>

using namespace std;

const int MAX_DIMENSION = 10;

class Puzzle {
    private:
        int board[MAX_DIMENSION][MAX_DIMENSION]; //stores current state of the board.
        int width; //width of the board
        int height; //height of the board
        int blankX; //x position of the blank space
        int blankY; //y position of the blank space
        int turns; //number of turns taken this game
    public:
        Puzzle(); //creates a 4x4 puzzle
        Puzzle(int dimension); //creates a dimension x dimension puzzle
        Puzzle(int newWidth, int newHeight); //creates a width x height puzzle
        
        void setDimensions(int newWidth, int newHeight); //resets the puzzle with the new dimensions
        
        int getWidth () const ; //returns the width
        int getHeight () const ; //returns the height
        int getBoard(int x,int y) const; //returns tile at the board index specified
        int getTurns() const; //returns the current number of turns
        int getBlankX() const; //returns blankX
        int getBlankY() const; //returns blankY
        
        //both swap function increment "turns" by 1
        void swap(int x, int y); //swaps the tile at position x,y with the blank space, if possible
        void swap(int tile); //swaps the tile with "tile" on it with the blank space, if possible
        
        bool isSolved() const; // returns true if the puzzle is solved, i.e. in order
        
        ostream& output(ostream& os) const; //outputs board in a human readable format
        
        friend ostream& operator << (ostream& os, const Puzzle& p); //outputs the puzzle to os in nice looking format
        friend istream& operator >> (istream& is, Puzzle& p); //changes board state from input, i.e. a savefile
        
    private:
        void initPuzzle(); //fils the puzzle, in order, with the tiles neccesary
        void shufflePuzzle(); // randomly shuffles the tiles of the puzzle with FisherYates
        bool isSolvable(); //returns true if the current puzzle is solvable to the ascending order state
};

