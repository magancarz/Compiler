#pragma once

#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include "Memory.h"

#define CODE_GENERATOR_DEBUG 0
#define CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 0

struct Condition {
	unsigned int conditionCodeSize;
	unsigned int jumpIfTruePosition;
	unsigned int jumpIfFalsePosition;
};

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();

	// functions to make differences in output code
	void writeCode(const std::string& code);
	void writeCode(const std::string& code, unsigned int value);
	void changeCode(unsigned int codePosition, const std::string& code);
	void changeCode(unsigned int codePosition, const std::string& code, unsigned int value);
	void insertCode(unsigned int codePosition, const std::string& code);
	void insertCode(unsigned int codePosition, const std::string& code, unsigned int value);

	// code generating functions

	unsigned int addValueToAccumulator(Memory* memory, Variable* variable);
	unsigned int subValueFromAccumulator(Memory* memory, Variable* variable);

	unsigned int loadValueToAccumulator(Memory* memory, Variable* variable);

	unsigned int setValueToAccumulator(Memory* memory, Variable* variable);
	unsigned int setValueToAccumulator(Memory* memory, unsigned int value);

	unsigned int storeValueFromAccumulator(Memory* memory, Variable* variable);
	unsigned int storeValueFromAccumulatorToPointedVariable(Memory* memory, Variable* pointer);

	unsigned int assignValueToVariable(Memory* memory, const std::string& name, const std::string& value);
	unsigned int assignValueToVariable(Memory* memory, const std::string& name, unsigned int value);
	unsigned int assignValueToVariable(Memory* memory, const std::string& name, Variable* variable);

	unsigned int generateProcedureEndCode(Memory* memory, Procedure* procedure);
	unsigned int executeProcedure(Memory* memory, const std::string& procedureName, const std::vector<Variable*>& procedureExecutionVariables);

	unsigned int ifCondition(Memory* memory, Condition* condition, unsigned int commandsLength);
	unsigned int ifElseCondition(Memory* memory, Condition* condition, unsigned int commands1Length, unsigned int commands2Length);
	unsigned int whileLoop(Memory* memory, Condition* condition, unsigned int commandsLength);
	unsigned int repeatUntilLoop(Memory* memory, Condition* condition, unsigned int commandsLength);

	unsigned int readValue(Memory* memory, const std::string& variableName);
	unsigned int printOutValue(Memory* memory, Variable* variable);

	unsigned int add(Memory* memory, Variable* a, Variable* b);
	unsigned int sub(Memory* memory, Variable* a, Variable* b);
	unsigned int mul(Memory* memory, Variable* a, Variable* b);
	unsigned int div(Memory* memory, Variable* a, Variable* b);
	unsigned int mod(Memory* memory, Variable* a, Variable* b);
	
	Condition* equal(Memory* memory, Variable* a, Variable* b);
	Condition* nequal(Memory* memory, Variable* a, Variable* b);
	Condition* greater(Memory* memory, Variable* a, Variable* b);
	Condition* less(Memory* memory, Variable* a, Variable* b);
	Condition* greq(Memory* memory, Variable* a, Variable* b);
	Condition* leq(Memory* memory, Variable* a, Variable* b);
	
	std::string getCode();

	inline FILE* getInput() { return m_input; }

private:
	FILE* m_input;
	std::ofstream m_output;

	std::vector<std::string> m_code;

	unsigned int m_commandPointer = 0;
};