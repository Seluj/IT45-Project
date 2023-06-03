//
// Created by jules on 02/06/2023.
//

#include "kMedoids.hpp"
#include <limits>

/* ----------------------------------- Constructor ----------------------------------- */
    
    kMedoids::kMedoids() {
        this->medoids = std::vector<int>();
        this->assignments = std::vector<std::vector<int>>();
    }
    
    kMedoids::kMedoids(std::vector<int> medoids, std::vector<std::vector<int>> assignments) {
        this->medoids = std::move(medoids);
        this->assignments = std::move(assignments);
    }

/* ----------------------------------- KMedoid ----------------------------------- */

  void kMedoids::kMedoidsAlgo(data* data1){
    for (int i = 0; i < data1->nbCenters; i++){
        /* code */
    }
    //We assign each mission to a center
    this->medoidsAssign(data1);
    //We update the medoids
    this->medoidsUpdate();
    //We calculate the cost
    this->calculateCost();
  }

  void kMedoids::medoidsAssign(data* data1){
    float distance = std::numeric_limits<float>::max();
    int row = 0;
    for (int i = 0; i < data1->nbMissions; i++) { //We iterate over the missions and/or centers to assign
        for (int j = 0; j < data1->nbCenters; j++) { //We iterate over the medoids
            while (i == this->medoids[j]) { //To make sure we don't compare a medoid to itself
                row = i++;
            }
            if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the mission and the medoid with the smallest distant previously found
                distance = data1->distancesMatrix->getDistance(row, medoids[j]);
                //Assign the mission or center to the medoid
            }
            row++;
        }
    }
  }

  void kMedoids::medoidsUpdate(){

  }
    
  void kMedoids::calculateCost(){

  }