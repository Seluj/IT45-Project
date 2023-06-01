//
// Created by jules on 01/06/23.
//

#include "missionsCSV.hpp"

missionsCSV::missionsCSV(const std::string &path) {
  int i = 0; // Iterator for the rows
  int j; // Iterator for the columns

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/missions.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    j = 0;
    for (csv::CSVField& field: row) { // Input iterator for the fields
      if (j == 0) {
        this->id.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 1) {
        this->day.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 2) {
        this->startingPeriod.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 3) {
        this->endingPeriod.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 4) {
        this->skill.push_back(field.get<std::string>()); // Add a new field, push back the value of the field and convert it to string
      } else {
        this->speciality.push_back(field.get<std::string>()); // Add a new field, push back the value of the field and convert it to string
      }
      j++;
    }
    i++;
  }
  this->nbMissions = i; // Set the number of missions
}

missionsCSV::~missionsCSV() = default;

std::vector<int> missionsCSV::getId() {
  return this->id;
}

std::vector<int> missionsCSV::getDay() {
  return this->day;
}

std::vector<int> missionsCSV::getStartingPeriod() {
  return this->startingPeriod;
}

std::vector<int> missionsCSV::getEndingPeriod() {
  return this->endingPeriod;
}

std::vector<std::string> missionsCSV::getSkill() {
  return this->skill;
}

std::vector<std::string> missionsCSV::getSpeciality() {
  return this->speciality;
}

void missionsCSV::printId() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->id[i] << std::endl;
  }
}

void missionsCSV::printDay() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->day[i] << std::endl;
  }
}

void missionsCSV::printStartingPeriod() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->startingPeriod[i] << std::endl;
  }
}

void missionsCSV::printEndingPeriod() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->endingPeriod[i] << std::endl;
  }
}

void missionsCSV::printSkill() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->skill[i] << std::endl;
  }
}

void missionsCSV::printSpeciality() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->speciality[i] << std::endl;
  }
}

void missionsCSV::printMissions() {
  for (int i = 0; i < this->nbMissions; i++) {
    std::cout << this->id[i] << " " << this->day[i] << " " << this->startingPeriod[i] << " " << this->endingPeriod[i] << " " << this->skill[i] << " " << this->speciality[i] << std::endl;
  }
}