#ifndef __ADGRAPH__
#define __ADGRAPH__

#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>
using std::vector;

class ADNode;
class ADGraph;

class ADOperator {
public:
	virtual vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	virtual double computeOp(vector<ADNode *> *);
};

class ADNode {
public:
	vector<ADNode *> preNodes, postNodes;
	ADOperator *op;
	vector<ADNode *> postNodeDiff;
	ADNode *NodeDiff;
	double val;
	
	void ConnectPreNode(ADNode *);
	void ConnectPostNode(ADNode *);
	void SetVal(double);
	void ComputeNode();

	ADNode();
	ADNode(ADOperator *);
	~ADNode();
};

class ADGraph {
public:
	vector<ADNode *> Nodes, inputNodes, outputNodes;
	
	ADNode *CreateInputNode();
	ADNode *CreateOpNode(ADOperator *);
	ADNode *CreateConstNode(double);
	void ConnectNode(ADNode *, ADNode *);
	void TopoSort();
	void BuildADGraph();
	void Compute();
	double GetDiff(ADNode *);

	ADNode *Add(ADNode *, ADNode *);
	ADNode *Sub(ADNode *);
	ADNode *Sub(ADNode *, ADNode *);
	ADNode *Mul(ADNode *, ADNode *);
	ADNode *Div(ADNode *, ADNode *);
	ADNode *Sin(ADNode *);
	ADNode *Cos(ADNode *);
	ADNode *Tan(ADNode *);
	ADNode *Log(ADNode *);
	ADNode *Exp(ADNode *);

	ADGraph();
	~ADGraph();
};

#endif
