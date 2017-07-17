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


vector<vector<double>> Load::readFile(){
	string str;
	fstream file(Filename);
	int lim_data= 2500;
	vector<vector<double>> data;
	char delims[] = ",";
	if (file.is_open()){
		int n= 0;
		int len_data=0;
		int first= 1;

		while ( getline (file,str) ){
			if (first == 1)
				first= -1;
			else{

				if(++len_data > lim_data)
					break;

				char *token = strtok((char*)(str.c_str()), delims);
				vector<double> vecteur;
				int elem=0;
				while (token != NULL) {

					if(elem >= 6 and elem < 10) 
						vecteur.push_back(strtod(token, NULL));
			
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

