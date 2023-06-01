//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_MISSIONSCSV_HPP
#define IT45_PROJECT_MISSIONSCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"
#include "../classes/mission.hpp"

class missionsCSV {
private:
  std::vector<mission *> missions;
  int nbMissions;

public:
  missionsCSV(const std::string& path);
  ~missionsCSV();
  void printMissions();

  std::vector<mission *> getMissions();
  int getNbMissions();
};


#endif //IT45_PROJECT_MISSIONSCSV_HPP
