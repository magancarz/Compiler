#pragma once

#include <vector>
#include <string>
#include "Variable.h"

class Procedure {
public:
	Procedure();
	~Procedure();

	inline std::string getName() const { return m_name; }
	void setProcedureName(const std::string& name) { m_name = name; }
	
	void setCodeSize(unsigned int size) { m_codeSize = size; }
	inline unsigned int getCodeSize() const { return m_codeSize; }

	void addVariable(Variable* variable) { m_variables.push_back(variable); }
	std::vector<Variable*>& getProcedureVariables() { return m_variables; }
	std::vector<Variable*>* getProcedurePointers();

	inline unsigned int getProcedureStartPoint() { return m_procedureStartPoint; }
	void setProcedureStartPoint(unsigned int startPoint) { m_procedureStartPoint = startPoint; }

	inline unsigned int getProcedureEndingJumpPosition() { return m_endingJumpPosition; }
	void setProcedureEndingJumpPosition(unsigned int endingJumpPosition) { m_endingJumpPosition = endingJumpPosition; }

private:
	std::vector<Variable*> m_variables;
	
	std::string m_name;
	
	unsigned int m_procedureStartPoint,
				 m_endingJumpPosition;

	unsigned int m_codeSize;
};