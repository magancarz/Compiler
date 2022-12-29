#pragma once

#include <vector>
#include <string>
#include "../variables/Variable.h"
#include "../codeGenerator/Procedure.h"

class Memory {
public:
	Memory();
	~Memory();

	void initialize_helping_variables();

	void add_variable_to_memory(unsigned int value);
	void add_variable_to_memory(const std::string& name, unsigned int value);
	Variable* add_procedure_pointer_to_memory(const std::string& name, Variable* pointing);
	Variable* add_procedure_variable_to_memory(const std::string& name);
	
	Variable* get_variable_from_memory(unsigned int memory_position) const;
	Variable* get_variable_from_memory(const std::string& name) const;

	void change_variable_value(unsigned int memory_position, unsigned int value) const;
	void change_variable_value(const std::string& name, unsigned int value) const;

	bool check_if_variable_exists(const std::string& name) const;

	Variable* find_variable(unsigned int memory_position) const;
	Variable* find_variable(const std::string& name) const;
	static Variable* get_value_holder(unsigned int value);
	Variable* get_variable(const std::string& name) const;
	
	void add_new_procedure();
	Procedure* get_current_procedure() const { return m_current_procedure; }
	void add_variable_to_procedure(const std::string& name);
	void set_identifier_to_current_procedure(const std::string& name);
	Procedure* finish_procedure(unsigned int commands_size);
	void clear_current_procedure();
	bool check_if_procedure_exists(const std::string& name) const;

	void prepare_procedure_execution_variable(const std::string& name);
	std::vector<Variable*>& get_procedure_execution_variables();
	void clear_procedure_execution_variables();

	std::vector<Variable*>& get_memory_variables() { return m_variables; }

	std::vector<Procedure*>& get_procedures() { return m_procedures; }

private:
	unsigned int m_free_memory_pointer = 0;

	std::vector<Variable*> m_variables;
	
	Procedure* m_current_procedure = nullptr;
	std::vector<Procedure*> m_procedures;

	std::string m_executed_procedure_identifier;
	std::vector<Variable*> m_procedure_execution_variables;
};