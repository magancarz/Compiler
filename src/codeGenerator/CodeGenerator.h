#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>

#include "../memory/Memory.h"

#define CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 1

struct Condition {
	unsigned int condition_code_size;
	unsigned long long jump_if_true_position;
	unsigned long long jump_if_false_position;
};

class CodeGenerator {
public:
	CodeGenerator(int argc, char** argv);
	~CodeGenerator();

	void set_memory_pointer(Memory* memory);

	// adds new line of code to m_code
	void write_code(const std::string& code);
	void write_code(const std::string& code, unsigned long long value);

	// changes line of code at given position
	void change_code(unsigned int code_position, const std::string& code);
	void change_code(unsigned int code_position, const std::string& code, unsigned long long value);

	// adds variable value to accumulator and generates machine code for this operation
	unsigned int add_value_to_accumulator(const Variable* variable);

	// subtracts variable value from acumulator and generates machine code for this operation
	unsigned int sub_value_from_accumulator(const Variable* variable);

	// loads variable value to accumulator and generates machine code for this operation
	unsigned int load_value_to_accumulator(const Variable* variable);

	// sets value to accumulator and generates machine code for this operation
	unsigned int set_value_to_accumulator(Variable* variable);
	unsigned int set_value_to_accumulator(unsigned long long value);

	// store value from accumulator to a specific variable in memory and generates machine code for this operation
	unsigned int store_value_from_accumulator(Variable* variable);
	unsigned int store_value_from_accumulator_to_pointed_variable(const Variable* pointer);

	// store value from accumulator to a specific variable (used in assigning variables values) and generates machine code for this operation
	unsigned int assign_value_to_variable(const std::string& name, const std::string& value);
	unsigned int assign_value_to_variable(const std::string& name, unsigned long long value);
	unsigned int assign_value_to_variable(const std::string& name, const Variable* variable);

	// generates code for READ command
	unsigned int read_value(const std::string& variable_name);

	// generates code for WRITE command
	unsigned int print_out_value(Variable* variable);

	// divides accumulator by half and generates machine code for this operation
	unsigned int divide_accumulator_by_half();

	// generates essential code for procedures creation and execution
	unsigned int generate_initial_code_for_procedure();
	unsigned int generate_procedure_end_code(Procedure* procedure);
	unsigned int execute_procedure(const std::string& procedure_name, const std::vector<Variable*>& procedure_execution_variables);

	// generates code for IF flow control
	unsigned int if_condition(const Condition* condition, unsigned int commands_length);

	// generates code for IF ELSE flow control
	unsigned int if_else_condition(const Condition* condition, unsigned int commands1_length, unsigned int commands2_length);
	unsigned int generate_middle_if_else_jump();

	// code for managing variables initialization in loops
	void loop_begin();
	void loop_end();

	// generates code for WHILE loop
	unsigned int while_loop(const Condition* condition, unsigned int commands_length);

	// generates code for REPEAT UNTIL loop
	unsigned int repeat_until_loop(const Condition* condition, unsigned int commands_length);

	// generates code for add operation
	unsigned int add(Variable* a, Variable* b);

	// generates code for subtract operation
	unsigned int subtract(Variable* a, Variable* b);

	// generates code for multiply operation
	unsigned int multiply(Variable* a, Variable* b);

	// generates code for divide operation
	unsigned int divide(Variable* a, Variable* b);

	// generates code for modulo operation
	unsigned int modulo(Variable* a, Variable* b);

	// generates code for EQUAL condition
	Condition* equal(Variable* a, Variable* b);

	// generates code for NOT EQUAL condition
	Condition* not_equal(Variable* a, Variable* b);

	// generates code for GREATER condition
	Condition* greater(Variable* a, Variable* b);

	// generates code for LESS condition
	Condition* less(Variable* a, Variable* b);

	// generates code for GREATER OR EQUAL condition
	Condition* greater_or_equal(Variable* a, Variable* b);

	// generates code for LESSER OR EQUAL condition
	Condition* less_or_equal(Variable* a, Variable* b);

	// returns code converted to it's virtual machine's form
	std::string get_code() const;

	FILE* get_input() const;

	// writes converted code to output file
	void generate_output();

private:
	FILE* m_input;
	std::ofstream m_output;

	Memory* m_memory = nullptr;

	std::vector<std::string> m_code;

	// current position at which new code will be written
	unsigned int m_command_pointer = 0;

	unsigned int m_loop_count = 0;
	std::unordered_map<unsigned int, std::unordered_map<unsigned int, bool>> m_loop_variables_tracking;
};