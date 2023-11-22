

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

void Game() {
  int n = 100000;
  std::cout << "Welcome! Do you want to play as the first (x) or second (o) player?" << std::endl;
  char c;
  int player;
  InputXO:
  std::cin >> c;
  if (c=='x') {
    std::cout << "You play as x (first)" << std::endl;
    player = +1;
  } else if (c=='o') {
    std::cout << "You play as o (second)" << std::endl;
    player = -1;
  } else {
    std::cout << "Can only be either x or o! Try again" << std::endl;
    goto InputXO;
  }

  State s;
  int a;
  std::string str;
  while (s.getEnded() == GOING_ON) {
    s.draw();
    if (s.turn == player) {
      ActionList va = s.getValidActions();
      std::cout << "Choose your move!" << std::endl;
      InputMove:
      std::cin >> str;
      if ((str.size() != 2) || !std::isdigit(str[0]) || !std::isdigit(str[1])) {
        std::cout << "Invalid Move! Try again" << std::endl;
        goto InputMove;
      }
      int i = str[0] - '0';
      int j = str[1] - '0';
      if (i==0 || j==0) {
        std::cout << "Invalid Move! Try again" << std::endl;
        goto InputMove;
      }
      a = 9*(i-1) + (j-1);
      bool valid = false;
      for (Action aa : va) {
        if (a==aa)
          valid = true;
      }
      if (!valid) {
        std::cout << "Invalid Move! Try again" << std::endl;
        goto InputMove;
      }
    } else {
      MonteCarloTreeSearch tree(s);
      a = tree.search(n, 1.);
    }
    s.NextState(a);
  }
  s.draw();
  if (s.getEnded() == player)
    std::cout << "CONGRATULATIONS! YOU HAVE WON!" << std::endl;
  else if (s.getEnded() == -player)
    std::cout << "YOU HAVE LOST!" << std::endl;
  else
    std::cout << "REMIS!" << std::endl;
}





int main()
{
  Game();
  return 0;

/*
  // Selfplay
  for (int f=0; true; f++) {
    std::ofstream File("games/selfplay" + std::to_string(f) + ".txt"); // TODO FPRINT

    State s;
    for (int i=0; i<4; i++) {
      ActionList va = s.getValidActions();
      int k = std::rand() % va.size();
      int a = va[k];
      s.NextState(a);
      //std::cout << a << std::endl;
      File << a << ';';
    }
    while (s.getEnded() == GOING_ON) {
      MonteCarloTreeSearch tree(s);
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      int a = tree.search(10000);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
      s.NextState(a);
      File << a << ';';
    }
    File.close();
}*/

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
