//-------------------------------------------------------------
// KNIGHT.H FILE FOR INITIALIZING CLASSES AND GENERIC FUNCTIONS
//-------------------------------------------------------------

#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>
#include<cstring>
//Libraries that allow the use of unicode
#include<locale>
#include<codecvt>
////Libraries that allow exception handling methods outOfRangeExcetion and invalid_argumet
#include<stdexcept>
#include<limits>

using namespace std;

//----------------------------
//Initializing the board class
//----------------------------
class Board{
    private:
        char** board;
    public:
        void draw_board();
        bool check_board_state();
        void generate_initial_mines();
        void generate_additional_mines();
        void remove_mines();
        void generate_flags();
        Board();
        ~Board();
        friend class Game;
};

//-----------------------------
//Initializing the figure class
//-----------------------------
class Figure{
    private:
    public:
        bool check_move_legality(); //When figures other than knight are implemented, type of figure should be a function parameter
        void make_move(); //Logic resembling if (check_move_legality == true) do_the_move
        bool check_player_input();
        friend class Game;
};

//---------------------------
//Initializing the Game class
//---------------------------
class Game{
    public:
        void draw_board(Board& b);
        void add_figure(Figure& f); //adds an object of class figure
        void setup_variables();
        void enter_name();
        void show_scoreboard();
};

//------------------------------
//Initializing generic functions
//------------------------------
int generate_random_number_1_8();
void read_from_file();
void write_to_file();

#endif