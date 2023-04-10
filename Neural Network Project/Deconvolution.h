#pragma once

#include "Layer.h"
#include <Eigen>

struct DC_Parameters_Default {
	int stride = 1;
	int padding = 1;
	int kernelSize = 3;
	int inputChannels = 1;
	int outputChannels = 1;
	
};
struct DC_Parameters : DC_Parameters_Default { //gives default values until overriden
	int stride;
	int padding;
	int kernelSize;
	int inputChannels;
	int outputChannels;
};

class DeconvolutionLayer : Layer<DC_Parameters> {
private:
	DC_Parameters parameters;
	Eigen::MatrixXd kernel;

public:	
	//Constructors
	DeconvolutionLayer();
	DeconvolutionLayer(DC_Parameters params);
	DeconvolutionLayer(DC_Parameters params, Eigen::MatrixXd kernel) {};

	//Destructor
	~DeconvolutionLayer();

	//methods
	Eigen::MatrixXd Run(); //Run(Input)
	DC_Parameters getParameters(); //should be able to initialise with any Parameter type? change in parent>
	void setParameters(DC_Parameters); 

	void setKernel(Eigen::MatrixXd kernel);
	Eigen::MatrixXd getKernel();
	Eigen::MatrixXd Run(Eigen::MatrixXd input);
};
