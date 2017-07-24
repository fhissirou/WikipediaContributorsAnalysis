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



Point init_size(int val){

    int  nb= (int)sqrt(val);
    Point p;
    p.x= nb;
    p.y= nb;
    return p;
}




vector<vector<Node> > init_carte(vector<vector<double> > data, Point p){
    vector<vector<Node> >_map;
    int index=0;

    //_map= new Node*[p.x];
    for(int x_c=0;x_c < p.x; x_c++){
        //_map[x_c]= new Node[p.y];
        vector<Node> v_map;
        for(int y_c=0; y_c< p.y; y_c++){
            Node node;
            node.vec= data[index++];
            v_map.push_back(node);
            //_map[x_c][y_c].color= init_rgb();
        }
        _map.push_back(v_map);
    }
    return _map;
}




int main(int args, char *argv[]){
    vector<vector<double> > all_data;
    vector<vector<double> > data_hierarchical;
    vector<thread> threads_som;
    vector<Som> all_som;
    vector<vector<Node> > _map;
    
    double len_one_som_data=2500;
    string strPathfileExtract="../../data/output/extract_pages_infos.csv";
    
    Load load(strPathfileExtract, 10);
    all_data = load.readFile();


    cout<<"len "<<all_data.size()<<endl;

    for(int d= 0; d < 20000; d+=len_one_som_data){
        Som s;
        all_som.push_back(s);   
    }

    Point taille= init_size(all_data.size());
    Point p = init_size(len_one_som_data);
    cout<<taille.x<<" et "<<taille.y<<endl;

    _map= init_carte(all_data, taille);
    int dx=0;
    int d=0;
    while(dx < taille.x){
        
        int dy=0;
        while(dy< taille.y){
            int x= dx;
            vector<vector<Node> > sous_map;
            while((x < (dx+p.x)) && (x < taille.x) && (dy < taille.y)){
                vector<Node> s_m;
                int y= dy;
                while((y < (dy+p.y)) && (y < taille.y)){
                    s_m.push_back(_map[x][y++]);
                                //cout<<x<<" - "<<y<<endl;
                }
                

                sous_map.push_back(s_m);
                x++;
            }
            
            //cout<<"alloc "<<endl;
            //cout<<sous_map.size()<<" +++ "<<sous_map[d].size()<<endl;
            threads_som.push_back(thread(&Som::runs,&all_som[d], sous_map, 100, 10));
            cout<<"Starting threads SOM "<< threads_som.size()<<endl; 
            dy+=p.y;
            d++;
            //cout<<dx<<" - "<<dy<<endl;
        }
        dx+=p.x;     
    }
    cout<<"finist"<<endl;

    for(int d=0; d<threads_som.size(); d++){
            cout<<"join"<<endl;
        threads_som[d].join();
    }

    
    /*for(int i=0; i< all_som.size(); i++){
        vector < vector<double> > dt;
        dt= all_som[i].get_alldata_activation();

        for(int j=0; j<dt.size(); j++){
            data_hierarchical.push_back(dt[j]);
        }
    }



    Som som_hierarchical;
    thread thread_som_hierarchical(&Som::runs, &som_hierarchical, data_hierarchical, 400, 4);
    thread_som_hierarchical.join();
    cout<<endl<<"---------------SOM data hierarchical-------------------------"<<endl;
    som_hierarchical.affiche1();

    cout<<endl<<endl<<data_hierarchical.size()<<endl<<endl;
    //affiche(data_hierarchical);*/

    return 0;
}










//%------------------------------------------------------------------------------
/*
int main(int args, char *argv[]){
    vector<vector<double> > all_data;
    vector<vector<double> > data_hierarchical;
    vector<thread> threads_som;
    vector<Som> all_som;
    Node **Carte;
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


    int Taille = init_size_carte(data.size());

    Carte= new Node*[this->Constants.XCart];
    for(int x_c=0;x_c < this->Constants.XCarte; x_c++){
        this->Carte[x_c]= new Node[this->Constants.YCarte];
        for(int y_c=0; y_c< this->Constants.YCarte; y_c++){
                this->Carte[x_c][y_c].vec= data[index++];
        }
    }



    for(int d= 0; d < len_data; d+=len_one_som_data){
        vector<vector<double> > data;
        for(int dd = d; (dd < (d+len_one_som_data)) && (dd < len_data); dd++){
            data.push_back(all_data[dd]);
        }

        cout<<"Starting threads SOM "<< nb+1<<endl;
        threads_som.push_back(thread(&Som::runs,&all_som[nb], data, 800, 10));
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



    Som som_hierarchical;
    thread thread_som_hierarchical(&Som::runs, &som_hierarchical, data_hierarchical, 400, 4);
    thread_som_hierarchical.join();
    cout<<endl<<"---------------SOM data hierarchical-------------------------"<<endl;
    som_hierarchical.affiche1();

    cout<<endl<<endl<<data_hierarchical.size()<<endl<<endl;
    //affiche(data_hierarchical);

    return 0;
}

*/