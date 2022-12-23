#include "Procedure.h"

Procedure::Procedure() {

}

Procedure::~Procedure() {
	delete m_variables;
}

std::vector<Variable*>* Procedure::getProcedurePointers() {
	std::vector<Variable*>* pointers = new std::vector<Variable*>();

	for(std::vector<Variable*>::iterator it = m_variables->begin(); it != m_variables->end(); it++) {
		Variable* variable = *it;
		if(variable->isPointer()) {
			pointers->push_back(variable);
		}
	}

	return pointers;
}