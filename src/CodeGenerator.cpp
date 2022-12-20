#include "CodeGenerator.h"

#include <sstream>
#include <iostream>

CodeGenerator::CodeGenerator(int argc, char** argv) {
	m_input = fopen(argv[1], "r");
    m_output = std::ofstream(argv[2]);

	// initialize temp variables
	writeCode("SET", 1);
	writeCode("STORE", 5);
}

CodeGenerator::~CodeGenerator() {
	fclose(m_input);
}

void CodeGenerator::writeCode(const std::string& code) {
	m_code.push_back(code);
	m_commandPointer++;
}

void CodeGenerator::writeCode(const std::string& code, unsigned int value) {
	std::stringstream finalCode;
	finalCode << code << " " << value;
	m_code.push_back(finalCode.str());

	m_commandPointer++;
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

void CodeGenerator::storeValueFromAccumulator(Memory* memory, Variable* variable) {
	Variable* accumulator = memory->getVariableFromMemory(0);
	variable->setValue(accumulator->getValue());

	writeCode("STORE", variable->getMemoryPosition());

	#if CODE_GENERATOR_DEBUG 1
	printf("Assigned value %d from accumulator to the variable named %s at position %d.\n",
		accumulator->getValue().c_str(), variable->getName().c_str(), variable->getMemoryPosition());
	#endif
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
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
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
		addValueToAccumulator(memory, b);
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
		loadValueToAccumulator(memory, a);
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
	

	unsigned int zero = 0;
	Variable* accumulator = memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(memory, result);
	} else if(a->getName().empty() || b->getName().empty()) {
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* resultVariable = memory->getVariableFromMemory(4);
		Variable* oneVariable = memory->getVariableFromMemory(5);
		
		if(a->getName().empty()) {
			setValueToAccumulator(memory, a->getValue());
			storeValueFromAccumulator(memory, temp1Variable);
			a = temp1Variable;
			loadValueToAccumulator(memory, b);
			storeValueFromAccumulator(memory, temp2Variable);
		} else {
			loadValueToAccumulator(memory, a);
			storeValueFromAccumulator(memory, temp1Variable);
			setValueToAccumulator(memory, b->getValue());
			storeValueFromAccumulator(memory, temp2Variable);
			b = temp2Variable;
		}
		
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);

		unsigned int startOfMultiplying = m_commandPointer;

		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, temp1Variable);
			
		// store the result
		storeValueFromAccumulator(memory, resultVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, temp2Variable);
		subValueFromAccumulator(memory, oneVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfMultiplying);

		loadValueToAccumulator(memory, resultVariable);
	} else {
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* resultVariable = memory->getVariableFromMemory(4);
		Variable* oneVariable = memory->getVariableFromMemory(5);
		
		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, temp1Variable);
		setValueToAccumulator(memory, b);
		storeValueFromAccumulator(memory, temp2Variable);
		
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);

		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, oneVariable);

		unsigned int startOfMultiplying = m_commandPointer;

		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, temp1Variable);
			
		// store the result
		storeValueFromAccumulator(memory, resultVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, temp2Variable);
		subValueFromAccumulator(memory, oneVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfMultiplying);

		loadValueToAccumulator(memory, resultVariable);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::div(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal / bVal : 0;

	unsigned int zero = 0;
	// check extreme cases
	if(aVal == 0 || bVal == 0) {
		setValueToAccumulator(memory, zero);

		std::string val = std::to_string(result);
		return new std::string(val);
	} else if(aVal == 1 || bVal == 1) {
		Variable* resultVar = (aVal == 1) ? b : a;
		loadValueToAccumulator(memory, resultVar);

		std::string val = std::to_string(result);
		return new std::string(val);
	}

	Variable* accumulator = memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(memory, result);
	} else if(a->getName().empty() || b->getName().empty()) {
		Variable* tempVariable = memory->getVariableFromMemory(1);
		Variable* resultVariable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* oneVariable = memory->getVariableFromMemory(4);
		
		if(a->getName().empty()) {
			setValueToAccumulator(memory, a->getValue());
			storeValueFromAccumulator(memory, tempVariable);
			a = tempVariable;
		} else {
			setValueToAccumulator(memory, b->getValue());
			storeValueFromAccumulator(memory, temp3Variable);
			b = temp3Variable;
		}

		// checking a <= b case
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);

		unsigned int divideActionStart = m_commandPointer;
		writeCode("JZERO", divideActionStart + 13);

		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, tempVariable);

		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);
		
		loadValueToAccumulator(memory, tempVariable);

		unsigned int startOfDividingLoop = m_commandPointer;

		subValueFromAccumulator(memory, b);
			
		// store the result
		storeValueFromAccumulator(memory, tempVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);

		loadValueToAccumulator(memory, tempVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfDividingLoop);

		unsigned int endingJumpLocation = m_commandPointer;
		writeCode("JUMP", endingJumpLocation + 6);

		// checking if b > a
		loadValueToAccumulator(memory, b);
		subValueFromAccumulator(memory, a);
		// return value if b > a
		setValueToAccumulator(memory, zero);

		unsigned int divisorBiggerThanDividendJump = m_commandPointer;
		writeCode("JPOS", divisorBiggerThanDividendJump + 2);

		// return value if a == b
		loadValueToAccumulator(memory, oneVariable);
	} else {
		Variable* tempVariable = memory->getVariableFromMemory(1);
		Variable* resultVariable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* oneVariable = memory->getVariableFromMemory(4);
		Variable* temp5Variable = memory->getVariableFromMemory(5);
		
		// checking a <= b case
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);

		unsigned int divideActionStart = m_commandPointer;
		writeCode("JZERO", divideActionStart + 13);

		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, tempVariable);

		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);
		
		loadValueToAccumulator(memory, tempVariable);

		unsigned int startOfDividingLoop = m_commandPointer;

		subValueFromAccumulator(memory, b);
			
		// store the result
		storeValueFromAccumulator(memory, tempVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);

		loadValueToAccumulator(memory, tempVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfDividingLoop);

		unsigned int endingJumpLocation = m_commandPointer;
		writeCode("JUMP", endingJumpLocation + 6);

		// checking if b > a
		loadValueToAccumulator(memory, b);
		subValueFromAccumulator(memory, a);
		// return value if b > a
		setValueToAccumulator(memory, zero);

		unsigned int divisorBiggerThanDividendJump = m_commandPointer;
		writeCode("JPOS", divisorBiggerThanDividendJump + 2);

		// return value if a == b
		loadValueToAccumulator(memory, oneVariable);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::mod(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal % bVal : 0;
	

	unsigned int zero = 0;
	// check extreme cases
	if(aVal == 0 || bVal == 0) {
		setValueToAccumulator(memory, zero);

		std::string val = std::to_string(result);
		return new std::string(val);
	} else if(aVal == 1 || bVal == 1) {
		setValueToAccumulator(memory, zero);

		std::string val = std::to_string(result);
		return new std::string(val);
	}

	Variable* accumulator = memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(memory, result);
	} else if(a->getName().empty() || b->getName().empty()) {
		Variable* tempVariable = memory->getVariableFromMemory(1);
		Variable* resultVariable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* oneVariable = memory->getVariableFromMemory(4);
		
		if(a->getName().empty()) {
			setValueToAccumulator(memory, a->getValue());
			storeValueFromAccumulator(memory, tempVariable);
			a = tempVariable;
		} else {
			setValueToAccumulator(memory, b->getValue());
			storeValueFromAccumulator(memory, temp3Variable);
			b = temp3Variable;
		}

		// checking a <= b case
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);

		unsigned int divideActionStart = m_commandPointer;
		writeCode("JZERO", divideActionStart + 13);

		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, tempVariable);
		storeValueFromAccumulator(memory, tempVariable);


		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);
		
		loadValueToAccumulator(memory, tempVariable);

		unsigned int startOfDividingLoop = m_commandPointer;

		subValueFromAccumulator(memory, b);
			
		// store the result
		storeValueFromAccumulator(memory, tempVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);

		loadValueToAccumulator(memory, tempVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfDividingLoop);

		unsigned int endingJumpLocation = m_commandPointer;
		writeCode("JUMP", endingJumpLocation + 2);

		// return value if b > a
		setValueToAccumulator(memory, zero);

	} else {
		Variable* tempVariable = memory->getVariableFromMemory(1);
		Variable* resultVariable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* oneVariable = memory->getVariableFromMemory(4);
		Variable* temp5Variable = memory->getVariableFromMemory(5);
		
		// checking a <= b case
		loadValueToAccumulator(memory, a);
		subValueFromAccumulator(memory, b);

		unsigned int divideActionStart = m_commandPointer;
		writeCode("JZERO", divideActionStart + 13);

		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, tempVariable);

		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);
		
		loadValueToAccumulator(memory, tempVariable);

		unsigned int startOfDividingLoop = m_commandPointer;

		subValueFromAccumulator(memory, b);
			
		// store the result
		storeValueFromAccumulator(memory, tempVariable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);

		loadValueToAccumulator(memory, tempVariable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfDividingLoop);

		unsigned int endingJumpLocation = m_commandPointer;
		writeCode("JUMP", endingJumpLocation + 6);

		// checking if b > a
		loadValueToAccumulator(memory, b);
		subValueFromAccumulator(memory, a);
		// return value if b > a
		setValueToAccumulator(memory, zero);

		unsigned int divisorBiggerThanDividendJump = m_commandPointer;
		writeCode("JPOS", divisorBiggerThanDividendJump + 2);

		// return value if a == b
		loadValueToAccumulator(memory, oneVariable);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string CodeGenerator::getCode() {
	std::stringstream code;
	for(std::string s : m_code) {
		code << s << "\n";
	}

	return code.str();
}