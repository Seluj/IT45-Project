/**
 * @file solution.cpp
 * @brief Source file for solution.hpp
 * @date 11/06/2023
 * 
 * Source file containing the solution class
*/

#include "solution.hpp"

solution::solution(data *data, std::string name) {

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
        // We initialize the vector with 6 types of info : 0 = Number of hours and 1 = time range
        this->hours[data->employees[i]->getId()][j].resize(7);
      }
      // We initialize both type of hours to 0
      this->hours[data->employees[i]->getId()][j][0] = 0;
      this->hours[data->employees[i]->getId()][j][1] = 0;
    }
  }

  this->name = name;
}

void solution::initialSolution(data *data1) {
  std::vector<std::string> skills = {"LSF", "LPC"};
  bool assigned = true;
  float minDistance = std::numeric_limits<float>::max();
  int soonestMission = std::numeric_limits<int>::max();
  int tempAssigned = 0; //Hold the id of the mission that has been temporarily assigned as "best mission"
  int idEmployee = 0;
  int idMission = 0;
  int tempCompDistance = 0; //Used to compare distance

  for (int d = 0; d < 5; d++) { //Iterate over each day
    for (int c = 0; c < data1->nbCenters; c++) { //Iterate over each center
      for (int s = 0; s < 2; s++) { //Iterate over each skill
        for (int e = 0; e < data1->centers[c]->getNbEmployees(skills[s]); e++) { //Iterate over each employee
          idEmployee = data1->centers[c]->getEmployeeId(skills[s], e);
          assigned = true;
          while (this->hours[idEmployee][d][0] < 420 && this->hours[idEmployee][d][1] < 780 &&
                 assigned) { //While the employee still has time to work on the day we try to affect him a mission
            assigned = false;
            soonestMission = std::numeric_limits<int>::max();
            minDistance = std::numeric_limits<float>::max();

            for (int m = 0; m < data1->centers[c]->getNbMissions(skills[s]); m++) { //Iterate over each mission
              idMission = data1->centers[c]->getMissionId(skills[s], m);
              if (this->hours[idEmployee][d][4] != 0) {
                tempCompDistance = c;
              } else {
                tempCompDistance = this->hours[idEmployee][d][4] + data1->nbCenters - 1;
              }
              if (data1->missions[idMission - 1]->getAssigned("int") <
                  2) { //Test if the mission hasn't been assigned to an employee yet
                //We make sure the mission starts after the previous one and is sooner than the other missions tested
                if (this->hours[idEmployee][d][3] < data1->missions[idMission - 1]->getStartingPeriod() &&
                    data1->missions[idMission - 1]->getStartingPeriod() - this->hours[idEmployee][d][3] <=
                    soonestMission) {
                  if (hasTime(idEmployee, d, idMission, data1,
                              c)) { //Test if the employee has enough time to do the mission
                    if (data1->missions[idMission - 1]->getStartingPeriod() - this->hours[idEmployee][d][3] ==
                        soonestMission) { //If the mission starts as soon as another one we've tested, we compare their distance
                      if (data1->distancesMatrix->getDistance(idMission - 1 + data1->nbCenters, tempCompDistance) <=
                          minDistance) { //Compare distances
                        if (data1->distancesMatrix->getDistance(idMission - 1 + data1->nbCenters, tempCompDistance) ==
                            minDistance) { //If the distances are equal we compare wether the skills match or not
                          if (data1->employees[idEmployee - 1]->getSpeciality() == data1->missions[idMission -
                                                                                                   1]->getSpeciality()) { //We test to see if the employee has the specialty required for the mission
                            soonestMission =
                              data1->missions[idMission - 1]->getStartingPeriod() - this->hours[idEmployee][d][3];
                            minDistance = data1->distancesMatrix->getDistance(idMission - 1 + data1->nbCenters,
                                                                              tempCompDistance);
                            tempAssigned = idMission;
                            assigned = true;
                          }
                        } else {
                          soonestMission =
                            data1->missions[idMission - 1]->getStartingPeriod() - this->hours[idEmployee][d][3];
                          minDistance = data1->distancesMatrix->getDistance(idMission - 1 + data1->nbCenters,
                                                                            tempCompDistance);
                          tempAssigned = idMission;
                          assigned = true;
                        }

                      }

                    } else {
                      soonestMission =
                        data1->missions[idMission - 1]->getStartingPeriod() - this->hours[idEmployee][d][3];
                      minDistance = data1->distancesMatrix->getDistance(idMission - 1 + data1->nbCenters,
                                                                        tempCompDistance);
                      tempAssigned = idMission;
                      assigned = true;
                    }

                  }

                }
              }

            }
            if (assigned) {
              data1->missions[tempAssigned - 1]->setAssigned(2);
              this->affectations[skills[s]][idEmployee][d][tempAssigned] = true;
              if (this->hours[idEmployee][d][4] == 0) { //Check to  see if a previous mission has been assigned
                this->hours[idEmployee][d][0] = std::ceil(
                  data1->distancesMatrix->getDistance(tempAssigned - 1 + data1->nbCenters, c) * 13.88 / 60);
                this->hours[idEmployee][d][2] = data1->missions[tempAssigned - 1]->getStartingPeriod() - std::ceil(
                  data1->distancesMatrix->getDistance(tempAssigned - 1 + data1->nbCenters, c) * 13.88 / 60);
                this->hours[idEmployee][d][5] = tempAssigned;
              } else {
                this->hours[idEmployee][d][0] += std::ceil(
                  data1->distancesMatrix->getDistance(tempAssigned - 1 + data1->nbCenters,
                                                      this->hours[idEmployee][d][4] - 1 + data1->nbCenters) * 13.88 /
                  60);
              }
              this->hours[idEmployee][d][0] += data1->missions[tempAssigned - 1]->getDuration();
              this->hours[idEmployee][d][1] =
                data1->missions[tempAssigned - 1]->getEndingPeriod() - this->hours[idEmployee][d][2];
              this->hours[idEmployee][d][3] = data1->missions[tempAssigned - 1]->getEndingPeriod();
              this->hours[idEmployee][d][4] = tempAssigned;
              this->hours[idEmployee][d][6] = std::ceil(minDistance);
            }
          }
          //We can now update the final values regarding the hours of the employee
          this->hours[idEmployee][d][0] += std::ceil(
            data1->distancesMatrix->getDistance(this->hours[idEmployee][d][4] - 1 + data1->nbCenters, c) * 13.88 / 60);
          this->hours[idEmployee][d][1] += std::ceil(
            data1->distancesMatrix->getDistance(this->hours[idEmployee][d][4] - 1 + data1->nbCenters, c) * 13.88 / 60);
          this->hours[idEmployee][d][3] += std::ceil(
            data1->distancesMatrix->getDistance(this->hours[idEmployee][d][4] - 1 + data1->nbCenters, c) * 13.88 / 60);
          this->hours[idEmployee][d][6] +=std::ceil(
            data1->distancesMatrix->getDistance(this->hours[idEmployee][d][4] - 1 + data1->nbCenters, c));

        }

      }

    }

  }
}

solution::~solution() = default;

solution *solution::compareSolutions(std::vector<solution *> solutions, data *data) {
  solution *tempSolution = solutions[0];
  for (int i = 1; i < solutions.size() - 1; i++) {
    for (int j = i; j < solutions.size(); j++) {
      tempSolution = tempSolution->compareSolutions(solutions[j], data);
    }
  }
  return tempSolution;
}

solution *solution::compareSolutions(solution *newSolution, data *data) {
  if (this->compareNBAffectations(newSolution, data) == 0) { // If the new solution has more affectations
    // We return the new solution
    return newSolution;
  } else if (this->compareNBAffectations(newSolution, data) ==
             1) { // If the new solution has the same number of affectations
    if (this->compareDistance(newSolution, data) == 0) { // If the new solution has less distance to travel
      // We return the new solution
      return newSolution;
    } else if (this->compareDistance(newSolution, data) ==
               1) { // If the new solution has the same distance to travel
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
  int nbAffectationsThis = this->getNBAffectations(data);
  int nbAffectationsNew = newSolution->getNBAffectations(data);

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
  float lengthThis = this->getDistance(data);
  float lengthNew = newSolution->getDistance(data);

  // We compare the length of the path for the current solution and the new solution
  if (lengthThis > lengthNew) { // If the current solution has a longer path than the new solution we return 0
    return 0;
  } else if (lengthThis == lengthNew) { // If the current solution has the same length of path than the new solution we return 1
    return 1; //If the current solution has a shorter path than the new solution we return 2
  } else {
    return 2;
  }
}

int solution::compareNBSpeciality(solution *newSolution, data *data) {
  // We count the number of speciality covered for both solutions
  int nbSpecialistsThis = this->getNBSpeciality(data);
  int nbSpecialistsNew = newSolution->getNBSpeciality(data);

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

int solution::minutesWeek(int idEmployee, int days) {
  int nbMinutes = 0;
  if (days > 0) {
    for (int i = 0; i < days; i++) {
      nbMinutes = nbMinutes + this->hours[idEmployee][i][0];
    }
  }
  return nbMinutes;
}

bool solution::hasTime(int idEmployee, int day, int idMission, data *data, int center) {
  int idLastMission = this->hours[idEmployee][day][4];
  int newWorkTime = this->hours[idEmployee][day][0] +
                    data->missions[idMission - 1]->getDuration(); //Le temps de travail ajouté par la mission
  int newAmpTime;
  int nbCenters = data->nbCenters;

  if (idLastMission != 0 && this->hours[idEmployee][day][3] + std::ceil(
    data->distancesMatrix->getDistance(idLastMission - 1 + nbCenters, idMission - 1 + nbCenters) * 13.88 / 60) <
                            data->missions[idLastMission -
                                           1]->getStartingPeriod()) { //We check to see if the employee arrives on time to do the mission
    return false;
  }


  if (idLastMission != 0) { //We check to see if the employee has already been assigned a mission
    newWorkTime = newWorkTime + std::ceil(
      data->distancesMatrix->getDistance(idLastMission - 1 + nbCenters, idMission - 1 + nbCenters) * 13.88 / 60 +
      data->distancesMatrix->getDistance(center, idMission - 1 + nbCenters) * 13.88 /
      60); //We add the time to go to the mission + the time to come back to the center
    newAmpTime = this->hours[idEmployee][day][1] + data->missions[idMission - 1]->getEndingPeriod() -
                 this->hours[idEmployee][day][3] + std::ceil(
      data->distancesMatrix->getDistance(center, idMission - 1 + nbCenters) * 13.88 /
      60); //Le temps d'amplitude horaire ajouté par la mission
  } else {
    newWorkTime = newWorkTime + std::ceil(
      data->distancesMatrix->getDistance(center, idMission - 1 + nbCenters) * 13.88 * 2 /
      60); //We add the time to go to the mission + the time to come back to the center
    newAmpTime = data->missions[idMission - 1]->getEndingPeriod() - data->missions[idMission - 1]->getStartingPeriod() +
                 data->distancesMatrix->getDistance(center, idMission - 1 + nbCenters) *
                 2; //Le temps d'amplitude horaire ajouté par la mission
  }

  if (newAmpTime < 780 && newWorkTime < 420 &&
      minutesWeek(idEmployee, day) + newWorkTime < 2100) { //We check if the employee has enough time to do the mission
    return true;
  } else {
    return false;
  }

}

void solution::printSolution(data *data) {
  std::cout << std::endl << "------------------------- " << this->name << " : ------------------------- " << std::endl;
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
      std::cout << "Day "
                << j + 1
                << " - nbHours: " << hours[data->employees[i]->getId()][j][0]
                << " // timeRange: " << hours[data->employees[i]->getId()][j][1]
                << " // start of work: " << hours[data->employees[i]->getId()][j][2]
                << " // end of work: " << hours[data->employees[i]->getId()][j][3]
                << " // id last mission: " << hours[data->employees[i]->getId()][j][4]
                << " // id first mission: " << hours[data->employees[i]->getId()][j][5]
                << " // Distance traveled: " << hours[data->employees[i]->getId()][j][6]
                << std::endl;
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

int solution::getNBAffectations(data *data) {
  int nbAffectations = 0;
  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int k = 0; k < 5; k++) { // For each day
      // We count the number of affectations for the current solution and the new solution
      nbAffectations += this->countAffectations(data, i, k);
    }
  }
  return nbAffectations;
}

float solution::getDistance(data *data) {
  float length = 0;
  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int k = 0; k < 5; k++) { // For each day
      // We add the distance traveled each day by each employee
      length += this->hours[data->employees[i]->getId()][k][6];
    }
  }
  return length;
}

int solution::getNBSpeciality(data *data) {
  int nbSpecialists = 0;
  for (int i = 0; i < data->nbEmployees; i++) { // For each employee
    for (int k = 0; k < 5; k++) { // For each day
      for (int j = 0; j < data->nbMissions; j++) {  // For each mission
        if (data->employees[i]->getSkill() ==
            data->missions[j]->getSkill()) {  // If the employee has the skill for the mission
          if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[j]->getId()]) { // If the employee is affected to the mission
            if (data->employees[i]->getSpeciality() ==
                data->missions[j]->getSpeciality()) { // If the employee has the speciality for the mission
              // We increment the number of speciality covered for the current solution
              nbSpecialists++;
            }
          }
        }
      }
    }
  }
  return nbSpecialists;
}
