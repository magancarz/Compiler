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

bool Variable::is_initialized() const {
	return m_is_initialized;
}

void Variable::set_is_initialized(const bool value) {
	m_is_initialized = value;
}

void Variable::set_name(const std::string& name) {
	m_name = name;
}

std::string Variable::get_name() {
	return m_name;
}

void Variable::set_value(const unsigned int value) {
	m_value = value;
}

unsigned int Variable::get_value() const {
	return m_value;
}

unsigned int Variable::get_memory_position() const {
	return m_memory_position;
}

void Variable::set_parent_procedure_name(const std::string& name) {
	m_parent_procedure_name = name;
}

const std::string& Variable::get_parent_procedure_name() {
	return m_parent_procedure_name;
}

bool Variable::is_in_procedure() const {
	return m_is_in_procedure;
}

bool Variable::is_pointer() const {
	return m_is_pointer;
}

Variable* Variable::get_pointed_variable() const {
	return m_pointing;
}