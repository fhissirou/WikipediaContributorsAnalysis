#include "load.h"


Load::Load()
{
}

Load::Load(string str, int nb)
{
  setNbcluster(nb);
  setFilename(str);
}

void Load::setNbcluster(int nb){
  Nbcluster= nb;
}
int Load::getNbcluster(){
  return Nbcluster;
}


void Load::setFilename(string str){
  Filename= str;
}
string Load::getFilename(){
  return Filename;
}


vector<vector<double> > Load::readFile(){
	string str;
	fstream file(Filename);
	vector<vector<double> > data;
	double max= 0.05;
	double min= 0.001;
	char delims[] = ",";
	if (file.is_open()){
		int first= 1;

		while ( getline (file,str) ){
			if (first == 1)
				first= -1;
			else{
				char *token = strtok((char*)(str.c_str()), delims);
				vector<double> vecteur;
				int elem=0;
				while (token != NULL) {

					if(elem >= 6 and elem < 10){ 
						double valeur =  strtod(token, NULL);
						
						if(valeur==0.0)
							valeur= (((double)rand() / (double)RAND_MAX) * (max - min)) + min; 
						vecteur.push_back(valeur);
					}
			
					token =strtok(NULL, delims);
					elem++;
				}
				
				data.push_back(vecteur);
			}
			
		}
		file.close();
	}
	return data;

}

