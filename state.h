#ifndef STATE_H
#define STATE_H

#include <vector>
#include <stdint.h>


#define REMIS 0
#define GOING_ON 20


class State {
public:
    State();
    State(const State& other);
    void NextState(int a);
    std::vector<int> getValidActions();
    int getEnded();
    void draw();
    void random_move();

//private:
    int8_t board[81];
    int8_t won[9];
    int8_t active_board;
    int8_t turn;

    bool subboard_is_won(int aa, int player);
    bool subboard_is_full(int aa);
    void fill_subboard(int aa, int player);
};

#endif // STATE_H
