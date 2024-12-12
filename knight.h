//-------------------------------------------------------------
// KNIGHT.H FILE FOR INITIALIZING CLASSES AND GENERIC FUNCTIONS
//-------------------------------------------------------------

#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>

using namespace std;

//----------------------------
//Initializing the board class
//----------------------------
class Board{
    public:
        
    private:
        void draw_board();
        bool check_board_state();
        void generate_initial_mines();
        void generate_additional_mines();
        void remove_mines();
        void generate_flags();
};

//-----------------------------
//Initializing the figure class
//-----------------------------
class Figures{
    public:
    private:
        bool check_move_legality(); //When figures other than knight are implemented, type of figure should be a function parameter
        void make_the_move(); //Logic resembling if (check_move_legality == true) do_the_move
};

//---------------------------
//Initializing the Game class
//---------------------------
class Game{
    private:
        void add_figure(); //adds an object of class figure
        void add_board(); //adds an object of class Board
        void setup_variables();
        void enter_name();
        void show_scoreboard();
};

//------------------------------
//Initializing generic functions
//------------------------------

#endif