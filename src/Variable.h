#pragma once

#include <string>

class Variable {
public:
	Variable(unsigned int value, unsigned int memoryPosition);
	Variable(const std::string& name, unsigned int value, unsigned int memoryPosition);
	Variable(bool isInProcedure, const std::string& name, unsigned int memoryPosition);
	Variable(bool isInProcedure, const std::string& name, unsigned int memoryPosition, Variable* pointing);

	inline void setName(const std::string& name) { m_name = name; }
	inline std::string getName() { return m_name; }

	inline void setValue(const unsigned int value) { m_value = value; }
	inline unsigned int getValue() { return m_value; }

	inline unsigned int getMemoryPosition() { return m_memoryPosition; }

	void setParentProcedureName(const std::string& name) { m_parentProcedureName = name; }
	inline const std::string& getParentProcedureName() { return m_parentProcedureName; }

	inline bool isInProcedure() { return m_isInProcedure; }

	inline bool isPointer() { return m_isPointer; }
	
	inline Variable* getPointedVariable() { return m_pointing; }

private:
	std::string m_name = "";
	unsigned int m_value = 0;

	unsigned int m_memoryPosition;

	std::string m_parentProcedureName;
	bool m_isInProcedure = false;
	bool m_isPointer = false;
	Variable* m_pointing = nullptr;
};