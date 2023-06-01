//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_CENTERSCSV_HPP
#define IT45_PROJECT_CENTERSCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"
#include "../classes/center.hpp"

class centersCSV {
private:
  std::vector<center *> centers;
  int nbCenters;

public:
  centersCSV(const std::string& path);
  ~centersCSV();
  std::vector<center *> getCenters();
  int getNbCenters();
  void printCenters();
};


#endif //IT45_PROJECT_CENTERSCSV_HPP
