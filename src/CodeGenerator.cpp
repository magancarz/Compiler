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
		
		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		#if CODE_GENERATOR_DEBUG 1
		writeCode("set up multiplication");
		#endif

		if(a->getName().empty()) {
			setValueToAccumulator(memory, aVal);
		} else {
			loadValueToAccumulator(memory, a);
		}
		storeValueFromAccumulator(memory, temp1Variable);
		storeValueFromAccumulator(memory, temp4Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(memory, bVal);
		} else {
			loadValueToAccumulator(memory, b);
		}
		storeValueFromAccumulator(memory, temp2Variable);
		storeValueFromAccumulator(memory, temp5Variable);

		// current power of 2
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, temp3Variable);

		// result
		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, temp6Variable);

		#if CODE_GENERATOR_DEBUG 1
		writeCode("start of the loop");
		#endif

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(memory, temp5Variable);
		subValueFromAccumulator(memory, temp3Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		#if CODE_GENERATOR_DEBUG 1
		writeCode("jump if current power of 2 >= remainding multiplier");
		#endif
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

		#if CODE_GENERATOR_DEBUG 1
		writeCode("check if current power of 2 > or == remainding multiplier");
		#endif

		loadValueToAccumulator(memory, temp3Variable);
		subValueFromAccumulator(memory, temp5Variable);

		unsigned int jumpVariable1 = m_commandPointer;
		writeCode("JZERO", jumpVariable1 + 18);

		#if CODE_GENERATOR_DEBUG 1
		writeCode("current power of 2 > remainding multiplier");
		#endif
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
		
		#if CODE_GENERATOR_DEBUG 1
		writeCode("current power of 2 == remainding multiplier");
		#endif
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
	unsigned int result = (bVal != 0)? aVal / bVal : 0;

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
		storeValueFromAccumulator(memory, temp1Variable);

		setValueToAccumulator(memory, zero);
		storeValueFromAccumulator(memory, resultVariable);
		
		loadValueToAccumulator(memory, temp1Variable);

		unsigned int startOfDividingLoop = m_commandPointer;

		subValueFromAccumulator(memory, b);
			
		// store the result
		storeValueFromAccumulator(memory, temp1Variable);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);

		loadValueToAccumulator(memory, temp1Variable);

		// check if accumulator is 0, if it is, then exit multiplication, if not, go back to startOfMultiplying position
		writeCode("JPOS", startOfDividingLoop);

		unsigned int endingJumpLocation = m_commandPointer;
		writeCode("JUMP", endingJumpLocation + 6);

		// checking if b > a
		loadValueToAccumulator(memory, b);
		subValueFromAccumulator(memory, temp1Variable);
		// return value if b > a
		setValueToAccumulator(memory, zero);

		unsigned int divisorBiggerThanDividendJump = m_commandPointer;
		writeCode("JPOS", divisorBiggerThanDividendJump + 2);

		// return value if a == b
		loadValueToAccumulator(memory, oneVariable);
	} else {
		// dividend
		Variable* temp1Variable = memory->getVariableFromMemory(1);
		
		Variable* temp2Variable = memory->getVariableFromMemory(2);
		Variable* temp3Variable = memory->getVariableFromMemory(3);
		
		Variable* resultVariable = memory->getVariableFromMemory(4);
		Variable* oneVariable = memory->getVariableFromMemory(5);
		
		//// checking a <= b case, if not, then jump to start of the division loop
		loadValueToAccumulator(memory, a);
		storeValueFromAccumulator(memory, temp1Variable);
		//subValueFromAccumulator(memory, b);

		//unsigned int agrtbJump = m_commandPointer;
		//writeCode("JPOS", agrtbJump + 6);

		//// checking if b > a, if it is, then jump to end of the division and assign 0 to the accumulator
		//loadValueToAccumulator(memory, b);
		//subValueFromAccumulator(memory, temp1Variable);
		//
		//unsigned int bgrtaJump = m_commandPointer;
		//writeCode("JPOS", bgrtaJump + 20);

		//// return value if a == b
		//loadValueToAccumulator(memory, oneVariable);
		//unsigned int aeqbJump = m_commandPointer;
		//writeCode("JUMP", aeqbJump + 19);

		// setup the division loop
		setValueToAccumulator(memory, 1);
		storeValueFromAccumulator(memory, resultVariable);

		unsigned int startOfDivisionLoop = m_commandPointer;

		loadValueToAccumulator(memory, temp1Variable);
		writeCode("HALF");
		storeValueFromAccumulator(memory, temp1Variable);

		// if rdividend is <= jump to step, where we can check if rdividend == divisor or rdividend < divisor
		subValueFromAccumulator(memory, b);
		unsigned int rdleqb = m_commandPointer;
		writeCode("JZERO", rdleqb + 4);

		// load multiplication count, subtract one from it and store it in temp1 variable
		loadValueToAccumulator(memory, resultVariable);
		addValueToAccumulator(memory, oneVariable);
		storeValueFromAccumulator(memory, resultVariable);

		// after HALF, rdividend is still bigger than divisor, so jump to start of the loop
		writeCode("JUMP", startOfDivisionLoop);

		//// return value if b == rdividend, if it is, then jump to the moment of the loop where result += 1
		//loadValueToAccumulator(memory, b);
		//subValueFromAccumulator(memory, temp1Variable);
		//unsigned int beqrdJump = m_commandPointer;
		//writeCode("JZERO", startOfDivisionLoop);

		//// checking if b > rdividend
		//loadValueToAccumulator(memory, resultVariable);
		//addValueToAccumulator(memory, oneVariable);
		//unsigned int bgrtrdJump = m_commandPointer;
		//writeCode("JUMP", bgrtrdJump + 2);

		//setValueToAccumulator(memory, zero);

		loadValueToAccumulator(memory, resultVariable);
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