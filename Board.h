#ifndef PROJECT2_BOARD_H
#define PROJECT2_BOARD_H

#include "graph.h"

class Board {
public:
    ~Board();
    int size;
    int visual_height;
    int fields_total;
    int pawns_red;
    int pawns_blue;
    int *matrix;
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

    void print_matrix();
    void print_graphs();
    void print_stats();

    int pawns_total() { return pawns_red + pawns_blue; };

    void destroy();
};


#endif //PROJECT2_BOARD_H
