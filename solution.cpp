/**
 * @file solution.cpp
 * @brief Source file for solution.hpp
 * @date 11/06/2023
 * 
 * Source file containing the solution class
*/

#include "solution.hpp"

solution::solution(data *data) {

  // Initialize the affectations matrix
  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int j = 0; j < data->nbMissions; j++) { // For each mission
      if (data->employees[i]->getSkill() ==
          data->missions[j]->getSkill()) { // If the employee has the skill required for the mission
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].empty()) { // If the vector is empty (not initialized) we initialize it
          // We initialize the vector with 5 days
          this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].resize(5);
        }
        // We initialize the affectation to false
        this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay() -
                                                                                        1][data->missions[j]->getId()] = false;
      }
    }
  }

  // Initialize the hours matrix
  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    if (this->hours[data->employees[i]->getId()].empty()) { // If the vector is empty (not initialized) we initialize it
      // We initialize the vector with 5 days
      this->hours[data->employees[i]->getId()].resize(5);
    }
    for (int j = 0; j < 5; j++) { // For each day
      if (this->hours[data->employees[i]->getId()][j].empty()) { // If the vector is empty (not initialized) we initialize it
        // We initialize the vector with 2 types of hours : 0 = Number of hours and 1 = time range
        this->hours[data->employees[i]->getId()][j].resize(2);
      }
      // We initialize both type of hours to 0
      this->hours[data->employees[i]->getId()][j][0] = 0;
      this->hours[data->employees[i]->getId()][j][1] = 0;
    }
  }
}


solution::solution() {

}

solution solution::initialSolution(kMedoids *kMedoids1, data *data1){

}

solution::~solution() = default;


solution *solution::compareSolutions(solution *newSolution, data *data) {
  if (this->compareNBAffectations(newSolution, data) == 0) { // If the new solution has more affectations
    // We return the new solution
    return newSolution;
  } else if (this->compareNBAffectations(newSolution, data) ==
             1) { // If the new solution has the same number of affectations
    if (this->compareDistance(newSolution, data) == 0) { // If the new solution has less distance to travel
      // We return the new solution
      return newSolution;
    } else if (this->compareDistance(newSolution, data) == 1) { // If the new solution has the same distance to travel
      if (this->compareNBSpeciality(newSolution, data) == 0) {  // If the new solution has more specialities covered
        // We return the new solution
        return newSolution;
      }
    }
  }
  // Otherwise we return the current solution
  return this;
}

int solution::compareNBAffectations(solution *newSolution, data *data) {
  // We count the number of affectations for both solutions
  int nbAffectationsThis = 0;
  int nbAffectationsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int k = 0; k < 5; k++) { // For each day
      // We count the number of affectations for the current solution and the new solution
      nbAffectationsThis += this->countAffectations(data, i, k);
      nbAffectationsNew += newSolution->countAffectations(data, i, k);
    }
  }

  // We compare the number of affectations
  if (nbAffectationsThis <
      nbAffectationsNew) // If the current solution has less affectations than the new solution we return 0
    return 0;
  else if (nbAffectationsThis ==
           nbAffectationsNew) // If the current solution has the same number of affectations than the new solution we return 1
    return 1;
  else  // If the current solution has more affectations than the new solution we return 2
    return 2;
}

int solution::compareDistance(solution *newSolution, data *data) {
  // We count the distance to travel for both solutions
  int nbAffectations;                     // Number of affectations for the current employee and the current day
  int lastTime = 0, time = 0;             // Last time and current time
  int lastIdMission = 0, idMission = 0;   // Last mission and current mission
  float lengthThis = 0, lengthNew = 0;    // Length of the path for the current solution and the new solution

  for (int i = 0; i < data->nbEmployees; i++) { // For each employee

    // We count the length of the path for the current solution
    for (int j = 0; j < 5; j++) { // For each day
      // We count the number of affectations for the current employee and the current day
      nbAffectations = this->countAffectations(data, i, j);
      lastTime = 0;
      time = INT_MAX;
      lastIdMission = data->employees[i]->getIdCenter(); // Before the first mission the employee is at the center

      for (int k = 0; k <
                      nbAffectations; k++) { // For each affectation we need to find the length of the path between the missions and the last mission
        for (int l = 0; l < data->nbMissions; l++) { // For each mission
          if (data->employees[i]->getSkill() ==
              data->missions[l]->getSkill()) { // If the employee has the skill for the mission
            if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[l]->getId()]) { // If the employee is affected to the mission
              if (data->missions[l]->getStartingPeriod() < time && data->missions[l]->getStartingPeriod() >
                                                                   lastTime) { // If the starting period of the mission is between the last mission and the current mission
                // We update the time and the id of the mission
                time = data->missions[l]->getStartingPeriod();
                idMission = data->missions[l]->getId();
              }
            }
          }
        }

        // We add the distance between the last mission and the current mission to the length of the path
        lengthThis += data->distancesMatrix->getDistance(lastIdMission, idMission);
        // We update the last mission, the last time and the current time
        lastIdMission = idMission;
        lastTime = time;
        time = INT_MAX;
      }
    }

    // We count the length of the path for the new solution
    // It is the same code as before but we use the new solution instead of the current solution
    for (int j = 0; j < 5; j++) {
      nbAffectations = newSolution->countAffectations(data, i, j);
      lastTime = 0;
      time = INT_MAX;
      lastIdMission = data->employees[i]->getIdCenter();

      for (int k = 0; k < nbAffectations; k++) {
        for (int l = 0; l < data->nbMissions; l++) {
          if (data->employees[i]->getSkill() == data->missions[l]->getSkill()) {
            if (newSolution->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[l]->getId()]) {
              if (data->missions[l]->getStartingPeriod() < time && data->missions[l]->getStartingPeriod() > lastTime) {
                time = data->missions[l]->getStartingPeriod();
                idMission = data->missions[l]->getId();
              }
            }
          }
        }

        lengthNew += data->distancesMatrix->getDistance(lastIdMission, idMission);
        lastIdMission = idMission;
        lastTime = time;
        time = INT_MAX;
      }
    }
  }

  // We compare the length of the path for the current solution and the new solution
  if (lengthThis > lengthNew) // If the current solution has a longer path than the new solution we return 0
    return 0;
  else if (lengthThis ==
           lengthNew) // If the current solution has the same length of path than the new solution we return 1
    return 1;
  else // If the current solution has a shorter path than the new solution we return 2
    return 2;
}

int solution::compareNBSpeciality(solution *newSolution, data *data) {
  // We count the number of speciality covered for both solutions
  int nbSpecialistsThis = 0;
  int nbSpecialistsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int j = 0; j < data->nbMissions; j++) { // For each mission
      if (data->employees[i]->getSkill() ==
          data->missions[j]->getSkill()) { // If the employee has the skill for the mission
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) { // If the employee is affected to the mission
          if (data->employees[i]->getSpeciality() ==
              data->missions[j]->getSpeciality()) { // If the employee has the speciality for the mission
            // We increment the number of speciality covered for the current solution
            nbSpecialistsThis++;
          }
        }
        if (newSolution->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) { // If the employee is affected to the mission
          if (data->employees[i]->getSpeciality() ==
              data->missions[j]->getSpeciality()) { // If the employee has the speciality for the mission
            // We increment the number of speciality covered for the new solution
            nbSpecialistsNew++;
          }
        }
      }
    }
  }

  // We compare the number of speciality covered for both solutions
  if (nbSpecialistsThis <
      nbSpecialistsNew) // If the current solution has less speciality covered than the new solution we return 0
    return 0;
  else if (nbSpecialistsThis ==
           nbSpecialistsNew) // If the current solution has the same number of speciality covered than the new solution we return 1
    return 1;
  else  // If the current solution has more speciality covered than the new solution we return 2
    return 2;
}

void solution::printSolution(data *data) {
  std::cout << std::endl << "------------------------- Solution : ------------------------- " << std::endl;
  std::vector<std::string> skills = {"LSF", "LPC"};

  for (const auto &skill: skills) { // For each skill
    std::cout << "Table for skill : " << skill << std::endl;
    for (int j = 0; j < data->nbEmployees; j++) { // For each employee
      if (data->employees[j]->getSkill() == skill) {  // If the employee has the skill
        std::cout << "Employee " << data->employees[j]->getId() << " : " << std::endl;
        for (int l = 0; l < 5; l++) { // For each day
          std::cout << "Day " << l + 1 << " : ";
          for (int k = 0; k < data->nbMissions; k++) {  // For each mission
            if (data->employees[j]->getSkill() ==
                data->missions[k]->getSkill())  // If the employee has the skill for the mission
              // We print the affectation
              std::cout
                << affectations[skill][data->employees[j]->getId()][l][data->missions[k]->getId()]
                << " ";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
    }
  }
  std::cout << "Hours : " << std::endl;
  for (int i = 0; i < data->nbEmployees; i++) {
    std::cout << "Employee " << data->employees[i]->getId() << " : " << std::endl;
    for (int j = 0; j < 5; j++) {
      std::cout << "Day " << j + 1 << " : " << hours[data->employees[i]->getId()][j][0] << " "
                << hours[data->employees[i]->getId()][j][1] << std::endl;
    }
    std::cout << std::endl;
  }
}

int solution::countAffectations(data *data, int i, int k) {
  // We count the number of affectations for the employee i and the day k
  int nbAffectations = 0;
  for (int j = 0; j < data->nbMissions; j++) {  // For each mission
    if (data->employees[i]->getSkill() ==
        data->missions[j]->getSkill()) {  // If the employee has the skill for the mission
      if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[j]->getId()]) // If the employee is affected to the mission
        // We increment the number of affectations
        nbAffectations++;
    }
  }
  // We return the number of affectations
  return nbAffectations;
}
