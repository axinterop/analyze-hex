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

void print_yes_no(bool a) {
    if (a)
        cout << "YES\n";
    else
        cout << "NO\n";
}

bool Board::init() {
    string response;
    std::getline(cin, response);
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
    string response;
    while (1 == 1) {
        char future_ch;
        future_ch = cin.peek();
        if (future_ch == '\n') {
            cin.get();
            continue;
        } else if (isalnum(future_ch)) {
            getline(cin, response);
            if (response == "BOARD_SIZE")
                output_mask += 1;
            else if (response == "PAWNS_NUMBER")
                output_mask += 2;
            else if (response == "IS_BOARD_CORRECT")
                output_mask += 4;
            else if (response == "IS_GAME_OVER")
                output_mask += 8;
            else if (response == "IS_BOARD_POSSIBLE")
                output_mask += 16;
            else if (!(output_mask & 32) && response.find("NAIVE") != -1)
                output_mask += 32;
            else if (!(output_mask & 64) && response.find("PERFECT") != -1)
                output_mask += 64;
        } else
            break;
    }
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
    return DFS(check_for, false);
}

FIELD_TYPE Board::is_game_over() {
    if (!OI.IS_BOARD_CORRECT)
        return FIELD_TYPE::EMPTY;

    if (check_if_won(RED)) {
        return FIELD_TYPE::RED;
    } else if (check_if_won(BLUE)) {
        return FIELD_TYPE::BLUE;
    } else {
        return FIELD_TYPE::EMPTY;
    }
}

bool Board::is_possible() {
    if (!OI.IS_BOARD_CORRECT)
        return false;
    FIELD_TYPE won = OI.IS_GAME_OVER;
    if (won == FIELD_TYPE::EMPTY)
        return true;
    if (won == FIELD_TYPE::RED && pawns_red - 1 != pawns_blue)
        return false;
    if (won == FIELD_TYPE::BLUE && pawns_red != pawns_blue)
        return false;

    vector<int> *all_vertices = get_all_vertices(won);
    bool found_path;
    for (int v_ignore: *all_vertices) {
        found_path = DFS(won, true, v_ignore);
        if (!found_path)
            return true;
    }
    return false;
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

bool Board::DFS(FIELD_TYPE check_for, bool forget, int to_ignore, vector<int> *v_path) {
    if (forget) {
        if (check_for == RED)
            red_g.forget_visited();
        else if (check_for == BLUE)
            blue_g.forget_visited();
    }

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

    bool found_path;
    for (int start_v: start_vertices) {
        if (check_for == BLUE)
            found_path = blue_g.DFS(start_v, size, check_for, to_ignore, v_path);
        else if (check_for == RED)
            found_path = red_g.DFS(start_v, size, check_for, to_ignore, v_path);
        if (found_path)
            return true;
    }
    return false;
}

vector<int> *Board::get_all_vertices(FIELD_TYPE get_for) {
    auto *result = new vector<int>();
    for (int pi = 0; pi < fields_total; pi++) {
        if (get_for == RED) {
            if (!red_g.adjLists[pi].empty())
                result->push_back(pi);
        } else if (get_for == BLUE) {
            if (!blue_g.adjLists[pi].empty())
                result->push_back(pi);
        }
    }
    return result;
}

void Board::print_reqs() {
    if (output_mask & 1) {
        cout << OI.BOARD_SIZE << endl;
        cout << endl;
    }

    if (output_mask & 2) {
        cout << OI.PAWNS_NUMBER << endl;
        cout << endl;
    }

    if (output_mask & 4) {
        print_yes_no(OI.IS_BOARD_CORRECT);
        cout << endl;
    }

    if (output_mask & 8) {
        if (OI.IS_GAME_OVER == RED)
            cout << "YES RED\n";
        else if (OI.IS_GAME_OVER == BLUE)
            cout << "YES BLUE\n";
        else
            cout << "NO\n";
        cout << endl;
    }

    if (output_mask & 16) {
        print_yes_no(OI.IS_BOARD_POSSIBLE);
        cout << endl;
    }

    if (output_mask & 32) {
        print_yes_no(OI.CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT);
        print_yes_no(OI.CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT);
        print_yes_no(OI.CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT);
        print_yes_no(OI.CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT);
        cout << endl;
    }

    if (output_mask & 64) {
        print_yes_no(OI.CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT);
        print_yes_no(OI.CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT);
        print_yes_no(OI.CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT);
        print_yes_no(OI.CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT);
        cout << endl;
    }

}
