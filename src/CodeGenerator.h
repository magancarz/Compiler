#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>
#include "Memory.h"

#define CODE_GENERATOR_DEBUG 0
#define CODE_GEN_ADD 1
#define CODE_GEN_SUB 2
#define CODE_GEN_MUL 3
#define CODE_GEN_DIV 4
#define CODE_GEN_MOD 5

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();

	void writeCode(const std::string& code);
	void writeCode(const std::string& code, unsigned int value);

	//TODO: refactor
	void addValueToAccumulator(Memory* memory, Variable* variable);
	void subValueFromAccumulator(Memory* memory, Variable* variable);
	void mulValueFromAccumulator(Memory* memory, Variable* variable);
	void divValueFromAccumulator(Memory* memory, Variable* variable);
	void modValueFromAccumulator(Memory* memory, Variable* variable);

	std::string* loadValueToAccumulator(Memory* memory, Variable* variable);

	std::string* setValueToAccumulator(Memory* memory, Variable* variable);
	std::string* setValueToAccumulator(Memory* memory, unsigned int value);

	void assignValueToVariable(Memory* memory, const std::string& name, const std::string& value);

	void assignValueToVariable(Memory* memory, const std::string& name, unsigned int value);

	void assignValueToVariable(Memory* memory, const std::string& name, Variable* variable);

	void readValue(Memory* memory, const std::string& variableName);
	void printOutValue(Memory* memory, Variable* variable);

	std::string* add(Memory* memory, Variable* a, Variable* b);

	std::string* sub(Memory* memory, Variable* a, Variable* b);

	std::string* mul(Memory* memory, Variable* a, Variable* b);

	std::string* div(Memory* memory, Variable* a, Variable* b);

	std::string* mod(Memory* memory, Variable* a, Variable* b);

	std::string getCode();

	inline FILE* getInput() { return m_input; }

private:
	FILE* m_input;
	std::ofstream m_output;

	std::vector<std::string> m_code;
};