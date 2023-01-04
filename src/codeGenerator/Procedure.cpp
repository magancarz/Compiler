#include "Procedure.h"

void Procedure::add_variable(Variable* variable) {
	// if a variable is a pointer, then add it to vector of pointers too
	if(variable->is_pointer()) {
		m_pointers.push_back(variable);
	}

	m_variables.push_back(variable);
}

std::string Procedure::get_name() const {
	return m_name;
}

void Procedure::set_procedure_name(const std::string& name) {
	m_name = name;
}

void Procedure::set_code_size(const unsigned int size) {
	m_code_size = size;
}

unsigned int Procedure::get_code_size() const {
	return m_code_size;
}

std::vector<Variable*>& Procedure::get_procedure_variables() {
	return m_variables;
}

std::vector<Variable*>& Procedure::get_procedure_pointers() {
	return m_pointers;
}

unsigned int Procedure::get_procedure_start_point() const {
	return m_procedure_start_point;
}

void Procedure::set_procedure_start_point(const unsigned int start_point) {
	m_procedure_start_point = start_point;
}

unsigned int Procedure::get_procedure_ending_jump_position() const {
	return m_ending_jump_position;
}

void Procedure::set_procedure_ending_jump_position(const unsigned int ending_jump_position) {
	m_ending_jump_position = ending_jump_position;
}