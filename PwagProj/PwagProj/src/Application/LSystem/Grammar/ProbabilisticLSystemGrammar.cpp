#include "ProbabilisticLSystemGrammar.h"
#include <random>
#include <cctype> // for toupper

ProbabilisticLSystemGrammar::ProbabilisticLSystemGrammar() {
}

ProbabilisticLSystemGrammar::ProbabilisticLSystemGrammar(const ProbabilisticLSystemGrammar& other) {
    this->currentString = other.currentString;
    this->currentSymbols = other.currentSymbols;
    this->rules = other.rules;
}

// Overloaded addRule with probability`
void ProbabilisticLSystemGrammar::addRule(char predecessor, const std::string& successor, double probability) {
    rules[to_upper(predecessor)].push_back({ to_upper(successor), probability });
}

// Default addRule without probability
void ProbabilisticLSystemGrammar::addRule(char predecessor, const std::string& successor) {
    addRule(predecessor, successor, 1.0); // Assign a default probability of 1.0
}

std::shared_ptr<ILSystemGrammar> ProbabilisticLSystemGrammar::clone() const {
    return std::make_shared<ProbabilisticLSystemGrammar>(*this);
}
void ProbabilisticLSystemGrammar::generate(int iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < iterations; ++i) {
        std::string nextString;
        std::vector<Symbol> nextSymbols;

        for (const Symbol& prev : currentSymbols) {
            char c = prev.symbol;
            auto it = rules.find(c);

            if (it != rules.end() && !it->second.empty()) {
                double totalProb = 0.0;
                // Calculate total probability
                for (const auto& pair : it->second) {
                    totalProb += pair.second;
                }

                std::uniform_real_distribution<> dis(0, totalProb);
                double prob = dis(gen);

                // Create a vector with normalized probabilities
                std::vector<double> normalizedProbs;
                for (const auto& pair : it->second) {
                    normalizedProbs.push_back(pair.second / totalProb);
                }

                // Select a rule based on its relative probability
                double runningTotal = 0.0;
                size_t selectedRuleIndex = 0;
                for (size_t j = 0; j < normalizedProbs.size(); ++j) {
                    runningTotal += normalizedProbs[j];
                    if (prob <= runningTotal) {
                        selectedRuleIndex = j;
                        break;
                    }
                }

                // Apply the selected rule
                auto selectedRule = it->second.begin();
                std::advance(selectedRule, selectedRuleIndex);
                nextString += selectedRule->first;
                for (const char& ch : selectedRule->first) {
                    nextSymbols.push_back(Symbol(ch, prev.age - 1));
                }
            }
            else {
                // If there are no rules for the character, keep it unchanged.
                nextString += c;
                nextSymbols.push_back(Symbol(prev.symbol, prev.age));
            }
        }
        currentString = nextString;
        currentSymbols = nextSymbols;
    }
}
