#include "som.h"

Som::Som()
{
}

Som::Som(vector<vector<double>> data, int nb_iteration, int nb_voisin)
{
    Constants.LenData= data.size();
    Constants.LenVec= data[0].size();
    Constants.MaxIteration= nb_iteration;
    Constants.MaxVoisin= nb_voisin;

    init_size_carte(Constants.LenData);
    create_carte(data);
    normalise_data();
    affiche1();
    //affiche2();
    cout<<endl<<"data.size()= "<<data.size()<<endl;
    cout<<"XCarte= "<<Constants.XCarte<<" ; YCarte= "<<Constants.YCarte<<endl;

    calc_moyenne();
    gen_vecteur(0.02, 0.95, 100);

    training();
    affiche1();


}


void Som::init_size_carte(int val){

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




void Som::create_carte(vector<vector<double> > data){
    int index=0;

    Carte= new Node*[Constants.XCarte];
    for(int x_c=0;x_c < Constants.XCarte; x_c++){
        Carte[x_c]= new Node[Constants.YCarte];
        for(int y_c=0; y_c< Constants.YCarte; y_c++){
                Carte[x_c][y_c].vec= data[index++];
        }
    }
}


void Som::affiche1()
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


void Som::affiche2()
{
    for(int y_c=0; y_c< Constants.YCarte; y_c++)
        cout<<"    "<<y_c;
    cout<<endl;
    for(int x_c =0; x_c < Constants.XCarte; x_c++){
        cout<<x_c<<" ";
        for(int y_c=0; y_c< Constants.YCarte; y_c++){
            cout<<"  .  ";
        }
        cout<<endl;
    }
}


void Som::normalise_data()
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

void Som::calc_moyenne()
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
        TabMoyenne[d]/=Constants.LenData;
        cout<<TabMoyenne[d]<<" ";
    }
    cout<<endl<<endl;

}

void Som::gen_vecteur(double ecart_max, double ecart_min, int taille)
{

    cout<<"gen vecteurs autour de la Moyenne"<<endl;
    Constants.LenDataGen= taille;
    for(int elem= 0; elem < taille; elem++){
        vector<double> vec;
        for(int d=0; d< Constants.LenVec; d++){
            double max = TabMoyenne[d] + ecart_max;
            double min = TabMoyenne[d] + ecart_min;
            double val= (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
            vec.push_back(val);
            //cout << val<<" ";
        }
        InputData.push_back(vec);
        //cout<<endl;
    }

}



void  Som::swap_indice(int taille){
    

    TabSwapIndice.resize(taille,0.0);
    srand(clock());

    for(int elem=0;elem< taille;elem++){
        TabSwapIndice[elem]= elem;
    }

    for(int d_1= 0; d_1<taille;d_1++){

        int d_2 = rand() % taille;
        while(d_1 == d_2){
            d_2 = rand() % taille;
        }

        int tmp= TabSwapIndice[d_1];
        TabSwapIndice[d_1]= TabSwapIndice[d_2];
        TabSwapIndice[d_2]= tmp;
    }

    /*for(int elem=0;elem< taille;elem++){
        cout << TabSwapIndice[elem]<<" ";
    }*/
}





double Som::calc_distance(vector<double> vec1, vector<double> vec2)
{
    double distance=0.0;
    for(int d =0; d < Constants.LenVec; d++){
        distance +=pow((vec1[d] -vec2[d]), 2.0);
    }
    //cout<<"somdist= "<<distance<<" sqrt= "<<sqrt(distance)<<endl;
    return sqrt(distance);
}




double Som::bmu(vector<double> vec)
{
    //vector<double> listDistance;
    double dist_old= 0.0;
    double dist_new=0.0;

    dist_old= calc_distance(Carte[0][0].vec, vec);
    for(int x_c =0; x_c < Constants.XCarte; x_c++){
        for(int y_c=0; y_c < Constants.YCarte; y_c++){
            dist_new= calc_distance(Carte[x_c][y_c].vec, vec);
            //cout<<"old= "<<dist_old<<" et new= "<<dist_new<<endl;
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

    //cout<<"Winner ( "<<Constants.XWinner<<" - "<<Constants.YWinner<<" )"<<endl;

    //listDistance.push_back(dist);

    //sort(listDistance.begin(), listDistance.end());
    //for(unsigned int i = 0; i < listDistance.size(); i++)
    //   cout << listDistance.at(i) << '\n';
    return dist_new;
}


vector<double> Som::update_weights(vector<double> vec, vector<double> input_data, double distance, double coeff)
{
    for(int d=0; d< Constants.LenVec; d++){
        vec[d] += (input_data[d] - vec[d]) * distance * coeff;
    }
    return vec;
}

void Som::epoch(vector<double> input_data, int lim_rect_voisin)
{

    if(lim_rect_voisin > 0){

        double diff = bmu(input_data);


        for(int x_c= Constants.XWinner - lim_rect_voisin; x_c <= Constants.YWinner + lim_rect_voisin; x_c++){
            for(int y_c = Constants.YWinner - lim_rect_voisin; y_c <= Constants.YWinner + lim_rect_voisin; y_c++){
                if((x_c >= 0) && (x_c < Constants.XCarte)){
                    if((y_c >= 0) && (y_c < Constants.YCarte)){

                        double distance = calc_distance(
                            Carte[Constants.XWinner][Constants.YWinner].vec, 
                            Carte[x_c][y_c].vec);
                        double alpha= abs(distance - diff);



                       // cout<<"alpha "<<alpha<<" et dist= "<<distance<<endl;
                        /*for(int i=0; i<Constants.LenVec; i++)
                            cout<<Carte[x_c][y_c].vec[i]<<" ";
                        cout<<" avant "<<endl;*/
                        
                        Carte[x_c][y_c].vec= update_weights(Carte[x_c][y_c].vec, input_data, distance, 0.06);
                        
                        /*for(int i=0; i<Constants.LenVec; i++)
                            cout<<Carte[x_c][y_c].vec[i]<<" ";
                        cout<<" après"<<endl;*/

                    }
                }
            }   
        }
    }
}


void Som::training()
{
    int compt_voisin= 0;
    int compt= 0;
    int pas= (int)(Constants.MaxIteration / Constants.MaxVoisin);
    int iteration=0;
    while(iteration < Constants.MaxIteration){

        swap_indice(Constants.LenDataGen);
        //cout<<endl<<"----------------------------------------------------------"<<endl;
        for(int index=0; index< TabSwapIndice.size(); index++){

            epoch(InputData[index], Constants.MaxVoisin);

        }

        iteration++;
        if(compt_voisin > pas){
            Constants.MaxIteration--;
            compt_voisin= 0;
        }

    }
}








