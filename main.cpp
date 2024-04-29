#include <iostream>
#include "Board.h"

using namespace std;

int main() {
    int inp = -1;
    while (!cin.eof()) {
        Board B{};
        if (!B.init())
            continue;
        B.read();
        inp += 2;
        B.read_reqs();
        B.create_graphs();

        {
            if (B.is_correct()) {
                FIELD_TYPE won = B.is_game_over();
                if (won == RED)
                    cout << "YES RED\n";
                else if (won == BLUE)
                    cout << "YES BLUE\n";
                else
                    cout << "NO\n";
            } else
                cout << "NO\n";
            cout << endl;
        }

    }


    return 0;
}
