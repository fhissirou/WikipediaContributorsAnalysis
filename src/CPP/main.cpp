#include "load.h"
#include "som.h"
#include <thread>

using namespace std;


int main(int args, char *argv[]){
    vector<vector<double> > alldata;
    vector<thread> threads_som;
    vector<Som> allsom;
    double len_one_som_data=2500;
    string strPathfileExtract="../../data/output/extract_pages_infos.csv";
    Load load(strPathfileExtract, 10);
    alldata = load.readFile();
    int len_data= alldata.size();

    cout<<"len "<<len_data<<endl;
    int nb=0;
    for(int d= 0; d < len_data; d+=len_one_som_data){
        Som s;
        allsom.push_back(s);   
    }

    for(int d= 0; d < len_data; d+=len_one_som_data){
        vector<vector<double> > data;
        for(int dd = d; (dd < (d+len_one_som_data)) && (dd < len_data); dd++){
            data.push_back(alldata[dd]);
        }

        cout<<"Starting threads SOM "<< nb+1<<endl;
        threads_som.push_back(thread(&Som::runs,&allsom[nb], data, 800, 8));
        nb++;       
    }
    for(int d=0; d<threads_som.size(); d++)
        threads_som[d].join(); 

    return 0;
}