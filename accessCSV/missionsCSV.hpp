//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_MISSIONSCSV_HPP
#define IT45_PROJECT_MISSIONSCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"

class missionsCSV {
  private:
    std::vector<int> id;
    std::vector<int> day;
    std::vector<int> startingPeriod;
    std::vector<int> endingPeriod;
    std::vector<std::string> skill;
    std::vector<std::string> speciality;
    int nbMissions;

  public:
    missionsCSV(const std::string& path);
    ~missionsCSV();
    std::vector<int> getId();
    std::vector<int> getDay();
    std::vector<int> getStartingPeriod();
    std::vector<int> getEndingPeriod();
    std::vector<std::string> getSkill();
    std::vector<std::string> getSpeciality();
    void printId();
    void printDay();
    void printStartingPeriod();
    void printEndingPeriod();
    void printSkill();
    void printSpeciality();
    void printMissions();
};


#endif //IT45_PROJECT_MISSIONSCSV_HPP
