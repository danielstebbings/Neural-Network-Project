#pragma once

#include "Layer.h"

#include <Eigen>
#include <functional>

class ActivationLayer : BaseLayer
{
private:
	std::function <Eigen::MatrixXd(Eigen::MatrixXd)> activationFunction;
public:
	ActivationLayer();
	ActivationLayer(std::function <Eigen::MatrixXd(Eigen::MatrixXd)> activationFunction);

	std::function <Eigen::MatrixXd(Eigen::MatrixXd)> getActivationFunction();
	void setActivationFunction(std::function <Eigen::MatrixXd(Eigen::MatrixXd)> activationFunction);
	Eigen::MatrixXd Run(Eigen::MatrixXd input);
};