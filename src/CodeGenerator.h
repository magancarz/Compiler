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
	
	void setMemoryPointer(Memory* memory);

	// functions to make differences in output code
	void writeCode(const std::string& code);
	void writeCode(const std::string& code, unsigned int value);
	void changeCode(unsigned int codePosition, const std::string& code);
	void changeCode(unsigned int codePosition, const std::string& code, unsigned int value);
	void fixJumpCodeValues(unsigned int insertedCodePosition);
	void insertCode(unsigned int codePosition, const std::string& code);
	void insertCode(unsigned int codePosition, const std::string& code, unsigned int value);

	// code generating functions
	unsigned int addValueToAccumulator(Variable* variable);
	unsigned int subValueFromAccumulator(Variable* variable);

	unsigned int loadValueToAccumulator(Variable* variable);

	unsigned int setValueToAccumulator(Variable* variable);
	unsigned int setValueToAccumulator(unsigned int value);

	unsigned int storeValueFromAccumulator(Variable* variable);
	unsigned int storeValueFromAccumulatorToPointedVariable(Variable* pointer);

	unsigned int assignValueToVariable(const std::string& name, const std::string& value);
	unsigned int assignValueToVariable(const std::string& name, unsigned int value);
	unsigned int assignValueToVariable(const std::string& name, Variable* variable);

	unsigned int readValue(const std::string& variableName);
	unsigned int printOutValue(Variable* variable);
	
	unsigned int divideAccumulatorByHalf();

	unsigned int generateProcedureEndCode(Procedure* procedure);
	unsigned int executeProcedure(const std::string& procedureName, const std::vector<Variable*>& procedureExecutionVariables);

	unsigned int ifCondition(Condition* condition, unsigned int commandsLength);
	unsigned int ifElseCondition(Condition* condition, unsigned int commands1Length, unsigned int commands2Length);
	unsigned int whileLoop(Condition* condition, unsigned int commandsLength);
	unsigned int repeatUntilLoop(Condition* condition, unsigned int commandsLength);


	unsigned int add(Variable* a, Variable* b);
	unsigned int sub(Variable* a, Variable* b);
	unsigned int mul(Variable* a, Variable* b);
	unsigned int div(Variable* a, Variable* b);
	unsigned int mod(Variable* a, Variable* b);
	
	Condition* equal(Variable* a, Variable* b);
	Condition* nequal(Variable* a, Variable* b);
	Condition* greater(Variable* a, Variable* b);
	Condition* less(Variable* a, Variable* b);
	Condition* greq(Variable* a, Variable* b);
	Condition* leq(Variable* a, Variable* b);
	
	std::string getCode();

	inline FILE* getInput() { return m_input; }

private:
	FILE* m_input;
	std::ofstream m_output;

	Memory* m_memory;

	std::vector<std::string> m_code;

	unsigned int m_commandPointer = 0;
};