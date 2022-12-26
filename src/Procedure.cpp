#include "Procedure.h"

Procedure::Procedure() {

}

Procedure::~Procedure() {

}

std::vector<Variable*>* Procedure::getProcedurePointers() {
	std::vector<Variable*>* pointers = new std::vector<Variable*>();

	for(Variable* variable : m_variables) {
		if(variable->isPointer()) {
			pointers->push_back(variable);
		}
	}

	return pointers;
}