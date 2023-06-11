/**
 * @file center.hpp
 * @brief Header file for class center
 * @date 10/06/2023
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

  /**
   * 1st key: skill [LPC, LSF]<br>
   * 2nd key: day [0 - 4] : 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday<br>
   * 3rd key: time : Time in minutes<br>
   * value: capacity : Number of employees that can work at this time<br><br>
   *
   * Example 1: capacity["LPC"][1][480] = 3 means that the center has a capacity of 3 for the skill LPC on the day 1 at 480 minutes (8:00)<br>
   * Example 2: capacity["LSF"][4][960] = 2 means that the center has a capacity of 2 for the skill LSF on the day 4 at 960 minutes (16:00)
   */
  std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> capacity;    /// capacity of the center by skill and time
  std::vector<int> startingPeriodForPrinting;                                             /// time starting mission for printing

  /**
   * 1st key: skill [LPC, LSF]<br>
   * 2nd key: index<br>
   * value: an employee<br><br>
   *
   * Example 1: employees["LPC"][0] = employee1 means that the first employee of the list of employees with the skill LPC is employee1<br>
   * Example 2: employees["LSF"] = [employee1, employee2, employee3] means that the list of employees with the skill LSF is [employee1, employee2, employee3]
   */
  std::unordered_map<std::string, std::vector<employee *>> employees; /// list of employees by skill
  std::unordered_map<std::string, int> nbEmployees;                   /// number of employees by skill

  /**
   * 1st key: skill [LPC, LSF]<br>
   * 2nd key: index<br>
   * value: a mission<br><br>
   *
   * Example 1: missions["LPC"][0] = mission1 means that the first mission of the list of missions with the skill LPC is mission1<br>
   * Example 2: missions["LSF"] = [mission1, mission2, mission3] means that the list of missions with the skill LSF is [mission1, mission2, mission3]
   */
  std::unordered_map<std::string, std::vector<mission *>> missions;   /// list of missions by skill
  std::unordered_map<std::string, int> nbMissions;                    /// number of missions by skill

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

  int getCapacity(const std::string &skill, int day, int time);

  std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> getCapacity();

  int getNbEmployees(const std::string &skill);

  /* --------------------------------- Print Method --------------------------------- */

  void printCenter();

  /* --------------------------------- Add Employee/Mission --------------------------------- */

  /**
   * Add an employee to the right list of employees
   * @param employee The employee to add
   */
  void addEmployee(employee *employee);

  /**
   * Add a mission to the right list of missions
   * @param mission The mission to add
   */
  void addMission(mission *mission);

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
