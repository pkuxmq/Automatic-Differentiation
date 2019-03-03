#include "ADGraph.h"
#include "Operator.h"
#include <map>
#include <queue>
using std::map;
using std::queue;

extern Op_Add op_add;
extern Op_Sub op_sub;
extern Op_Mul op_mul;
extern Op_Div op_div;
extern Op_Sin op_sin;
extern Op_Cos op_cos;
extern Op_Tan op_tan;
extern Op_Log op_log;
extern Op_Exp op_exp;

vector<ADNode *> ADOperator::computeDiff(vector<ADNode *> *preNodes, vector<ADNode *> *GraphNodes) {
	vector<ADNode *> Diff;
	return Diff;
}

double ADOperator::computeOp(vector<ADNode *> *preNodes) {
	return 0;
}

ADNode::ADNode() {
	op = NULL;
	NodeDiff = NULL;
	val = 0;
}

ADNode::ADNode(ADOperator *o) {
	op = o;
	NodeDiff = NULL;
	val = 0;
}

ADNode::~ADNode() {}

void ADNode::ConnectPreNode(ADNode *n) {
	preNodes.push_back(n);
	n->postNodes.push_back(this);
}

void ADNode::ConnectPostNode(ADNode *n) {
	postNodes.push_back(n);
	n->preNodes.push_back(this);
}

void ADNode::SetVal(double v) {
	val = v;
}

void ADNode::ComputeNode() {
	if (op != NULL)
		val = op->computeOp(&preNodes);
}

ADGraph::ADGraph() {}

ADGraph::~ADGraph() {
	for (auto i : Nodes)
		delete i;
}

void ADGraph::ConnectNode(ADNode *pre, ADNode *post) {
	pre->ConnectPostNode(post);
}

void ADGraph::TopoSort() {
	map<ADNode *, int> NodeMap;
	int NodeNum = Nodes.size();
	for (int i = 0; i < NodeNum; i++)
		NodeMap[Nodes[i]] = i;

	int *degree = new int[NodeNum];
	memset(degree, 0, sizeof(int) * NodeNum);

	for (int i = 0; i < NodeNum; i++) {
		for (auto j : Nodes[i]->postNodes)
			degree[NodeMap[j]]++;
	}

	vector<ADNode *> OrderedNodes;
	queue<ADNode *> WaitingList;
	for (int i = 0; i < NodeNum; i++)
		if (degree[i] == 0)
			WaitingList.push(Nodes[i]);

	while (!WaitingList.empty()) {
		auto i = WaitingList.front();
		WaitingList.pop();
		OrderedNodes.push_back(i);
		for (auto j : i->postNodes) {
			degree[NodeMap[j]]--;
			if (degree[NodeMap[j]] == 0)
				WaitingList.push(j);
		}
	}

	Nodes = OrderedNodes;
}

void ADGraph::BuildADGraph() {
	TopoSort();
	
	int NodeNum = Nodes.size();

	for (int i = NodeNum - 1; i >= 0; i--) {
		if (Nodes[i]->postNodes.empty()) {
			Nodes[i]->NodeDiff = CreateConstNode(1);
		}
		else if (Nodes[i]->postNodes.size() == 1) {
			Nodes[i]->NodeDiff = Nodes[i]->postNodeDiff[0];
		}
		else {
			ADNode *d = CreateOpNode(&op_add);
			for (auto k : Nodes[i]->postNodeDiff)
				ConnectNode(k, d);
			Nodes[i]->NodeDiff = d;
		}

		if (Nodes[i]->op == NULL)
			continue;

		vector<ADNode *> DiffNodes = Nodes[i]->op->computeDiff(&(Nodes[i]->preNodes), &(Nodes));
		int n = DiffNodes.size();
		for (int j = 0; j < n; j++) {
			ADNode *d = CreateOpNode(&op_mul);
			ConnectNode(Nodes[i]->NodeDiff, d);
			ConnectNode(DiffNodes[j], d);

			Nodes[i]->preNodes[j]->postNodeDiff.push_back(d);

		}
	}

}

void ADGraph::Compute() {
	TopoSort();

	for (auto i : Nodes)
		i->ComputeNode();
}

double ADGraph::GetDiff(ADNode *node) {
	return node->NodeDiff->val;
}

ADNode *ADGraph::CreateInputNode() {
	ADNode *node = new ADNode(NULL);
	Nodes.push_back(node);
	inputNodes.push_back(node);
	return node;
}

ADNode *ADGraph::CreateOpNode(ADOperator *o) {
	ADNode *node = new ADNode(o);
	Nodes.push_back(node);
	return node;
}

ADNode *ADGraph::CreateConstNode(double c) {
	ADNode *node = new ADNode(NULL);
	node->SetVal(c);
	Nodes.push_back(node);
	return node;
}

ADNode *ADGraph::Add(ADNode *n1, ADNode *n2) {
	ADNode *node = new ADNode(&op_add);

	ConnectNode(n1, node);
	ConnectNode(n2, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Sub(ADNode *n) {
	ADNode *node = new ADNode(&op_sub);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Sub(ADNode *n1, ADNode *n2) {
	ADNode *node = new ADNode(&op_sub);

	ConnectNode(n1, node);
	ConnectNode(n2, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Mul(ADNode *n1, ADNode *n2) {
	ADNode *node = new ADNode(&op_mul);

	ConnectNode(n1, node);
	ConnectNode(n2, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Div(ADNode *n1, ADNode *n2) {
	ADNode *node = new ADNode(&op_div);

	ConnectNode(n1, node);
	ConnectNode(n2, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Sin(ADNode *n) {
	ADNode *node = new ADNode(&op_sin);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Cos(ADNode *n) {
	ADNode *node = new ADNode(&op_cos);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Tan(ADNode *n) {
	ADNode *node = new ADNode(&op_tan);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Log(ADNode *n) {
	ADNode *node = new ADNode(&op_log);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}

ADNode *ADGraph::Exp(ADNode *n) {
	ADNode *node = new ADNode(&op_exp);

	ConnectNode(n, node);

	Nodes.push_back(node);

	return node;
}
