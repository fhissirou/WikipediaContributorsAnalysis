#include "fonction.h"

/*
void affiche(vector<vector<double> > vec){
    for(int i =0; i< 50; i++){
        for(int j=0; j< 50; j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

void affiche2(vector<vector<Node> > vec){
    for(int i =0; i< 10; i++){
        cout<<i<<"\t";
        for(int j=0; j< 10; j++){
            for(int k=0; k< vec[i][j].vec.size(); k++)
                cout<<vec[i][j].vec[k]<<" ; ";
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl<<"---------------------------------------------"<<endl<<endl;
}



void affiche_col(vector<vector<Node> > vec){
    for(int i =0; i< vec.size(); i++){
        cout<<i<<"\t";
        for(int j=0; j< vec[i].size(); j++){
            cout<<"[";
            for(int k=0; k< vec[i][j].rgb.size(); k++)
                cout<<vec[i][j].rgb[k]<<" , ";
            cout<<"]"<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<endl<<"---------------------------------------------"<<endl<<endl;
}
*/

Point init_size(int val){

    int  nb= (int)sqrt(val);
    Point p;
    p.x= nb;
    p.y= nb;
    return p;
}

vector<double> random_rgb(){
    vector<double> rgb;
    double min= 0.01;
    double max= 1;

    for(int i=0; i< 3; i++){ 
        double val = (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
        rgb.push_back(val);
    }
    return rgb;
}



vector<vector<double> > gen_vecteur(double max, double min, int _size_vec, int nb)
{
    vector<vector<double> > tab_vec;
    //cout<<"gen vecteurs autour de la Moyenne"<<endl;
    //this->Constants.LenDataGen= taille;
    /*for(int elem= 0; elem < nb; elem++){
        vector<double> vec;
        for(int d=0; d< _size_vec; d++){
            //double max = this->TabMoyenne[d] + ecart_max;
            //double min = this->TabMoyenne[d] + ecart_min;
            double val= (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
            vec.push_back(val);
            //cout << val<<" ";
            cout<<elem<<": val= "<<val<<" ";
        }
        cout<<endl;
        tab_vec.push_back(vec);
        //cout<<endl;
    }*/
     //create a data set
  vector<double> red, green, blue, yellow, orange, purple, dk_green, dk_blue;

  red.push_back(1);
  red.push_back(0);
  red.push_back(0);

  green.push_back(0);
  green.push_back(1);
  green.push_back(0);

  dk_green.push_back(0);
  dk_green.push_back(0.5);
  dk_green.push_back(0.25);

  blue.push_back(0);
  blue.push_back(0);
  blue.push_back(1);

  dk_blue.push_back(0);
  dk_blue.push_back(0);
  dk_blue.push_back(0.5);

  yellow.push_back(1);
  yellow.push_back(1);
  yellow.push_back(0.2);

  orange.push_back(1);
  orange.push_back(0.4);
  orange.push_back(0.25);

  purple.push_back(1);
  purple.push_back(0);
  purple.push_back(1);


  tab_vec.push_back(yellow);
  tab_vec.push_back(red);
  tab_vec.push_back(green);
  tab_vec.push_back(blue);
  tab_vec.push_back(orange);
  //tab_vec.push_back(purple);
  //tab_vec.push_back(dk_green);
  //tab_vec.push_back(dk_blue);
    return tab_vec;
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
            node.rgb= random_rgb();
            v_map.push_back(node);
        }
        _map.push_back(v_map);
    }
    return _map;
}
vector<vector<Node> > update_map(vector<vector<Node> >& _map, vector<Som> l_som, Point taille, Point p){
    int d= 0;

    for(int dx=0; dx < taille.x; dx+=p.x){
        for(int dy=0; dy< taille.y; dy+=p.y){

            for(int x=dx; (x<taille.x) && (x< dx+p.x) && (dy < taille.y); x++){
                for(int y=dy; (y< taille.y) && (y < (dy+p.y)); y++){
                    int s_x= x - dx;
                    int s_y= y - dy;
                    _map[x][y]= l_som[d].Carte[s_x][s_y];
                }
            }
            d++;
        }
    }
    return _map;
}
/*int get_list_map(vector<Som> lsom, int pas){
    vector<vector<vector<Node> list_map;
    vector<vector<Node> > _map;
    vector<vector<double> > v;
    for(int i=0; i<l_som.size(); i++){
        dt= l_som[i].get_alldata_activation();
        for(int d= 0; d < dt.size(); d++)

    }
}



vector<vector<double> carte_to_vec(vector<vector<Node> > _map){
    vector<vector<double> >data;
    for(int i=0; i< _map.size(); i++){
        for(int j=0; j< _map[i].size; j++){
            dt.append(data)
        }
    }
}
*/

vector<vector<vector<double> > > get_rgb_matrice(vector<vector<Node> > _map){
    vector<vector<vector<double> > > mat_data;
   
   for(int i=0; i< _map.size(); i++){
    vector<vector<double> > list_vec;
    for(int j=0; j< _map[i].size(); j++){
        /*vector<double> vec;
        for(int k=0; k< 3; k++){
            vec.push_back(_map[i][j].vec[k]);
        }
        list_vec.push_back(vec);*/
        list_vec.push_back(_map[i][j].rgb);
    }
    mat_data.push_back(list_vec);
   } 
   return mat_data;
}



vector<Som> run_sous_som(vector< vector<Node> >_map, vector<vector<double> > input_data, Point taille, Point p, int max_iteration, double t_apprentissage){
    int dx=0;
    int d=0;
    vector<Som> all_som;
    vector<thread> threads_som;
    for(int i= 0; i < taille.x; i+=p.x){
        for(int j=0; j< taille.y; j+=p.y){
            Som s;
            all_som.push_back(s);   
        }
    }
    
    while(dx < taille.x){
        
        int dy=0;
        while(dy< taille.y){
            int x= dx;
            vector<vector<Node> > sous_map;
            while((x < (dx+p.x)) && (x < taille.x) && (dy < taille.y)){
                vector<Node> s_m;
                int y= dy;
                while((y < (dy+p.y)) && (y < taille.y))
                    s_m.push_back(_map[x][y++]);
                
                sous_map.push_back(s_m);
                x++;
            }

            //affiche2(_map);
            
            threads_som.push_back(thread(&Som::config,&all_som[d++], sous_map, input_data, max_iteration, t_apprentissage));
            cout<<"Starting threads SOM "<< threads_som.size()<<endl; 
            dy+=p.y;
        }
        dx+=p.x;  
    }

    for(int d=0; d<threads_som.size(); d++){
        threads_som[d].join();
    }
    return all_som;
}

vector<vector<vector<double> > > runs(){
    vector<vector<double> > all_data;
    vector<vector<double> > data_hierarchical;
    //vector<thread> threads_som;
    vector<Som> all_som;
    vector<vector<Node> > _map;
    double t_apprentissage= 0.07;
    int max_iteration= 650;
    double len_one_som_data=1024;
    string strPathfileExtract="../../data/output/extract_pages_infos.csv";
    
    Load load(strPathfileExtract, 10);
    all_data = load.readFile();
    Point p = init_size(len_one_som_data);
    Point taille= init_size(all_data.size());

    vector<vector<double> > input_data= gen_vecteur(0.7, 0.2, all_data[0].size(), 100);

    cout<<"len "<<all_data.size()<<endl;

    /*for(int i= 0; i < taille.x; i+=p.x){
        for(int j=0; j< taille.y; j+=p.y){
            Som s;
            all_som.push_back(s);   
        }
    }*/

    _map= init_carte(all_data, taille);
    /*int dx=0;
    int d=0;
    //affiche2(_map);
    //affiche_col(_map);
    while(dx < taille.x){
        
        int dy=0;
        while(dy< taille.y){
            int x= dx;
            vector<vector<Node> > sous_map;
            while((x < (dx+p.x)) && (x < taille.x) && (dy < taille.y)){
                vector<Node> s_m;
                int y= dy;
                while((y < (dy+p.y)) && (y < taille.y))
                    s_m.push_back(_map[x][y++]);
                
                sous_map.push_back(s_m);
                x++;
            }

            //affiche2(_map);
            
            threads_som.push_back(thread(&Som::config,&all_som[d++], sous_map, max_iteration, max_voisin));
            cout<<"Starting threads SOM "<< threads_som.size()<<endl; 
            dy+=p.y;
        }
        dx+=p.x;  
    }

    for(int d=0; d<threads_som.size(); d++){
        threads_som[d].join();
    }*/
    Point pp = p;
    int nb=0;
    for(int i=0; i< 4; i++){
        all_som= run_sous_som(_map,input_data, taille, pp, max_iteration/2, t_apprentissage);
        _map = update_map(_map, all_som, taille, pp);
        nb++;
        if(((pp.x+all_som[nb].Constants.XCarte) <= taille.x) && ((p.y+all_som[nb].Constants.XCarte) <= taille.y) ){
            pp.x+=all_som[nb].Constants.XCarte;
            p.y+= p.y;
        }
        else{
            pp = taille;
            nb=0;
        }
        cout<<"iter = "<<i<<endl;
    }

    all_som= run_sous_som(_map, input_data, taille, taille, max_iteration, t_apprentissage);
    _map = update_map(_map, all_som, taille, taille);


    


    cout<<"finale"<<endl;
    //affiche2(_map);

    
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

    return get_rgb_matrice(_map);
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






BOOST_PYTHON_MODULE(fonction) {
    // An established convention for using boost.python.
    using namespace boost::python;
    
    /*boost::python::class_<std::vector<double> >("PyVec")
        .def(boost::python::vector_indexing_suite<std::vector<double> >());
    // Expose the function hello().*/
    /*class_<vector<double> >("vector<int>")
        .def("__getitem__", (double const&(vector<double>::*)(vector<double>::size_type) const)&vector<double>::at, return_value_policy<copy_const_reference>())
        .def("__len__", &vector<double>::size)
    ;*/


    class_<vector<double> >("vector<double>")
        .def(vector_indexing_suite<vector<double> >());

    class_<vector<vector<double> > >("vector<vector<double> >")
      .def(vector_indexing_suite<vector<vector<double> > >());


    class_<vector<vector<vector<double> > > >("vector<vector<vector<double> > > ")
      .def(vector_indexing_suite<vector<vector<vector<double> > > >());

    def("runs", &runs);

    // Expose the class Som.
    /*class_<Som>("Som")
        //.def("__init__", raw_function(A_init), "vecpython")
        .def(init<int>())
        .def("init_data", &Som::init_data)
        .def("moyenne", &Som::moyenne)
        .def("affiche_moyenne", &Som::affiche_moyenne)
        .def("affiche_data", &Som::affiche_data)
        .def("get_taille", &Som::get_taille)
        .def("set_taille", &Som::set_taille)
        .add_property("Taille", &Som::get_taille, &Som::set_taille)
    ;*/
}
