#include <cassert>
#include <vector>
#include <math.h>
using std::vector;

vector<pair<char,std::function<double(double,double)>>> bewerking={
        {'+',[](double a,double b)->double{
            return a + b;
        }},
        {'-',[](double a,double b)->double{
            return a - b;
        }},
        {'/',[](double a,double b)->double{
            return a / b;
        }},
        {'*',[](double a,double b)->double{
            return a * b;
        }},
        {'^',[](double a,double b)->double{
            return pow(a, b);
        }}
};
