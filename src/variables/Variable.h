#pragma once

#include <string>

class Variable {
public:
	Variable(unsigned int value, unsigned int memory_position);
	Variable(std::string name, unsigned int value, unsigned int memory_position);
	Variable(bool is_in_procedure, std::string name, unsigned int memory_position);
	Variable(bool is_in_procedure, std::string name, unsigned int memory_position, Variable* pointing);

	bool is_initialized() const { return m_is_initialized; }
	void set_is_initialized(const bool value) { m_is_initialized = value; }

	void set_name(const std::string& name) { m_name = name; }
	std::string get_name() { return m_name; }

	void set_value(const unsigned int value) { m_value = value; }
	unsigned int get_value() const { return m_value; }

	unsigned int get_memory_position() const { return m_memory_position; }

	void set_parent_procedure_name(const std::string& name) { m_parent_procedure_name = name; }
	const std::string& get_parent_procedure_name() { return m_parent_procedure_name; }

	bool is_in_procedure() const { return m_is_in_procedure; }

	bool is_pointer() const { return m_is_pointer; }
	
	Variable* get_pointed_variable() const { return m_pointing; }

private:
	bool m_is_in_procedure = false;

	std::string m_name;
	unsigned int m_value = 0;

	unsigned int m_memory_position;

	Variable* m_pointing = nullptr;
	std::string m_parent_procedure_name;
	bool m_is_pointer = false;
	bool m_is_initialized = false;
};