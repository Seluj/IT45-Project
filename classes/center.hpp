/**
 * @file center.hpp
 * @brief Header file for class center
 * @date 01/06/2023
 *
 * Header file containing the definition of the class center
 * This class is used to store the data of a center
 */

#ifndef IT45_PROJECT_CENTER_HPP
#define IT45_PROJECT_CENTER_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include "employee.hpp"
#include "mission.hpp"

/**
 * @class center
 * @brief Class representing a center
 *
 * This class is used to store the data of a center
 * A Center is characterized by:
 * - an id
 * - a name
 * - a capacity
 * - a list of employees
 * - a list of missions
 * - And the number of employees and missions in each list
 */
class center {

private:
  int id;                               // id of the center
  std::string name;                     // name of the center

  std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> capacity; // capacity of the center by skill and time
  std::vector<int> startingPeriodForPrinting;                             // time starting mission for printing

  std::unordered_map<std::string, std::vector<employee *>> employees; // list of employees by skill
  std::unordered_map<std::string, int> nbEmployees;                   // number of employees by skill

  std::unordered_map<std::string, std::vector<mission *>> missions;   // list of missions by skill
  std::unordered_map<std::string, int> nbMissions;                    // number of missions by skill

public:

  /* --------------------------------- Constructors --------------------------------- */

  center();
  center(int id, std::string name);

  /* --------------------------------- Destructor --------------------------------- */

  ~center();

  /* --------------------------------- Setters --------------------------------- */

  void updateCapacity(std::string skill, int day, int time);

  void updateCapacity(std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> newCapacity);

  void updateMissions(std::unordered_map<std::string, std::vector<mission *>> newMissions);

  /* --------------------------------- Getters --------------------------------- */

  int getCapacity(const std::string& skill, int day, int time);

  std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> getCapacity();

  int getNbEmployees(const std::string& skill);

  int getNbMissions(const std::string& skill);

  /* --------------------------------- Print Method --------------------------------- */

  void printCenter();

  /* --------------------------------- Add Employee/Mission --------------------------------- */

  /**
   * Add an employee to the right list of employees
   * @param employee The employee to add
   */
  void addEmployee(employee* employee);

  /**
   * Add a mission to the right list of missions
   * @param mission The mission to add
   */
  void addMission(mission* mission);

  /**
   * Calculate the capacity of the center
   * @param mission The list of missions
   */
  void computeCapacity(std::vector<mission *> mission);

  /***
   * Order the starting period for printing
   */
  void orderStartingPeriodForPrinting();
};


#endif //IT45_PROJECT_CENTER_HPP
