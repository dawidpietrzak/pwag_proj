// SimpleLSystemGrammar.cpp
#include "LSystemGrammar.h"
#include <iostream>

SimpleLSystemGrammar::SimpleLSystemGrammar()
{
}

SimpleLSystemGrammar::SimpleLSystemGrammar(const SimpleLSystemGrammar& other)
{
    this->currentString = other.currentString;
	this->currentSymbols = other.currentSymbols;
    this->rules = other.rules;
}

void SimpleLSystemGrammar::addRule(char predecessor, const std::string& successor)
{
     rules[to_upper(predecessor)].push_back(to_upper(successor));
}

void SimpleLSystemGrammar::generate(int iterations)
{
    for (int i = 0; i < iterations; ++i) {
        std::string nextString;
		std::vector<Symbol> nextSymbols;
        for (Symbol prev : currentSymbols) {

			char c = prev.symbol;
            auto it = rules.find(c);
            if (it != rules.end()) {
                for (const auto& successor : it->second) {
                    nextString += successor;
					for (const char& ch : successor) // copy successor into nextSymbols (with age decremented for each c)
					    nextSymbols.push_back(Symbol(ch, prev.age - 1));
                }
            }
            else {
                nextString += c;
				nextSymbols.push_back(Symbol(prev));
            }
        }
        currentString = nextString;
		currentSymbols = nextSymbols;
    }
}

std::string SimpleLSystemGrammar::getCurrentString() const
{
    return currentString;
}

std::vector<Symbol> SimpleLSystemGrammar::getCurrentSymbols() const
{
    return currentSymbols;
}

void SimpleLSystemGrammar::setCurrentString(const std::string& str)
{
	for (auto c : str) {
		currentSymbols.push_back(Symbol(to_upper(c), 0));
	}
	currentString = to_upper(str);
}
