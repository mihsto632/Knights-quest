#include"knight.cpp"

int main(){

    //Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Set locale to support Unicode
    //locale::global(locale("en_US.UTF-8")); // Set locale for Unicode
    setlocale(LC_ALL, "en_US.UTF-8");
    wcout.imbue(std::locale(""));
    wcout << "\033[2J\033[H\n";

    //Creating class objects
    Game g;
    Board b;

    //Setting up variables and game modes
    g.set_game_mode(); // Player chooses between tutorial, easy, hard and survival
    g.setup_variables(b);
    g.generate_initial_mines(b);

    //Infinite while loop of making moves until an ending condition has been met
    while (1){
        g.draw_board(b);
        g.make_move(b);
    }

    return 0;
}
