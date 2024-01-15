#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include <string>
#include <cctype>
#include <algorithm>
#include <type_traits>
#include <locale>

template <typename T>
T to_upper(const T& input) {
    if constexpr (std::is_same<T, char>::value) {
        // For a single character
        return std::toupper(input);
    } else if constexpr (std::is_same<T, std::string>::value) {
        // For a string
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), 
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    } else {
        // If the input type is neither char nor std::string, return the input as-is
        return input;
    }
}

struct Symbol {
	char symbol;
    int age;

    Symbol(char symbolValue, int ageValue) {
        symbol = symbolValue;
        age = ageValue;
    }

    Symbol(const char* symbolValue, int ageValue) {
        symbol = symbolValue[0];
        age = ageValue;
    }
};

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
    
	virtual std::vector<Symbol> getCurrentSymbols() const = 0;

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
    std::vector<Symbol> getCurrentSymbols() const override;
    void setCurrentString(const std::string& str) override;

protected:
    std::string currentString;
    std::vector<Symbol> currentSymbols;
    std::map<char, std::vector<std::string>> rules;
};
