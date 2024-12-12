#include"knight.h"

//------------------------------------
//Class Board function implementations
//------------------------------------

//Board class constructor for initializing a board with blank elements
Board::Board(){
    //Initialize all board elements to ' '
    board = new char*[8];

    for (int i=0; i<8; i++){
        board[i] = new char[8];
    }
}

//Board class destructor
Board::~Board(){
    for (int i=0; i<8; i++){
        delete[] board[i];
    }
    delete[] board;
}

//draw_board function
void Board::draw_board(){
    wcout << "\033[2J\033[H\n";
    wcout<<" ___ ___ ___ ___ ___ ___ ___ ___\n";
    board[0][0] = 'H';
    int count_rows{8};
    for (int i=0; i<8; i++){
        wcout<<"| ";
        for (int j=0; j<8; j++){
            if (board[i][j] == 'H'){
                wcout << L'\u265E'; //♞
                //wcout<<L"\U0001F4A9"; //💩
                wcout<<" | ";
            }
            else if(board[i][j] == 'X'){
                wcout<<L"\U0001F6A9"; //🚩
                //wcout<<L"\U0001F6BD"; //🚽
                //wcout << L'\u274C'; //❌
                wcout<<"| ";
            }

            else if(board[i][j] == '*'){
                wcout<<L'\U0001F4A3'; //💣
                //wcout << L'\u1F4A'; //alt bomb
                wcout<<"| ";
            }
            else{
                wcout<<(board[i][j])<< "  | ";
            }
        }
        wcout<<"  "<<count_rows;
        count_rows --;
        wcout<<"\n|___|___|___|___|___|___|___|___|\n";
    }
        wcout << "  A   B   C   D   E   F   G   H\n";
}


//-------------------------------------
//Class Figure function implementations
//-------------------------------------


//-----------------------------------
//Class Game function implementations
//-----------------------------------
//function that draws the board
void Game::draw_board(Board& b){
    b.draw_board();
}