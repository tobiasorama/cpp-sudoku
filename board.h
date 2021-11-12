class Board {
  int board [3][3][3][3];
  bool has_value [3][3][3][3];
  bool _solved = false;
  /*
    the two first indices give the position of a 3x3 box
    the last two indices give the position of values inside a box
  */

  /*
  1 2 3  4 5 6  7 8 9
  4 5 6  7 8 9  1 2 3
  7 8 9  1 2 3  4 5 6

  2 1 4  3 6 5  8 9 7
  3 6 5  8 9 7  2 1 4
  8 9 7  2 4 1  6 3 5

  5 7 2  9 1 4  3 6 8
  9 4 1  6 3 8  5 7 2
  6 3 8  5 7 2  9 4 1
  */

  public:
  Board() {
    //dummy board for debugging purposes
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
          for (int l = 0; l < 3; l++)
            board[i][j][k][l] = 0;
  }

  Board(std::string s) {
    int row, column;
    int index = -2;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (j < 3) {
          column = 0;
        } else if (j < 6) {
          column = 1;
        } else {
          column = 2;
        }

        if (i < 3) {
          row = 0;
        } else if (i < 6) {
          row = 1;
        } else {
          row = 2;
        }
        index += 2 + (j % 3 == 0 && j > 0? 1: 0) + (i % 3 == 0 && i > 0 && j == 0);
        has_value[row][column][i % 3][j % 3] = s.at(index) == '0'? false: true;
        board[row][column][i % 3][j % 3] = s.at(index) - 48;
      }
    }
  }

  void add_value(int i, int j, int k, int l, int add) {
    board[i][j][k][l] = add;
  }

  bool legal_addition(int i, int j, int k, int l, int add) {
    //check box
    for (int s = 0; s < 3; s++)
      for (int t = 0; t < 3; t++)
        if ((s != k || t != l) && board[i][j][s][t] == add)
          return false;

    //check row and column
    for (int s = 0; s < 3; s++)
      for (int t = 0; t < 3; t++) {
        if (s != i && board[s][j][t][l] == add)
          return false;
        if (s != j && board[i][s][k][t] == add)
          return false;
      }

    return true;
  }

  private:
  bool solver(int i, int j, int k, int l) {
    //calculate next position
    int ni = i;
    int nj = j;
    int nk = k;
    int nl = l;
    if (j == 2) {
      if (l == 2) {
        nj = 0;
        nl = 0;
        if (k == 2) {
          nk = 0;
          ni += 1;
        } else {
          nk += 1;
        }
      } else {
        nl += 1;
      }
    } else {
      if (l == 2) {
        nl = 0;
        nj += 1;
      } else {
        nl += 1;
      }
    }

    if (board[i][j][k][l] == 0) {
      for (int m = 1; m <= 9; m++) {
        if (legal_addition(i, j, k, l, m)) {
          add_value(i, j, k, l, m);
          if ((i == 2 && j == 2 && k == 2 && l == 2) || solver(ni, nj, nk, nl)) {
            return true;
          } else {
            add_value(i, j, k, l, 0);
          }
        }
      }

      return false;
    }

    if (legal_addition(i, j, k, l, board[i][j][k][l])) {
      if (i == 2 && j == 2 && k == 2 && l == 2)
        return true;
      return solver(ni, nj, nk, nl);
    }

    return false;
  }

  public:
  bool solved() {
    return _solved;
  }

  void solve() {
    _solved = solver(0, 0, 0, 0);
  }

  std::string make_string() {
    std::string s = "";
    for (int i = 0; i < 3; i++) {
      for (int k = 0; k < 3; k++) {
        for (int j = 0; j < 3; j++) {
          for (int l = 0; l < 3; l++) {
            s += (has_value[i][j][k][l]? "\033[96m": "") + std::to_string(board[i][j][k][l]) + "\33[0m "; //using ansi escape sequences to colour in predetermined values
          }
          s += " ";
        }
        s += "\n";
      }
      s += i < 2? "\n": "";
    }
    return s;
  }
};
