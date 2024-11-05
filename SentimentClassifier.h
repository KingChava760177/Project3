#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include <map>
#include "DSString.h"

class SentimentClassifier {
private:
    std::map<DSString, int> positiveWords;
    std::map<DSString, int> negativeWords;

public:
    void train(const char* trainingDataFile);
    int predict(const DSString& tweet);
    double evaluate(const char* testFile, const char* truthFile, const char* resultFile, const char* accuracyFile);
};

#endif // SENTIMENTCLASSIFIER_H
