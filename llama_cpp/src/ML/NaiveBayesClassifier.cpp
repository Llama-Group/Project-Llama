
#include "NaiveBayesClassifier.h"

using namespace std;

double Llama::NaiveBayesClassifier::getTheta(int feature, int featureValue, bool targetClass) {
	const int l = 1;
	
	double theta = 0;
	vector<int> distinct;
	int countY = 0;
	auto currentFeature = this->features[feature];
	for (auto it = currentFeature.begin(); it != currentFeature.end(); ++it) {
		if (std::find(distinct.begin(), distinct.end(), *it) == distinct.end()) {
			distinct.push_back(*it);
		}
		if (this->featureClass[distance(currentFeature.begin(), it)] == targetClass) {
			countY ++;
			if (*it == featureValue)
				theta ++;
		}
	}
	
	theta += l;
	theta = theta/(l*distinct.size() + countY);
	return theta;
}

double Llama::NaiveBayesClassifier::getPi(bool targetClass) {
	double pi = 0;
	
	for (const bool &c : this->featureClass) {
		if (c == targetClass) {
			pi ++;
		}
	}
	
	pi = pi/this->featureClass.size();
	
	return pi;
}

double Llama::NaiveBayesClassifier::getEstimation(std::vector<int> X, bool Y) {
	double retVal = 1;
	
	for (auto it = X.begin(); it != X.end(); ++it) {
		retVal *= this->getTheta((int)distance(X.begin(), it), *it, Y);
	}
	
	retVal *= this->getPi(Y);
	
	return retVal;
}

double Llama::NaiveBayesClassifier::getProbability(std::vector<int> X, bool Y) {
	double eY = this->getEstimation(X, Y);
	return eY/(eY+this->getEstimation(X, !Y));
}