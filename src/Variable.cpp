#include "Variable.h"

Variable::Variable(unsigned int value, unsigned int memoryPosition) :
m_name(""), m_value(value), m_memoryPosition(memoryPosition) {

}

Variable::Variable(const std::string& name, unsigned int value, unsigned int memoryPosition) :
m_name(name), m_value(value), m_memoryPosition(memoryPosition) {

}