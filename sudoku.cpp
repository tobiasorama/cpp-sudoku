#include <iostream>
#include <fstream>
#include <string>
#include "board.h"

int main(int argc, char* argv[]) {
  std::string s;
  std::ifstream f(argv[1]);
  while (f.good()) {
    s += f.get();
  }
  f.close();

  Board b = Board(s);
  std::string inp;
  std::cout << "----***SUDOKU***----\n\n";

  while (true) {
    std::cout << b.make_string() << "\n";
    std::cout << "Input positon and value (i j k l v) OR s to solve: ";
    std::getline(std::cin, inp);
    std::cout << "\n";
    if (inp == "s") {
      b.solve();
      if (b.solved()) {
        std::cout << "Solved!\n\n";
      } else {
        std::cout << "This board is unsolvable!\n\n";
      }
      std::cout << b.make_string();
      break;
    } else if (inp.size() == 9) {
      bool legal = inp.at(8) - 48 >= 0 && inp.at(8) - 48 <= 9? true: false;
      for (int i = 0; i <= 3; i++) {
        if (!(inp.at(2*i) - 48 >= 0 && inp.at(2*i) - 48 < 3 && inp.at(2*i + 1) == ' ')) {
          legal = false;
          break;
        }
      }

      if (legal) {
        int input [5] = {inp.at(0)-48, inp.at(2)-48, inp.at(4)-48, inp.at(6)-48, inp.at(8)-48};
        b.add_value(input[0], input[1], input[2], input[3], input[4]);
      } else {
        std::cout << "Invalid input\n\n";
      }
    } else {
      std::cout << "Invalid input\n\n";
    }
  }

}
