/**
 * @file missionsCSV.hpp
 * @brief Header file for class missionsCSV
 * @date 01/06/2023
 *
 * Header file containing the definition of the class missionsCSV
 * This class is used to read the missions.csv file and store the data in a vector of pointers to mission objects
 */

#ifndef IT45_PROJECT_MISSIONSCSV_HPP
#define IT45_PROJECT_MISSIONSCSV_HPP

#include "../csv.hpp"
#include "../classes/mission.hpp"

/**
 * @class missionsCSV
 * @brief Class used to read the missions.csv file and store the data in a vector of pointers to mission objects
 */
class missionsCSV {

private:
  std::vector<mission *> missions;  // Vector of pointers to mission objects
  int nbMissions;                   // Number of missions

public:

  /* --------------------------------- Constructor --------------------------------- */

  missionsCSV(const std::string &path);

  /* --------------------------------- Destructor --------------------------------- */

  ~missionsCSV();

  /* --------------------------------- Accessors --------------------------------- */

  std::vector<mission *> getMissions();

  int getNbMissions();

  /* --------------------------------- Print Method --------------------------------- */

  void printMissions();
};


#endif //IT45_PROJECT_MISSIONSCSV_HPP
