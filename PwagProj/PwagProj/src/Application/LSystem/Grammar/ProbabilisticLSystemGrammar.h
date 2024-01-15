#pragma once

#include "LSystemGrammar.h"

class ProbabilisticLSystemGrammar :
    public SimpleLSystemGrammar
{
public:
    ProbabilisticLSystemGrammar();
    ProbabilisticLSystemGrammar(const ProbabilisticLSystemGrammar& other);
    // Modified addRule to include probability
    void addRule(char predecessor, const std::string& successor, double probability);

    void addRule(char predecessor, const std::string& successor) override;

    std::shared_ptr<ILSystemGrammar> clone() const override;

    void generate(int iterations) override;

private:
    std::map<char, std::vector<std::pair<std::string, double>>> rules;
};


