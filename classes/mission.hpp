//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_MISSION_HPP
#define IT45_PROJECT_MISSION_HPP

#include <iostream>

class mission {
private:
  int id;
  int day;
  int startingPeriod;
  int endingPeriod;
  std::string skill;
  std::string speciality;

public:
  mission();
  mission(int id, int day, int startingPeriod, int endingPeriod, std::string skill, std::string speciality);
  ~mission();
  int getId();
  int getDay();
  int getStartingPeriod();
  int getEndingPeriod();
  std::string getSkill();
  std::string getSpeciality();
  void printMission();
};


#endif //IT45_PROJECT_MISSION_HPP
