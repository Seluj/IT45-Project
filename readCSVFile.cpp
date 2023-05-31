//
// Created by jules on 31/05/23.
//

#include "readCSVFile.hpp"

readCSVFile::~readCSVFile() {
  for (int i = 0; i < nbRows; i++) {
    delete[] table[i];
  }
  delete[] table;
}

readCSVFile::readCSVFile(std::string fileName) {
  std::ifstream file(fileName);
  std::string line;
  nbRows = 0;
  nbColumns = 0;

}
