#include "Operator.h"
using std::sin;
using std::cos;
using std::tan;
using std::log;
using std::exp;

Op_Add op_add;
Op_Sub op_sub;
Op_Mul op_mul;
Op_Div op_div;
Op_Sin op_sin;
Op_Cos op_cos;
Op_Tan op_tan;
Op_Log op_log;
Op_Exp op_exp;

vector<ADNode *> Op_Add::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	vector<ADNode *> Diffs;

	for (int i = 0; i < n; i++) {
		ADNode *d = new ADNode(NULL);
		d->SetVal(1);
		Diffs.push_back(d);
		GraphNodes->push_back(d);
	}

	return Diffs;
}

double Op_Add::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	for (auto i : *preNodes)
		val += i->val;

	return val;
}

vector<ADNode *> Op_Sub::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 2 && n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	if (n == 2) {
		ADNode *d1 = new ADNode(NULL);
		d1->SetVal(1);
		Diffs.push_back(d1);
		ADNode *d2 = new ADNode(NULL);
		d2->SetVal(-1);
		Diffs.push_back(d2);
	
		GraphNodes->push_back(d1);
		GraphNodes->push_back(d2);
	}
	else {
		ADNode *d1 = new ADNode(NULL);
		d1->SetVal(-1);
		Diffs.push_back(d1);

		GraphNodes->push_back(d1);
	}

	return Diffs;
}

double Op_Sub::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 2 && n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	if (n == 2)
		val = (*preNodes)[0]->val - (*preNodes)[1]->val;
	else
		val = -(*preNodes)[0]->val;

	return val;
}

vector<ADNode *> Op_Mul::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	vector<ADNode *> Diffs;

	if (n == 2) {
		Diffs.push_back((*preNodes)[1]);
		Diffs.push_back((*preNodes)[0]);
	}
	else {
		for (int i = 0; i < n; i++) {
			ADNode *d = new ADNode(&op_mul);
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				d->ConnectPreNode((*preNodes)[j]);
			}
			Diffs.push_back(d);
			GraphNodes->push_back(d);
		}
	}

	return Diffs;
}

double Op_Mul::computeOp(vector<ADNode *> *preNodes) {
	double val = 1;
	for (auto i : *preNodes)
		val *= i->val;

	return val;
}


vector<ADNode *> Op_Div::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 2) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d1 = new ADNode(NULL);
	d1->SetVal(1);
	ADNode *d2 = new ADNode(&op_div);
	d2->ConnectPreNode(d1);
	d2->ConnectPreNode((*preNodes)[1]);
	Diffs.push_back(d2);

	ADNode *d3 = new ADNode(&op_mul);
	d3->ConnectPreNode((*preNodes)[1]);
	d3->ConnectPreNode((*preNodes)[1]);
	ADNode *d4 = new ADNode(&op_div);
	d4->ConnectPreNode((*preNodes)[0]);
	d4->ConnectPreNode(d3);
	ADNode *d5 = new ADNode(&op_sub);
	d5->ConnectPreNode(d4);
	Diffs.push_back(d5);
	
	GraphNodes->push_back(d1);
	GraphNodes->push_back(d2);
	GraphNodes->push_back(d3);
	GraphNodes->push_back(d4);
	GraphNodes->push_back(d5);

	return Diffs;
}

double Op_Div::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 2) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = (*preNodes)[0]->val / (*preNodes)[1]->val;

	return val;
}

vector<ADNode *> Op_Sin::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d = new ADNode(&op_cos);
	d->ConnectPreNode((*preNodes)[0]);
	Diffs.push_back(d);

	GraphNodes->push_back(d);

	return Diffs;
}

double Op_Sin::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = sin((*preNodes)[0]->val);

	return val;
}

vector<ADNode *> Op_Cos::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d1 = new ADNode(&op_sin);
	d1->ConnectPreNode((*preNodes)[0]);
	ADNode *d2 = new ADNode(&op_sub);
	d2->ConnectPreNode(d1);
	Diffs.push_back(d2);

	GraphNodes->push_back(d1);
	GraphNodes->push_back(d2);

	return Diffs;
}

double Op_Cos::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = cos((*preNodes)[0]->val);

	return val;
}

vector<ADNode *> Op_Tan::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d1 = new ADNode(&op_cos);
	d1->ConnectPreNode((*preNodes)[0]);
	ADNode *d2 = new ADNode(&op_mul);
	d2->ConnectPreNode(d1);
	d2->ConnectPreNode(d1);
	ADNode *d3 = new ADNode(NULL);
	d3->SetVal(1);
	ADNode *d4 = new ADNode(&op_div);
	d4->ConnectPreNode(d3);
	d4->ConnectPreNode(d2);
	Diffs.push_back(d4);

	GraphNodes->push_back(d1);
	GraphNodes->push_back(d2);
	GraphNodes->push_back(d3);
	GraphNodes->push_back(d4);

	return Diffs;
}

double Op_Tan::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = tan((*preNodes)[0]->val);

	return val;
}

vector<ADNode *> Op_Log::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d1 = new ADNode(NULL);
	d1->SetVal(1);
	ADNode *d2 = new ADNode(&op_div);
	d2->ConnectPreNode(d1);
	d2->ConnectPreNode((*preNodes)[0]);
	Diffs.push_back(d2);

	GraphNodes->push_back(d1);
	GraphNodes->push_back(d2);

	return Diffs;
}

double Op_Log::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = log((*preNodes)[0]->val);

	return val;
}

vector<ADNode *> Op_Exp::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	vector<ADNode *> Diffs;

	ADNode *d = new ADNode(&op_exp);
	d->ConnectPreNode((*preNodes)[0]);
	Diffs.push_back(d);

	GraphNodes->push_back(d);

	return Diffs;
}

double Op_Exp::computeOp(vector<ADNode *> *preNodes) {
	double val = 0;
	int n = preNodes->size();
	
	if (n != 1) {
		fprintf(stderr, "Error node number %d for substraction!\n", n);
		exit(1);
	}

	val = exp((*preNodes)[0]->val);

	return val;
}
