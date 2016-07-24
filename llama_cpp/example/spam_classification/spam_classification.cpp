
#include "ML/NaiveBayesClassifier.h"

//	Table 1 contains (pretend!) training data for a naive Bayes spam filter where the goal is to predict spam based on whether the words “Viagra” and/or “Funds” appear in an incoming email.
//	The data was produced from 50 emails.
//	To understand the format of Table 1 note that the first line of the table states that 9 spam emails have been observed which contain neither “Viagra” nor “Funds”.
//	The second line states that 4 spam emails have been observed where “Funds” was in the email, but “Viagra” was not.
//	The other lines present data in the same way.
//
//	Spam	“Viagra”	“Funds”	Frequency
//	y		n			n		9
//	y		n			y		4
//	y		y			n		5
//	y		y			y		1
//	n		n			n		28
//	n		n			y		2
//	n		y			n		1
//	n		y			y		0
//				Table 1.

using namespace std;

int main() {
	vector<int> y = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	vector<int> n = {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0};
	
	vector<vector<int>> features;
	
	// Gather train data
	features.push_back(y);
	features.push_back(n);
	
	vector<bool> cls;
	
	// Gather class data
	for (int i = 0; i < 19; i++)
		cls.push_back(true);
	for (int i = 0; i < 31; i++)
		cls.push_back(false);
	
	// Create classifier
	Llama::NaiveBayesClassifier BC = Llama::NaiveBayesClassifier(features, cls);
	
	cout << "An email contains Viagra and Funds, ths probability for it to be a spam email is: " << BC.getProbability({1,1}, true)*100<<"%" << endl;
	cout << "An email does not contain Viagra and Funds, ths probability for it to be a spam email is: " << BC.getProbability({0,0}, true)*100<<"%" << endl;
}