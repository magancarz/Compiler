#pragma once

#include <vector>
#include <string>

#include "../variables/Variable.h"

class Procedure {
public:
	Procedure() = default;
	~Procedure() = default;

	std::string get_name() const { return m_name; }
	void set_procedure_name(const std::string& name) { m_name = name; }
	
	void set_code_size(const unsigned int size) { m_code_size = size; }
	unsigned int get_code_size() const { return m_code_size; }

	void add_variable(Variable* variable);
	std::vector<Variable*>& get_procedure_variables() { return m_variables; }
	std::vector<Variable*>& get_procedure_pointers() { return m_pointers; }

	unsigned int get_procedure_start_point() const { return m_procedure_start_point; }
	void set_procedure_start_point(const unsigned int start_point) { m_procedure_start_point = start_point; }

	unsigned int get_procedure_ending_jump_position() const { return m_ending_jump_position; }
	void set_procedure_ending_jump_position(const unsigned int ending_jump_position) { m_ending_jump_position = ending_jump_position; }

private:
	std::vector<Variable*> m_variables;
	std::vector<Variable*> m_pointers;
	
	std::string m_name;
	
	unsigned int m_procedure_start_point = 0,
				 m_ending_jump_position = 0;

	unsigned int m_code_size = 0;
};