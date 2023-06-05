/**
 * @file missionsCSV.cpp
 * @brief Implementation of the missionsCSV class
 * @date 01/06/2023
 */

#include "missionsCSV.hpp"

/* --------------------------------- Constructor --------------------------------- */

missionsCSV::missionsCSV(const std::string &path) {
  int i = 0;              // Iterator for the rows
  int j;                  // Iterator for the columns
  int id;                 // Id of the mission
  int day;                // Day of the mission
  int startingPeriod;     // Starting period of the mission
  int endingPeriod;       // Ending period of the mission
  std::string skill;      // Skill of the mission
  std::string speciality; // Speciality of the mission

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/Missions.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    j = 0;
    for (csv::CSVField& field: row) { // Input iterator for the fields
      if (j == 0) {
        id = field.get<int>(); // Convert the field to int and store it in id
      } else if (j == 1) {
        day = field.get<int>(); // Convert the field to int and store it in day
      } else if (j == 2) {
        startingPeriod = field.get<int>(); // Convert the field to int and store it in startingPeriod
      } else if (j == 3) {
        endingPeriod = field.get<int>(); // Convert the field to int and store it in endingPeriod
      } else if (j == 4) {
        skill = field.get<std::string>(); // Convert the field to string and store it in skill
      } else {
        speciality = field.get<std::string>(); // Convert the field to string and store it in speciality
      }
      j++;
    }
    this->missions.push_back(new mission(id, day, startingPeriod, endingPeriod, skill, speciality)); // Add a new mission to the vector
    i++;
  }
  this->nbMissions = i; // Set the number of missions
}

/* --------------------------------- Destructor --------------------------------- */

missionsCSV::~missionsCSV() = default;

/* --------------------------------- accessors --------------------------------- */

std::vector<mission *> missionsCSV::getMissions() {
  return this->missions;
}

int missionsCSV::getNbMissions() {
  return this->nbMissions;
}

/* --------------------------------- Print Method --------------------------------- */

void missionsCSV::printMissions() {
  for (int i = 0; i < this->nbMissions; i++) {
    this->missions[i]->printMission();
  }
}