#ifndef MCTS_NODE_H
#define MCTS_NODE_H

#include "state.h"

#define CP 1.  // Cp in the UCT Formula

class MCTSNode {
public:
    State state;
    MCTSNode* parent;
    std::vector<MCTSNode*> children;
    std::vector<int> toexpand;
    int visits;
    int cumScore;
    int action; // Aktion aus der der Knoten hervorgegangen ist
    int terminal; // Spiel endet in diesem Knoten

    MCTSNode(State state, int action=-1, MCTSNode* parent = nullptr)
        : state(state), action(action), parent(parent), visits(0), cumScore(0) {
          terminal = state.getEnded();
          if (terminal == GOING_ON)
            for (int a : state.getValidActions())
              toexpand.push_back(a);
        }

    ~MCTSNode() {
        for (MCTSNode* child : children) {
            delete child;
        }
    }


    MCTSNode* selectChild(double cp);
    MCTSNode* expand();
    int simulate();
    void backpropagate(double result);
};


#endif // MCTS_NODE_H
