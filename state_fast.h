#ifndef STATE_H
#define STATE_H

#include <vector>
#include <stdint.h>
#include <array>

#define REMIS 0
#define GOING_ON 20

typedef int8_t Action;
typedef std::vector<Action> ActionList;

class State {
public:
    State();
    State(const State& other);
    void NextState(int a);
    ActionList getValidActions();
    Action getRandomAction();
    int getEnded();
    void RandomMove();
    void draw();

//private:
    int8_t board[81];
    int8_t won[9];
    int8_t active_board;
    int8_t turn;
    int8_t nmoves; // wie viele züge schon gemacht worden sind
    int8_t nsubmoves[9]; // wie viele züge im subboard schon gemacht worden sind

    bool subboard_is_won(int aa, int player);
    bool subboard_is_full(int aa);
    void fill_subboard(int aa, int player);
};

#endif // STATE_H
