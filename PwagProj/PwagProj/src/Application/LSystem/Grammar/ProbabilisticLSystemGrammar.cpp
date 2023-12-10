#include "ProbabilisticLSystemGrammar.h"
#include <random>


ProbabilisticLSystemGrammar::ProbabilisticLSystemGrammar() {
    this->addRule('(', ""); // lerp growth only on new generation
    this->addRule(')', ""); // lerp growth only on new generation
}

ProbabilisticLSystemGrammar::ProbabilisticLSystemGrammar(const ProbabilisticLSystemGrammar& other) {
    this->currentString = other.currentString;
    this->rules = other.rules;
}

// Overloaded addRule with probability`
void ProbabilisticLSystemGrammar::addRule(char predecessor, const std::string& successor, double probability) {
    rules[predecessor].push_back({ successor, probability });
}

// Default addRule without probability
void ProbabilisticLSystemGrammar::addRule(char predecessor, const std::string& successor) {
    addRule(predecessor, successor, 1.0); // Assign a default probability of 1.0
}

std::shared_ptr<ILSystemGrammar> ProbabilisticLSystemGrammar::clone() const {
    return std::make_shared<ProbabilisticLSystemGrammar>(*this);
}

std::string ProbabilisticLSystemGrammar::getCurrentString() const {
    return currentString;
}

void ProbabilisticLSystemGrammar::setCurrentString(const std::string& str) {
    currentString = str;
}

inline void ProbabilisticLSystemGrammar::generate(int iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < iterations; ++i) {
        std::string nextString;
        for (char c : currentString) {
            auto it = rules.find(c);
            if (it != rules.end() && !it->second.empty()) {
                double totalProb = 0.0;
                // Calculate total probability
                for (const auto& pair : it->second) {
                    totalProb += pair.second;
                }

                std::uniform_real_distribution<> dis(0, 1.0); // Generate a number between 0 and 1
                double prob = dis(gen);

                if (prob <= totalProb) { // Check if the random number falls within the total probability
                    double cumulativeProb = 0.0;
                    for (const auto& pair : it->second) {
                        cumulativeProb += pair.second;
                        if (prob <= cumulativeProb) {
                            nextString += pair.first;
                            break;
                        }
                    }
                }
                else {
                    // In this case, no rule is selected, and the character remains unchanged.
                    nextString += c;
                }
            }
            else {
                // If there are no rules for the character, keep it unchanged.
                nextString += c;
            }
        }
        currentString = nextString + "@"; // @ end of single generation
    }
}
