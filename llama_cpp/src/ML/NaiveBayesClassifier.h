
#include <iostream>
#include <vector>

namespace Llama {
	class NaiveBayesClassifier {
	public:
		NaiveBayesClassifier(){};
		
		NaiveBayesClassifier(std::vector<std::vector<int>> Xs, std::vector<bool> Y) {
			this->features = Xs;
			this->featureClass = Y;
		}
		
		double getEstimation(std::vector<int>X, bool Y);
		double getProbability(std::vector<int>X, bool Y);
		
		void addTrainData(std::vector<int>X, bool Y) {
			features.push_back(X);
			featureClass.push_back(Y);
		}
		
		
	private:
		std::vector<std::vector<int>> features;
		std::vector<bool> featureClass;
		
		double theta;
		double pi;
		
		double getTheta(int feature, int featureValue, bool targetClass);
		double getPi(bool targetClass);
		
	};
}