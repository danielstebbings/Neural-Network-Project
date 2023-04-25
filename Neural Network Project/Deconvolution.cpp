
#include "Deconvolution.h"
#include <Eigen>

DeconvolutionLayer::DeconvolutionLayer()
{
	this->kernel = Eigen::MatrixXd::Constant(this->parameters.kernelSize, this->parameters.kernelSize, 1);
}; //Empty / default constructor

DeconvolutionLayer::DeconvolutionLayer(DC_Parameters params) {
	this->parameters = params;
	this->kernel = Eigen::MatrixXd::Constant(this->parameters.kernelSize, this->parameters.kernelSize,1);
};

DeconvolutionLayer::DeconvolutionLayer(DC_Parameters params, Eigen::MatrixXd kernel) {
	this->parameters = params;
	this->kernel = kernel;
};

//methods
DC_Parameters DeconvolutionLayer::getParameters() {
	return this->parameters;
}
void DeconvolutionLayer::setParameters(DC_Parameters params) {
	this->parameters = params;
};

Eigen::MatrixXd DeconvolutionLayer::getKernel() {
	return this->kernel;
};

void DeconvolutionLayer::setKernel(Eigen::MatrixXd kernel) {
	this->kernel = kernel;
};


Eigen::MatrixXd DeconvolutionLayer::Run(Eigen::MatrixXd input) { //algorithms based off beyond data science article, see report for citation
	int outputX = (input.rows() - 1) * this->parameters.stride + this->parameters.kernelSize - 2 * this->parameters.padding;
	int outputY = outputX;

	int paddedDimensions = (input.rows()*this->parameters.stride-1) + 2 * this->parameters.padding;
	Eigen::MatrixXd paddedinput = Eigen::MatrixXd::Zero(paddedDimensions, paddedDimensions);
	for (int i = 0; i < input.rows(); i++) {
		for (int j = 0; j < input.cols(); j++) {
			paddedinput(i*this->parameters.stride + this->parameters.padding, j* this->parameters.stride + this->parameters.padding) = input(i, j);
		}
	}
	Eigen::MatrixXd output = Eigen::MatrixXd::Zero(outputX, outputY);


	//Regular convolution code below
	int scanLength = paddedinput.rows() - this->parameters.kernelSize + 1; //length of scan
	for (int i = 0; i < scanLength; i++) {
		for (int j = 0; j < scanLength; j++) {
			
			output(i, j) = (paddedinput.block(i, //stride always 1 for deconvolution
				j, //stride always 1 for deconvolution
				this->parameters.kernelSize,
				this->parameters.kernelSize) //take kernelSize x kernelSize block
				.cwiseProduct(this->kernel)).sum(); //get sum of elementwise product
		}
	}
	return output;


};

