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
  srand(unsigned(time(nullptr)));

  std::string skillTemp;                                      // Temporary variable to store the skill of the mission
  int dayTemp, time;                                          // Temporary variables to store the day and the time of the mission
  mission *tempMission;                                       // Temporary variable to store the mission
  std::vector<mission *> missionUnmarked;                     // Vector containing all the unmarked missions
  int nbMissionsUnmarked = 0;                                 // Number of unmarked missions
  int centerShortestDistance, centerSecondShortestDistance;   // Index of the closest and second-closest centers
  float shortestDistance;                                     // Shortest distance between the unmarked mission and the centers

  int randomUnmarked, randomMarked;         // Random numbers

  int i, j, k;                              // Iterators

  std::map<std::string, std::map<int, int>> nbMissionsMarkedCenter; // Map containing the number of missions marked for each center

  // Get all the unmarked missions and change the assigned value of the marked missions
  for (i = 0; i < data1->nbMissions; i++) {
    if (data1->missions[i]->getAssigned("int") == 0) {
      missionUnmarked.push_back(data1->missions[i]);
      nbMissionsUnmarked++;
    } else if (data1->missions[i]->getAssigned("int") == 2) {
      data1->missions[i]->setAssigned(1);
    }
  }

  // If there is no unmarked mission, return the data
  if (nbMissionsUnmarked == 0) {
    return data1;
  }

  for (i = 0; i < data1->nbCenters; i++) {
    nbMissionsMarkedCenter["LSF"][i] = data1->centers[i]->getNbMissions("LSF");
    nbMissionsMarkedCenter["LPC"][i] = data1->centers[i]->getNbMissions("LPC");
  }


  for (i = 0; i < data1->nbMissions / 10; ++i) {
    randomUnmarked = rand() % nbMissionsUnmarked;


    skillTemp = missionUnmarked[randomUnmarked]->getSkill();
    dayTemp = missionUnmarked[randomUnmarked]->getDay();

    centerShortestDistance = 0;
    centerSecondShortestDistance = centerShortestDistance;
    shortestDistance = data1->distancesMatrix->getDistance(0, missionUnmarked[randomUnmarked]->getId() - 1);
    // Compute the shortest distance between the unmarked mission and the centers
    for (j = 0; j < data1->nbCenters - 1; j++) {
      for (k = i + 1; k < data1->nbCenters; k++) {
        if (shortestDistance > data1->distancesMatrix->getDistance(k, missionUnmarked[randomUnmarked]->getId() - 1)) {
          centerSecondShortestDistance = centerShortestDistance;
          centerShortestDistance = k;
          shortestDistance = data1->distancesMatrix->getDistance(k, missionUnmarked[randomUnmarked]->getId() - 1);
        }
      }
    }

    if (nbMissionsMarkedCenter[skillTemp][centerShortestDistance] == 0) {
      // If there is no mission marked for the skill of the unmarked mission in the closest center,
      // we look for the second-closest center with a marked mission
      centerShortestDistance = centerSecondShortestDistance;
    }

    if (nbMissionsMarkedCenter[skillTemp][centerShortestDistance] != 0) {
      time = 0;
      for (j = 0; j < nbMissionsMarkedCenter[skillTemp][centerShortestDistance]; j++) {
        if (time < data1->centers[centerShortestDistance]->getMission(j, skillTemp)->getStartingPeriod() &&
            data1->centers[centerShortestDistance]->getMission(j, skillTemp)->getDay() >= dayTemp) {
          time = data1->centers[centerShortestDistance]->getMission(j, skillTemp)->getStartingPeriod();
          randomMarked = j;
        }
      }

      tempMission = data1->centers[centerShortestDistance]->getMission(randomMarked, skillTemp);

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
