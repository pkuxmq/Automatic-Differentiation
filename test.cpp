#include <iostream>
#include <map>
#include "ADGraph.h"
#include "Operator.h"
using namespace std;

double f(double x1, double x2, double x3) {
	return (sin(x1+1)+cos(2*x2))*tan(log(x3)) + (sin(x2+1)+cos(2*x1))*exp(1+sin(x3));
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Too few arguments!\n");
		exit(1);
	}

	int X1 = atoi(argv[1]), X2 = atoi(argv[2]), X3 = atoi(argv[3]);
	ADGraph ADG;
	ADNode *x1 = ADG.CreateInputNode();
	ADNode *x2 = ADG.CreateInputNode();
	ADNode *x3 = ADG.CreateInputNode();
	ADNode *one = ADG.CreateConstNode(1);
	ADNode *two = ADG.CreateConstNode(2);

	ADNode *t1, *t2, *y;
   	t1 = ADG.Add(x1, one);
	t1 = ADG.Sin(t1);
	t2 = ADG.Mul(two, x2);
	t2 = ADG.Cos(t2);
	t1 = ADG.Add(t1, t2);
	t2 = ADG.Log(x3);
	t2 = ADG.Tan(t2);
	y = ADG.Mul(t1, t2);
	t1 = ADG.Add(x2, one);
	t1 = ADG.Sin(t1);
	t2 = ADG.Mul(two, x1);
	t2 = ADG.Cos(t2);
	t1 = ADG.Add(t1, t2);
	t2 = ADG.Sin(x3);
	t2 = ADG.Add(one, t2);
	t2 = ADG.Exp(t2);
	t1 = ADG.Mul(t1, t2);
	y = ADG.Add(y, t1);

	ADG.BuildADGraph();
	x1->SetVal(X1);
	x2->SetVal(X2);
	x3->SetVal(X3);
	ADG.Compute();

	double d1 = ADG.GetDiff(x1), d2 = ADG.GetDiff(x2), d3 = ADG.GetDiff(x3);
	cout << "Automatic differentiation results:" << endl;
	cout << "Diff for x1: " << d1 << endl;
	cout << "Diff for x2: " << d2 << endl;
	cout << "Diff for x3: " << d3 << endl;
	cout << endl;
	
	cout << "Numerical differentiation results:" << endl;
	cout << "Diff for x1: " << (f(X1 + 1e-8, X2, X3) - f(X1, X2, X3)) / 1e-8 << endl;
	cout << "Diff for x2: " << (f(X1, X2 + 1e-8, X3) - f(X1, X2, X3)) / 1e-8 << endl;
	cout << "Diff for x3: " << (f(X1, X2, X3 + 1e-8) - f(X1, X2, X3)) / 1e-8 << endl;
	cout << endl;
}
