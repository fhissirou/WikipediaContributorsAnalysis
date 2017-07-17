#ifndef Som_H
#define Som_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>  

using namespace std;

struct VarConst{

    int LenData;
    
    int XCarte;
    int YCarte;
    int LenVec;

    int XWinner;
    int YWinner;
};
typedef struct VarConst VarConst;

struct Node
{
    vector<double> vec;
    double act;
    string etiq;
};
typedef struct Node Node; 

class Som{
    private:
        int MaxCol;
        int MaxLigne;
        vector<double> TabMoyenne;
        vector<vector<double>> InputData;
        Node **Carte;
        VarConst Constants;


    public:
        Som();
        Som(vector<vector<double>> data);
        void affiche();
        void initSizeCarte(int val);
        void createCarte(vector<vector<double>> data);
        
        void normaliseData();
        double calcDistance(vector<double> vec1, vector<double> vec2);
        void calcMoyenne();
        void genVecteur(double ecart_max, double ecart_min, int taille);
        
        void BMU(vector<double> vec);
        void epoch(vector<double> input_data, int max_voisin);
        void training(vector<vector<double>> input_data);




};

#endif