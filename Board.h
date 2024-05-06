#ifndef PROJECT2_BOARD_H
#define PROJECT2_BOARD_H

#include "graph.h"

using namespace std;

typedef struct {
    int BOARD_SIZE = 0;
    int PAWNS_NUMBER = 0;
    bool IS_BOARD_CORRECT = false;
    FIELD_TYPE IS_GAME_OVER = EMPTY;
    bool IS_BOARD_POSSIBLE = false;

    bool CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT = false;
    bool CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT = false;
    bool CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT = false;
    bool CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT = false;

    bool CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT = false;
    bool CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT = false;
    bool CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT = false;
    bool CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT = false;
} OUTPUT_INFO;

class Board {
public:
    ~Board();
    int size;
    int visual_height;
    int fields_total;
    int pawns_red;
    int pawns_blue;
    int *matrix;
    OUTPUT_INFO OI;
    int output_mask = 0;
    Graph red_g;
    Graph blue_g;
    bool init();
    void read();
    void read_reqs();
    void create_graphs();
    void posibilities_for_pos(int arr[], int pos);

    bool is_correct();
    bool check_if_won(FIELD_TYPE check_for);
    FIELD_TYPE is_game_over();
    bool is_possible();
    bool DFS(FIELD_TYPE check_for, bool forget, int to_ignore = -1, vector<int> *v_path = nullptr);
    vector<int> *get_all_vertices(FIELD_TYPE get_for);

    void print_matrix();
    void print_graphs();
    void print_stats();
    void print_reqs();

    int pawns_total() { return pawns_red + pawns_blue; };

    void destroy();
};


#endif //PROJECT2_BOARD_H
