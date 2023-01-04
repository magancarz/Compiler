#pragma once

#include <string>

class Variable {
public:
	Variable(unsigned int value, unsigned int memory_position);

	Variable(std::string name, unsigned int value, unsigned int memory_position);

	Variable(bool is_in_procedure, std::string name, unsigned int memory_position);

	Variable(bool is_in_procedure, std::string name, unsigned int memory_position, Variable* pointing);

	bool is_initialized() const;
	void set_is_initialized(bool value);

	void set_name(const std::string& name);
	std::string get_name();

	void set_value(unsigned int value);
	unsigned int get_value() const;

	unsigned int get_memory_position() const;

	void set_parent_procedure_name(const std::string& name);
	const std::string& get_parent_procedure_name();

	bool is_in_procedure() const;

	bool is_pointer() const;
	
	Variable* get_pointed_variable() const;

private:
	bool m_is_in_procedure = false;
	std::string m_parent_procedure_name;

	std::string m_name;
	unsigned int m_value = 0;

	unsigned int m_memory_position;

	Variable* m_pointing = nullptr;
	bool m_is_pointer = false;

	bool m_is_initialized = false;
};