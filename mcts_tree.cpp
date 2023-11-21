
#include "mcts_tree.h"

#include <iostream>

int MonteCarloTreeSearch::search(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        MCTSNode* selectedNode = select();
        MCTSNode* expandedNode = selectedNode->expand();
        int simulationResult = expandedNode->simulate();
        expandedNode->backpropagate(simulationResult);
    }
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
    std::cout << qbest << std::endl;

    return abest;
}


MCTSNode* MonteCarloTreeSearch::select() {
    MCTSNode* node = root;
    while (node->toexpand.size() == 0 && node->terminal == GOING_ON)
      node = node->selectChild();

    return node;
}
