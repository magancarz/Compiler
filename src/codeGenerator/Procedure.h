#pragma once

#include <vector>
#include <string>

#include "../variables/Variable.h"

class Procedure {
public:
	Procedure() = default;
	~Procedure() = default;

	std::string get_name() const;
	void set_procedure_name(const std::string& name);
	
	void set_code_size(unsigned int size);
	unsigned int get_code_size() const;

	void add_variable(Variable* variable);
	std::vector<Variable*>& get_procedure_variables();
	std::vector<Variable*>& get_procedure_pointers();

	unsigned int get_procedure_start_point() const;
	void set_procedure_start_point(unsigned int start_point);

	unsigned int get_procedure_ending_jump_position() const;
	void set_procedure_ending_jump_position(unsigned int ending_jump_position);

private:
	std::vector<Variable*> m_variables;
	std::vector<Variable*> m_pointers;
	
	std::string m_name;
	
	unsigned int m_procedure_start_point = 0,
				 m_ending_jump_position = 0;

	unsigned int m_code_size = 0;
};