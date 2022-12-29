#include "Procedure.h"

void Procedure::add_variable(Variable* variable) {
	// if a variable is a pointer, then add it to vector of pointers too
	if(variable->is_pointer()) {
		m_pointers.push_back(variable);
	}

	m_variables.push_back(variable);
}