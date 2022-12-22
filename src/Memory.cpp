#include <iostream>
#include "Memory.h"

Memory::Memory() {
	Variable* accumulator = new Variable(0, 0);
	m_variables->push_back(accumulator);

	// variables for supporting calculations
	Variable* temp1 = new Variable("", 0, 1);
	m_variables->push_back(temp1);
	m_freeMemoryPointer++;
	Variable* temp2 = new Variable("", 0, 2);
	m_variables->push_back(temp2);
	m_freeMemoryPointer++;
	Variable* temp3 = new Variable("", 0, 3);
	m_variables->push_back(temp3);
	m_freeMemoryPointer++;
	Variable* temp4 = new Variable("", 0, 4);
	m_variables->push_back(temp4);
	m_freeMemoryPointer++;
	Variable* temp5 = new Variable("", 0, 5);
	m_variables->push_back(temp5);
	m_freeMemoryPointer++;
	Variable* temp6 = new Variable("", 0, 6);
	m_variables->push_back(temp6);
	m_freeMemoryPointer++;
	Variable* temp7 = new Variable("", 0, 7);
	m_variables->push_back(temp7);
	m_freeMemoryPointer++;
	Variable* temp8 = new Variable("", 0, 8);
	m_variables->push_back(temp8);
	m_freeMemoryPointer++;
	Variable* temp9 = new Variable("", 0, 9);
	m_variables->push_back(temp9);
	m_freeMemoryPointer++;

	// variable with value 1
	Variable* temp10 = new Variable("", 1, 10);
	m_variables->push_back(temp10);
	m_freeMemoryPointer++;
}

Memory::~Memory() {
	delete m_variables;
}

void Memory::addVariableToMemory(const std::string& name, unsigned int value) {
	if(!name.empty() && checkIfVariableExists(name)) {
		printf("Variable %s already exists.\n", name.c_str());
		exit(1);
	}

	#if MEMORY_DEBUG 1
	printf("Added variable %s to the memory at position %d.\n", name.c_str(), m_freeMemoryPointer);
	#endif // MEMORY_DEBUG

	Variable* newVariable = new Variable(name, value, m_freeMemoryPointer);
	m_variables->push_back(newVariable);
	m_freeMemoryPointer++;
}

void Memory::changeVariableValue(unsigned int memoryPosition, unsigned int value) {
	Variable* variable = m_variables->at(memoryPosition);
	variable->setValue(value);
	
	#if MEMORY_DEBUG 1
	printf("Changed value at position %d to %d.\n", memoryPosition, variable->getValue());
	#endif // MEMORY_DEBUG
}

void Memory::changeVariableValue(const std::string& name, unsigned int value) {
	if(!name.empty() && checkIfVariableExists(name)) {
		#if MEMORY_DEBUG 1
		printf("Changed variable %s value to %d.\n", name.c_str(), value);
		#endif // MEMORY_DEBUG

		Variable* variable = getVariable(name);
		variable->setValue(value);	
	} else {
		printf("Variable %s doesn't exist.\n", name.c_str());
		exit(1);
	}
}

Variable* Memory::getVariableFromMemory(unsigned int memoryPosition) {
	if(memoryPosition > m_variables->size()) {
		printf("Memory pointer out of range\n");
		exit(1);
	}
	
	return findVariable(memoryPosition);
}

Variable* Memory::getVariableFromMemory(const std::string& name) {
	if(!name.empty() && !checkIfVariableExists(name)) {
		printf("Variable %s doesn't exist.\n", name.c_str());
		exit(1);
	}

	return findVariable(name);
}

Variable* Memory::getValueHolder(unsigned int value) {
	return new Variable("", value, 0);
}

bool Memory::checkIfVariableExists(const std::string& name) {
	Variable* variable = findVariable(name);
	return (variable != nullptr)? true : false;
}

Variable* Memory::findVariable(unsigned int memoryPosition) {
	Variable* variable = m_variables->at(memoryPosition);
	return variable;
}

Variable* Memory::findVariable(const std::string& name) {
	Variable* variable = getVariable(name);
	return variable;
}

Variable* Memory::getVariable(const std::string& name) {
	for(std::vector<Variable*>::iterator it = m_variables->begin(); it != m_variables->end(); it++) {
		Variable* variable = *it;
		std::string variableName = variable->getName();
		if(variableName == name) {
			return variable;
		}
	}

	return nullptr;
}