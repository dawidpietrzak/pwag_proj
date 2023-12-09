#include "TextLSystemGrammar.h"
#include <iostream>

std::shared_ptr<ILSystemGrammar> TextLSystemGrammar::clone() const {
    return std::make_shared<TextLSystemGrammar>(*this);
}

void TextLSystemGrammar::parseText(const std::string& str) {
    std::string predecessor;
    std::string successor;
    bool isFirstLetter = true;

    for (char c : str) {
        if (isalpha(c)) {
            if (isFirstLetter) {
                if (!predecessor.empty()) {
                    // Add the previous rule
                    std::cout << predecessor[0] << " -> " << successor << std::endl;
                    addRule(predecessor[0], successor);
                    successor.clear();
                }
                predecessor = std::toupper(c); // First letter of a word is the predecessor
                isFirstLetter = false;
            }
            else {
                // Convert lowercase letters to L-system grammar characters
                static const char* lSystemChars = "+-&^[]<>|";
                successor += isupper(c) ? c : lSystemChars[(tolower(c) - 'a') % strlen(lSystemChars)];
            }
        }
        else {
            // Non-alphabetic characters indicate the end of a word
            if (!predecessor.empty()) {
                addRule(predecessor[0], successor);
                std::cout << predecessor[0] << " -> " << successor << std::endl;
            }
            predecessor.clear();
            successor.clear();
            isFirstLetter = true;
        }
    }

    // Add the last rule if there is one
    if (!predecessor.empty()) {
        addRule(predecessor[0], successor);
        std::cout << predecessor[0] << " -> " << successor << std::endl;
    }
}

void TextLSystemGrammar::addRule(char predecessor, const std::string& successor) {
    m_lSystem.addRule(predecessor, successor);
}

void TextLSystemGrammar::generate(int iterations) {
    m_lSystem.generate(iterations);
}

std::string TextLSystemGrammar::getCurrentString() const {
    return m_lSystem.getCurrentString();
}

void TextLSystemGrammar::setCurrentString(const std::string& str) {
    m_lSystem.setCurrentString(str);
}