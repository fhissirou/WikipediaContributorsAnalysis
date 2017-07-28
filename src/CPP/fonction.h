#ifndef FONCTION_H
#define FONCTION_H


#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <thread>
#include <iostream>
#include <vector>

#include "constants.h"
#include "som.h"
#include "load.h"

using namespace std;




Point init_size(int val);
vector<double> random_rgb();

vector<vector<Node> > init_carte(vector<vector<double> > data, Point p);
vector<vector<Node> > update_map(vector<vector<Node> >& _map, vector<Som> l_som, Point taille, Point p);
vector<vector<vector<double> > > get_rgb_matrice(vector<vector<Node> > _map);
vector<Som> run_sous_som(vector< vector<Node> >_map, vector<vector<double> > input_data, Point taille, Point p, int max_iteration, int max_voisin);
vector<vector<vector<double> > > runs();

vector<vector<double> > gen_vecteur(double max, double min, int _size_vec, int nb);


#endif 