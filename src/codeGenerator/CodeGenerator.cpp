#include "CodeGenerator.h"

#include <sstream>
#include <iostream>

extern int yylineno;

CodeGenerator::CodeGenerator(int argc, char** argv) {
	m_input = fopen(argv[1], "r");
    m_output = std::ofstream(argv[2]);

	// initialize temp variables
	write_code("SET", 1);
	write_code("STORE", 7);
}

CodeGenerator::~CodeGenerator() {
	fclose(m_input);
}

void CodeGenerator::set_memory_pointer(Memory* memory) {
	m_memory = memory;
}

void CodeGenerator::write_code(const std::string& code) {
	std::stringstream final_code;
	final_code << code;
	m_code.push_back(final_code.str());

	m_command_pointer++;
}

void CodeGenerator::write_code(const std::string& code, const unsigned int value) {
	std::stringstream final_code;
	final_code << code << " " << value;
	m_code.push_back(final_code.str());

	m_command_pointer++;
}

void CodeGenerator::change_code(const unsigned int code_position, const std::string& code) {
	std::stringstream final_code;
	final_code << code;
	m_code.at(code_position) = final_code.str();
}

void CodeGenerator::change_code(const unsigned int code_position, const std::string& code, const unsigned int value) {
	std::stringstream final_code;
	final_code << code << " " << value;
	m_code.at(code_position) = final_code.str();
}

unsigned int CodeGenerator::add_value_to_accumulator(Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	accumulator->set_value(accumulator->get_value() + variable->get_value());

	write_code("ADD", variable->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::sub_value_from_accumulator(Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	accumulator->set_value(accumulator->get_value() - variable->get_value());

	write_code("SUB", variable->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::load_value_to_accumulator(Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	const unsigned int value = variable->get_value();
	m_memory->change_variable_value(0, value);

	write_code("LOAD", variable->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::set_value_to_accumulator(Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	if(!variable->get_name().empty()) {
		return load_value_to_accumulator(variable);
	}

	const unsigned int value = variable->get_value();
	m_memory->change_variable_value(0, value);
	
	write_code("SET", value);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::set_value_to_accumulator(const unsigned int value) {
	const unsigned int command_start = m_command_pointer;

	m_memory->change_variable_value(0, value);

	write_code("SET", value);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::store_value_from_accumulator(Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	variable->set_value(accumulator->get_value());

	write_code("STORE", variable->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::store_value_from_accumulator_to_pointed_variable(Variable* pointer) {
	const unsigned int command_start = m_command_pointer;

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	pointer->get_pointed_variable()->set_value(accumulator->get_value());

	write_code("STOREI", pointer->get_pointed_variable()->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::assign_value_to_variable(const std::string& name, const std::string& value) {
	const unsigned int command_start = m_command_pointer;

	if(!value.empty()) {
		const unsigned int int_value = std::stoi(value);
		assign_value_to_variable(name, int_value);
	} else {
		constexpr unsigned int int_value = 0;
		assign_value_to_variable(name, int_value);
	}

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::assign_value_to_variable(const std::string& name, const unsigned int value) {
	const unsigned int command_start = m_command_pointer;

	Variable* variable = m_memory->get_variable(name);
	variable->set_value(value);
	variable->set_is_initialized(true);

	const unsigned int variable_memory_position = m_memory->get_variable(name)->get_memory_position();
	write_code("STORE", variable_memory_position);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::assign_value_to_variable(const std::string& name, Variable* variable) {
	const unsigned int command_start = m_command_pointer;

	const unsigned int value = variable->get_value();
	Variable* var = m_memory->get_variable(name);
	var->set_value(value);
	var->set_is_initialized(true);

	const unsigned int variable_memory_position = m_memory->get_variable(name)->get_memory_position();
	write_code("STORE", variable_memory_position);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::divide_accumulator_by_half() {
	const unsigned int command_start = m_command_pointer;

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	accumulator->set_value(accumulator->get_value() / 2);

	write_code("HALF");

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::generate_initial_code_for_procedure() {
	const unsigned int command_start = m_command_pointer;

	write_code("JUMP", m_command_pointer);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::generate_procedure_end_code(Procedure* procedure) {
	const unsigned int command_start = m_command_pointer;
	
	procedure->set_procedure_start_point(command_start - procedure->get_code_size());

	const std::vector<Variable*>& procedure_variables = procedure->get_procedure_variables();
	for(Variable* variable : procedure_variables) {
		if(variable->is_pointer()) {
			load_value_to_accumulator(variable);
			store_value_from_accumulator_to_pointed_variable(variable);
		}
	}

	write_code("JUMPI", procedure->get_procedure_variables().at(0)->get_memory_position());
	procedure->set_procedure_ending_jump_position(procedure->get_procedure_variables().at(0)->get_memory_position());
	
	change_code(procedure->get_procedure_start_point() - 1, "JUMP", m_command_pointer);
	
	return m_command_pointer - command_start + procedure->get_code_size();
}

unsigned int CodeGenerator::execute_procedure(const std::string& procedure_name, const std::vector<Variable*>& procedure_execution_variables) {
	const unsigned int command_start = m_command_pointer;
	
	Procedure* procedure = nullptr;
	const std::vector<Procedure*>& procedures = m_memory->get_procedures();
	for(Procedure* proc : procedures) {
		if(proc->get_name() == procedure_name) {
			procedure = proc;
			break;
		}
	}

	if(procedure != nullptr) {
		const std::vector<Variable*>& procedure_pointers = procedure->get_procedure_pointers();
		
		unsigned int i = 0;
		for(auto* pointer : procedure_pointers) {
			Variable* proc_exec_var = procedure_execution_variables.at(i);
			proc_exec_var->set_is_initialized(true);
			set_value_to_accumulator(proc_exec_var->get_memory_position());
			store_value_from_accumulator(pointer->get_pointed_variable());
			load_value_to_accumulator(proc_exec_var);
			store_value_from_accumulator(pointer);
			
			i++;
		}
		
		set_value_to_accumulator(m_command_pointer + 3);
		store_value_from_accumulator(procedure->get_procedure_variables().at(0));

		write_code("JUMP", procedure->get_procedure_start_point());
		
	} else {
		printf("Error at line %d: Procedure %s doesn't exist\n", yylineno, procedure_name.c_str());
		exit(1);
	}

	m_memory->clear_procedure_execution_variables();

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::if_condition(const Condition* condition, unsigned int commands_length) {
	const unsigned int command_start = m_command_pointer;

	// change value of "if false" jump in condition's code
	const std::string code_to_change = m_code.at(condition->jump_if_false_position);
	std::istringstream iss(code_to_change);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		change_code(condition->jump_if_false_position, "JUMP", command_start);
	} else if(starts == "JPOS") {
		change_code(condition->jump_if_false_position, "JPOS", command_start);
	} else  {
		change_code(condition->jump_if_false_position, "JZERO", command_start);
	}

	const unsigned int condition_code_size = condition->condition_code_size;
	delete condition;

	return m_command_pointer - command_start + condition_code_size;
}

unsigned int CodeGenerator::if_else_condition(const Condition* condition, unsigned int commands1_length, const unsigned int commands2_length) {
	const unsigned int command_start = m_command_pointer;
	change_code(command_start - commands2_length - 1, "JUMP", command_start);
	
	const unsigned int command_if_false_start = m_command_pointer;

	const std::string jump_if_false_code_to_change = m_code.at(condition->jump_if_false_position);
	std::istringstream iss(jump_if_false_code_to_change);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		change_code(condition->jump_if_false_position, "JUMP", command_if_false_start - commands2_length);
	} else if(starts == "JPOS") {
		change_code(condition->jump_if_false_position, "JPOS", command_if_false_start - commands2_length);
	} else  {
		change_code(condition->jump_if_false_position, "JZERO", command_if_false_start - commands2_length);
	}

	const unsigned int condition_code_size = condition->condition_code_size;
	delete condition;

	return m_command_pointer - command_start + condition_code_size + 1;
}

unsigned int CodeGenerator::generate_middle_if_else_jump() {
	const unsigned int command_start = m_command_pointer;

	write_code("JUMP", m_command_pointer);

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::while_loop(const Condition* condition, const unsigned int commands_length) {
	const unsigned int command_start = m_command_pointer;

	write_code("JUMP", command_start - commands_length - condition->condition_code_size);

	const std::string code_to_change = m_code.at(condition->jump_if_false_position);
	std::istringstream iss(code_to_change);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		change_code(condition->jump_if_false_position, "JUMP", m_command_pointer);
	} else if(starts == "JPOS") {
		change_code(condition->jump_if_false_position, "JPOS", m_command_pointer);
	} else  {
		change_code(condition->jump_if_false_position, "JZERO", m_command_pointer);
	}

	const unsigned int condition_code_size = condition->condition_code_size;
	delete condition;

	return m_command_pointer - command_start + condition_code_size;
}

unsigned int CodeGenerator::repeat_until_loop(const Condition* condition, const unsigned int commands_length) {
	const unsigned int command_start = m_command_pointer;

	const std::string code_to_change = m_code.at(condition->jump_if_false_position);
	std::istringstream iss(code_to_change);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		change_code(condition->jump_if_false_position, "JUMP", m_command_pointer - commands_length - condition->condition_code_size);
	} else if(starts == "JPOS") {
		change_code(condition->jump_if_false_position, "JPOS", m_command_pointer - commands_length - condition->condition_code_size);
	} else  {
		change_code(condition->jump_if_false_position, "JZERO", m_command_pointer - commands_length - condition->condition_code_size);
	}

	const unsigned int condition_code_size = condition->condition_code_size;
	delete condition;

	return m_command_pointer - command_start + condition_code_size;
}

unsigned int CodeGenerator::read_value(const std::string& variable_name) {
	const unsigned int command_start = m_command_pointer;
	Variable* variable = m_memory->get_variable(variable_name);
	variable->set_is_initialized(true);

	write_code("GET", variable->get_memory_position());

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::print_out_value(Variable* variable) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int variable_memory_position = variable->get_memory_position();
	
	if(variable->get_name().empty()) {
		set_value_to_accumulator(variable->get_value());
		write_code("PUT", 0);
		return m_command_pointer - command_start;
	}

	if(variable->is_initialized()) {
		write_code("PUT", variable_memory_position);
	} else {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, variable->get_name().c_str());
		exit(1);
	}

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::add(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = a_val + b_val;
	
	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	if(a->get_name().empty() && b->get_name().empty()) {
		Variable* accumulator = m_memory->get_variable_from_memory(0);
		set_value_to_accumulator(result);

	} else if(a->get_name().empty()) {
		set_value_to_accumulator(a);
		add_value_to_accumulator(b);

	} else if(b->get_name().empty()) {
		set_value_to_accumulator(b);
		add_value_to_accumulator(a);

	} else {
		load_value_to_accumulator(a);
		add_value_to_accumulator(b);

	}

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::subtract(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	if(a->get_name().empty() && b->get_name().empty()) {
		const unsigned int a_val = a->get_value();
		const unsigned int b_val = b->get_value();
		const unsigned int result = b_val > a_val ? 0 : a_val - b_val;

		Variable* accumulator = m_memory->get_variable_from_memory(0);
		set_value_to_accumulator(result);

	} else if(a->get_name().empty()) {
		set_value_to_accumulator(a);
		sub_value_from_accumulator(b);

	} else if(b->get_name().empty()) {
		Variable* temp_variable = m_memory->get_variable_from_memory(1);
		temp_variable->set_value(b->get_value());
		set_value_to_accumulator(temp_variable);
		store_value_from_accumulator(temp_variable);
		load_value_to_accumulator(a);
		sub_value_from_accumulator(temp_variable);

	} else {
		load_value_to_accumulator(a);
		sub_value_from_accumulator(b);

	}

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::multiply(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;

	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	
	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	if(a->get_name().empty() && b->get_name().empty()) {
		const unsigned int result = a_val * b_val;
		set_value_to_accumulator(result);
	} else {
		constexpr unsigned int zero = 0;
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);
		Variable* temp2_variable = m_memory->get_variable_from_memory(2);
		Variable* temp3_variable = m_memory->get_variable_from_memory(3);
		Variable* temp4_variable = m_memory->get_variable_from_memory(4);
		Variable* one_variable = m_memory->get_variable_from_memory(7);
		
		// set up required variables
		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
		} else {
			load_value_to_accumulator(a);
		}
		store_value_from_accumulator(temp1_variable);

		// multiplier and remainder of multiplier
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
		} else {
			load_value_to_accumulator(b);
		}
		store_value_from_accumulator(temp2_variable);

		set_value_to_accumulator(zero);
		store_value_from_accumulator(temp3_variable);

		const unsigned int start_of_the_loop = m_command_pointer;
		load_value_to_accumulator(temp2_variable);
		write_code("JZERO", m_command_pointer + 24);

		// check if Y is odd
		sub_value_from_accumulator(one_variable);
		write_code("JZERO", m_command_pointer + 19);

		load_value_to_accumulator(temp2_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp4_variable);
		add_value_to_accumulator(temp4_variable);
		store_value_from_accumulator(temp4_variable);
		load_value_to_accumulator(temp2_variable);
		sub_value_from_accumulator(temp4_variable);
		write_code("JZERO", m_command_pointer + 4);

		//if Y is odd, then add X to the result
		load_value_to_accumulator(temp3_variable);
		add_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp1_variable);
		add_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp1_variable);

		load_value_to_accumulator(temp2_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp2_variable);
		write_code("JUMP", start_of_the_loop);

		load_value_to_accumulator(temp3_variable);
		add_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp3_variable);
	}

	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::divide(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = (b_val != 0)? a_val % b_val : 0;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	if(a->get_name().empty() && b->get_name().empty()) {
		set_value_to_accumulator(result);
	} else {
		constexpr unsigned int zero = 0;
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);
		Variable* temp2_variable = m_memory->get_variable_from_memory(2);
		Variable* temp3_variable = m_memory->get_variable_from_memory(3);
		Variable* temp4_variable = m_memory->get_variable_from_memory(4);
		Variable* temp5_variable = m_memory->get_variable_from_memory(5);
		Variable* temp6_variable = m_memory->get_variable_from_memory(6);
		Variable* one_variable = m_memory->get_variable_from_memory(7);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
		} else {
			load_value_to_accumulator(a);
		}
		store_value_from_accumulator(temp2_variable);
		store_value_from_accumulator(temp5_variable);

		// multiplier and remainder of multiplier
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
		} else {
			load_value_to_accumulator(b);
		}
		store_value_from_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);
		
		// current power of 2
		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);
		
		// result
		set_value_to_accumulator(zero);
		store_value_from_accumulator(temp6_variable);

		// check if divisor is 0 or bigger than dividend
		load_value_to_accumulator(temp1_variable);
		unsigned int jump_variable = m_command_pointer;
		write_code("JZERO", jump_variable + 54);
		sub_value_from_accumulator(temp2_variable);
		write_code("JZERO", jump_variable + 5);
		set_value_to_accumulator(zero);
		write_code("JUMP", jump_variable + 54);

		// start of the loop
		const unsigned int start_of_the_multiplying_loop = m_command_pointer;

		// check if current value >= remaining multiplier
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		
		// jump to position where we can check if value > or == remaining multiplier
		write_code("JZERO", m_command_pointer + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		load_value_to_accumulator(temp3_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp4_variable);
		add_value_to_accumulator(temp4_variable);
		store_value_from_accumulator(temp4_variable);

		// go back to the start of the loop
		write_code("JUMP", start_of_the_multiplying_loop);

		load_value_to_accumulator(temp4_variable);
		sub_value_from_accumulator(temp5_variable);
		
		write_code("JPOS", m_command_pointer + 31);
		
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		store_value_from_accumulator(temp5_variable);

		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp6_variable);
		write_code("JUMP", m_command_pointer + 31);

		const unsigned int add_to_result_jump_position = m_command_pointer;
		load_value_to_accumulator(temp4_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp4_variable);
		write_code("JPOS", m_command_pointer + 3);
		load_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		store_value_from_accumulator(temp5_variable);

		load_value_to_accumulator(temp3_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp3_variable);
		write_code("JPOS", m_command_pointer + 3);
		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);
		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp6_variable);

		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);

		write_code("JUMP", start_of_the_multiplying_loop);
		
		load_value_to_accumulator(temp3_variable);
		sub_value_from_accumulator(one_variable);
		write_code("JZERO", m_command_pointer + 5);
		write_code("JUMP", add_to_result_jump_position);

		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp4_variable);
		store_value_from_accumulator(temp6_variable);

		load_value_to_accumulator(temp6_variable);
	}
	 
	return m_command_pointer - command_start;
}

unsigned int CodeGenerator::modulo(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	Variable* accumulator = m_memory->get_variable_from_memory(0);
	if(a->get_name().empty() && b->get_name().empty()) {
		const unsigned int result = (b_val != 0)? a_val % b_val : 0;
		set_value_to_accumulator(result);
	} else {
		constexpr unsigned int zero = 0;
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);
		Variable* temp2_variable = m_memory->get_variable_from_memory(2);
		Variable* temp3_variable = m_memory->get_variable_from_memory(3);
		Variable* temp4_variable = m_memory->get_variable_from_memory(4);
		Variable* temp5_variable = m_memory->get_variable_from_memory(5);
		Variable* temp6_variable = m_memory->get_variable_from_memory(6);
		Variable* one_variable = m_memory->get_variable_from_memory(7);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
		} else {
			load_value_to_accumulator(a);
		}
		store_value_from_accumulator(temp2_variable);
		store_value_from_accumulator(temp5_variable);

		// multiplier and remainder of multiplier
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
		} else {
			load_value_to_accumulator(b);
		}
		store_value_from_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);
		
		// current power of 2
		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);
		
		// result
		set_value_to_accumulator(zero);
		store_value_from_accumulator(temp6_variable);

		// check if divisor is 0 or bigger than dividend
		load_value_to_accumulator(temp1_variable);
		unsigned int jump_variable = m_command_pointer;
		write_code("JZERO", jump_variable + 54);
		sub_value_from_accumulator(temp2_variable);
		write_code("JZERO", jump_variable + 5);
		load_value_to_accumulator(temp2_variable);
		write_code("JPOS", jump_variable + 54);

		// start of the loop
		const unsigned int start_of_the_multiplying_loop = m_command_pointer;

		// check if current value >= remaining multiplier
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		
		// jump to position where we can check if value > or == remaining multiplier
		write_code("JZERO", m_command_pointer + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		load_value_to_accumulator(temp3_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp4_variable);
		add_value_to_accumulator(temp4_variable);
		store_value_from_accumulator(temp4_variable);

		// go back to the start of the loop
		write_code("JUMP", start_of_the_multiplying_loop);

		load_value_to_accumulator(temp4_variable);
		sub_value_from_accumulator(temp5_variable);
		
		write_code("JPOS", m_command_pointer + 31);
		
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		store_value_from_accumulator(temp5_variable);

		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp6_variable);
		write_code("JUMP", m_command_pointer + 31);

		const unsigned int add_to_result_jump_position = m_command_pointer;
		load_value_to_accumulator(temp4_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp4_variable);
		write_code("JPOS", m_command_pointer + 3);
		load_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);
		load_value_to_accumulator(temp5_variable);
		sub_value_from_accumulator(temp4_variable);
		store_value_from_accumulator(temp5_variable);

		load_value_to_accumulator(temp3_variable);
		divide_accumulator_by_half();
		store_value_from_accumulator(temp3_variable);
		write_code("JPOS", m_command_pointer + 3);
		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);
		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp3_variable);
		store_value_from_accumulator(temp6_variable);

		set_value_to_accumulator(1);
		store_value_from_accumulator(temp3_variable);

		load_value_to_accumulator(temp1_variable);
		store_value_from_accumulator(temp4_variable);

		write_code("JUMP", start_of_the_multiplying_loop);
		
		load_value_to_accumulator(temp3_variable);
		sub_value_from_accumulator(one_variable);
		write_code("JZERO", m_command_pointer + 5);
		write_code("JUMP", add_to_result_jump_position);

		load_value_to_accumulator(temp6_variable);
		add_value_to_accumulator(temp4_variable);
		store_value_from_accumulator(temp6_variable);

		load_value_to_accumulator(temp5_variable);
	}

	return m_command_pointer - command_start;
}

Condition* CodeGenerator::equal(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position, jump_if_true_position;
	if(a->get_name().empty() && b->get_name().empty()) {
		const unsigned int result = (a_val == b_val)? 1 : 0;
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);
		Variable* temp2_variable = m_memory->get_variable_from_memory(2);

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(a);
			store_value_from_accumulator(temp1_variable);
		}

		// multiplier and remainder of multiplier
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
			store_value_from_accumulator(temp2_variable);
		} else {
			load_value_to_accumulator(b);
			store_value_from_accumulator(temp2_variable);
		}

		sub_value_from_accumulator(temp1_variable);
		write_code("JPOS", m_command_pointer + 5);

		load_value_to_accumulator(temp1_variable);
		sub_value_from_accumulator(temp2_variable);
		
		write_code("JPOS", m_command_pointer + 2);
		
		jump_if_true_position = m_command_pointer;
		write_code("JUMP", jump_if_true_position + 2);
		
		jump_if_false_position = m_command_pointer;
		write_code("JUMP", jump_if_false_position + 1);

	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

Condition* CodeGenerator::not_equal(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position, jump_if_true_position;
	if(a->get_name().empty() && b->get_name().empty()) {
		const unsigned int result = (a_val != b_val)? 1 : 0;
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);
		Variable* temp2_variable = m_memory->get_variable_from_memory(2);

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(a);
			store_value_from_accumulator(temp1_variable);
		}

		// multiplier and remainder of multiplier
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
			store_value_from_accumulator(temp2_variable);
		} else {
			load_value_to_accumulator(b);
			store_value_from_accumulator(temp2_variable);
		}

		sub_value_from_accumulator(temp1_variable);
		write_code("JPOS", m_command_pointer + 4);

		load_value_to_accumulator(temp1_variable);
		sub_value_from_accumulator(temp2_variable);
		jump_if_true_position = m_command_pointer;
		write_code("JPOS", jump_if_true_position + 2);
		
		jump_if_false_position = m_command_pointer;
		write_code("JUMP", jump_if_false_position + 1);
	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

Condition* CodeGenerator::greater(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = (a_val > b_val)? 1 : 0;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position, jump_if_true_position;
	if(a->get_name().empty() && b->get_name().empty()) {
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);

		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(b);
			store_value_from_accumulator(temp1_variable);
		}

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
		} else {
			load_value_to_accumulator(a);
		}

		sub_value_from_accumulator(temp1_variable);
		jump_if_false_position = m_command_pointer;
		write_code("JZERO", jump_if_false_position + 2);
		jump_if_true_position = m_command_pointer;
		write_code("JUMP", jump_if_true_position + 1);
	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

Condition* CodeGenerator::less(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = (a_val < b_val)? 1 : 0;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position, jump_if_true_position;
	if(a->get_name().empty() && b->get_name().empty()) {
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(a);
			store_value_from_accumulator(temp1_variable);
		}

		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
		} else {
			load_value_to_accumulator(b);
		}

		sub_value_from_accumulator(temp1_variable);
		jump_if_false_position = m_command_pointer;
		write_code("JZERO", jump_if_false_position + 2);
		jump_if_true_position = m_command_pointer;
		write_code("JUMP", jump_if_true_position + 1);
	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

Condition* CodeGenerator::greater_or_equal(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = (a_val >= b_val)? 1 : 0;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position, jump_if_true_position;
	if(a->get_name().empty() && b->get_name().empty()) {
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(a);
			store_value_from_accumulator(temp1_variable);
		}
		
		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
		} else {
			load_value_to_accumulator(b);
		}
		
		sub_value_from_accumulator(temp1_variable);
		jump_if_false_position = m_command_pointer;
		write_code("JPOS", jump_if_false_position + 2);
		jump_if_true_position = m_command_pointer;
		write_code("JUMP", jump_if_true_position + 1);
	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

Condition* CodeGenerator::lesser_or_equal(Variable* a, Variable* b) {
	const unsigned int command_start = m_command_pointer;
	const unsigned int a_val = a->get_value();
	const unsigned int b_val = b->get_value();
	const unsigned int result = (a_val >= b_val)? 1 : 0;

	if(!a->get_name().empty() && !a->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, a->get_name().c_str());
		exit(1);
	}

	if(!b->get_name().empty() && !b->is_initialized()) {
		printf("Error at line %d: Use of uninitialized variable %s.\n", yylineno, b->get_name().c_str());
		exit(1);
	}

	unsigned int jump_if_false_position = 0, jump_if_true_position = 0;
	if(a->get_name().empty() && b->get_name().empty()) {
		set_value_to_accumulator(result);
	} else {
		Variable* temp1_variable = m_memory->get_variable_from_memory(1);

		if(b->get_name().empty()) {
			set_value_to_accumulator(b_val);
			store_value_from_accumulator(temp1_variable);
		} else {
			load_value_to_accumulator(b);
			store_value_from_accumulator(temp1_variable);
		}

		if(a->get_name().empty()) {
			set_value_to_accumulator(a_val);
		} else {
			load_value_to_accumulator(a);
		}
		
		sub_value_from_accumulator(temp1_variable);
		jump_if_false_position = m_command_pointer;
		write_code("JPOS", jump_if_false_position + 2);
		jump_if_true_position = m_command_pointer;
		write_code("JUMP", jump_if_true_position + 1);
	}

	auto* condition = new Condition{m_command_pointer - command_start, jump_if_true_position, jump_if_false_position};
	return condition;
}

std::string CodeGenerator::get_code() const {
	std::stringstream code;
	unsigned int i = 0;
	for(const std::string& s : m_code) {
		#if CODE_GENERATOR_DEBUG_COMMAND_LINES_NO
		code << i << ". ";
		#endif
		code << s << "\n";
		i++;
	}

	return code.str();
}

void CodeGenerator::generate_output() {
	for(const std::string& s : m_code) {
		if(s == "HALT") {
			m_output << s;
			return;
		}
		m_output << s << "\n";
	}
}