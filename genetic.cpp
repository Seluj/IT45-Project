/**
 * @file genetic.cpp
 * @brief Source file for genetic.hpp
 * @date 11/06/2023
 *
 * Source file containing the definitions of the methods of the genetic class
 */

#include "genetic.hpp"

/* --------------------------------- Constructor --------------------------------- */

genetic::genetic() = default;

/* --------------------------------- Methods --------------------------------- */

data *genetic::mutateData(data *data1) {
  for (const auto &mission: data1->missions) {
    if (mission->getAssigned("int") == 2) {
      mission->setAssigned(1);
    }
  }
  data1 = switchWithUnmarkedMission(data1); // First mutation
  //data1 = switchBetweenCenters(data1);      // Second mutation
  return data1;                             // Return the mutated data
}

data *genetic::switchWithUnmarkedMission(data *data1) {

  srand(unsigned(time(nullptr)));

  std::string skillTemp;
  int dayTemp, startingTemp;
  std::vector<mission *> missionUnmarked;
  int nbMissionsUnmarked = 0;
  int randomUnmarked, randomMarked;
  mission *tempMission;

  std::map<std::string, std::map<int, int>> nbMissionsMarkedCenter;
  std::map<std::string, int> nbMissionsMarkedCenter2;


  // Get all the unmarked missions and change the assigned value of the marked missions
  for (const auto &mission: data1->missions) {
    if (mission->getAssigned("int") == 0) {
      missionUnmarked.push_back(mission);
      nbMissionsUnmarked++;
    }
  }

  // If there is no unmarked mission, return the data
  if (nbMissionsUnmarked == 0) {
    std::cout << "No unmarked mission" << std::endl;
    return data1;
  }

  for (int i = 0; i < data1->nbCenters; i++) {
    nbMissionsMarkedCenter["LSF"][i] = data1->centers[i]->getNbMissions("LSF");
    nbMissionsMarkedCenter["LPC"][i] = data1->centers[i]->getNbMissions("LPC");
  }


  for (int i = 0; i < data1->nbMissions / 10; ++i) {
    randomUnmarked = rand() % nbMissionsUnmarked;


    skillTemp = missionUnmarked[randomUnmarked]->getSkill();
    dayTemp = missionUnmarked[randomUnmarked]->getDay();
    startingTemp = missionUnmarked[randomUnmarked]->getStartingPeriod();

    int centerShortestDistance = 0;
    float shortestDistance = data1->distancesMatrix->getDistance(0, missionUnmarked[randomUnmarked]->getId() - 1);
    // Compute the shortest distance between the unmarked mission and the centers
    for (int j = 0; j < data1->nbCenters - 1; j++) {
      for (int k = i + 1; k < data1->nbCenters; k++) {
        if (shortestDistance > data1->distancesMatrix->getDistance(k, missionUnmarked[randomUnmarked]->getId() - 1)) {
          centerShortestDistance = k;
          shortestDistance = data1->distancesMatrix->getDistance(k, missionUnmarked[randomUnmarked]->getId() - 1);
        }
      }
    }

    // Check if the center has missions of the same skill
    if (nbMissionsMarkedCenter[skillTemp][centerShortestDistance] == 0) {
      continue;
    }

    if (skillTemp == "LSF") {
      do {
        randomMarked = rand() % nbMissionsMarkedCenter["LSF"][centerShortestDistance];
      } while (data1->centers[centerShortestDistance]->getMission(randomMarked, "LSF")->getDay() != dayTemp
               || data1->centers[centerShortestDistance]->getMission(randomMarked, "LSF")->getStartingPeriod() !=
                  startingTemp);

      tempMission = data1->centers[centerShortestDistance]->getMission(randomMarked, "LSF");

      data1->missions[tempMission->getId() - 1]->setAssigned(1);
      data1->missions[missionUnmarked[randomUnmarked]->getId() - 1]->setAssigned(0);

      missionUnmarked[randomUnmarked]->setAssigned(1);
      data1->centers[centerShortestDistance]->swapMissions(randomMarked, missionUnmarked[randomUnmarked]);
      missionUnmarked[randomUnmarked] = tempMission;
      missionUnmarked[randomUnmarked]->setAssigned(0);
    } else {
      do {
        randomMarked = rand() % nbMissionsMarkedCenter["LPC"][centerShortestDistance];
      } while (data1->centers[centerShortestDistance]->getMission(randomMarked, "LPC")->getDay() != dayTemp
               || data1->centers[centerShortestDistance]->getMission(randomMarked, "LPC")->getStartingPeriod() !=
                  startingTemp);

      tempMission = data1->centers[centerShortestDistance]->getMission(randomMarked, "LPC");

      data1->missions[tempMission->getId() - 1]->setAssigned(1);
      data1->missions[missionUnmarked[randomUnmarked]->getId() - 1]->setAssigned(0);

      missionUnmarked[randomUnmarked]->setAssigned(1);
      data1->centers[centerShortestDistance]->swapMissions(randomMarked, missionUnmarked[randomUnmarked]);
      missionUnmarked[randomUnmarked] = tempMission;
      missionUnmarked[randomUnmarked]->setAssigned(0);
    }
  }
  return data1;
}