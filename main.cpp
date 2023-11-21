

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "state.h"
#include "mcts_tree.h"

/*
float rollout(const State& s0, int n=10) {
  int r = 0;
  for (int i=0; i<n; i++) {
    State s(s0);
    int status = GOING_ON;
    while (status == GOING_ON) {
      s.random_move();
      status = s.getEnded();
    }
    r += status;
  }
  return r * (1.0 / n);
}*/


/*
double pitagainstrandom(int n = 20) {
  int cumResult = 0;
  for (int i=0; i<n; i++) {
    State s;
    while (true) {
      // Random player
      s.random_move();
      //s.draw();
      if (s.getEnded() != GOING_ON)
        break;
      // MCTS
      MonteCarloTreeSearch tree(s);
      int a = tree.search(50);
      s.NextState(a);
      //s.draw();
      if (s.getEnded() != GOING_ON)
        break;
    }
    cumResult += s.getEnded();
  }
  return cumResult * (1. / n);
}*/




int main()
{

  //std::cout << pitagainstrandom(20);


  State s;
  while (s.getEnded() == GOING_ON) {
    MonteCarloTreeSearch tree(s);
    int a = tree.search(1000000);
    s.NextState(a);
    s.draw();
  }

  /*
  State s1;
  std::cout << rollout(s1, 10000);*/

  return 0;
}