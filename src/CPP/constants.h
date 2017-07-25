#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <vector>

using namespace std;

struct VarConst{

    int LenData;
    int LenDataGen;
    int LenVec;

    int XCarte;
    int YCarte;

    int XWinner;
    int YWinner;

    int MaxIteration;
    int MaxVoisin;
    int LenRGB;
};
typedef struct VarConst VarConst;


struct Node
{
    vector<double> vec;
    double act;
    string etiq;
    vector<double> rgb;
};
typedef struct Node Node; 



struct Point
{
    int x;
    int y;
};
typedef struct Point Point;



#endif 