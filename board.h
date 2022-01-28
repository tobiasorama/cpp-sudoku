#include <vector>
#include <sstream>
#include <iomanip>

class Board {
  int rows, cols, size;
  std::vector<int> board;
  std::vector<bool> has_value;
  bool _solved = false;

  bool solver(int pos) {
    if (pos >= size*size)
      return true;
    if (board[pos] == 0) {
      for (int m = 1; m <= size; m++)
        if (add_value(pos, m)) {
          if (solver(pos+1)) {
            return true;
          } else {
            board[pos] = 0;
          }
        }
      return false;
    }
    return solver(pos+1);
  }
  
  public:
  Board(std::ifstream &f) {
    f >> rows >> cols;
    size = rows*cols;
    int i = 0;
    board.resize(size*size);
    has_value.resize(size*size);
    while (f.good()) {
      f >> board[i];
      has_value[i] = (bool)board[i];
      i++;
      }
  }

  bool add_value(int row, int col, int add) {
    return add_value(row *size + col, add);
  }

  bool add_value(int pos, int add) {
    if (!add)
      return true;
    int col = pos % size;
    int row = (pos - col)/size;
    //check box
    int start_row = row - (row % rows);
    int start_col = col - (col % cols);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        if (
            (row != start_row + i || col != start_col + j) &&
            add == board[(start_row + i)*size + (start_col + j)]
        ) {
          return false;
        }

    //check column and row
    for (int i = 0; i < size; i++)
      if (i != row && board[i*size + col] == add)
        return false;
    for (int j = 0; j < size; j++)
      if (j != col && board[row*size + j] == add)
        return false;
    board[pos] = add;
    return true;
  }

  bool solved() {
    return _solved;
  }

  void solve() {
    _solved = solver(0);
  }

  std::string make_string() {
    int width = log10(size)  + 1;
    std::ostringstream s;
    int pos = 0;
    for (int i = 0; i < rows; i++) {
      for (int k = 0; k < rows; k++) {
        for (int j = 0; j < cols; j++) {
          for (int l = 0; l < cols; l++) {
            //using ansi escape sequences to colour in predetermined values
            s << (has_value[pos]? "\033[96m": "") << std::setw(width) << std::to_string(board[pos]) << "\33[0m ";
            pos += 1;
          }
          s << " ";
        }
        s << "\n";
      }
      s << (i < rows? "\n": "");
    }
    return s.str();
  }
};
