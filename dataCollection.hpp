/**
 * @file dataCollection.hpp
 * @brief Header file for dataCollection.cpp
 * @date 03/06/2023
 *
 * Header file containing the dataCollection class
 */

#ifndef IT45_PROJECT_DATACOLLECTION_HPP
#define IT45_PROJECT_DATACOLLECTION_HPP

#include "accessCSV/distanceCSV.hpp"
#include "accessCSV/centersCSV.hpp"
#include "accessCSV/missionsCSV.hpp"
#include "accessCSV/employeesCSV.hpp"

/**
 * @class dataCollection
 * @brief Class containing all the data from the CSV files
 */
class dataCollection {

private:

  distanceCSV *distance;    // Pointer to the distanceCSV object
  centersCSV *centers;      // Pointer to the centersCSV object
  missionsCSV *missions;    // Pointer to the missionsCSV object
  employeesCSV *employees;  // Pointer to the employeesCSV object

public:

  /* ------------------------------ Constructors ----------------------------- */

  dataCollection(const std::string &path);

  /* ------------------------------- Destructor ------------------------------ */

  ~dataCollection();

  /* -------------------------------- Getters -------------------------------- */

  distanceCSV *getDistance();

  centersCSV *getCenters();

  missionsCSV *getMissions();

  employeesCSV *getEmployees();

  /* -------------------------------- Print Method -------------------------------- */

  void printDataCollection();
};


#endif //IT45_PROJECT_DATACOLLECTION_HPP
