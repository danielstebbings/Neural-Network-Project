#include "pooling.h"

#include <Eigen>					
#include <string>

	//don't need activation function for pooling layer due to MAX and AVG pooling methods - no need for weights in this layer



Eigen::MatrixXd PoolingLayer::avg_pool( Eigen::MatrixXd input, int filter, int stride) {
	int ip_width = input.rows();
	int ip_height = input.cols();					//should be square input but have these 2 lines just incase it's rectangular

	int output_rows = (ip_width - filter) / stride + 1;			//working out dimensions of output matrix
	int output_cols = (ip_height - filter) / stride + 1;		//reasoning for formula in logbook i think, +1 used since counting initial instance of filter

	Eigen::MatrixXd output(output_rows, output_cols);			//initialising output matrix

	for (int i = 0; i < output_rows; i++) {						//looping through output matrix		
		for (int j = 0; j < output_cols; j++) {
			int start_row = i * stride;						//updates the starting point for each quadrant is calculated in such a way since it moves n*stride times along hence why it's given by i*stride
			int start_col = j * stride;						//likewise for j*stride
			output(i, j) = input.block(start_row, start_col, filter, filter).mean();		//use of block means that we can section off input matrix into desired quadrants
		}																					//filter used twice in argument since square matrix
	}																						//.mean() used to calculate average of each quadrant
	return output;

}

Eigen::MatrixXd PoolingLayer::max_pool(Eigen::MatrixXd input, int filter, int stride) {			//exact same as avg_pool but use of maxCoeff() instead of mean()
	int ip_width = input.rows();
	int ip_height = input.cols();					

	int output_rows = (ip_width - filter) / stride + 1;		
	int output_cols = (ip_height - filter) / stride + 1;		

	Eigen::MatrixXd output(output_rows, output_cols);			

	for (int i = 0; i < output_rows; i++) {							
		for (int j = 0; j < output_cols; j++) {
			int start_row = i * stride;						
			int start_col = j * stride;						
			output(i, j) = input.block(start_row, start_col, filter, filter).maxCoeff();		//maxCoeff used here to obtain max value of selected quadrant
		}																					
	}																						
	return output;

}


double PoolingLayer::global_pool(Eigen::MatrixXd input, std::string global_pool_type) {
	double ans;					//maybe i should make this case sensitive

	if (global_pool_type == "max") {
		ans = input.maxCoeff();
	}
	else if (global_pool_type == "min") {
		ans = input.minCoeff();
	}
	else if (global_pool_type == "avg") {
		ans = input.mean();
	}
	else {
		throw std::exception("invalid pooling type, please enter 'max', 'min' or 'avg'");
	}

	return ans;				//should return a single value
};


PL_Parameters PoolingLayer::getParameters() {
	return this->parameters;
}

void PoolingLayer::setParameters(PL_Parameters params) {
	this->parameters = params;
}


PoolingLayer::PoolingLayer() = default;

PoolingLayer::PoolingLayer(PL_Parameters params) { //Constructor
	this->parameters = params;
}

PoolingLayer::~PoolingLayer() = default; //Destructor


Eigen::MatrixXd PoolingLayer::Run(Eigen::MatrixXd input) {

	Eigen::MatrixXd output; //output matrix

	//switch statement to determine which pooling method to use
	std::string pooling_type = this->parameters.pooling_type;

	if (pooling_type == "max")
	{
		output = max_pool(input, this->parameters.filter, this->parameters.stride);
	}
	else if (pooling_type == "avg")
	{
		output = avg_pool(input, this->parameters.filter, this->parameters.stride);
	}
	else if (pooling_type == "global_max")
	{
		Eigen::MatrixXd maxPooled(1, 1);
		maxPooled(0, 0) = global_pool(input, "max");
		output = maxPooled;
	}
	else if (pooling_type == "global_min")
	{
		Eigen::MatrixXd minPooled(1, 1);
		minPooled(0, 0) = global_pool(input, "min");
		output = minPooled;
	}
	else if (pooling_type == "global_avg")
	{
		Eigen::MatrixXd avgPooled(1, 1);
		avgPooled(0, 0) = global_pool(input, "avg");
		output = avgPooled;
	}
	else
	{
		throw std::exception("invalid pooling type, please enter 'max', 'global_[max/min]' or 'avg'");
	}
	
	return output;
};

