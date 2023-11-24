
#include "mcts_tree.h"

extern "C" __declspec(dllexport) int __cdecl MakeMove(int* board, int* won, int active_board, int n, double cp) {
  State s;
  for (int i=0; i<81; i++)
    s.board[i] = board[i];
  for (int i=0; i<9; i++)
    s.won[i] = won[i];
  s.active_board = active_board;
  MonteCarloTreeSearch mcts(s);
  return int(mcts.search(n, cp));
}

extern "C" __declspec(dllexport) double __cdecl GetQ(int* board, int* won, int active_board, int n, double cp) {
  State s;
  for (int i=0; i<81; i++)
    s.board[i] = board[i];
  for (int i=0; i<9; i++)
    s.won[i] = won[i];
  s.active_board = active_board;
  MonteCarloTreeSearch mcts(s);
  mcts.Q;
}



/*
# In Python:

import ctypes
lib = ctypes.CDLL(path+'dll.dll', winmode=0)

IntArray81 = ctypes.c_int * 81
IntArray9  = ctypes.c_int * 9

board = IntArray81(*tuple(s.board.astype('int').flatten()))
won = IntArray9(*tuple(s.won.astype('int').flatten()))
active_board = 3*s.active_board[0] + s.active_board[1]
n = 1000
a = lib.MakeMove(board, won, active_board, n)
print(a)

*/
