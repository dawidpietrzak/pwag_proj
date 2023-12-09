#pragma once

#include "LSystemGrammar.h"

class TextLSystemGrammar: public ILSystemGrammar
{
public:
	// Odziedziczono za poœrednictwem elementu ILSystemGrammar
	virtual std::shared_ptr<ILSystemGrammar> clone() const override;
	void parseText(const std::string& str);
	virtual void addRule(char predecessor, const std::string& successor) override;
	virtual void generate(int iterations) override;
	virtual std::string getCurrentString() const override;
	virtual void setCurrentString(const std::string& str) override;

private:
	SimpleLSystemGrammar m_lSystem;
};

