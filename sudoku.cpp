#include <iostream>
#include <fstream>
#include <string>
#include "board.hpp"

int main(int argc, char* argv[]) {
  std::ifstream ifs(argv[1]);
  Board b = Board(ifs);
  std::string inp;
  while (true) {
    int row, col, val;
    char inp;
    std::cout << "\n";
    std::cout << b.make_string();
    std::cout << "Input 'a' to solve, 'b' to enter value: ";
    std::cin >> inp;
    std::cout << "\n";
    if (inp == 'a') {
      b.solve();
      std::cout << b.make_string();
      if (b.solved()) {
        std::cout << "The board is solved!\n";
      } else {
        std::cout << "The board cannot be solved\n";
      }
      return 0;
    } else {
      std::cout << "Input (row column value): ";
      std::cin >> row >> col >> val;
      if (!b.add_value(row, col, val))
        std::cout << "Not a valid value\n";
    } 
  }

}
