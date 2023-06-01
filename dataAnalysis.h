//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_DATAANALYSIS_H
#define IT45_PROJECT_DATAANALYSIS_H

#include "dataCollection.hpp"
#include "data.h"
#include "classes/center.h"

class dataAnalysis {
public:
  dataAnalysis(dataCollection* d, data* data1);

  void dataAnalysisPrint(data *data1);
};


#endif //IT45_PROJECT_DATAANALYSIS_H
