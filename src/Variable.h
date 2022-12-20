#pragma once

#include <string>

class Variable {
public:
	Variable(unsigned int value, unsigned int memoryPosition);
	Variable(const std::string& name, unsigned int value, unsigned int memoryPosition);

	inline void setName(const std::string& name) { m_name = name; }
	inline std::string getName() { return m_name; }

	inline void setValue(const unsigned int value) { m_value = value; }
	inline unsigned int getValue() { return m_value; }

	inline unsigned int getMemoryPosition() { return m_memoryPosition; }

private:
	std::string m_name = "";
	unsigned int m_value = 0;

	unsigned int m_memoryPosition = 1;
};