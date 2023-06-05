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
    int row = 0; //Keeps track of the distance row
    int tempAssign = 0; //Position of the medoid the assignment has been assigned to [it's position in the distance matrix]

    //For the first i positions [i < nbCenters] we make sure that the medoid the assignment is compared to is not a center [We can't assign a center to a center]
    for (int i = 0; i < data1->nbCenters; i++) {
        for (int j = 0; j < data1->nbCenters; j++) {
            //We verify that we haven't already assigned a center to this medoid
            if (this->assignments[j].empty() == true){
                //We check that the row is not the one belonging to a medoid
                if (row == this->medoids[j]) {
                    row++;
                }
                //We check that the medoid isn't a center to avoid assigning a center to a center
                if (this->medoids[j] > data1->nbCenters) {
                    //We make sure the center has the capacity for this mission
                    if (data1->centers[i]->getCapacity(data1->missions[this->medoids[j] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[j] - data1->nbCenters]->getStartingPeriod()) > 0){
                        if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the assignment and the medoid with the smallest distant previously found
                            distance = data1->distancesMatrix->getDistance(row, medoids[j]); //New smallest distance
                            tempAssign = j; //Keep track of the new best medoid
                        }
                    }
                }
            }
            row++; //We increment the row
        }
        //We assign the assignment to the medoid
        this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),i);
        //We update the capacity of the center
        data1->centers[i]->updateCapacity(data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getStartingPeriod());
    }
    
    //Now we move on to assinging the missions to the medoids
    for (int i = data1->nbCenters-1; i < data1->nbMissions; i++) { //We iterate over the assignments, we know these ones are missions
        for (int j = 0; j < data1->nbCenters; j++) { //We iterate over the medoids
            //We check that the position of our i is not on a medoid
            while (i == this->medoids[j]) {
                row = i++;
            }
            //Check that the medoid [Or the center assigned to this medoid] has enough capacity to take on the mission
            if (/*To be completed*/) {
                if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the mission and the medoid with the smallest distant previously found
                    distance = data1->distancesMatrix->getDistance(row, medoids[j]);
                    //Keep track of best medoid assignment
                    tempAssign = this->medoids[j];
                }
            }
            row++; //We increment the row
        }
        //We assign the mission to the medoid
        this->assignments[i][tempAssign] = 1; //REVOIR FONCTIONNEMENT DE CETTE MATRICE!!!!
        //Change the capacity of the center



    }
  }

  void kMedoids::medoidsUpdate(){

  }
    
  void kMedoids::calculateCost(){

  }

  void kMedoids::printMedoids(){
    printf("Assignments for each Medoid : \n");
    for (int i = 0; i < this->medoids.size(); i++){ //We iterate over the medoids
        printf("Medoid : %d ", this->medoids[i]);
        for (int j = 0; j < this->assignments[i].size() ; j++) //We iterate over the assignments 
        {
            printf("%d ", this->assignments[i][j]);
        }
        printf("\n");
    }
    std::cout << std::endl;
  }