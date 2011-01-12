// 15 Puzzle driver program. Loads a save state, if neccesary
// and provides a user interface to the 15 puzzle
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Puzzle.h" //can't forget this

using namespace std;

int main()
{
    srand(time(NULL)); //initialize seed to time
    string answer ; //declare an input answer provided by the user
    Puzzle p; //make a puzzle
    
    int letterCount = 0;
    cout << "letterCount == " << letterCount << endl;
    
    
    
    //First, ask the user if he would like to hear the directions
    cout << "Would you like to hear the directions? y for 'yes' n for 'no.'  " << flush ;
    cin >> answer ;//If yes, provide the directions
    if ( answer == "y" || answer == "Y" ) {
        cout << endl ;
        cout << "Solve the puzzle by arranging the tiles in ascending order. To move " << endl ;
        cout << "tiles, choose a tile to slide into the blank space. The fewer turns  "<< endl ;
        cout << "it takes you to solve the puzzle, the better." << endl ;
        cout << "w: slides a tile downward into the blank space. " << endl ;
        cout << "a: slides a tile right into the blank space. " << endl ;
        cout << "s: slides a tile upward into the blank space. " << endl ;
        cout << "d: slides a tile left into the blank space. " << endl << endl ;
    } //next, ask if the user would like to load a previous game
    cout << "Would you like to load a previous game? y for 'yes' n for 'no.'  " << flush ;
    cin >> answer ; //if yes, try to find it
    if ( answer == "y" || answer == "Y" ) {
        cout << "enter the filename you saved to: "; cin >> answer;
        ifstream infile(answer.c_str());
        if(!infile) { //check for error
            cout << "error reading infile. byebye\n";
            system("PAUSE");
            exit(1);    
        }
        //then try to read it
        if ( !(infile >> p) ) {//check for error again
            cout <<"Error. Invalid save file." << endl ;
            system("PAUSE") ;
            exit(1) ;
        }
        infile.close() ; //always close the file
    } else {
        do {//then ask what size puzzle they want
            cout << "Would you like a custom size puzzle? ( default 4x4 ) \ny for 'yes' n for 'no.' "; cin >> answer;
            if ( answer == "y" || answer == "Y" ) {
                int height, width = 0; //read in the dimentions
                cout << "How tall would you like your puzzle? "; cin >> width;
                cout << "How wide would you like your puzzle? "; cin >> height;
                p.setDimensions(width,height);
                break ;
            }
            if ( answer == "n" || answer == "N" ) {
                break ;
            } //check for error on their input
            cout << "Error. Invalid input." << endl ;
        } while ( !( answer == "y" || answer == "Y" || answer == "n" || answer == "N" ) ) ;
    }
    
    //This is the actual game
    do {
        system("cls"); //clear console
        p.output(cout); //print puzzle
        
        //take input
        cout << p.getTurns() << " moves taken so far.\n";
        cout << "enter w,a,s, or d to move the tile that direction into the blank space." << endl ;
        cout << "Also, at any time, enter \"save\" to save, and \"quit\" to quit.\n";
        cin >> answer ;//And then make the moves
        if ( answer =="w" ) { //the +1 or -1 determines what piece will be swapped
            p.swap( p.getBlankX() - 1 , p.getBlankY() ) ;
            continue;
        }
        if ( answer =="s" ) {
            p.swap( p.getBlankX() + 1 , p.getBlankY() ) ;
            continue;
        }
        if ( answer =="a" ) {
            p.swap( p.getBlankX() , p.getBlankY() - 1 ) ;
            continue;
        }
        if ( answer =="d" ) {
            p.swap( p.getBlankX() , p.getBlankY() + 1) ;
            continue;
        }
        //if they ever want to save the game, let them.
        if(answer == "save") {
            cout << "enter file name to save to: "; cin >> answer;
            cout << "\nsaving to " << answer << "...\n";
            ofstream outfile(answer.c_str());//save the game
            if(!outfile) {//make sure the file was read correctly
                cout << "error reading outfile. try again \n";
                system("PAUSE");
                exit(1);    
            } else {
                outfile << p; //save the game
            }
            outfile.close(); //always close the file
            continue;
        }
        //and let them quit if they want to 
        if (answer == "quit" ) {
            cout << "byebye\n\n";
            system("PAUSE");
            return 0;
        }   
    } while(!p.isSolved());
    //game over
    system("cls"); //clear console
    p.output(cout); //print puzzle
    cout << "YOU WIN!!!" << endl ; //tell them they won
    cout << " Total turns :  " << p.getTurns() << endl ; //tally the moves
    if ( p.getWidth() == 4 && p.getTurns() > 90 ) {
        cout << "Weak... that took you too long." << endl ;                 //the following is a list of senarios that constitute how well
    } else if ( p.getWidth() == 4 && p.getTurns() < 30 ) {                  //the player solved the puzzle
        cout << "Good Work :-) You're quick." << endl ;
    } else if (p.getWidth() == 4) {
        cout << "Not bad, but you could have done better." << endl ;
    }
    if ( p.getWidth() == 3 && p.getTurns() > 60 ) {
        cout << "Weak... that took you too long." << endl ;
    } else if ( p.getWidth() == 3 && p.getTurns() < 30 ) {
        cout << "Good Work :-) You're quick." << endl ;
    } else if (p.getWidth() == 3) {
        cout << "Not bad, but you could have done better." << endl ;
    }
    if ( p.getWidth() == 2 && p.getTurns() > 10 ) {
        cout << "Weak... that took you too long." << endl ;
    } else if ( p.getWidth() == 2 && p.getTurns() < 4 ) {
        cout << "Good Work :-) You're quick." << endl ;
    } else if (p.getWidth() == 2) {
        cout << "Not bad, but you could have done better." << endl ;
    }
    //and now that everything is done, it's time to quit
    system("PAUSE");
    return 0;
}
