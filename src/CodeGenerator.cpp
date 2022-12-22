#include "CodeGenerator.h"

#include <sstream>
#include <iostream>

CodeGenerator::CodeGenerator(int argc, char** argv) {
	m_input = fopen(argv[1], "r");
    m_output = std::ofstream(argv[2]);

	// initialize temp variables
	writeCode("SET", 1);
	writeCode("STORE", 10);
}

CodeGenerator::~CodeGenerator() {
	fclose(m_input);
}

void CodeGenerator::writeCode(const std::string& code) {
	std::stringstream finalCode;
	#if CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 1
	finalCode << m_commandPointer << ". ";
	#endif
	finalCode << code;
	m_code.push_back(finalCode.str());

	m_commandPointer++;
}

void CodeGenerator::writeCode(const std::string& code, unsigned int value) {
	std::stringstream finalCode;
	#if CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 1
	finalCode << m_commandPointer << ". ";
	#endif
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
	} else {
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* temp4Variable = memory->getVariableFromMemory(4);
		Variable* temp5Variable = memory->getVariableFromMemory(5);
		Variable* temp6Variable = memory->getVariableFromMemory(6);
		Variable* oneVariable = memory->getVariableFromMemory(10);
		
		// set up required variables
		if(a->getName().empty()) {
			setValueToAccumulator(memory, aVal);
		} else {
			loadValueToAccumulator(memory, a);
		}
		storeValueFromAccumulator(memory, temp1Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(memory, bVal);
		} else {
			loadValueToAccumulator(memory, b);
		}
		storeValueFromAccumulator(memory, temp2Variable);

		subValueFromAccumulator(memory, temp1Variable);
		unsigned int jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 7);
		loadValueToAccumulator(memory, temp2Variable);
		storeValueFromAccumulator(memory, temp3Variable);
		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp2Variable);
		loadValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp1Variable);

		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		loadValueToAccumulator(memory, temp2Variable);
		storeValueFromAccumulator(memory, temp5Variable);
		// current power of 2
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);

		// result
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, temp6Variable);

		// check if multiplier is 0 or 1
		loadValueToAccumulator(memory, temp2Variable);
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 38);
		subValueFromAccumulator(memory, oneVariable);
		writeCode("JPOS", jumpVariable + 5);
		loadValueToAccumulator(memory, temp1Variable);
		writeCode("JUMP", jumpVariable + 38);

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp3Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		unsigned int jumpToCheckRelation = m_commandPointer;
		writeCode("JZERO", jumpToCheckRelation + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		loadValueToAccumulator(memory, temp3Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp4Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		// go back to the start of the loop
		writeCode("JUMP", startOfTheMultiplyLoop);

		loadValueToAccumulator(memory, temp3Variable);
		subValueFromAccumulator(memory, temp5Variable);

		unsigned int jumpVariable1 = m_commandPointer;
		writeCode("JZERO", jumpVariable1 + 18);

		loadValueToAccumulator(memory, temp3Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp3Variable);
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		loadValueToAccumulator(memory, temp4Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp4Variable);
		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp6Variable);

		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		writeCode("JUMP", startOfTheMultiplyLoop);
		
		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp6Variable);
	}

	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::div(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal % bVal : 0;

	unsigned int zero = 0;
	Variable* accumulator = memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(memory, result);
	} else {
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* temp4Variable = memory->getVariableFromMemory(4);
		Variable* temp5Variable = memory->getVariableFromMemory(5);
		Variable* temp6Variable = memory->getVariableFromMemory(6);
		Variable* oneVariable = memory->getVariableFromMemory(10);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->getName().empty()) {
			setValueToAccumulator(memory, aVal);
		} else {
			loadValueToAccumulator(memory, a);
		}
		storeValueFromAccumulator(memory, temp2Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(memory, bVal);
		} else {
			loadValueToAccumulator(memory, b);
		}
		storeValueFromAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);
		
		// current power of 2
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);
		
		// result
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, temp6Variable);

		// check if divisor is 0 or bigger than dividend
		loadValueToAccumulator(memory, temp1Variable);
		unsigned int jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 54);
		subValueFromAccumulator(memory, temp2Variable);
		writeCode("JPOS", jumpVariable + 54);

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		loadValueToAccumulator(memory, temp3Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp4Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		// go back to the start of the loop
		writeCode("JUMP", startOfTheMultiplyLoop);

		loadValueToAccumulator(memory, temp4Variable);
		subValueFromAccumulator(memory, temp5Variable);

		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 31);
		
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp6Variable);
		jumpVariable = m_commandPointer;
		writeCode("JUMP", jumpVariable + 31);

		unsigned int addToResultJumpPosition = m_commandPointer;
		loadValueToAccumulator(memory, temp4Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp4Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		loadValueToAccumulator(memory, temp3Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp3Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);
		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp6Variable);

		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		writeCode("JUMP", startOfTheMultiplyLoop);
		
		loadValueToAccumulator(memory, temp3Variable);
		subValueFromAccumulator(memory, oneVariable);
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 5);
		writeCode("JUMP", addToResultJumpPosition);

		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp6Variable);

		loadValueToAccumulator(memory, temp6Variable);
	}
	 
	std::string val = std::to_string(result);
	return new std::string(val);
}

std::string* CodeGenerator::mod(Memory* memory, Variable* a, Variable* b) {
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal % bVal : 0;

	unsigned int zero = 0;
	Variable* accumulator = memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(memory, result);
	} else {
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		Variable* temp4Variable = memory->getVariableFromMemory(4);
		Variable* temp5Variable = memory->getVariableFromMemory(5);
		Variable* temp6Variable = memory->getVariableFromMemory(6);
		Variable* oneVariable = memory->getVariableFromMemory(10);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->getName().empty()) {
			setValueToAccumulator(memory, aVal);
		} else {
			loadValueToAccumulator(memory, a);
		}
		storeValueFromAccumulator(memory, temp2Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(memory, bVal);
		} else {
			loadValueToAccumulator(memory, b);
		}
		storeValueFromAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);
		
		// current power of 2
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);
		
		// result
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, temp6Variable);

		// check if divisor is 0 or bigger than dividend
		loadValueToAccumulator(memory, temp1Variable);
		unsigned int jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 54);
		subValueFromAccumulator(memory, temp2Variable);
		writeCode("JPOS", jumpVariable + 54);

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		loadValueToAccumulator(memory, temp3Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp4Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		// go back to the start of the loop
		writeCode("JUMP", startOfTheMultiplyLoop);

		loadValueToAccumulator(memory, temp4Variable);
		subValueFromAccumulator(memory, temp5Variable);

		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 31);
		
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp6Variable);
		jumpVariable = m_commandPointer;
		writeCode("JUMP", jumpVariable + 31);

		unsigned int addToResultJumpPosition = m_commandPointer;
		loadValueToAccumulator(memory, temp4Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp4Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		loadValueToAccumulator(memory, temp3Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp3Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);
		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp3Variable);
		storeValueFromAccumulator(memory, temp6Variable);

		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);

		loadValueToAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		writeCode("JUMP", startOfTheMultiplyLoop);
		
		loadValueToAccumulator(memory, temp3Variable);
		subValueFromAccumulator(memory, oneVariable);
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 5);
		writeCode("JUMP", addToResultJumpPosition);

		loadValueToAccumulator(memory, temp6Variable);
		addValueToAccumulator(memory, temp4Variable);
		storeValueFromAccumulator(memory, temp6Variable);

		loadValueToAccumulator(memory, temp5Variable);
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