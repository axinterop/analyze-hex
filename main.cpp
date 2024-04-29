#include <iostream>
#include "Board.h"

using namespace std;

int main() {
    while (!cin.eof()) {
        Board B{};
        if (!B.init())
            continue;
        B.read();
        B.read_reqs();
        B.create_graphs();

//
        if (B.is_correct())
            B.is_game_over();
        else
            cout << "NO\n";

//        B.is_game_over();


//        B.is_game_over();

//        B.print_graphs();
//        B.print_stats();
//        B.print_matrix();
        cout << endl;
    }
    return 0;
}
