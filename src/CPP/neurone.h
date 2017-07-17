#ifndef Neurone_H
#define Neurone_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <math>



class Neurone{
    private:
        int MaxCol;
        int MaxLigne;
        vector<vector<double>> Data;

    public:
        Som();
        void normaliseData();
        <vector<double>> calcDistanceEuclidienne(<vector<double> vec1, <vector<double> vec2);


};


#endif