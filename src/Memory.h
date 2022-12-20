#pragma once

#include <vector>
#include <string>
#include "Variable.h"

#define MEMORY_DEBUG 1

class Memory {
public:
	Memory();
	~Memory();

	void addVariableToMemory(const std::string& name, unsigned int value);
	
	void changeVariableValue(unsigned int memoryPosition, unsigned int value);
	void changeVariableValue(const std::string& name, unsigned int value);

	Variable* getVariableFromMemory(unsigned int memoryPosition);
	Variable* getVariableFromMemory(const std::string& name);

	bool checkIfVariableExists(const std::string& name);

	Variable* findVariable(unsigned int memoryPosition);
	Variable* findVariable(const std::string& name);
	Variable* getVariable(const std::string& name);

	inline std::vector<Variable>* getMemoryVariables() { return m_variables; }

private:
	unsigned int m_freeMemoryPointer = 1;

	std::vector<Variable>* m_variables = new std::vector<Variable>();

};