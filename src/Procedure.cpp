#include "Procedure.h"

void Procedure::add_variable(Variable* variable) {
	if(variable->is_pointer()) {
		m_pointers.push_back(variable);
	}

	m_variables.push_back(variable);
}