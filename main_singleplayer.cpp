

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "state.h"
#include "mcts_tree.h"

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
    if (s.turn == player) {  // PLAYER MOVE
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
    } else {  // AI MOVE
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
}
