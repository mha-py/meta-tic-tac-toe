
#include "state.h"
#include <iostream>
#include <cassert>


State::State() {
  for (int i=0; i<81; i++)
    board[i] = 0;
  for (int i=0; i<9; i++)
    won[i] = GOING_ON;
  active_board = -1;
  turn = 1;
}


State::State(const State& other)
  : active_board(other.active_board), turn(other.turn) {
  for (int i = 0; i < 81; i++)
      board[i] = other.board[i];
  for (int i = 0; i < 9; i++)
      won[i] = other.won[i];
}



void State::NextState(int a) {
  assert(0<=a && a < 81);
  int i = a / 9;
  int j = a % 9;
  int ii = i/3;
  int jj = j/3;
  int aa = 3*ii+jj;
  assert(board[a]==0); // board must be empty
  if (active_board != -1)
    assert(aa == active_board); // you can only play in the active subboard

  // do the move
  board[a] = turn;

  // Check if sub board is won
  if (subboard_is_won(aa, turn)) {
    won[aa] = turn;
    fill_subboard(aa, turn);
  }
  else if (subboard_is_full(aa))
    won[aa] = REMIS;

  // find out the subboard for the next player to play
  ii = i%3;
  jj = j%3;
  aa = 3*ii+jj;
  if (won[aa] != GOING_ON)
    active_board = -1;
  else
    active_board = aa;

  turn *= -1;

}

std::vector<int> State::getValidActions() {
  std::vector<int> va;
  if (active_board == -1) {  // no board active -> all empty squares
    for (int a=0; a<81; a++)
      if (board[a] == 0)
        va.push_back(a);
  } else {  // only on the active sub board
    int ii = active_board / 3;
    int jj = active_board % 3;
    for (int i=3*ii; i<3*(ii+1); i++)
      for (int j=3*jj; j<3*(jj+1); j++)
        if (board[9*i+j] == 0) {
          va.push_back(9*i+j);
        }
  }
  return va;
}

int State::getEnded() {
  // Zeilen
  for (int ii=0; ii<3; ii++)
    if (won[3*ii+0] == won[3*ii+1] && won[3*ii+1] == won[3*ii+2] && won[3*ii+0] != REMIS && won[3*ii+0] != GOING_ON)
      return won[3*ii+0];
  // Spalten
  for (int jj=0; jj<3; jj++)
    if (won[3*0+jj] == won[3*1+jj] && won[3*1+jj] == won[3*2+jj] && won[3*0+jj] != REMIS && won[3*0+jj] != GOING_ON)
      return won[3*0+jj];
  // Diagonale
  if (won[0]==won[4] && won[4]==won[8] && won[0] != REMIS && won[0] != GOING_ON)
    return won[0];
  // Antidiagonale
  if (won[2]==won[4] && won[4]==won[6] && won[2] != REMIS && won[2] != GOING_ON)
    return won[2];

  // Zwei Fälle noch möglich: Brett ist voll -> Remis, oder das Spiel dauert an
  for (int a=0; a<81; a++)
    if (board[a] == 0)
      return GOING_ON;
  return REMIS;
}


void State::draw() {

  std::cout << "\n+-1-2-3-+-4-5-6-+-7-8-9-+" << std::endl;

  for (int ii = 0; ii < 3; ii++) {
    for (int i = 0; i < 3; i++) {
      std::cout << (3 * ii + i + 1) << ' ';
      for (int jj = 0; jj < 3; jj++) {
        bool active = (3*ii+jj == active_board); // aktives subboard soll farblich markiert werden
        for (int j = 0; j < 3; j++) {
          const int8_t cell_value = board[9*(3 * ii + i) + 3 * jj + j];
          if (cell_value == 1) {
            std::cout << "x ";
          } else if (cell_value == -1) {
            std::cout << "o ";
          } else {
            if (!active)
              std::cout << "  ";
            else
              std::cout << ". ";
          }
        }
        std::cout << "| ";
      }
      std::cout << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
  }

  if (turn > 0)
    std::cout << "      x to move" << std::endl;
  else
    std::cout << "      o to move" << std::endl;
}


void State::random_move() {
  std::vector<int> va = getValidActions();
  int k = std::rand() % va.size();
  NextState(va[k]);
}




bool State::subboard_is_won(int aa, int player) {
  int ii = aa / 3;
  int jj = aa % 3;

  // Überprüfe die Zeilen und Spalten des Teilbretts
  for (int i = 0; i < 3; i++)
    if ((board[9 * (3 * ii + i) + 3 * jj] == player &&
         board[9 * (3 * ii + i) + 3 * jj + 1] == player &&
         board[9 * (3 * ii + i) + 3 * jj + 2] == player) ||
        (board[9 * (3 * ii) + 3 * jj + i] == player &&
         board[9 * (3 * ii + 1) + 3 * jj + i] == player &&
         board[9 * (3 * ii + 2) + 3 * jj + i] == player))
      return true;

  // Überprüfe die Diagonalen des Teilbretts
  if ((board[9 * (3 * ii) + 3 * jj] == player &&
       board[9 * (3 * ii + 1) + 3 * jj + 1] == player &&
       board[9 * (3 * ii + 2) + 3 * jj + 2] == player) ||
      (board[9 * (3 * ii) + 3 * jj + 2] == player &&
       board[9 * (3 * ii + 1) + 3 * jj + 1] == player &&
       board[9 * (3 * ii + 2) + 3 * jj] == player))
    return true;

  return false;
}



bool State::subboard_is_full(int aa) {
  int ii = aa / 3;
  int jj = aa % 3;

  // Überprüfe, ob alle Felder im Teilbrett belegt sind
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (board[9 * (3 * ii + i) + 3 * jj + j] == 0)
        return false;

  return true;
}


void State::fill_subboard(int aa, int player) {
  int ii = aa / 3;
  int jj = aa % 3;

  // Fülle das Teilbrett mit dem Spielerwert
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      board[9 * (3 * ii + i) + 3 * jj + j] = player;
}
