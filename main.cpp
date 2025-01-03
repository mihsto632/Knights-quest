#include"knight.cpp"

int main(){

    //Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Set locale to support Unicode
    locale::global(locale("en_US.UTF-8")); // Set locale for Unicode
    wcout.imbue(locale("en_US.UTF-8")); // Set wcout to use UTF-8
    wcout << "\033[2J\033[H\n";

    Game g;
    Board b();
    g.set_game_mode(); // Player chooses between tutorial, easy, hard and survival
    g.setup_variables(b);
    g.generate_initial_mines(b);
    //g.draw_board(b);
    while (1){
        g.draw_board(b);
        g.make_move(b);
    }

    return 0;
}
