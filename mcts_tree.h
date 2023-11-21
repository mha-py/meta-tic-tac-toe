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

    int search(int iterations);

private:
    MCTSNode* root;
    MCTSNode* select();
};

#endif // MCTS_TREE_H
