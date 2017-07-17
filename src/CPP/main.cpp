#include "load.h"
#include "som.h"

using namespace std;

int main(int args, char *argv[]){

    string strPathfileExtract="../../data/output/extract_pages_infos.csv";
    Load load(strPathfileExtract, 10);
    //load.readFile();

    Som som(load.readFile());

    return 0;
}