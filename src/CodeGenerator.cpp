#include "CodeGenerator.h"

#include <sstream>
#include <iostream>

CodeGenerator::CodeGenerator(int argc, char** argv) {
	m_input = fopen(argv[1], "r");
    m_output = std::ofstream(argv[2]);
}

CodeGenerator::~CodeGenerator() {
	fclose(m_input);
}

void CodeGenerator::writeCode(const std::string& code) {
	m_code.push_back(code);
}

void CodeGenerator::writeCode(const std::string& code, unsigned int value) {
	std::stringstream finalCode;
	finalCode << code << " " << value;
	m_code.push_back(finalCode.str());
}

void CodeGenerator::addValueToAccumulator(Memory* memory, Variable* variable) {
	Variable* accumulator = memory->getVariableFromMemory(0);
	accumulator->setValue(accumulator->getValue() + variable->getValue());

	writeCode("ADD", variable->getMemoryPosition());
}

void CodeGenerator::subValueFromAccumulator(Memory* memory, Variable* variable) {
	Variable* accumulator = memory->getVariableFromMemory(0);
	accumulator->setValue(accumulator->getValue() - variable->getValue());

	writeCode("SUB", variable->getMemoryPosition());
}

std::string* CodeGenerator::loadValueToAccumulator(Memory* memory, Variable* variable) {
	unsigned int value = variable->getValue();
	memory->changeVariableValue(0, value);

	writeCode("LOAD", variable->getMemoryPosition());	
	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d to accumulator.\n", value);
	#endif

	std::string val = std::to_string(value);
	return new std::string(val);
}

std::string* CodeGenerator::setValueToAccumulator(Memory* memory, Variable* variable) {
	unsigned int value = variable->getValue();
	memory->changeVariableValue(0, value);

	writeCode("SET", value);	
	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d to accumulator.\n", value);
	#endif

	std::string val = std::to_string(value);
	return new std::string(val);
}

std::string* CodeGenerator::setValueToAccumulator(Memory* memory, unsigned int value) {
	memory->changeVariableValue(0, value);

	writeCode("SET", value);	
	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d to accumulator.\n", value);
	#endif

	std::string val = std::to_string(value);
	return new std::string(val);
}

void CodeGenerator::assignValueToVariable(Memory* memory, const std::string& name, const std::string& value) {
	if(!value.empty()) {
		unsigned int intValue = std::stoi(value);
		assignValueToVariable(memory, name, intValue);
	} else {
		unsigned int val = 0;
		assignValueToVariable(memory, name, val);
	}
}

void CodeGenerator::assignValueToVariable(Memory* memory, const std::string& name, unsigned int value) {
	memory->changeVariableValue(name, value);
	
	unsigned int variableMemoryPointer = memory->getVariable(name)->getMemoryPosition();
	writeCode("STORE", variableMemoryPointer);
	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d to the variable named %s.\n", value, name.c_str());
	#endif
}

void CodeGenerator::assignValueToVariable(Memory* memory, const std::string& name, Variable* variable) {
	unsigned int value = variable->getValue();
	memory->changeVariableValue(name, value);
	unsigned int variableMemoryPointer = memory->getVariable(name)->getMemoryPosition();
	
	writeCode("STORE", variableMemoryPointer);
	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d to the variable named %s.\n", value, name.c_str());
	#endif
}

void CodeGenerator::readValue(Memory* memory, const std::string& variableName) {
	Variable* variable = memory->getVariable(variableName);

	writeCode("READ", variable->getMemoryPosition());
}

void CodeGenerator::printOutValue(Memory* memory, Variable* variable) {
	unsigned int variableMemoryPointer = variable->getMemoryPosition();
	
	writeCode("PUT", variableMemoryPointer);
	#if CODE_GENERATOR_DEBUG 1
	printf("Printing out value assigned to variable %s", variable->getName().c_str());
	#endif
}

std::string* CodeGenerator::add(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = 0;
	unsigned int bVal = 0;
	unsigned int result = aVal + bVal;

	if(a->getName().empty() && b->getName().empty()) {
		Variable* accumulator = memory->getVariableFromMemory(0);
		setValueToAccumulator(memory, result);
	} else if(a->getName().empty()) {
		setValueToAccumulator(memory, a);
		addValueToAccumulator(memory, b);
	} else if(b->getName().empty()) {
		setValueToAccumulator(memory, b);
		addValueToAccumulator(memory, a);
	} else {
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);
	}

	std::string val = std::to_string(aVal + bVal);
	return new std::string(val);
}

std::string* CodeGenerator::sub(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = bVal > aVal ? 0 : aVal - bVal;

	if(a->getName().empty() && b->getName().empty()) {
		Variable* accumulator = memory->getVariableFromMemory(0);
		setValueToAccumulator(memory, result);
	} else if(a->getName().empty()) {
		setValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);
	} else if(b->getName().empty()) {
		Variable* tempVariable = memory->getVariableFromMemory(1);
		tempVariable->setValue(b->getValue());
		setValueToAccumulator(memory, tempVariable);
		writeCode("STORE", 1);
		setValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, tempVariable);
	} else {
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::mul(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = aVal * bVal;

	if(!a->getName().empty() && !b->getName().empty()) {
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);

	} else {
		Variable* accumulator = memory->getVariableFromMemory(0);
		setValueToAccumulator(memory, result);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::div(Memory* memory, Variable* a, Variable* b) {
	std::string str = "0";
	return &str;
}

std::string* CodeGenerator::mod(Memory* memory, Variable* a, Variable* b) {
	std::string str = "0";
	return &str;
}

std::string CodeGenerator::getCode() {
	std::stringstream code;
	for(std::string s : m_code) {
		code << s << "\n";
	}

	return code.str();
}