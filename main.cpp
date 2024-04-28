#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

using namespace std;

typedef enum {
    EMPTY,
    RED,
    BLUE,
} FIELD_TYPE;

typedef struct {
    int size;
    int height;
    int fields_total;
    int pawns_red;
    int pawns_blue;
    int *matrix;
} Board;


int power_of_ten(int n) {
    int r = 0;
    while (n) {
        if (n / 10 > 0) {
            r++;
        }
        n /= 10;
    }
    return r;
}

void print_board_as_square(int BOARD[], int BOARD_SIZE) {
    if (power_of_ten(BOARD_SIZE) >= 1) {
        cout << " ";
    }
    cout << "  x ";
    for (int k = 0; k < BOARD_SIZE; k++)
        cout << k % 10 << " ";
    cout << endl;
    cout << "y   ";
    for (int k = 0; k < BOARD_SIZE; k++) {
        cout << "--";
    }
    cout << endl;
    for (int y = 0; y < BOARD_SIZE; y++) {
        cout << y;
        for (int j = 0; j < power_of_ten(BOARD_SIZE) + 1 - power_of_ten(y); j++)
            cout << " ";
        cout << "| ";

        for (int x = 0; x < BOARD_SIZE; x++) {
            int c = BOARD[y * BOARD_SIZE + x];
            if (c == EMPTY)
                cout << "_ ";
            if (c == RED)
                cout << "r ";
            if (c == BLUE)
                cout << "b ";
        }
        cout << endl;
    }
}

void board_read(Board *B) {
    string response;
    for (int row = 1; row < B->height; row++) {
        getline(cin, response);

        int empties = 0;
        int reds = 0;
        int blues = 0;
        int emptyCount = 0;
        bool valid = false;
        bool count_empty = false;
        int in_this_row = -1;
        FIELD_TYPE ft = EMPTY;
        for (char P: response) {
            if (P == '<') count_empty = true;
            if (count_empty && P == ' ') emptyCount++;
            if (emptyCount == 3) {
                empties++;
                ft = EMPTY;
                count_empty = false;
                valid = true;
            }
            if (P == 'r') {
                reds++;
                ft = RED;
                valid = true;
            }
            if (P == 'b') {
                blues++;
                ft = BLUE;
                valid = true;
            }

            if (valid) {
                in_this_row++;
                valid = false;
                emptyCount = 0;

                int startIndex = 0;
                if (row <= B->size)
                    startIndex = (row - 1) * B->size;
                else if (row > B->size) {
                    startIndex = B->fields_total - 2 * B->size + row;
                }

                int index = startIndex - in_this_row * (B->size - 1);
                B->matrix[index] = ft;
            }
        }

        B->pawns_red += reds;
        B->pawns_blue += blues;
    }
    getline(cin, response);
};

bool board_init(Board *B) {
    string response;
    getline(cin, response);
    if (response.size() < 4 || isalnum(response[0]))
        return false;

    signed char ch = 0;
    int c = 0;
    for (int i = 0; i < response.size(); i++) {
        ch = response[i];
        if (ch == ' ')
            c++;
        else
            break;
    }

    int board_size = c / 3 + 1;
    int board_height = board_size * 2;
    int board_fields_num = board_size * board_size;

    B->size = board_size;
    B->height = board_height;
    B->fields_total = board_fields_num;
    B->pawns_red = 0;
    B->pawns_blue = 0;
    B->matrix = (int *) calloc(board_fields_num, sizeof(*B->matrix));

    return true;
}

void board_destroy(Board *B) {
    free(B->matrix);
}

void read_reqs() { return; };

bool is_board_correct(Board *B) {
    int pawn_diff = B->pawns_red - B->pawns_blue;
    if (pawn_diff == 0 | pawn_diff == 1) {
        cout << "YES" << endl;
        return true;
    } else {
        cout << "NO" << endl;
        return false;
    }
};

void posibilities_for_pos(Board *B, int arr[], int pos) {
    int cur_p = pos;
    int next_poses[6] = {
            cur_p - (B->size + 1),
            cur_p - B->size,
            cur_p - 1,
            cur_p + 1,
            cur_p + B->size,
            cur_p + B->size + 1,
    };
    for (int i = 0; i < 6; i++) {
        int next_p = next_poses[i];
        if (!(next_p >= 0 && next_p < B->fields_total))
            next_p = -1;
        if (B->size > 2) {
            if (cur_p % B->size == 0 && next_p % B->size == B->size - 1)
                next_p = -1;
            if (cur_p % B->size == B->size - 1 && next_p % B->size == 0)
                next_p = -1;
        } else {
            if (cur_p % B->size == 0 && next_p == cur_p - 1)
                next_p = -1;
            if (cur_p % B->size == B->size - 1 && next_p == cur_p + 1)
                next_p = -1;
        }
        arr[i] = next_p;
    }
}

bool blue_won(Board *B) {
    Graph g(B->fields_total);
    // Check for blue
    vector<int> start_vertices;
    for (int cur_p = 0; cur_p < B->fields_total; cur_p++) {
        if (B->matrix[cur_p] == FIELD_TYPE::BLUE) {
            if (cur_p / B->size == 0)
                start_vertices.push_back(cur_p);
            int moves[6] = {};
            posibilities_for_pos(B, moves, cur_p);
            for (int next_p: moves)
                if (next_p != -1 && B->matrix[next_p] == FIELD_TYPE::BLUE)
                    g.addEdge(cur_p, next_p);
        }
    }
    for (int v: start_vertices) {
        cout << v << ": ";
        g.DFS(v);
        cout << endl;
    }
    return true;
}

bool red_won(Board *B) {
    Graph g(B->fields_total);
    // Check for red
    vector<int> start_vertices;
    for (int cur_p = 0; cur_p < B->fields_total; cur_p++) {
        if (B->matrix[cur_p] == FIELD_TYPE::RED) {
            if (cur_p / B->size == 0)
                start_vertices.push_back(cur_p);
            int moves[6] = {};
            posibilities_for_pos(B, moves, cur_p);
            for (int next_p: moves)
                if (next_p != -1 && B->matrix[next_p] == FIELD_TYPE::RED)
                    g.addEdge(cur_p, next_p);
        }
    }
    for (int v: start_vertices) {
        cout << v << ": ";
        g.DFS(v);
        cout << endl;
    }
    return true;
}

void is_game_over(Board *B) {
    cout << "BLUE: " << endl;
    blue_won(B);
    cout << "RED: " << endl;
    red_won(B);
}

int main() {
    while (!cin.eof()) {
        Board B;
        if (!board_init(&B))
            continue;
        board_read(&B);

        is_board_correct(&B);
        is_game_over(&B);
        cout << "Board size: " << B.size << "x" << B.size << ", Amount of fields: " << B.fields_total << endl;
        cout << "Red: " << B.pawns_red << ", Blue: " << B.pawns_blue << endl;
        cout << "Total pawns: " << B.pawns_red + B.pawns_blue << endl;
        cout << "H: " << B.height << endl;

        print_board_as_square(B.matrix, B.size);
        cout << endl;

        board_destroy(&B);
    }
    return 0;
}
