#ifndef MCTS_TREE_H
#define MCTS_TREE_H

#include "mcts_node.h"


class MonteCarloTreeSearch {
public:
    MonteCarloTreeSearch(State state) {
        // Hier die Initialisierung, z.B. Wurzelknoten erstellen
        root = new MCTSNode(state);
    }

    ~MonteCarloTreeSearch() {
        delete root;
    }

    int search(int iterations, double cp);

private:
    MCTSNode* root;
    MCTSNode* select(double cp);
};

#endif // MCTS_TREE_H
