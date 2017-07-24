#ifndef Som_H
#define Som_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip> 
#include <mutex>  
#include <thread>

using namespace std;



struct VarConst{

    int LenData;
    int LenDataGen;
    int LenVec;

    int XCarte;
    int YCarte;

    int XWinner;
    int YWinner;

    int MaxIteration;
    int MaxVoisin;
};
typedef struct VarConst VarConst;

struct Colors
{
    double r;
    double g;
    double b;
};
typedef struct Colors Colors;

struct Node
{
    vector<double> vec;
    double act;
    string etiq;
    Colors color;
};
typedef struct Node Node; 



struct Point
{
    int x;
    int y;
};
typedef struct Point Point;

class Som{
    private:
        vector<double> TabMoyenne;
        vector<double> TabSwapIndice;
        vector<vector<double> > InputData;
        vector<vector<double> >TabDataActivation;
        vector<Point> TabIndiceActivation;
        vector<vector<Node> > Carte;
        VarConst Constants;


    public:
        Som();
        void runs(vector<vector<Node> > _map, int nb_iteration, int nb_voisin);
        void runs1(vector<vector<double> > data, int nb_iteration, int nb_voisin);
        void affiche1();
        void affiche2();
        void init_size_carte(int val);
        void create_carte(vector<vector<double>> data);
        
        void normalise_data();
        double calc_distance(vector<double> vec1, vector<double> vec2);
        void calc_moyenne();
        void gen_vecteur(double ecart_max, double ecart_min, int taille);
        void swap_indice(int taille);
        void add_point(int x, int y);
        void set_alldata_activation();
        vector<vector<double> > get_alldata_activation();
        
        double bmu(vector<double> vec);
        vector<double> update_weights(vector<double> vec1, vector<double> input_vec2, double distance, double coeff);
        void epoch(vector<double> input_data, int max_voisin);
        void training();




};

#endif