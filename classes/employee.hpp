/**
 * @file employee.hpp
 * @brief Header file for class employee
 * @date 01/06/2023
 *
 * Header file containing the definition of the class employee
 * This class is used to store the data of an employee
 */

#ifndef IT45_PROJECT_EMPLOYEE_HPP
#define IT45_PROJECT_EMPLOYEE_HPP

#include <iostream>
#include <vector>

/**
 * @class employee
 * @brief Class representing an employee
 *
 * This class is used to store the data of an employee
 * An employee is characterized by:
 * - an id
 * - an id of a center (the center where he works)
 * - a skill
 * - a speciality
 */
class employee {

private:
  int id;                 // id of the employee
  int idCenter;           // id of the center where he works
  std::string skill;      // skill of the employee
  std::string speciality; // speciality of the employee
  std::vector<int> missions; // missions of the employee

public:

  /* --------------------------------- Constructors --------------------------------- */

  employee();
  employee(int id, int idCenter, std::string skill, std::string speciality);

  /* --------------------------------- Destructor --------------------------------- */

  ~employee();

  /* --------------------------------- Getters --------------------------------- */

  int getId();
  int getIdCenter();
  std::string getSkill();
  std::string getSpeciality();
  std::vector<int> getMissions();

  /**
   * Add a mission to the employee
   * @param idMission
   */
  void addMission(int idMission);

  /**
   * Remove a mission from the employee
   * @param idMission
   */
  void removeMission(int idMission);

  /* --------------------------------- Print Method --------------------------------- */

  void printEmployee();
};


#endif //IT45_PROJECT_EMPLOYEE_HPP
