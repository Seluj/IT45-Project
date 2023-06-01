#ifndef IT45_PROJECT_DISTANCECSV_HPP
#define IT45_PROJECT_DISTANCECSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"

class distanceCSV {
  private:
    std::vector<std::vector<float>> matrix; // 2D vector of floats to store the matrix
    int nbRows;                             // Number of rows of the matrix
    int nbColumns;                          // Number of columns of the matrix
  public:

    /* --------------------------------- Constructor --------------------------------- */

    distanceCSV(const std::string& path);

    /* --------------------------------- Destructor --------------------------------- */

    ~distanceCSV();

    /* --------------------------------- Accessors --------------------------------- */

    std::vector<std::vector<float>> getMatrix();
    int getNbRows();
    int getNbColumns();

    /* --------------------------------- Print the matrix --------------------------------- */

    void printMatrix();

    /* --------------------------------- Modify the matrix --------------------------------- */

    /**
     * Modify the value of the element at the position (i, j) of the matrix
     * @param i index of the row
     * @param j index of the column
     * @param value new value of the element
     */
    void modifyElement(int i, int j, float value);

    /**
     * Modify the value of all the elements of the row i with the same value
     * @param i index of the row
     * @param value new value of the elements
     */
    void modifyRow(int i, float value);

    /**
     * Modify the value of all the elements of the row i with a vector of values
     * @param i index of the row
     * @param row vector of new values of the elements
     */
    void modifyRow(int i, std::vector<float> row);

    /**
     * Modify the value of all the elements of the column j with the same value
     * @param j index of the column
     * @param value new value of the elements
     */
    void mofifyColumn(int j, float value);

    /**
     * Modify the value of all the elements of the column j with a vector of values
     * @param j index of the column
     * @param column vector of new values of the elements
     */
    void mofifyColumn(int j, std::vector<float> column);
};


#endif //IT45_PROJECT_DISTANCECSV_HPP
