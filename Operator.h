#ifndef __OPERATOR__
#define __OPERATOR__

#include "ADGraph.h"

class Op_Add : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Sub : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Mul : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Div : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Sin : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Cos : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Tan : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Log : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

class Op_Exp : public ADOperator {
public:
	vector<ADNode *> computeDiff(vector<ADNode *> *, vector<ADNode *> *);
	double computeOp(vector<ADNode *> *);
};

#endif
