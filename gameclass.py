
import numpy as np

class GameState:
    board = np.zeros((9,9), int)
    won = np.zeros((3,3))
    active_board = None
    turn = 1
    
    def copy(self):
        other = GameState()
        other.board = self.board.copy()
        other.won = self.won.copy()
        other.active_board = self.active_board
        other.turn = self.turn
        return other

class GameClass:
    'Meta Tic Tac Toe'

    @staticmethod
    def getNextState(s, a):
        s = s.copy()
        i, j = a
        ii, jj = i//3, j//3

        # Check if the move is valid
        assert s.board[i,j] == 0, 'Square must be empty!'
        if s.active_board:
            assert (ii, jj) == s.active_board, 'Can only place into the active board!'

        # Do the move
        s.board[i, j] = s.turn

        # Check if a sub board is won
        if GameClass.subboard_is_won(s.board, ii, jj):
            s.won[ii,jj] = s.turn
            s.board[3*ii:3*(ii+1), 3*jj:3*(jj+1)] = s.turn
        elif GameClass.subboard_is_full(s.board, ii, jj):
            s.won[ii,jj] = 1e-5

        # Find out the find board to play for the next player
        ii, jj = i%3, j%3
        if s.won[ii,jj]:
            s.active_board = None
        else:
            s.active_board = ii, jj
            
        s.turn *= -1

        return s


    @staticmethod
    def getValidActions(s):
        valid_actions = []

        if type(s.active_board) is type(None):
            for i in range(9):
                for j in range(9):
                    if s.board[i,j] == 0:
                        valid_actions.append((i, j))
        else:
            ii, jj = s.active_board
            for i in range(3*ii, 3*(ii+1)):
                for j in range(3*jj, 3*(jj+1)):
                    if s.board[i,j] == 0:
                        valid_actions.append((i, j))

        return valid_actions

    
    @staticmethod
    def getEnded(s):
        cols = s.won.sum(0)
        rows = s.won.sum(1)
        if cols.max() == 3: return 1
        if cols.min() == -3: return -1
        if rows.max() == 3: return 1
        if rows.min() == -3: return -1
        if s.won[0,0] == s.won[1,1] == s.won[2,2] != 0 or \
           s.won[0,2] == s.won[1,1] == s.won[2,0] != 0:
            return s.won[1,1]
        if np.sum(abs(s.board)) == 81:
            return 1e-5
        return None

    @staticmethod
    def exchangePlayers(s):
        s = s.copy()
        s.board *= -1
        s.turn *= -1
        s.won *= -1
        return s

    @staticmethod
    def gethashable(s):
        return s.board.tostring()
            
    
    @staticmethod
    def subboard_is_won(board, ii, jj):
        'Checks if the active sub board is won by any player'
        subboard = board[ii*3:(ii+1)*3, jj*3:(jj+1)*3]
        return np.any(abs(subboard.sum(0))==3) or \
               np.any(abs(subboard.sum(1))==3) or \
               subboard[0,0] == subboard[1,1] == subboard[2,2] != 0 or \
               subboard[0,2] == subboard[1,1] == subboard[2,0] != 0
    
    @staticmethod
    def subboard_is_full(board, ii, jj):
        'Checks if the active sub board is won by any player'
        subboard = board[ii*3:(ii+1)*3, jj*3:(jj+1)*3]
        return np.sum(abs(subboard)) == 9




from colorama import Back, Fore

def draw_state(s):
    board = s.board
    active_board = s.active_board
    print("+-1-2-3-+-4-5-6-+-7-8-9-+")
    ##print("+-------+-------+-------+")
    for i in range(3):
        # Draw the horizontal lines between sub-boards

        for j in range(3):
            # Draw the rows within each sub-board
            ##row = "| "
            row = str(3*i+j+1) + ' '
            for k in range(3):
                # Draw the columns within each sub-board
                if (i, k) == active_board:
                    row += Back.YELLOW
                for l in range(3):
                    # Convert the numeric values in the array to 'x', 'o', or ' '
                    cell_value = board[3 * i + j][3 * k + l]
                    if cell_value == 1:
                        row += "\033[31mx "  # Red color for 'x'   ## "\033[1;31mx "
                    elif cell_value == -1:
                        row += "\033[34mo "  # Blue color for 'o'
                    else:
                        row += "  "
                row += Back.RESET + Fore.RESET
                row += "| "

            print(row)

        print("+-------+-------+-------+")

