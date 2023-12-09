#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

// Abstract base class for L-System Grammars
class ILSystemGrammar {
public:

    virtual std::shared_ptr<ILSystemGrammar> clone() const = 0;

    // Pure virtual function for adding a production rule
    virtual void addRule(char predecessor, const std::string& successor) = 0;

    // Pure virtual function for generating the L-System string for a number of iterations
    virtual void generate(int iterations) = 0;

    // Pure virtual function for getting the current L-System string
    virtual std::string getCurrentString() const = 0;

    virtual void setCurrentString(const std::string& str) = 0;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ILSystemGrammar() {}
};


class SimpleLSystemGrammar : public ILSystemGrammar
{
public:
    SimpleLSystemGrammar();
    std::shared_ptr<ILSystemGrammar> clone() const override {
        return std::make_shared<SimpleLSystemGrammar>(*this);
    }
    SimpleLSystemGrammar(const SimpleLSystemGrammar& other); // Copy constructor

    void addRule(char predecessor, const std::string& successor) override;
    void generate(int iterations) override;

    std::string getCurrentString() const override;
    void setCurrentString(const std::string& str) override { currentString = str; }

private:
    std::string currentString;
    std::map<char, std::vector<std::string>> rules;
};
