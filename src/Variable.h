#pragma once

#include <string>

class Variable {
public:
	Variable(unsigned int value, unsigned int memory_position);
	Variable(std::string name, unsigned int value, unsigned int memory_position);
	Variable(bool is_in_procedure, std::string name, unsigned int memory_position);
	Variable(bool is_in_procedure, std::string name, unsigned int memory_position, Variable* pointing);

	inline bool is_initialized() { return m_is_initialized; }
	void set_is_initialized(bool value) { m_is_initialized = value; }

	inline void set_name(const std::string& name) { m_name = name; }
	inline std::string get_name() { return m_name; }

	inline void set_value(const unsigned int value) { m_value = value; }
	inline unsigned int get_value() { return m_value; }

	inline unsigned int get_memory_position() { return m_memory_position; }

	void set_parent_procedure_name(const std::string& name) { m_parent_procedure_name = name; }
	inline const std::string& get_parent_procedure_name() { return m_parent_procedure_name; }

	inline bool is_in_procedure() { return m_is_in_procedure; }

	inline bool is_pointer() { return m_is_pointer; }
	
	inline Variable* get_pointed_variable() { return m_pointing; }

private:
	bool m_is_in_procedure = false;

	std::string m_name = "";
	unsigned int m_value = 0;

	unsigned int m_memory_position;

	Variable* m_pointing = nullptr;
	std::string m_parent_procedure_name;
	bool m_is_pointer = false;
	bool m_is_initialized = false;
};