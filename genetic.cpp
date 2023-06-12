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

  std::string skillTemp;
  int dayTemp, startingTemp;
  data *tempData = new data(*data1);
  std::vector<mission *> missionUnmarked;
  int randomUnmarked, randomMarked;
  mission *tempMission;

  for (int i = 0; i < tempData->nbMissions; i++) {
    if (tempData->missions[i]->getAssigned() == false) {
      missionUnmarked.push_back(tempData->missions[i]);
    }
  }

  int nbMissionsUnmarked = missionUnmarked.size();
  int nbMissionsMarkedCenter1 = tempData->centers[0]->getMissions().size();
  int nbMissionsMarkedCenter2 = tempData->centers[1]->getMissions().size();

  for (int i = 0; i < 20; ++i) {
    randomUnmarked = rand() % nbMissionsUnmarked;


    skillTemp = missionUnmarked[randomUnmarked]->getSkill();
    dayTemp = missionUnmarked[randomUnmarked]->getDay();
    startingTemp = missionUnmarked[randomUnmarked]->getStartingPeriod();

    if (tempData->distancesMatrix->getDistance(0, missionUnmarked[randomUnmarked]->getId()) <
        tempData->distancesMatrix->getDistance(1, missionUnmarked[randomUnmarked]->getId())) {

      do {
        randomMarked = rand() % nbMissionsMarkedCenter1;
      } while (tempData->centers[0]->getMissions()[randomMarked]->getSkill() != skillTemp
               || tempData->centers[0]->getMissions()[randomMarked]->getDay() != dayTemp
               || tempData->centers[0]->getMissions()[randomMarked]->getStartingPeriod() != startingTemp);

      tempMission = tempData->centers[0]->getMissions()[randomMarked];

      tempData->missions[tempMission->getId() - 1]->setAssigned(1);
      tempData->missions[missionUnmarked[randomUnmarked]->getId() - 1]->setAssigned(0);

      missionUnmarked[randomUnmarked]->setAssigned(1);
      tempData->centers[0]->swapMissions(randomMarked, missionUnmarked[randomUnmarked]);
      missionUnmarked[randomUnmarked] = tempMission;
      missionUnmarked[randomUnmarked]->setAssigned(0);
    } else {

      do {
        randomMarked = rand() % nbMissionsMarkedCenter2;
      } while (tempData->centers[1]->getMissions()[randomMarked]->getSkill() != skillTemp
               || tempData->centers[1]->getMissions()[randomMarked]->getDay() != dayTemp
               || tempData->centers[1]->getMissions()[randomMarked]->getStartingPeriod() != startingTemp);


      tempMission = tempData->centers[1]->getMissions()[randomMarked];

      tempData->missions[tempMission->getId() - 1]->setAssigned(1);
      tempData->missions[missionUnmarked[randomUnmarked]->getId() - 1]->setAssigned(0);

      missionUnmarked[randomUnmarked]->setAssigned(1);
      tempData->centers[1]->swapMissions(randomMarked, missionUnmarked[randomUnmarked]);
      missionUnmarked[randomUnmarked] = tempMission;
      missionUnmarked[randomUnmarked]->setAssigned(0);
    }
  }

  return tempData;
}

std::vector<solution *> genetic::selection(std::vector<solution *> population, data *data1) {
  int decalage = 0;
  int random;
  int populationSize = population.size();
  int popSizeDivided = populationSize / 2;
  if (populationSize % 2 != 0) {
    decalage = 1;
  }
  std::vector<int> selected1(popSizeDivided);
  std::vector<int> selected2((popSizeDivided) + decalage);
  std::vector<solution *> firstPart(popSizeDivided);
  std::vector<solution *> secondPart((popSizeDivided) + decalage);
  solution *bestSolutionFirstPart;
  solution *bestSolutionSecondPart;

  std::vector<solution *> selectedPopulation(2);

  for (int i = 0; i < popSizeDivided; i++) {
    do {
      random = rand() % populationSize;
    } while (std::find(selected1.begin(), selected1.end(), random) != selected1.end());
    selected1[i] = random;
  }
  for (int i = 0; i < popSizeDivided + decalage; ++i) {
    if (std::find(selected1.begin(), selected1.end(), i) == selected1.end()) {
      selected2[i] = i;
    }
  }
  for (int i = 0; i < popSizeDivided; ++i) {
    firstPart[i] = population[selected1[i]];
  }
  for (int i = 0; i < popSizeDivided + decalage; ++i) {
    secondPart[i] = population[selected2[i]];
  }

  bestSolutionFirstPart = firstPart[0];
  for (int i = 0; i < popSizeDivided - 1; i++) {
    for (int j = i + 1; j < popSizeDivided; j++) {
      bestSolutionFirstPart = bestSolutionFirstPart->compareSolutions(firstPart[j], data1);
    }
  }
  bestSolutionSecondPart = secondPart[0];
  for (int i = 0; i < popSizeDivided + decalage - 1; i++) {
    for (int j = i + 1; j < popSizeDivided + decalage; j++) {
      bestSolutionSecondPart = bestSolutionSecondPart->compareSolutions(secondPart[j], data1);
    }
  }

  selectedPopulation[0] = bestSolutionFirstPart;
  selectedPopulation[1] = bestSolutionSecondPart;

  return selectedPopulation;
}