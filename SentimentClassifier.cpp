#include "SentimentClassifier.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

void SentimentClassifier::train(const char* trainingDataFile) {
    std::ifstream file(trainingDataFile);
    if (!file.is_open()) {
        std::cerr << "Could not open training data file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string sentiment, id, date, query, user, tweet;

        // Read fields from CSV line
        std::getline(ss, sentiment, ',');
        std::getline(ss, id, ',');
        std::getline(ss, date, ',');
        std::getline(ss, query, ',');
        std::getline(ss, user, ',');
        std::getline(ss, tweet);

        // Validate and convert sentiment
        int sentimentValue;
        try {
            sentimentValue = std::stoi(sentiment);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid sentiment value in line: " << line << "\n";
            continue;  // Skip this line if sentiment is invalid
        }

        // Tokenize tweet and update positive/negative word counts
        std::stringstream tweetStream(tweet);
        std::string word;
        while (tweetStream >> word) {
            DSString dsWord(word.c_str());  // Convert to DSString
            if (sentimentValue == 4) {
                positiveWords[dsWord]++;
            } else if (sentimentValue == 0) {
                negativeWords[dsWord]++;
            }
        }
    }
    file.close();
}

int SentimentClassifier::predict(const DSString& tweet) {
    int score = 0;
    std::stringstream tweetStream(tweet.c_str());
    std::string word;

    while (tweetStream >> word) {
        DSString dsWord(word.c_str());  // Convert to DSString
        if (positiveWords.find(dsWord) != positiveWords.end()) {
            score++;
        }
        if (negativeWords.find(dsWord) != negativeWords.end()) {
            score--;
        }
    }
    return score > 0 ? 4 : 0; // Return 4 for positive, 0 for negative
}

double SentimentClassifier::evaluate(const char* testFile, const char* truthFile, const char* resultFile, const char* accuracyFile) {
    std::ifstream testFileStream(testFile);
    std::ifstream truthFileStream(truthFile);
    std::ofstream resultFileStream(resultFile);
    std::ofstream accuracyFileStream(accuracyFile);

    if (!testFileStream.is_open() || !truthFileStream.is_open() || !resultFileStream.is_open() || !accuracyFileStream.is_open()) {
        std::cerr << "Could not open one of the files.\n";
        return 0.0;
    }

    int correct = 0, total = 0;
    std::string testLine, truthLine;

    while (std::getline(testFileStream, testLine) && std::getline(truthFileStream, truthLine)) {
        std::stringstream testSS(testLine);
        std::stringstream truthSS(truthLine);
        
        std::string id, date, query, user, tweet;
        std::getline(testSS, id, ',');
        std::getline(testSS, date, ',');
        std::getline(testSS, query, ',');
        std::getline(testSS, user, ',');
        std::getline(testSS, tweet);

        std::string sentiment, truthID;
        std::getline(truthSS, sentiment, ',');
        std::getline(truthSS, truthID);

        int actualSentiment;
        try {
            actualSentiment = std::stoi(sentiment);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid sentiment value in truth file: " << truthLine << "\n";
            continue;  // Skip this line if sentiment is invalid
        }

        DSString dsTweet(tweet.c_str());  // Convert to DSString
        int predictedSentiment = predict(dsTweet);

        resultFileStream << predictedSentiment << ", " << id << "\n";
        
        if (predictedSentiment == actualSentiment) {
            correct++;
        } else {
            // Log incorrect predictions in accuracy file
            accuracyFileStream << predictedSentiment << ", " << actualSentiment << ", " << id << "\n";
        }
        total++;
    }

    double accuracy = static_cast<double>(correct) / total;
    
    // Write the accuracy with three decimal places at the beginning of the file
    accuracyFileStream.seekp(0, std::ios::beg);  // Go to the beginning of the file
    accuracyFileStream << std::fixed << std::setprecision(3) << accuracy << "\n";

    testFileStream.close();
    truthFileStream.close();
    resultFileStream.close();
    accuracyFileStream.close();

    return accuracy;
}
