

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

#include <chrono>
#include <fstream>
#include <stdio.h>
#include <string>
#include <locale> // isdigit



int main()
{


  // Selfplay
  for (int f=0; true; f++) {
    std::ofstream File("games/selfplay" + std::to_string(f) + ".txt"); // TODO FPRINT

    State s0;
    std::vector<State*> states;
    std::vector<int> actions;
    while (s0.getEnded() == GOING_ON) {
      State* scpy = new State(s0);
      states.push_back(scpy);
      ActionList va = s0.getValidActions();
      int k = std::rand() % va.size();
      int a = va[k];
      s0.NextState(a);
      actions.push_back(a);
    }
    // Zufälligen Zustand auswählen
    int k = rand() % states.size();
    State* s = states[k];
    for (int i=0; i<k; i++)
      File << actions[i] << ';';
    File << std::endl;

    while (s->getEnded() == GOING_ON) {
      MonteCarloTreeSearch tree(*s);
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      int a = tree.search(10000, 1.);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
      s->NextState(a);
      File << a << ';';
    }
    File.close();
    for (State* s : states)
      delete s;
}

/*
  State s;
  while (s.getEnded() == GOING_ON) {
    MonteCarloTreeSearch tree(s);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int a = tree.search(100000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    s.NextState(a);
    //s.draw();
  }*/

  /*
  State s1;
  std::cout << rollout(s1, 10000);*/

  return 0;
}
