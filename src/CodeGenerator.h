#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();

	void writeCode(const std::string& code);

	std::string getCode();

	inline FILE* getInput() { return m_input; }

private:
	FILE* m_input;
	std::ofstream m_output;

	std::vector<std::string> m_code;
};