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

std::vector<solution *> genetic::createInitialPopulation(data *data1, int populationSize) {

}

std::vector<solution *> genetic::selection(std::vector<solution *> population, data *data1) {
  int decalage = 0;
  int random;
  int nbTest;
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

std::vector<solution *> genetic::crossover(std::vector<solution *> population, data *data1) {
  return std::vector<solution *>();
}

std::vector<solution *> genetic::mutation(std::vector<solution *> population, data *data1) {
  return std::vector<solution *>();
}