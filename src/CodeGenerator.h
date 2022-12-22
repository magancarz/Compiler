#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>
#include "Memory.h"

#define CODE_GENERATOR_DEBUG 0
#define CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 0

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();

	void writeCode(const std::string& code);
	void writeCode(const std::string& code, unsigned int value);

	// accumulator related functions
	unsigned int addValueToAccumulator(Memory* memory, Variable* variable);
	unsigned int subValueFromAccumulator(Memory* memory, Variable* variable);

	unsigned int loadValueToAccumulator(Memory* memory, Variable* variable);

	unsigned int setValueToAccumulator(Memory* memory, Variable* variable);
	unsigned int setValueToAccumulator(Memory* memory, unsigned int value);

	unsigned int storeValueFromAccumulator(Memory* memory, Variable* variable);

	unsigned int assignValueToVariable(Memory* memory, const std::string& name, const std::string& value);
	unsigned int assignValueToVariable(Memory* memory, const std::string& name, unsigned int value);
	unsigned int assignValueToVariable(Memory* memory, const std::string& name, Variable* variable);

	unsigned int readValue(Memory* memory, const std::string& variableName);
	unsigned int printOutValue(Memory* memory, Variable* variable);

	unsigned int add(Memory* memory, Variable* a, Variable* b);
	unsigned int sub(Memory* memory, Variable* a, Variable* b);
	unsigned int mul(Memory* memory, Variable* a, Variable* b);
	unsigned int div(Memory* memory, Variable* a, Variable* b);
	unsigned int mod(Memory* memory, Variable* a, Variable* b);
	
	unsigned int equal(Memory* memory, Variable* a, Variable* b);
	unsigned int nequal(Memory* memory, Variable* a, Variable* b);
	unsigned int greater(Memory* memory, Variable* a, Variable* b);
	unsigned int less(Memory* memory, Variable* a, Variable* b);
	unsigned int greq(Memory* memory, Variable* a, Variable* b);
	unsigned int leq(Memory* memory, Variable* a, Variable* b);
	
	std::string getCode();

	inline FILE* getInput() { return m_input; }

private:
	FILE* m_input;
	std::ofstream m_output;

	std::vector<std::string> m_code;

	unsigned int m_commandPointer = 0;
};