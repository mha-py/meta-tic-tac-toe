
#include "mcts_node.h"
#include <cmath>

MCTSNode* MCTSNode::selectChild() {
    // Implementiere die Auswahllogik für das beste Kind
    // Hier könnte zum Beispiel UCB1 verwendet werden
    MCTSNode* cbest = nullptr;
    double ubest = -99999.;
    for (MCTSNode* c : children) {
      double u;
      u = state.turn * c->cumScore * (1. / c->visits);
      u += 2. * CP * std::sqrt(2.*std::log(1.*visits)/c->visits);
      if (u > ubest) {
        cbest = c;
        ubest = u;
      }
    }

    return cbest;
}

MCTSNode* MCTSNode::expand() {
    // Implementiere die Logik für das Hinzufügen eines neuen Kindknotens
    // return den neu hinzugefügten Kindknoten
    if (terminal != GOING_ON)
      return this;

    // Zufallszug aus den noch zu expandierenden Züge wählen
    int k = rand() % toexpand.size();
    int a = toexpand[k];
    toexpand.erase(toexpand.begin()+k);

    // Neuen Knoten erstellen
    State s(state);
    s.NextState(a);
    MCTSNode* child = new MCTSNode(s, a, this);

    // ... und zur Liste hinzufügen
    children.push_back(child);

    return child;
}

int MCTSNode::simulate() {
    // Implementiere die Logik für eine Simulation vom aktuellen Zustand
    // ...
    State s(state);
    int r = s.getEnded();
    while (r == GOING_ON) {
      s.random_move();
      r = s.getEnded();
    }
    return r;
}

void MCTSNode::backpropagate(double result) {
    // Implementiere die Logik für das Zurückverfolgen der Simulationsergebnisse
    cumScore += result;
    visits++;
    if (parent != nullptr)
      parent->backpropagate(result);
}
