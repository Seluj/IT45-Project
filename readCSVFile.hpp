//
// Created by jules on 31/05/23.
//

#ifndef IT45_PROJECT_READCSVFILE_HPP
#define IT45_PROJECT_READCSVFILE_HPP

#include <iostream>
#include <fstream>
#include <string>

class readCSVFile {
  private:
    std::string **table;
    int nbRows;
    int nbColumns;
  public:
    readCSVFile(std::string fileName);
    ~readCSVFile();
    void printTable();
    std::string **getTable();
    int getNbRows();
    int getNbColumns();
};


#endif //IT45_PROJECT_READCSVFILE_HPP
