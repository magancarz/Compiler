#pragma once

#include <vector>
#include <string>
#include "Variable.h"
#include "Procedure.h"

class Memory {
public:
	Memory();
	~Memory();

	void initializeHelpingVariables();

	void addVariableToMemory(unsigned int value);
	void addVariableToMemory(const std::string& name, unsigned int value);
	Variable* addProcedurePointerToMemory(const std::string& name, bool isInProcedure, Variable* pointing);
	Variable* addProcedureVariableToMemory(const std::string& name, bool isInProcedure);
	
	Variable* getVariableFromMemory(unsigned int memoryPosition);
	Variable* getVariableFromMemory(const std::string& name);

	void changeVariableValue(unsigned int memoryPosition, unsigned int value);
	void changeVariableValue(const std::string& name, unsigned int value);

	bool checkIfVariableExists(const std::string& name);

	Variable* findVariable(unsigned int memoryPosition);
	Variable* findVariable(const std::string& name);
	Variable* getValueHolder(unsigned int value);
	Variable* getVariable(const std::string& name);
	
	void addNewProcedure();
	inline Procedure* getCurrentProcedure() { return m_currentProcedure; }
	void addVariableToProcedure(const std::string& name);
	void setIdentifierToCurrentProcedure(const std::string& name);
	Procedure* finishProcedure(unsigned int commandsSize);
	void clearCurrentProcedure();
	bool checkIfProcedureExists(const std::string& name);

	void prepareProcedureExecutionVariable(const std::string& name);
	std::vector<Variable*>& getProcedureExecutionVariables();
	void clearProcedureExecutionVariables();

	inline std::vector<Variable*>& getMemoryVariables() { return m_variables; }

	inline std::vector<Procedure*>& getProcedures() { return m_procedures; }

private:
	unsigned int m_freeMemoryPointer = 0;

	std::vector<Variable*> m_variables;
	
	Procedure* m_currentProcedure = nullptr;
	std::vector<Procedure*> m_procedures;

	std::string m_executedProcedureIdentifier;
	std::vector<std::string> m_procedureExecutionVariablesNames;
	std::vector<Variable*> m_procedureExecutionVariables;
};