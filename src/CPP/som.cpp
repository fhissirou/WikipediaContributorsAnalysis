#include "som.h"

Som::Som()
{
}
/// carte n'ont pas la meme taille de lendata et lenvec c'est le probleme a reglé
void Som::runs(vector<vector<Node> > _map, int nb_iteration, int nb_voisin)
{

    this->Constants.MaxIteration= nb_iteration;
    this->Constants.MaxVoisin= nb_voisin;    
    this->Carte= _map;
    this->Constants.XCarte= _map.size();
    this->Constants.YCarte= _map[0].size();
    this->Constants.LenVec=_map[0][0].vec.size();
    this->Constants.LenData= this->Constants.XCarte * this->Constants.YCarte;

    
    //this->init_size_carte(this->Constants.LenData);
    //this->create_carte(data);
    this->normalise_data();
        cout<<this->Constants.LenData<<" LenVec= "<<this->Constants.LenVec<<endl;
    //affiche1();
    //affiche2();
    this->calc_moyenne();
    this->gen_vecteur(0.02, 0.95, 200);
    this->training();
    this->set_alldata_activation();
}


void Som::runs1(vector<vector<double>> data, int nb_iteration, int nb_voisin)
{
    this->Constants.LenData= data.size();
    this->Constants.LenVec= data[0].size();
    this->Constants.MaxIteration= nb_iteration;
    this->Constants.MaxVoisin= nb_voisin;

    //this->init_size_carte(this->Constants.LenData);
    //this->create_carte(data);
    //this->normalise_data();
    //affiche1();
    //affiche2();
    this->calc_moyenne();
    this->gen_vecteur(0.02, 0.95, 200);
    this->training();
    this->set_alldata_activation();
}



/*void Som::init_size_carte(int val){

    int  nb1= (int)sqrt(val);
    int nb2= 1 + (int)sqrt(val);
    int coord=0;

    if(abs((nb1*nb1) - val) <= abs((nb2*nb2) - val))
        coord= nb1;
    else
        coord= nb2;

    this->Constants.XCarte= nb1;coord;
    this->Constants.YCarte= nb1;coord;
}




void Som::create_carte(vector<vector<double> > data){
    int index=0;

    this->Carte= new Node*[this->Constants.XCarte];
    for(int x_c=0;x_c < this->Constants.XCarte; x_c++){
        this->Carte[x_c]= new Node[this->Constants.YCarte];
        for(int y_c=0; y_c< this->Constants.YCarte; y_c++){
                this->Carte[x_c][y_c].vec= data[index++];
        }
    }
}
*/

void Som::affiche1()
{
    cout<<"debut";
    for(int x_c =0; x_c < this->Constants.XCarte; x_c++){
        for(int y_c=0; y_c< this->Constants.YCarte; y_c++){
            for(int d=0; d< this->Constants.LenVec;d++){
                cout<<this->Carte[x_c][y_c].vec[d]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}


void Som::affiche2()
{
    for(int y_c=0; y_c< this->Constants.YCarte; y_c++)
        cout<<"    "<<y_c;
    cout<<endl;
    for(int x_c =0; x_c < this->Constants.XCarte; x_c++){
        cout<<x_c<<" ";
        for(int y_c=0; y_c< this->Constants.YCarte; y_c++){
            cout<<"  .  ";
        }
        cout<<endl;
    }
}


void Som::normalise_data()
{
    double somme=0.0;
    double norme=0.0;

    for(int x_c =0; x_c < this->Constants.XCarte; x_c++){
        for(int y_c=0; y_c< this->Constants.YCarte; y_c++){
            somme=0.0;
            for(int d =0; d < this->Constants.LenVec; d++){
               somme+= pow(this->Carte[x_c][y_c].vec[d], 2.0); 
            }

            norme= sqrt(somme);
            for(int d =0; d < this->Constants.LenVec; d++){
                this->Carte[x_c][y_c].vec[d] /= norme;
            }
        }
    }
}

void Som::calc_moyenne()
{
    //this->MTX.lock();
    this->TabMoyenne.resize(this->Constants.LenVec,0.0);
    //this->MTX.unlock();
    
    for(int x_c =0; x_c <this->Constants.LenVec; x_c++){
        for(int y_c=0; y_c < this->Constants.YCarte; y_c++){
            for(int d=0; d< this->Constants.LenVec; d++){
                //cout<<"1 - ";
                this->TabMoyenne[d] +=this->Carte[x_c][y_c].vec[d]; 
                //cout<<"2"<<endl;
            }
        }
    }

    //cout<<"Moyenne"<<endl;
    for(int d=0; d< this->Constants.LenVec;d++){
        this->TabMoyenne[d]/=this->Constants.LenData;
        //cout<<this->TabMoyenne[d]<<" ";
    }
    //cout<<endl<<endl;

}

void Som::gen_vecteur(double ecart_max, double ecart_min, int taille)
{

    //cout<<"gen vecteurs autour de la Moyenne"<<endl;
    this->Constants.LenDataGen= taille;
    for(int elem= 0; elem < taille; elem++){
        vector<double> vec;
        for(int d=0; d< this->Constants.LenVec; d++){
            double max = this->TabMoyenne[d] + ecart_max;
            double min = this->TabMoyenne[d] + ecart_min;
            double val= (((double)rand() / (double)RAND_MAX) * (max - min)) + min;
            vec.push_back(val);
            //cout << val<<" ";
        }
        this->InputData.push_back(vec);
        //cout<<endl;
    }

}



void  Som::swap_indice(int taille){
    

    this->TabSwapIndice.resize(taille,0.0);
    srand(clock());

    for(int elem=0;elem< taille;elem++){
        this->TabSwapIndice[elem]= elem;
    }

    for(int d_1= 0; d_1<taille;d_1++){

        int d_2 = rand() % taille;
        while(d_1 == d_2){
            d_2 = rand() % taille;
        }

        int tmp= this->TabSwapIndice[d_1];
        this->TabSwapIndice[d_1]= this->TabSwapIndice[d_2];
        this->TabSwapIndice[d_2]= tmp;
    }

    /*for(int elem=0;elem< taille;elem++){
        cout << this->TabSwapIndice[elem]<<" ";
    }*/
}





double Som::calc_distance(vector<double> vec1, vector<double> vec2)
{
    double distance=0.0;
    for(int d =0; d < this->Constants.LenVec; d++){
        distance +=pow((vec1[d] -vec2[d]), 2.0);
    }
    //cout<<"somdist= "<<distance<<" sqrt= "<<sqrt(distance)<<endl;
    return sqrt(distance);
}

void Som::add_point(int x, int y)
{
    bool exist_point= false;

    for(int i=0; i< this->TabIndiceActivation.size(); i++){
        int x2= this->TabIndiceActivation[i].x;
        int y2= this->TabIndiceActivation[i].y;
        
        if((x == x2) && (y == y2)){
            exist_point= true;
            break;
        }
    }
    if(exist_point == false){
        Point p;
        p.x= x;
        p.y= y;
        this->TabIndiceActivation.push_back(p);
    }
}

void Som::set_alldata_activation()
{
    for(int i=0; i< this->TabIndiceActivation.size(); i++){
        int x= this->TabIndiceActivation[i].x;
        int y= this->TabIndiceActivation[i].y;
        this->TabDataActivation.push_back(this->Carte[x][y].vec);
    }

}

vector<vector<double> > Som:: get_alldata_activation(){
    return this->TabDataActivation;
}

double Som::bmu(vector<double> vec)
{
    //vector<double> listDistance;
    double dist_old= 0.0;
    double dist_new=0.0;

    dist_old= this->calc_distance(this->Carte[0][0].vec, vec);
    for(int x_c =0; x_c < this->Constants.XCarte; x_c++){
        for(int y_c=0; y_c < this->Constants.YCarte; y_c++){
            dist_new= this->calc_distance(this->Carte[x_c][y_c].vec, vec);
            //cout<<"old= "<<dist_old<<" et new= "<<dist_new<<endl;
            if(dist_new < dist_old){
                dist_old= dist_new;
                this->Constants.XWinner= x_c;
                this->Constants.YWinner=y_c;
            }
            else if(dist_new == dist_old){
                double random = (double)rand() / (double)RAND_MAX;
                if (random < 0.5) {
                    this->Constants.XWinner= x_c;
                    this->Constants.YWinner= y_c;
                }
            }
        }

    }

    this->add_point(Constants.XWinner, Constants.YWinner);
    return dist_new;
}


vector<double> Som::update_weights(vector<double> vec, vector<double> input_data, double distance, double coeff)
{
    for(int d=0; d< this->Constants.LenVec; d++){
        vec[d] += (input_data[d] - vec[d]) * distance * coeff;
    }
    return vec;
}

void Som::epoch(vector<double> input_data, int lim_rect_voisin)
{

    if(lim_rect_voisin > 0){

        double diff = bmu(input_data);


        for(int x_c= this->Constants.XWinner - lim_rect_voisin; x_c <= this->Constants.YWinner + lim_rect_voisin; x_c++){
            for(int y_c = this->Constants.YWinner - lim_rect_voisin; y_c <= this->Constants.YWinner + lim_rect_voisin; y_c++){
                if((x_c >= 0) && (x_c < this->Constants.XCarte)){
                    if((y_c >= 0) && (y_c < this->Constants.YCarte)){

                        double distance = this->calc_distance(
                            this->Carte[this->Constants.XWinner][this->Constants.YWinner].vec, 
                            this->Carte[x_c][y_c].vec);
                        double alpha= abs(distance - diff);



                       // cout<<"alpha "<<alpha<<" et dist= "<<distance<<endl;
                        /*for(int i=0; i<this->Constants.LenVec; i++)
                            cout<<Carte[x_c][y_c].vec[i]<<" ";
                        cout<<" avant "<<endl;*/
                        
                        this->Carte[x_c][y_c].vec= update_weights(this->Carte[x_c][y_c].vec, input_data, distance, 0.06);
                        
                        /*for(int i=0; i<this->Constants.LenVec; i++)
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
    int pas= (int)(this->Constants.MaxIteration / this->Constants.MaxVoisin);
    int iteration=0;
    while(iteration < this->Constants.MaxIteration){

        swap_indice(this->Constants.LenDataGen);
        //cout<<endl<<"----------------------------------------------------------"<<endl;
        for(int index=0; index< this->TabSwapIndice.size(); index++){

            epoch(this->InputData[index], this->Constants.MaxVoisin);

        }

        iteration++;
        compt_voisin++;
        if(compt_voisin > pas){
            this->Constants.MaxVoisin--;
            cout<<"compt_voisin= "<<Constants.MaxVoisin<<endl;
            compt_voisin= 0;
        }

    }
}








