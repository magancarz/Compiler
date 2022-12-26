#include <iostream>
#include "Memory.h"

Memory::Memory() {
	initializeHelpingVariables();
}

Memory::~Memory() {
	
}

void Memory::initializeHelpingVariables() {
	// accumulator
	addVariableToMemory(0);

	// variables for supporting calculations
	addVariableToMemory(0);
	addVariableToMemory(0);
	addVariableToMemory(0);
	addVariableToMemory(0);
	addVariableToMemory(0);
	addVariableToMemory(0);

	// "one" value holder
	addVariableToMemory(1);
}

void Memory::addVariableToMemory(unsigned int value) {
	Variable* newVariable = new Variable(value, m_freeMemoryPointer);
	m_variables.push_back(newVariable);
	m_freeMemoryPointer++;
}

void Memory::addVariableToMemory(const std::string& name, unsigned int value) {
	if(!name.empty() && checkIfVariableExists(name)) {
		printf("Variable %s already exists.\n", name.c_str());
		exit(1);
	}

	Variable* newVariable = new Variable(name, value, m_freeMemoryPointer);
	m_variables.push_back(newVariable);
	m_freeMemoryPointer++;
}

Variable* Memory::addProcedureVariableToMemory(const std::string& name, bool isInProcedure) {
	if(name.empty()) {
		printf("Procedure variable name is empty.\n", name.c_str());
		exit(1);
	}

	Variable* newVariable = new Variable(true, name, m_freeMemoryPointer);
	m_variables.push_back(newVariable);
	m_freeMemoryPointer++;

	return newVariable;
}

Variable* Memory::addPointerToMemory(const std::string& name, bool isInProcedure, Variable* pointing) {
	if(name.empty()) {
		printf("Procedure variable name is empty.\n", name.c_str());
		exit(1);
	}

	Variable* newVariable = new Variable(0, m_freeMemoryPointer);
	m_variables.push_back(newVariable);
	m_freeMemoryPointer++;

	Variable* newVariablePointer = new Variable(true, name, m_freeMemoryPointer, newVariable);
	m_variables.push_back(newVariablePointer);
	m_freeMemoryPointer++;

	return newVariablePointer;
}

void Memory::addNewProcedure() {
	// add new procedure to memory and add variable that functions
	// as a storage for holding position to go back from procedure
	m_currentProcedure = new Procedure();
	m_currentProcedure->getProcedureVariables().push_back(new Variable(true, "", m_freeMemoryPointer));
	m_freeMemoryPointer++;
}

void Memory::addVariableToProcedure(const std::string& name) {
	if(m_currentProcedure == nullptr) {
		addNewProcedure();
	}
	
	// if the name is empty -> add variable as pointer
	if(m_currentProcedure->getName().empty()) {
		m_currentProcedure->getProcedureVariables().push_back(addPointerToMemory(name, true, nullptr));
		return;
	}

	// if the name isn't empty, then add it as a normal variable
	m_currentProcedure->getProcedureVariables().push_back(addProcedureVariableToMemory(name, true));
}

void Memory::setIdentifierToCurrentProcedure(const std::string& name) {
	if(m_currentProcedure == nullptr) {
		addNewProcedure();
	}

	m_currentProcedure->setProcedureName(name);
}

Procedure* Memory::finishProcedure(unsigned int commandsSize) {
	m_currentProcedure->setCodeSize(commandsSize);
	m_procedures.push_back(m_currentProcedure);
	return m_currentProcedure;
}

void Memory::clearCurrentProcedure() {
	m_currentProcedure = nullptr;
}

void Memory::changeVariableValue(unsigned int memoryPosition, unsigned int value) {
	Variable* variable = m_variables[memoryPosition];
	variable->setValue(value);
}

void Memory::changeVariableValue(const std::string& name, unsigned int value) {
	if(!name.empty() && checkIfVariableExists(name)) {
		Variable* variable = getVariable(name);
		variable->setValue(value);	
	} else {
		printf("Variable %s doesn't exist.\n", name.c_str());
		exit(1);
	}
}

Variable* Memory::getVariableFromMemory(unsigned int memoryPosition) {
	if(memoryPosition > m_variables.size()) {
		printf("Memory pointer out of range\n");
		exit(1);
	}
	
	return findVariable(memoryPosition);
}

Variable* Memory::getVariableFromMemory(const std::string& name) {
	if(!name.empty() && checkIfVariableExists(name)) {
		return findVariable(name);	
	} else {
		printf("Variable %s doesn't exist.\n", name.c_str());
		exit(1);
	}
}

Variable* Memory::getValueHolder(unsigned int value) {
	return new Variable("", value, 0);
}

bool Memory::checkIfVariableExists(const std::string& name) {
	Variable* variable = findVariable(name);
	return (variable != nullptr)? true : false;
}

Variable* Memory::findVariable(unsigned int memoryPosition) {
	Variable* variable = m_variables[memoryPosition];
	return variable;
}

Variable* Memory::findVariable(const std::string& name) {
	Variable* variable = getVariable(name);
	return variable;
}

Variable* Memory::getVariable(const std::string& name) {
	for(Variable* variable : m_variables) {
		std::string variableName = variable->getName();

		// if we are adding new procedure, then avoid checking regular
		// variable names, similarly avoid procedure variables when we are looking for a regular variable
		if(m_currentProcedure != nullptr) {
			if(variableName == name && variable->isInProcedure()) {
				return variable;
			}
		} else {
			if(variableName == name && !variable->isInProcedure()) {
				return variable;
			}
		}
	}

	return nullptr;
}

void Memory::clearProcedureExecutionVariables() {
	// we don't need to delete pointers inside of vector,
	// because we are still using them
	m_procedureExecutionVariables.clear();
}

void Memory::prepareProcedureExecutionVariable(Memory* memory, const std::string& name) {
	m_procedureExecutionVariables.push_back(memory->getVariableFromMemory(name));
}