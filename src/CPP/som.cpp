#include "som.h"

Som::Som()
{
}

Som::Som(vector<vector<double>> data)
{
    Constants.LenData= data.size();
    Constants.LenVec= data[0].size();

    initSizeCarte(Constants.LenData);
    createCarte(data);
    normaliseData();
    affiche();
    cout<<endl<<"data.size()= "<<data.size()<<endl;
    cout<<"XCarte= "<<Constants.XCarte<<" ; YCarte= "<<Constants.YCarte<<endl;

    calcMoyenne();
    genVecteur(-0.7, 0.7, 10);
}


void Som::initSizeCarte(int val){

    int  nb1= (int)sqrt(val);
    int nb2= 1 + (int)sqrt(val);
    int coord=0;

    if(abs((nb1*nb1) - val) <= abs((nb2*nb2) - val))
        coord= nb1;
    else
        coord= nb2;

    Constants.XCarte= coord;
    Constants.YCarte= coord;
}




void Som::createCarte(vector<vector<double> > data){
    int index=0;

    Carte= new Node*[Constants.XCarte];
    for(int x_c=0;x_c < Constants.XCarte; x_c++){
        Carte[x_c]= new Node[Constants.YCarte];
        for(int y_c=0; y_c< Constants.YCarte; y_c++){
                Carte[x_c][y_c].vec= data[index++];
        }
    }
}


void Som::affiche()
{
    for(int x_c =0; x_c < Constants.XCarte; x_c++){
        for(int y_c=0; y_c< Constants.YCarte; y_c++){
            for(int d=0; d< Constants.LenVec;d++){
                cout<<Carte[x_c][y_c].vec[d]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}


void Som::normaliseData()
{
    double somme=0.0;
    double norme=0.0;

    for(int x_c =0; x_c < Constants.XCarte; x_c++){
        for(int y_c=0; y_c< Constants.YCarte; y_c++){
            somme=0.0;
            for(int d =0; d < Constants.LenVec; d++){
               somme+= pow(Carte[x_c][y_c].vec[d], 2.0); 
            }

            norme= sqrt(somme);
            for(int d =0; d < Constants.LenVec; d++){
                Carte[x_c][y_c].vec[d] /= norme;
            }
        }
    }
}

void Som::calcMoyenne()
{
    TabMoyenne.resize(Constants.LenVec,0.0);

    for(int x_c =0; x_c <Constants.LenVec; x_c++){
        for(int y_c=0; y_c < Constants.YCarte; y_c++){
            for(int d=0; d< Constants.LenVec; d++){
                TabMoyenne[d] +=Carte[x_c][y_c].vec[d]; 
            }
        }
    }

    cout<<"Moyenne"<<endl;
    for(int d=0; d< Constants.LenVec;d++){
        TabMoyenne[d]/=Constants.LenVec;
        cout<<TabMoyenne[d]<<" ";
    }
    cout<<endl<<endl;

}

void Som::genVecteur(double ecart_max, double ecart_min, int taille)
{

    cout<<"gen vecteurs autour de la Moyenne"<<endl;
    for(int elem= 0; elem < taille; elem++){
        vector<double> vec;
        for(int d=0; d< Constants.LenVec; d++){
            double max = TabMoyenne[d] + ecart_max;
            double min = TabMoyenne[d] + ecart_min;
            double val= (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
            vec.push_back(val);
            cout << val<<" ";
        }
        InputData.push_back(vec);
        cout<<endl;
    }

}





double Som::calcDistance(vector<double> vec1, vector<double> vec2)
{
    double distance=0.0;
    for(int d =0; d < Constants.LenVec; d++){
        distance +=pow((vec1[d] -vec2[d]), 2.0);
    }
    return distance;
}




void Som::BMU(vector<double> vec)
{
    //vector<double> listDistance;
    double dist_old= 0.0;
    double dist_new=0.0;

    dist_old= calcDistance(Carte[0][0].vec, vec);
    for(int x_c =0; x_c < Constants.XCarte; x_c++){
        for(int y_c=0; y_c < Constants.YCarte; y_c++){
            dist_new= calcDistance(Carte[x_c][y_c].vec, vec);
            
            if(dist_new < dist_old){
                dist_old= dist_new;
                Constants.XWinner= x_c;
                Constants.YWinner=y_c;
            }
            else if(dist_new == dist_old){
                double random = (double)rand() / (double)RAND_MAX;
                if (random < 0.5) {
                    Constants.XWinner= x_c;
                    Constants.YWinner= y_c;
                }
            }
        }

    }

    //listDistance.push_back(dist);

    //sort(listDistance.begin(), listDistance.end());
    //for(unsigned int i = 0; i < listDistance.size(); i++)
    //   cout << listDistance.at(i) << '\n';
}




void Som::epoch(vector<double> input_data, int lim_rect_voisin)
{

    if(lim_rect_voisin > 0){

        
        
        BMU(input_data);

        for(int x_c= Constants.XWinner - lim_rect_voisin; x_c <= Constants.YWinner + lim_rect_voisin; x_c++){
            for(int y_c = Constants.YWinner - lim_rect_voisin; y_c <= Constants.YWinner + lim_rect_voisin; y_c++){
                if((x_c >= 0) && (x_c < Constants.XCarte)){
                    if((y_c >= 0) && (y_c < Constants.YCarte)){

                    }
                }
            }   
        }
    }
}


void Som::training(vector<vector<double>> input_data)
{
    int index_input_vec = rand() % input_data.size();
}


/*

int *swap_indice(){
    int index1=0;
    int index2=0;
    int  tmp=0;
    int i=0;
    int verif =0;
    int *tab_indice;
    tab_indice = (int*) calloc(ConstValeur.MAX_LEN_DATA, sizeof(int));
    //srand(time(NULL));
    srand(clock());

    for(index1=0;index1< ConstValeur.MAX_LEN_DATA;index1++){
        tab_indice[index1]= index1;
    }

    for(index1= 0; index1<ConstValeur.MAX_LEN_DATA;index1++){

        index2 = rand() % ConstValeur.MAX_LEN_DATA;
        while(index1 == index2){
            index2 = rand() % ConstValeur.MAX_LEN_DATA;
        }

        tmp= tab_indice[index1];
        tab_indice[index1]= tab_indice[index2];
        tab_indice[index2]= tmp;
    }


    return tab_indice;
}
*/


