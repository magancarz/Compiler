#include "Variable.h"

Variable::Variable(const unsigned int value, const unsigned int memory_position) :
m_value(value), m_memory_position(memory_position) {

}

Variable::Variable(std::string name, const unsigned int value, const unsigned int memory_position) :
m_name(std::move(name)), m_value(value), m_memory_position(memory_position) {

}

Variable::Variable(const bool is_in_procedure, std::string name, const unsigned int memory_position) :
m_is_in_procedure(is_in_procedure), m_name(std::move(name)), m_memory_position(memory_position) {

}

Variable::Variable(const bool is_in_procedure, std::string name, const unsigned int memory_position, Variable* pointing) :
m_is_in_procedure(is_in_procedure), m_name(std::move(name)), m_memory_position(memory_position), m_pointing(pointing), m_is_pointer(true), m_is_initialized(true) {
	
}