#include "Memory.h"

#include <iostream>
#include <algorithm>

extern int yylineno;

Memory::Memory() {
	initialize_helping_variables();
}

Memory::~Memory() {
	for(const auto v : m_variables) {
		delete v;
	}
	m_variables.clear();

	for(const auto p : m_procedures) {
		delete p;
	}
	m_procedures.clear();
}

void Memory::initialize_helping_variables() {
	// accumulator
	add_variable_to_memory(0);

	// variables for supporting calculations
	add_variable_to_memory(0);
	add_variable_to_memory(0);
	add_variable_to_memory(0);
	add_variable_to_memory(0);
	add_variable_to_memory(0);
	add_variable_to_memory(0);

	// "zero" value holder
	add_variable_to_memory(0);

	// "one" value holder
	add_variable_to_memory(1);
}

void Memory::add_variable_to_memory(const unsigned long long value) {
	auto* new_variable = new Variable(value, m_free_memory_pointer);
	m_variables.push_back(new_variable);
	m_free_memory_pointer++;
}

void Memory::add_variable_to_memory(const std::string& name, const unsigned long long value) {
	if(!name.empty() && check_if_variable_exists(name)) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Variable " + name + " already exist.\n");
	}

	auto* new_variable = new Variable(name, value, m_free_memory_pointer);
	m_variables.push_back(new_variable);
	m_free_memory_pointer++;
}

Variable* Memory::get_variable_from_memory(const std::string& name) const {
	if(!name.empty() && check_if_variable_exists(name)) {
		return find_variable(name);
	}

	throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Variable " + name + " doesn't exist.\n");
}

void Memory::change_variable_value(const unsigned int memory_position, const unsigned long long value) const {
	Variable* variable = m_variables.at(memory_position);
	variable->set_value(value);
}

void Memory::change_variable_value(const std::string& name, const unsigned long long value) const {
	if(!name.empty() && check_if_variable_exists(name)) {
		Variable* variable = get_variable(name);
		variable->set_value(value);
	} else {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Variable " + name + " doesn't exist.\n");
	}
}

bool Memory::check_if_variable_exists(const std::string& name) const {
	const Variable* variable = find_variable(name);
	return (variable != nullptr)? true : false;
}

Variable* Memory::find_variable(const unsigned int memory_position) const {
	if(memory_position > m_variables.size()) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Memory out of scope\n");
	}
	Variable* variable = m_variables.at(memory_position);
	return variable;
}

Variable* Memory::find_variable(const std::string& name) const {
	Variable* variable = get_variable(name);
	return variable;
}

Variable* Memory::get_value_holder(const unsigned long long value) {
	// return variable as value holder for a constant
	return new Variable("", value, 0);
}

Variable* Memory::get_variable(const std::string& name) const {
	for(Variable* variable : m_variables) {
		std::string variable_name = variable->get_name();

		// if we are adding new procedure, then avoid checking regular
		// variable names, similarly avoid procedure variables when we are looking for a regular variable
		if(m_current_procedure != nullptr) {
			if(variable_name == name && variable->is_in_procedure() && variable->get_parent_procedure_name() == m_current_procedure->get_name()) {
				return variable;
			}
		} else {
			if(variable_name == name && !variable->is_in_procedure()) {
				return variable;
			}
		}
	}

	return nullptr;
}

void Memory::add_new_procedure() {
	// add new procedure to memory and add variable that functions
	// as a storage for holding position to go back from procedure
	m_current_procedure = new Procedure();
	m_current_procedure->get_procedure_variables().push_back(new Variable(true, "", m_free_memory_pointer));
	m_free_memory_pointer++;
}

Procedure* Memory::get_current_procedure() const {
	return m_current_procedure;
}

void Memory::add_variable_to_procedure(const std::string& name) {
	if(m_current_procedure == nullptr) {
		add_new_procedure();
	}
	
	// if the name is empty, then add variable as a pointer, otherwise add it as a regular variable
	if(m_current_procedure->get_name().empty()) {
		m_current_procedure->add_variable(add_procedure_pointer_variable_to_memory(name, nullptr));
		return;
	}

	m_current_procedure->add_variable(add_procedure_variable_to_memory(name));
}

Variable* Memory::add_procedure_variable_to_memory(const std::string& name) {
	if(!name.empty() && check_if_variable_exists(name)) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Variable " + name + " already exists in current procedure.\n");
	}

	// create and add new variable to the memory, then mark it as a specific procedure variable
	auto* new_variable = new Variable(true, name, m_free_memory_pointer);
	new_variable->set_parent_procedure_name(m_current_procedure->get_name());
	m_variables.push_back(new_variable);
	m_free_memory_pointer++;

	return new_variable;
}

Variable* Memory::add_procedure_pointer_variable_to_memory(const std::string& name, Variable* pointing) {
	if(!name.empty() && check_if_variable_exists(name)) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Variable " + name + " already exists in current procedure.\n");
	}

	// create variable which will hold memory position of pointed variable
	auto* new_variable = new Variable(0, m_free_memory_pointer);
	m_variables.push_back(new_variable);
	m_free_memory_pointer++;

	// create and add variable that will be marked as a pointer
	auto* new_variable_pointer = new Variable(true, name, m_free_memory_pointer, new_variable);
	m_variables.push_back(new_variable_pointer);
	m_free_memory_pointer++;

	return new_variable_pointer;
}

void Memory::set_identifier_to_current_procedure(const std::string& name) {
	if(!name.empty() && check_if_procedure_exists(name)) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Procedure " + name + " already exists.\n");
	}

	// in case of procedure with no parameters
	if(m_current_procedure == nullptr) {
		add_new_procedure();
	}

	// mostly needed for procedure pointer variables
	for(auto* var : m_current_procedure->get_procedure_variables()) {
		var->set_parent_procedure_name(name);
	}

	m_current_procedure->set_procedure_name(name);
}

Procedure* Memory::finish_procedure(const unsigned int commands_size) {
	// size of the code inside the procedure
	m_current_procedure->set_code_size(commands_size);

	m_procedures.push_back(m_current_procedure);
	return m_current_procedure;
}

void Memory::clear_current_procedure() {
	m_current_procedure = nullptr;
}

Variable* Memory::get_variable_from_memory(const unsigned int memory_position) const {
	if(memory_position > m_variables.size()) {
		throw std::runtime_error("Error at line " + std::to_string(yylineno) + ": Memory pointer out of range\n");
	}
	
	return find_variable(memory_position);
}

bool Memory::check_if_procedure_exists(const std::string& name) const {
	if(std::any_of(m_procedures.begin(), m_procedures.end(),
		[name](const Procedure* procedure){ return procedure->get_name() == name; })) {
		return true;
	}

	return false;
}

void Memory::prepare_procedure_execution_variable(const std::string& name) {
	// get variable from memory and store it for further procedure execution functions
	m_procedure_execution_variables.push_back(get_variable_from_memory(name));
}

std::vector<Variable*>& Memory::get_procedure_execution_variables() {
	return m_procedure_execution_variables;
}

void Memory::clear_procedure_execution_variables() {
	m_procedure_execution_variables.clear();
}

std::vector<Variable*>& Memory::get_memory_variables() {
	return m_variables;
}

std::vector<Procedure*>& Memory::get_procedures() {
	return m_procedures;
}