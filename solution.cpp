/**
 * @file solution.cpp
 * @brief Source file for solution.hpp
 * @date 08/06/2023
 * 
 * Source file containing the solution class
*/

#include "solution.hpp"

solution::solution(data *data) {

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].empty()) {
          this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].resize(5);
        }
        this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()-1][data->missions[j]->getId()] = false;
      }
    }
  }


  for (int i = 0; i < data->nbEmployees; i++) {
    if (this->hours[data->employees[i]->getId()].empty()) {
      this->hours[data->employees[i]->getId()].resize(5);
    }
    for (int j = 0; j < 5; j++) {
      if (this->hours[data->employees[i]->getId()][j].empty()) {
        this->hours[data->employees[i]->getId()][j].resize(2);
      }
      this->hours[data->employees[i]->getId()][j][0] = 0;
      this->hours[data->employees[i]->getId()][j][1] = 0;
    }
  }
}


solution::solution() {

}

void solution::initialSolution(data *data1){
  std::vector<std::string> skills = {"LSF", "LPC"};
  bool assigned = true;
  float minDistance = std::numeric_limits<float>::max();
  float tempDistance = 0;
  int soonestMission = std::numeric_limits<int>::max();
  int tempAssigned = 0; //Hold the id of the mission that has been temporarily assigned
  int idEmployee = 0;
  int idMission = 0;

  for (int d = 0; d < 5; d++) { //Iterate over each day
    for (int c = 0; c < data1->nbCenters; c++) { //Iterate over each center
      for (int s = 0; s < 2; s++) { //Iterate over each skill
        for (int e = 0; e < data1->centers[c]->getNbEmployees(skills[s]); e++) { //Iterate over each employee
          idEmployee = data1->centers[c]->getEmployeeId(skills[s], e);
          assigned = true;
          while (this->hours[idEmployee][0][d] < 420 && this->hours[idEmployee][1][d] < 780 && assigned) { //While the employee still has time to work on the day we try to affect him a mission
            assigned = false;
            soonestMission = std::numeric_limits<int>::max();
            for (int m = 0; m < data1->centers[c]->getNbMissions(skills[s]); m++) { //Iterate over each mission
              idMission = data1->centers[c]->getMissionId(skills[s], m);
              if (!data1->missions[idMission-1]->getAssigned("bool")) { //Test if the mission hasn't been assigned to an employee yet
                //We make sure the mission starts after the previous one
                if (this->hours[idEmployee][3][d] < data1->missions[idMission-1]->getStartingPeriod() && data1->missions[idMission-1]->getStartingPeriod() - this->hours[idEmployee][3][d] <= soonestMission) {
                  if (hasTime(idEmployee, d, idMission, data1, c)) { //Test if the employee has enough time to do the mission
                    if (data1->missions[m]->getStartingPeriod() - this->hours[idEmployee][3][d] == soonestMission) { //If the mission starts as soon as another one, we now compare their distance
                      if (/* condition */) { //If the distance is the same, we compare wether the speciality matches or not
                        if (/* condition */) { 

                        } else {

                        }
                        
                      } else {

                      }
                      

                    } else {
                      soonestMission = data1->missions[m]->getStartingPeriod() - this->hours[][3][d];
                      tempAssigned = m;
                    }
                    

                    //Test to see how close the mission is [we will affect the closest mission to the employee]
                  }

                }
              }

            }
            if (assigned) {
              data1->missions[tempAssigned]->setAssigned(true);
              this->affectations[skills[s]][e+1][d][tempAssigned] = true;
            }

          }
          
        }
        
      }
      
    }
    
  }
}

solution::~solution() = default;


void solution::printSolution(data *data) {
  std::cout << std::endl << "------------------------- Solution : ------------------------- " << std::endl;
  std::vector<std::string> skills = {"LSF", "LPC"};

  for (const auto & skill : skills) {
    std::cout << "Table for skill : " << skill << std::endl;
    for (int j = 0; j < data->nbEmployees; j++) {
      if (data->employees[j]->getSkill() == skill) {
        std::cout << "Employee " << data->employees[j]->getId() << " : " << std::endl;
        for (int l = 0; l < 5; l++) {
          std::cout << "Day " << l + 1 << " : ";
          for (int k = 0; k < data->nbMissions; k++) {
            if (data->employees[j]->getSkill() == data->missions[k]->getSkill())
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
}

solution *solution::compareSolutions(solution *newSolution, data *data) {
  if (this->compareNBAffectations(newSolution, data) == 0) {
    return newSolution;
  } else if (this->compareNBAffectations(newSolution, data) == 1) {
    if (this->compareDistance(newSolution, data) == 0) {
      return newSolution;
    } else if (this->compareDistance(newSolution, data) == 1) {
      if (this->compareNBSpecialists(newSolution, data) == 0) {
        return newSolution;
      }
    }
  }
  return this;
}

int solution::countAffectations(data * data, int i, int k) {
  int nbAffectations = 0;
  for (int j = 0; j < data->nbMissions; j++) {
    if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
      if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[j]->getId()])
        nbAffectations++;
    }
  }
  return nbAffectations;
}

int solution::compareNBAffectations(solution *newSolution, data *data) {
  int nbAffectationsThis = 0;
  int nbAffectationsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int k = 0; k < 5; k++) {
      nbAffectationsThis += this->countAffectations(data, i, k);
      nbAffectationsNew += newSolution->countAffectations(data, i, k);
    }
  }

  if (nbAffectationsThis < nbAffectationsNew)
    return 0;
  else if (nbAffectationsThis == nbAffectationsNew)
    return 1;
  else
    return 2;
}

int solution::compareDistance(solution *newSolution, data *data) {
  int nbAffectations;
  int lastTime = 0, time = 0;
  int lastIdMission = 0, idMission = 0;
  float lengthThis = 0, lengthNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < 5; j++) {
      nbAffectations = this->countAffectations(data, i, j);
      lastTime = time;
      time = INT_MAX;
      lastIdMission = data->employees[i]->getIdCenter();
      for (int k = 0; k < nbAffectations; k++) {
        for (int l = 0; l < data->nbMissions; l++) {
          if (data->employees[i]->getSkill() == data->missions[l]->getSkill()) {
            if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[l]->getId()]) {
              if (data->missions[l]->getStartingPeriod() < time && data->missions[l]->getStartingPeriod() > lastTime) {
                time = data->missions[l]->getStartingPeriod();
                idMission = data->missions[l]->getId();
              }
            }
          }
        }
        lengthThis += data->distancesMatrix->getDistance(lastIdMission, idMission);
        lastIdMission = idMission;
      }
    }
    for (int j = 0; j < 5; j++) {
      nbAffectations = newSolution->countAffectations(data, i, j);
      lastTime = time;
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
      }
    }
  }

  if (lengthThis < lengthNew)
    return 0;
  else if (lengthThis == lengthNew)
    return 1;
  else
    return 2;
}

int solution::compareNBSpecialists(solution *newSolution, data *data) {
  int nbSpecialistsThis = 0;
  int nbSpecialistsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) {
          if (data->employees[i]->getSpeciality() == data->missions[j]->getSpeciality())
            nbSpecialistsThis++;
        }
        if (newSolution->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) {
          if (data->employees[i]->getSpeciality() == data->missions[j]->getSpeciality())
            nbSpecialistsNew++;
        }
      }
    }
  }

  if (nbSpecialistsThis < nbSpecialistsNew)
    return 0;
  else if (nbSpecialistsThis == nbSpecialistsNew)
    return 1;
  else
    return 2;
}

int solution::hoursWeek(int idEmployee){
  int nbHours = 0;
  for (int i = 0; i < 5; i++)
  {
    nbHours = nbHours + this->hours[idEmployee][i][0];
  }
  return nbHours;
}

bool solution::hasTime(int idEmployee, int day, int idMission, data *data, int center){
  int tempMinutes = 0;
  int idLastMission = this->hours[idEmployee][day][4];
  int newWorkTime = this->hours[idEmployee][day][0] + data->missions[idMission-1]->getDuration(); //Le temps de travail ajouté par la mission
  int newAmpTime;

  if (idLastMission != 0 && this->hours[idEmployee][day][3]+ data->distancesMatrix->getDistance(idLastMission-1, idMission-1)* < data->missions[idLastMission-1]->getStartingPeriod()) { //We check to see if the employee arrives on time to do the mission
    return false;
  }
  

  if (idLastMission != 0) { //We check to see if the employee has already been assigned a mission
    newWorkTime = newWorkTime + data->distancesMatrix->getDistance(idLastMission-1, idMission-1)* + data->distancesMatrix->getDistance(center, idMission-1); //We add the time to go to the mission + the time to come back to the center
    newAmpTime = this->hours[idEmployee][day][1] + data->missions[idMission-1]->getEndingPeriod() - this->hours[idEmployee][day][3] + data->distancesMatrix->getDistance(center, idMission-1); //Le temps d'amplitude horaire ajouté par la mission
  } else {
    newWorkTime = newWorkTime + data->distancesMatrix->getDistance(center, idMission-1) * * 2; //We add the time to go to the mission + the time to come back to the center
    newAmpTime = data->missions[idMission-1]->getEndingPeriod() - data->missions[idMission-1]->getStartingPeriod() + + data->distancesMatrix->getDistance(center, idMission-1) * 2; //Le temps d'amplitude horaire ajouté par la mission
  }

  if (newAmpTime < 780 && newWorkTime < 420 && hoursWeek(idEmployee) < 35) { //We check if the employee has enough time to do the mission
    return true;
  } else {
    return false;
  }

  }
  
}


