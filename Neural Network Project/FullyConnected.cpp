
#include "FullyConnected.h"
#include "ActivationFunction.h"

#include <Eigen>
/*
Eigen::VectorXd FullyConnectedLayer::to_linear(Eigen::MatrixXd ip) {

	Eigen::VectorXd ans = Eigen::Map<Eigen::VectorXd>(ip.data(), ip.size());
	return ans;
}
probs don't need rn
*/

FC_Parameters FullyConnectedLayer::getParameters() {
	return this->parameters;
};

void FullyConnectedLayer::setParameters(FC_Parameters params) {
	this->parameters = params;
};

FC_Parameters FullyConnectedLayer::getWeight() {			//not sure 
	//unsure of output or what to put in code;
	return this->parameters;
};

void FullyConnectedLayer::setWeight(FC_Parameters weights) {

};

FullyConnectedLayer::FullyConnectedLayer() { //Empty / default constructor

};

FullyConnectedLayer::FullyConnectedLayer(FC_Parameters params) { //constructor with parameters
	//not sure what to include in here

};

FullyConnectedLayer::~FullyConnectedLayer() {	//default destructor
};

Eigen::MatrixXd FullyConnectedLayer::Run(Eigen::MatrixXd input) {
	Eigen::MatrixXd ans1, ans2;
	ans1 = input * this->parameters.weight;
	ans2 = softmax(ans1);		// i changed this from ans2 to ans1
	return ans2;
};