#include "SentimentClassifier.h"
#include <iostream>

int main() {
    // File names based on the CSV files
    const char* trainingFile = "train_dataset_20k.csv";
    const char* testingFile = "test_dataset_10k.csv";
    const char* truthFile = "test_dataset_sentiment_10k.csv";
    const char* resultFile = "results.csv";
    const char* accuracyFile = "accuracy.txt";

    SentimentClassifier classifier;

    // Train the classifier
    classifier.train(trainingFile);

    // Evaluate the classifier with test data and write results
    double accuracy = classifier.evaluate(testingFile, truthFile, resultFile, accuracyFile);

    std::cout << "Classifier Accuracy: " << accuracy * 100 << "%\n";

    return 0;
}
