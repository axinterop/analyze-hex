#include <vector>

#include "Board.h"

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

bool Board::init() {
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

    int s = c / 3 + 1;
    int board_height = s * 2;
    int board_fields_num = s * s;

    size = s;
    visual_height = board_height;
    fields_total = board_fields_num;
    pawns_red = 0;
    pawns_blue = 0;
    matrix = (int *) calloc(board_fields_num, sizeof(matrix));
    return true;
}

void Board::read() {
    string response;
    for (int row = 1; row < visual_height; row++) {
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
                if (row <= size)
                    startIndex = (row - 1) * size;
                else if (row > size) {
                    startIndex = fields_total - 2 * size + row;
                }

                int index = startIndex - in_this_row * (size - 1);
                matrix[index] = ft;
            }
        }

        pawns_red += reds;
        pawns_blue += blues;
    }
    getline(cin, response);
}

void Board::read_reqs() {
    return;
}

void Board::create_graphs() {
    red_g = *new Graph(fields_total);
    blue_g = *new Graph(fields_total);

    for (int cur_p = 0; cur_p < fields_total; cur_p++) {
        auto cur_ft = (FIELD_TYPE) matrix[cur_p];
        if (cur_ft != FIELD_TYPE::EMPTY) {
            int moves[6] = {};
            posibilities_for_pos(moves, cur_p);
            for (int next_p: moves)
                if (next_p != -1 && matrix[next_p] == cur_ft)
                    if (cur_ft == FIELD_TYPE::RED)
                        red_g.addEdge(cur_p, next_p);
                    else if (cur_ft == FIELD_TYPE::BLUE)
                        blue_g.addEdge(cur_p, next_p);
        }
    }
}

void Board::destroy() {
    free(matrix);
}

Board::~Board() {
    destroy();
}

void Board::print_matrix() {
    if (power_of_ten(size) >= 1) {
        cout << " ";
    }
    cout << "  x ";
    for (int k = 0; k < size; k++)
        cout << k % 10 << " ";
    cout << endl;
    cout << "y   ";
    for (int k = 0; k < size; k++) {
        cout << "--";
    }
    cout << endl;
    for (int y = 0; y < size; y++) {
        cout << y;
        for (int j = 0; j < power_of_ten(size) + 1 - power_of_ten(y); j++)
            cout << " ";
        cout << "| ";

        for (int x = 0; x < size; x++) {
            int c = matrix[y * size + x];
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

bool Board::is_correct() {
    int pawn_diff = pawns_red - pawns_blue;
    if (pawn_diff == 0 | pawn_diff == 1)
        return true;
    else
        return false;
}

void Board::posibilities_for_pos(int *arr, int pos) {
    int cur_p = pos;
    int next_poses[6] = {
            cur_p - (size + 1),
            cur_p - size,
            cur_p - 1,
            cur_p + 1,
            cur_p + size,
            cur_p + size + 1,
    };
    for (int i = 0; i < 6; i++) {
        int next_p = next_poses[i];
        if (!(next_p >= 0 && next_p < fields_total))
            next_p = -1;
        if (size > 2) {
            if (cur_p % size == 0 && next_p % size == size - 1)
                next_p = -1;
            if (cur_p % size == size - 1 && next_p % size == 0)
                next_p = -1;
        } else {
            if (cur_p % size == 0 && next_p == cur_p - 1)
                next_p = -1;
            if (cur_p % size == size - 1 && next_p == cur_p + 1)
                next_p = -1;
        }
        arr[i] = next_p;
    }
}

bool Board::check_if_won(FIELD_TYPE check_for) {
    if (pawns_total() < size)
        return false;

    vector<int> start_vertices;
    int cur_p;

    for (int i = 0; i < size; i++) {
        if (check_for == RED)
            cur_p = i * size;
        else if (check_for == BLUE)
            cur_p = i;
        if (matrix[cur_p] == check_for)
            start_vertices.push_back(cur_p);
    }

    for (int v : start_vertices) {
        bool found_path = false;
        if (check_for == BLUE)
            found_path = blue_g.DFS(v, size, check_for);
        else if (check_for == RED)
            found_path = red_g.DFS(v, size, check_for);
        if (found_path)
            return true;
    }
    return false;
}

FIELD_TYPE Board::is_game_over() {
    if (check_if_won(RED)) {
        cout << "YES RED\n";
        return FIELD_TYPE::RED;
    }
    else if (check_if_won(BLUE)) {
        cout << "YES BLUE\n";
        return FIELD_TYPE::BLUE;
    } else {
        cout << "NO\n";
        return FIELD_TYPE::EMPTY;
    }
}

void Board::print_graphs() {
    cout << "RED GRAPH:" << endl;
    red_g.printEdges();
    cout << "----------------\n" << endl;

    cout << "BLUE GRAPH:" << endl;
    blue_g.printEdges();
    cout << "----------------\n" << endl;
}

void Board::print_stats() {
    cout << "Board size: " << size << "x" << size << endl;
    cout << "Total fields: " << fields_total << endl;
    cout << "Red: " << pawns_red << ", Blue: " << pawns_blue << endl;
    cout << "Total pawns: " << pawns_red + pawns_blue << endl;
    cout << "Height: " << visual_height << endl;
}
