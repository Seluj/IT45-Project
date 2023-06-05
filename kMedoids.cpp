//
// Created by jules on 02/06/2023.
//

#include "kMedoids.hpp"
#include <limits>

/* ----------------------------------- Constructor ----------------------------------- */
    
    kMedoids::kMedoids() {
        this->cost = 0;
        this->oldCost = std::numeric_limits<float>::max();
        this->medoids = std::vector<int>();
        this->assignments = std::vector<std::vector<int>>();
    }
    
    kMedoids::kMedoids(float cost, float oldCost,std::vector<int> medoids, std::vector<std::vector<int>> assignments) {
        this->cost = cost;
        this->oldCost = oldCost;
        this->medoids = std::move(medoids);
        this->assignments = std::move(assignments);
    }

/* ----------------------------------- KMedoid ----------------------------------- */

  void kMedoids::kMedoidsAlgo(data* data1) {
    int i = 0; //Keeps track of the number of iterations
    //How many do we want to iterate?
    while (this->cost < this->oldCost && i < 4){
        //We assign each mission to a center
        this->medoidsAssign(data1);

        //We calculate the cost of the new solution
        this->oldCost = this->cost;
        this->cost = 0;
        for (int j = 0; j < data1->nbCenters; j++) //We cumulate the cost of each of our medoids
        {
            this->cost = this->calculateCost();
        }
        
        //We update the medoids
        this->medoidsUpdate();
        i++;
    }
  }

  void kMedoids::medoidsAssign(data* data1) {
    float distance;
    int row = 0; //Keeps track of the distance row
    int tempAssign = 0; //Position of the medoid the assignment has been assigned to [it's position in the distance matrix]

    //For the first i positions [i < nbCenters] we make sure that the medoid the assignment is compared to is not a center [We can't assign a center to a center]
    for (int i = 0; i < data1->nbCenters; i++) {
        distance = std::numeric_limits<float>::max(); //We reset the distance

        for (int j = 0; j < data1->nbCenters; j++) {

            //We verify that we haven't already assigned a center to this medoid
            if (this->assignments[j].empty() == true) {

                //We check that the row is not the one belonging to a medoid
                if (row == this->medoids[j]) {
                    row++;
                }

                //We check that the medoid isn't a center to avoid assigning a center to a center
                if (this->medoids[j] > data1->nbCenters) {

                    //We make sure the center has the capacity for this mission
                    if (data1->centers[i]->getCapacity(data1->missions[this->medoids[j] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[j] - data1->nbCenters]->getStartingPeriod()) > 0) {
                        
                        if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the assignment and the medoid with the smallest distant previously found
                            distance = data1->distancesMatrix->getDistance(row, medoids[j]); //New smallest distance
                            tempAssign = j; //Keep track of the new best medoid
                        }
                    }
                }
            }
        }
        //We assign the assignment to the medoid
        this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),row);
        //We update the capacity of the center
        data1->centers[i]->updateCapacity(data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getStartingPeriod());
        row++; //We increment the row
    }
    
    //Now we move on to assinging the missions to the medoids
    for (int i = data1->nbCenters-1; i < data1->nbMissions; i++) { //We iterate over the assignments, we know these ones are missions
        distance = std::numeric_limits<float>::max(); //We reset the distance

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
    
  float kMedoids::calculateCost(){

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