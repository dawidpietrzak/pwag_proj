// SimpleLSystemGrammar.cpp
#include "LSystemGrammar.h"

SimpleLSystemGrammar::SimpleLSystemGrammar()
{

}

SimpleLSystemGrammar::SimpleLSystemGrammar(const SimpleLSystemGrammar& other)
{
    this->currentString = other.currentString;
    this->rules = other.rules;
}

void SimpleLSystemGrammar::addRule(char predecessor, const std::string& successor)
{
    rules[predecessor].push_back(successor);
}

void SimpleLSystemGrammar::generate(int iterations)
{
    for (int i = 0; i < iterations; ++i) {
        std::string nextString;
        for (char c : currentString) {
            auto it = rules.find(c);
            if (it != rules.end()) {
                for (const auto& successor : it->second) {
                    nextString += successor;
                }
            }
            else {
                nextString += c;
            }
        }
        currentString = nextString;
    }
}

std::string SimpleLSystemGrammar::getCurrentString() const
{
    return currentString;
}