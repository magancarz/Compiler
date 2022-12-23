#pragma once

#include <vector>
#include <string>
#include "Variable.h"
#include "Procedure.h"

#define MEMORY_DEBUG 0

class Memory {
public:
	Memory();
	~Memory();

	void addVariableToMemory(const std::string& name, unsigned int value);
	Variable* addProcedureVariableToMemory(const std::string& name, bool isInProcedure);
	Variable* addProcedurePointerToMemory(const std::string& name, bool isInProcedure, Variable* pointing);
	
	void addNewProcedure();
	void addVariableToProcedure(const std::string& name);
	void setIdentifierToCurrentProcedure(const std::string& name);
	Procedure* finishProcedure(unsigned int commandsSize);
	void clearCurrentProcedure();

	void loadVariableToProcedureHead(const std::string& name);

	void changeVariableValue(unsigned int memoryPosition, unsigned int value);
	void changeVariableValue(const std::string& name, unsigned int value);

	Variable* getVariableFromMemory(unsigned int memoryPosition);
	Variable* getVariableFromMemory(const std::string& name);
	Variable* getValueHolder(unsigned int value);

	bool checkIfVariableExists(const std::string& name);

	Variable* findVariable(unsigned int memoryPosition);
	Variable* findVariable(const std::string& name);
	Variable* getVariable(const std::string& name);

	inline std::vector<Variable*>* getMemoryVariables() { return m_variables; }

	inline std::vector<Procedure*>* getProcedures() { return m_procedures; }

private:
	unsigned int m_freeMemoryPointer = 1;

	std::vector<Variable*>* m_variables = new std::vector<Variable*>();
	
	Procedure* m_currentProcedure = nullptr;
	std::vector<Procedure*>* m_procedures = new std::vector<Procedure*>();
};