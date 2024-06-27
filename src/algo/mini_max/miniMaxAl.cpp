// #include <iostream>
#include <vector>

const int BoardSize = 3;
const char EmptyCell = '-';
const char PlayerX = 'X';
const char PlayerO = 'O';

// Function prototypes
void PrintBoard(const std::vector<std::vector<char>>& board);
bool HasWon(const std::vector<std::vector<char>>& board, char player);
bool IsBoardFull(const std::vector<std::vector<char>>& board);
int Evaluate(const std::vector<std::vector<char>>& board);
int Minimax(std::vector<std::vector<char>>& board, int depth, bool is_maximizing);
std::pair<int, int> FindBestMove(std::vector<std::vector<char>>& board);

// void PrintBoard(const std::vector<std::vector<char>>& board) {
//     for (int i = 0; i < BoardSize; ++i) {
//         for (int j = 0; j < BoardSize; ++j) {
//             std::cout << board[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

bool HasWon(const std::vector<std::vector<char>>& board, char player) {
    for (int i = 0; i < BoardSize; ++i) {
        bool row_win = true;
        bool col_win = true;
        for (int j = 0; j < BoardSize; ++j) {
            if (board[i][j] != player) row_win = false;
            if (board[j][i] != player) col_win = false;
        }
        if (row_win || col_win) return true;
    }

    bool diag1_win = true;
    bool diag2_win = true;
    for (int i = 0; i < BoardSize; ++i) {
        if (board[i][i] != player) diag1_win = false;
        if (board[i][BoardSize - 1 - i] != player) diag2_win = false;
    }
    if (diag1_win || diag2_win) return true;

    return false;
}

bool IsBoardFull(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (board[i][j] == EmptyCell) return false;
        }
    }
    return true;
}

int Evaluate(const std::vector<std::vector<char>>& board) {
    if (HasWon(board, PlayerX)) return 10;
    if (HasWon(board, PlayerO)) return -10;
    //In case no winner
    return 0;
}

int Minimax(std::vector<std::vector<char>>& board, int depth, bool is_maximizing) {
    int score = Evaluate(board);

    if (score != 0 || depth == 0) return score;

    if (is_maximizing) {
        int best_score = -1000;
        for (int i = 0; i < BoardSize; ++i) {
            for (int j = 0; j < BoardSize; ++j) {
                if (board[i][j] == EmptyCell) {
                    board[i][j] = PlayerX;
                    best_score = std::max(best_score, Minimax(board, depth - 1, !is_maximizing)); //Max is a function that returns maximum of two variables
                    board[i][j] = EmptyCell;
                }
            }
        }
        return best_score;
    }
    else {
        int best_score = 1000;
        for (int i = 0; i < BoardSize; ++i) {
            for (int j = 0; j < BoardSize; ++j) {
                if (board[i][j] == EmptyCell) {
                    board[i][j] = PlayerO;
                    best_score = std::min(best_score, Minimax(board, depth - 1, !is_maximizing));
                    board[i][j] = EmptyCell;
                }
            }
        }
        return best_score;
    }
}

std::pair<int, int> FindBestMove(std::vector<std::vector<char>>& board) {
    int best_score = -1000;
    std::pair<int, int> best_move;

    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (board[i][j] == EmptyCell) {
                board[i][j] = PlayerX;
                int move_score = Minimax(board, 5, false);
                board[i][j] = EmptyCell;
                if (move_score > best_score) {
                    best_score = move_score;
                    best_move = std::make_pair(i, j);
                }
            }
        }
    }

    return best_move;
}
