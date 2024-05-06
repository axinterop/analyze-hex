#include "Board.h"
#include <iostream>

int main() {
    while (!cin.eof()) {
        Board B{};
        if (!B.init())
            continue;
        B.read();
        B.read_reqs();
        B.create_graphs();

        B.OI.BOARD_SIZE = B.size;

        B.OI.PAWNS_NUMBER = B.pawns_total();

        B.OI.IS_BOARD_CORRECT = B.is_correct();

        B.OI.IS_GAME_OVER = B.is_game_over();

        B.OI.IS_BOARD_POSSIBLE = B.is_possible();

        B.print_reqs();
    }

    return 0;
}
