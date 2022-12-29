#pragma once

#include <fstream>
#include <vector>

#include "../memory/Memory.h"

#define CODE_GENERATOR_DEBUG 0
#define CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 0

struct Condition {
	unsigned int condition_code_size;
	unsigned int jump_if_true_position;
	unsigned int jump_if_false_position;
};

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();
	
	void set_memory_pointer(Memory* memory);

	// functions to make differences in output code
	void write_code(const std::string& code);
	void write_code(const std::string& code, unsigned int value);
	void change_code(unsigned int code_position, const std::string& code);
	void change_code(unsigned int code_position, const std::string& code, unsigned int value);

	// code generating functions
	unsigned int add_value_to_accumulator(Variable* variable);
	unsigned int sub_value_from_accumulator(Variable* variable);

	unsigned int load_value_to_accumulator(Variable* variable);

	unsigned int set_value_to_accumulator(Variable* variable);
	unsigned int set_value_to_accumulator(unsigned int value);

	unsigned int store_value_from_accumulator(Variable* variable);
	unsigned int store_value_from_accumulator_to_pointed_variable(Variable* pointer);

	unsigned int assign_value_to_variable(const std::string& name, const std::string& value);
	unsigned int assign_value_to_variable(const std::string& name, unsigned int value);
	unsigned int assign_value_to_variable(const std::string& name, Variable* variable);

	unsigned int read_value(const std::string& variable_name);
	unsigned int print_out_value(Variable* variable);
	
	unsigned int divide_accumulator_by_half();

	unsigned int generate_initial_code_for_procedure();
	unsigned int generate_procedure_end_code(Procedure* procedure);
	unsigned int execute_procedure(const std::string& procedure_name, const std::vector<Variable*>& procedure_execution_variables);

	unsigned int if_condition(const Condition* condition, unsigned int commands_length);
	unsigned int if_else_condition(const Condition* condition, unsigned int commands1_length, unsigned int commands2_length);
	unsigned int generate_middle_if_else_jump();
	unsigned int while_loop(const Condition* condition, unsigned int commands_length);
	unsigned int repeat_until_loop(const Condition* condition, unsigned int commands_length);

	unsigned int add(Variable* a, Variable* b);
	unsigned int subtract(Variable* a, Variable* b);
	unsigned int multiply(Variable* a, Variable* b);
	unsigned int divide(Variable* a, Variable* b);
	unsigned int modulo(Variable* a, Variable* b);
	
	Condition* equal(Variable* a, Variable* b);
	Condition* not_equal(Variable* a, Variable* b);
	Condition* greater(Variable* a, Variable* b);
	Condition* less(Variable* a, Variable* b);
	Condition* greater_or_equal(Variable* a, Variable* b);
	Condition* lesser_or_equal(Variable* a, Variable* b);
	
	std::string get_code() const;

	FILE* get_input() const { return m_input; }

	void generate_output();

private:
	FILE* m_input;
	std::ofstream m_output;

	Memory* m_memory = nullptr;

	std::vector<std::string> m_code;

	unsigned int m_command_pointer = 0;
};