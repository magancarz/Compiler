#pragma once

#include <vector>
#include <string>
#include "../variables/Variable.h"
#include "../codeGenerator/Procedure.h"

class Memory {
public:
	Memory();
	~Memory();

	// creates temporary variables which helps in operations
	void initialize_helping_variables();
	
	// used mainly to create constants or temporary variables in memory
	void add_variable_to_memory(unsigned long long value);

	// used to create regular variables
	void add_variable_to_memory(const std::string& name, unsigned long long value);

	Variable* get_variable_from_memory(unsigned int memory_position) const;
	Variable* get_variable_from_memory(const std::string& name) const;

	void change_variable_value(unsigned int memory_position, unsigned long long value) const;
	void change_variable_value(const std::string& name, unsigned long long value) const;

	bool check_if_variable_exists(const std::string& name) const;

	// finds and returns variable based on memory position or name
	Variable* find_variable(unsigned int memory_position) const;
	Variable* find_variable(const std::string& name) const;

	// creates and returns variable as a constant
	static Variable* get_value_holder(unsigned long long value);
	Variable* get_variable(const std::string& name) const;

	// creates and adds new procedure to the memory
	void add_new_procedure();

	Procedure* get_current_procedure() const;

	// creates and adds new variable or pointer to the memory and assigns it to the procedure
	void add_variable_to_procedure(const std::string& name);
	Variable* add_procedure_variable_to_memory(const std::string& name);
	Variable* add_procedure_pointer_variable_to_memory(const std::string& name, Variable* pointing);

	// sets identifier to recently developed procedure
	void set_identifier_to_current_procedure(const std::string& name);

	// does actions to finish and prepare recently developed procedure for further operations
	Procedure* finish_procedure(unsigned int commands_size);

	// clears memory and variables used to develop procedure
	void clear_current_procedure();

	bool check_if_procedure_exists(const std::string& name) const;

	// add variable which will be in function execution
	void prepare_procedure_execution_variable(const std::string& name);

	std::vector<Variable*>& get_procedure_execution_variables();

	// clears memory used in procedure execution
	void clear_procedure_execution_variables();

	std::vector<Variable*>& get_memory_variables();

	std::vector<Procedure*>& get_procedures();

private:
	unsigned int m_free_memory_pointer = 0;

	std::vector<Variable*> m_variables;
	
	Procedure* m_current_procedure = nullptr;
	std::vector<Procedure*> m_procedures;

	std::string m_executed_procedure_identifier;
	std::vector<Variable*> m_procedure_execution_variables;
};