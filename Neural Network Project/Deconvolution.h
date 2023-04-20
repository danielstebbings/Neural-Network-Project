#pragma once

#include "Layer.h"

#include "Convolution.h"
#include "Deconvolution.h"
#include "FullyConnected.h"
#include "Pooling.h"


#include <Eigen>




class DeconvolutionLayer : BaseLayer {
private:
	struct DC_Parameters_Default {
		int stride = 1;
		int padding = 1;
		int kernelSize = 3;
		int inputChannels = 1;
		int outputChannels = 1;
	};
	DC_Parameters parameters;
	Eigen::MatrixXd kernel;

public:
	struct DC_Parameters : DC_Parameters_Default { //gives default values until overriden
		int stride;
		int padding;
		int kernelSize;
		int inputChannels;
		int outputChannels;
	};
	//Constructors
	DeconvolutionLayer();
	DeconvolutionLayer(DC_Parameters params);
	DeconvolutionLayer(DC_Parameters params, Eigen::MatrixXd kernel);

	//Destructor
	~DeconvolutionLayer();

	//Parameters
	//methods
	Eigen::MatrixXd Run(); //Run(Input)
	DC_Parameters getParameters(); //should be able to initialise with any Parameter type? change in parent>
	void setParameters(DC_Parameters); 

	void setKernel(Eigen::MatrixXd kernel);
	Eigen::MatrixXd getKernel();
	Eigen::MatrixXd Run(Eigen::MatrixXd input);
};
