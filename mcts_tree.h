#ifndef MCTS_TREE_H
#define MCTS_TREE_H

#include "mcts_node.h"


// Class representing the Monte Carlo Tree Search algorithm
class MonteCarloTreeSearch {
public:
    // Constructor to initialize the Monte Carlo Tree Search with a given initial state
    MonteCarloTreeSearch(State state) {
        // Initialize the tree by creating the root node
        root = new MCTSNode(state);
    }
    // Destructor to clean up memory by deleting the root node
    ~MonteCarloTreeSearch() {
        delete root;
    }

    // Function to perform the Monte Carlo Tree Search for a specific number of iterations
    int search(int iterations, double cp);

private:
    MCTSNode* root; // Pointer to the root node of the tree

    // Private functnion for selecting the most promising move based on UCB1
    MCTSNode* select(double cp);

};

#endif // MCTS_TREE_H
