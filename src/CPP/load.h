#ifndef Load_H
#define Load_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>  

using namespace std;


class Load{
    private:
        string Filename;
        int Nbcluster;


    public:
        Load(string str, int nb);
        Load();
        void setNbcluster(int nb);
        int getNbcluster();

        void setFilename(string str);
        string getFilename();

        vector<vector<double> > readFile();

};

#endif