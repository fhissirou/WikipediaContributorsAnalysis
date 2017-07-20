#include "load.h"
#include "som.h"
#include <thread>

using namespace std;

void affiche(vector<vector<double> > vec){
    for(int i =0; i< vec.size(); i++){
        for(int j=0; j< vec[i].size(); j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(int args, char *argv[]){
    vector<vector<double> > all_data;
    vector<vector<double> > data_hierarchical;
    vector<thread> threads_som;
    vector<Som> all_som;
    double len_one_som_data=2500;
    string strPathfileExtract="../../data/output/extract_pages_infos.csv";
    Load load(strPathfileExtract, 10);
    all_data = load.readFile();
    int len_data= all_data.size();

    cout<<"len "<<len_data<<endl;
    int nb=0;
    for(int d= 0; d < len_data; d+=len_one_som_data){
        Som s;
        all_som.push_back(s);   
    }

    for(int d= 0; d < len_data; d+=len_one_som_data){
        vector<vector<double> > data;
        for(int dd = d; (dd < (d+len_one_som_data)) && (dd < len_data); dd++){
            data.push_back(all_data[dd]);
        }

        cout<<"Starting threads SOM "<< nb+1<<endl;
        threads_som.push_back(thread(&Som::runs,&all_som[nb], data, 20, 4));
        nb++;       
    }
    for(int d=0; d<threads_som.size(); d++)
        threads_som[d].join();

    
    for(int i=0; i< all_som.size(); i++){
        vector < vector<double> > dt;
        dt= all_som[i].get_alldata_activation();

        for(int j=0; j<dt.size(); j++){
            data_hierarchical.push_back(dt[j]);
        }
    }

    cout<<endl<<endl<<data_hierarchical.size()<<endl<<endl;

    Som som_hierarchical;
    thread thread_som_hierarchical(&Som::runs, &som_hierarchical, data_hierarchical, 10, 4);
    thread_som_hierarchical.join();
    cout<<endl<<"---------------SOM data hierarchical-------------------------"<<endl;
    som_hierarchical.affiche1();
    //affiche(data_hierarchical);

    return 0;
}