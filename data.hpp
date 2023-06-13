/**
 * @file data.hpp
 * @brief Header file for the data class
 * @date 01/06/2023
 *
 * Header file containing the definition of the data class
 * This class is used to store the data of the problem and will be modified by the different algorithms
 */

#ifndef IT45_PROJECT_DATA_HPP
#define IT45_PROJECT_DATA_HPP

#include "inclusion.hpp"
#include "classes/center.hpp"
#include "classes/mission.hpp"
#include "classes/employee.hpp"
#include "classes/distances.hpp"

/**
 * @class data
 * @brief Class used to store the data of the problem and will be modified by the different algorithms
 */
class data {

public:
  /**
   * Data about the centers<br>
   * A center stores his id, his coordinates, his capacity and his employees
   */
  std::vector<center *> centers;    // Vector of pointers to center objects
  int nbCenters;                    // Number of centers

  /**
   * Data about the missions
   */
  std::vector<mission *> missions;  // Vector of pointers to mission objects
  int nbMissions;                   // Number of missions

  /**
   * Data about the employees
   */
  std::vector<employee *> employees; // Vector of pointers to employee objects
  int nbEmployees;                  // Number of employees

  /**
   * Data about the matrix of distances
   */
  distances *distancesMatrix{};       // Pointer to the distances class

  data();                           // Default constructor

  void printData();                 // Function to print the data
};


#endif //IT45_PROJECT_DATA_HPP
