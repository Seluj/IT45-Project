/**
 * @file mission.hpp
 * @brief Header file for class mission
 * @date 01/06/2023
 *
 * Header file containing the definition of the class mission
 */

#ifndef IT45_PROJECT_MISSION_HPP
#define IT45_PROJECT_MISSION_HPP

#include "../inclusion.hpp"

/**
 * @class mission
 * @brief Class representing a mission
 *
 * This class is used to store the data of a mission
 * A mission is characterized by:
 * - an id
 * - a day
 * - a starting period
 * - an ending period
 * - a skill
 * - a speciality
 */
class mission {

private:
  int id;                 // id of the mission
  int assigned;           // 0 if not assigned, 1 if assigned to a Center, 2 if assigned to an Employee
  int day;                // day of the mission
  int startingPeriod;     // starting period of the mission
  int endingPeriod;       // ending period of the mission
  std::string skill;      // skill of the mission
  std::string speciality; // speciality of the mission

public:

  /* --------------------------------- Constructors --------------------------------- */

  mission();

  mission(mission *missionToCopy);

  mission(int id, int day, int startingPeriod, int endingPeriod, std::string skill, std::string speciality);

  /* --------------------------------- Destructor --------------------------------- */

  ~mission();

  /* --------------------------------- Getters --------------------------------- */

  int getId();

  int getAssigned(const std::string& type = "bool");

  int getDay();

  int getStartingPeriod();

  int getEndingPeriod();
  
  int getDuration();

  std::string getSkill();

  std::string getSpeciality();

  /* --------------------------------- Setters --------------------------------- */

  void setAssigned(int assigned);

  /* --------------------------------- Print Method --------------------------------- */

  void printMission();
};


#endif //IT45_PROJECT_MISSION_HPP
