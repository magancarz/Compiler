#include "Variable.h"

Variable::Variable(unsigned int value, unsigned int memoryPosition) :
m_name(""), m_value(value), m_memoryPosition(memoryPosition) {

}

Variable::Variable(const std::string& name, unsigned int value, unsigned int memoryPosition) :
m_name(name), m_value(value), m_memoryPosition(memoryPosition) {

}

Variable::Variable(bool isInProcedure, const std::string& name, unsigned int memoryPosition) :
m_name(name), m_memoryPosition(memoryPosition), m_isInProcedure(isInProcedure) {

}

Variable::Variable(bool isInProcedure, const std::string& name, unsigned int memoryPosition, Variable* pointing) :
m_name(name), m_memoryPosition(memoryPosition), m_isInProcedure(isInProcedure), m_pointing(pointing), m_isPointer(true) {
	
}