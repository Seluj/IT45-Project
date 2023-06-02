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
 * - a list of employees LSF
 * - a list of employees LCP
 * - a list of missions LSF
 * - a list of missions LCP
 * - And the number of employees and missions in each list
 */
class center {

private:
  int id;                               // id of the center
  std::string name;                     // name of the center
  int capacity;                         // capacity of the center

  std::vector<employee*> employeesLSF;  // list of employees LSF
  int nbEmployeesLSF;                   // number of employees LSF
  std::vector<employee*> employeesLCP;  // list of employees LCP
  int nbEmployeesLCP;                   // number of employees LCP
  std::vector<mission*> missionsLSF;    // list of missions LSF
  int nbMissionsLSF;                    // number of missions LSF
  std::vector<mission*> missionsLCP;    // list of missions LCP
  int nbMissionsLCP;                    // number of missions LCP

public:

  /* --------------------------------- Constructors --------------------------------- */

  center();
  center(int id, std::string name);

  /* --------------------------------- Destructor --------------------------------- */

  ~center();

  /* --------------------------------- Getters --------------------------------- */


  /* --------------------------------- Print Method --------------------------------- */

  void printCenter();

  /* --------------------------------- Add Employee/Mission --------------------------------- */

  /**
   * Add an employee to the list of employees LSF
   * @param employee The employee to add
   */
  void addEmployeeLSF(employee* employee);

  /**
   * Add an employee to the list of employees LCP
   * @param employee The employee to add
   */
  void addEmployeeLCP(employee* employee);

  /**
   * Add a mission to the list of missions LSF
   * @param mission The mission to add
   */
  void addMissionLSF(mission* mission);

  /**
   * Add a mission to the list of missions LCP
   * @param mission The mission to add
   */
  void addMissionLCP(mission* mission);
};


#endif //IT45_PROJECT_CENTER_HPP
