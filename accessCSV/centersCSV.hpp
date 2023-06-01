//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_CENTERSCSV_HPP
#define IT45_PROJECT_CENTERSCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"

class centersCSV {
  private:
    std::vector<int> id;
    std::vector<std::string> name;
    int nbCenters;
  public:
    centersCSV(const std::string& path);
    ~centersCSV();
    std::vector<int> getId();
    std::vector<std::string> getName();
    void printId();
    void printName();
    void printCenters();
};


#endif //IT45_PROJECT_CENTERSCSV_HPP
