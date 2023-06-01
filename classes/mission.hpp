/**
 * @file mission.hpp
 * @brief Header file for class mission
 * @date 01/06/2021
 *
 * Header file containing the definition of the class mission
 */

#ifndef IT45_PROJECT_MISSION_HPP
#define IT45_PROJECT_MISSION_HPP

#include <iostream>

/**
 * @class mission
 * @brief Class representing a mission
 */
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
