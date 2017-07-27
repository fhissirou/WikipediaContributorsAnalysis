#ifndef Som_H
#define Som_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip> 
#include "constants.h"

using namespace std;


class Som{
    public:
        vector<double> TabMoyenne;
        vector<double> TabSwapIndice;
        vector<vector<double> > InputData;
        vector<vector<double> >TabDataActivation;
        vector<Point> TabIndiceActivation;
        vector<vector<Node> > Carte;
        VarConst Constants;




    public:
        Som();
        void config(vector<vector<Node> > _map, int nb_iteration, int t_apprentissage );
        void affiche1();
        void affiche2();
        //void init_size_carte(int val);
        //void create_carte(vector<vector<double>> data);
        
        void normalise_data();
        double calc_distance(vector<double> vec1, vector<double> vec2);
        void calc_moyenne();
        void gen_vecteur(double ecart_max, double ecart_min, int taille);
        void swap_indice(int taille);
        void add_point(int x, int y);
        void set_alldata_activation();
        vector<vector<double> > get_alldata_activation();
        
        double bmu(vector<double> vec);
        double get_rayon_voisinage(double iteration);
        double get_valeur_ajustement(double dist_carre, double rayon);
        vector<double> update_weights(vector<double> vec1, vector<double> input_vec2, double distance, double coeff);
        void epoch(vector<double> input_data, int max_voisin);
        void training();

};

#endif