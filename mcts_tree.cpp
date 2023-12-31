
#include "mcts_tree.h"

#include <iostream>

// Function to search for the best move for the given state
int MonteCarloTreeSearch::search(int iterations, double cp) {

    // Build up the tree and do the rollouts
    for (int i = 0; i < iterations; ++i) {
        MCTSNode* selectedNode = select(cp);
        MCTSNode* expandedNode = selectedNode->expand();
        int simulationResult = expandedNode->simulate();
        expandedNode->backpropagate(simulationResult);
    }

    // Find the best move
    int abest = 0;
    int nbest = 0;
    double qbest = -99999;
    for (MCTSNode* c : root->children) {
      double q = c->cumScore * (1. / c->visits);
      double n = c->visits;
      if (n > nbest) {
        abest = c->action;
        nbest = n;
        qbest = q;
      }
      int i = c->action / 9;
      int j = c->action % 9;
      //std::cout << i+1 << j+1 << "   " << c->cumScore * (1. / c->visits) << "   " << c->visits << std::endl;
    }
    //std::cout << qbest << std::endl; // **
    Q = qbest;
    
    return abest;
}

// Helper Function to select a node which can be expanded
MCTSNode* MonteCarloTreeSearch::select(double cp) {
    MCTSNode* node = root;
    while (node->toexpand.size() == 0 && node->terminal == GOING_ON)
      node = node->selectChild(cp);

    return node;
}
