#pragma once

#include <vector>
#include <string>
#include <map>

// Abstract base class for L-System Grammars
class ILSystemGrammar {
public:
    // Pure virtual function for adding a production rule
    virtual void addRule(char predecessor, const std::string& successor) = 0;

    // Pure virtual function for generating the L-System string for a number of iterations
    virtual void generate(int iterations) = 0;

    // Pure virtual function for getting the current L-System string
    virtual std::string getCurrentString() const = 0;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ILSystemGrammar() {}
};


class SimpleLSystemGrammar : public ILSystemGrammar {
private:
    std::string axiom;
    std::string currentString;
    std::map<char, std::vector<std::string>> rules;

public:
    SimpleLSystemGrammar(const std::string& axiom);
    void addRule(char predecessor, const std::string& successor) override;
    void generate(int iterations) override;
    std::string getCurrentString() const override;
};
