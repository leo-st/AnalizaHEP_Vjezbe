#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
using namespace std;

class Analyzer{

public:
	double Binomial(int, double, int);
	long int Factorial(int);
	double CPUpper(int, double, int);
	double CPLower(int, double, int);
	void ClopperPearson(int, double);
	void Show();
};
