
#include "mcts_node.h"
#include <cmath>

// Function to select the best child node based on the UCB1 algorithm
MCTSNode* MCTSNode::selectChild(double cp) {
    MCTSNode* cbest = nullptr;
    double ubest = -99999.;
    // Iterate over children to find the one with the highest UCB1 score
    for (MCTSNode* c : children) {
      double u;
      u = state.turn * c->cumScore * (1. / c->visits);
      u += 2. * cp * std::sqrt(2.*std::log(1.*visits)/c->visits);
      if (u > ubest) {
        cbest = c;
        ubest = u;
      }
    }

    return cbest;
}

// Function to expand the current node by adding a new child node
MCTSNode* MCTSNode::expand() {
  // Return the current node if it is already terminal
    if (terminal != GOING_ON)
      return this;

    // Randomly select a move from the remaining unexpanded moves
    int k = rand() % toexpand.size();
    int a = toexpand[k];
    toexpand.erase(toexpand.begin()+k);

    // Create a new state and node for the selected move
    State s(state);
    s.NextState(a);
    MCTSNode* child = new MCTSNode(s, a, this);

    // Add the new child to the list of children
    children.push_back(child);

    return child;
}

// Function to simulate a game from the current state and return the result
int MCTSNode::simulate() {
    State s(state);
    int r = s.getEnded();
    // Continue making random moves until the game ends
    while (r == GOING_ON) {
      s.RandomMove();
      r = s.getEnded();
    }
    return r;
}

// Function to backpropagate the simulation results through the tree
void MCTSNode::backpropagate(double result) {
    cumScore += result;
    visits++;
    // Recursively backpropagate the result to the parent node
    if (parent != nullptr)
      parent->backpropagate(result);
}
