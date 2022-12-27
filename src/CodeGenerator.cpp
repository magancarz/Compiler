#include "CodeGenerator.h"

#include <sstream>
#include <iostream>

CodeGenerator::CodeGenerator(int argc, char** argv) {
	m_input = fopen(argv[1], "r");
    m_output = std::ofstream(argv[2]);

	// initialize temp variables
	writeCode("SET", 1);
	writeCode("STORE", 7);
}

CodeGenerator::~CodeGenerator() {
	fclose(m_input);
}

void CodeGenerator::setMemoryPointer(Memory* memory) {
	m_memory = memory;
}

void CodeGenerator::writeCode(const std::string& code) {
	std::stringstream finalCode;
	finalCode << code;
	m_code.push_back(finalCode.str());

	m_commandPointer++;
}

void CodeGenerator::writeCode(const std::string& code, unsigned int value) {
	std::stringstream finalCode;
	finalCode << code << " " << value;
	m_code.push_back(finalCode.str());

	m_commandPointer++;
}

void CodeGenerator::changeCode(unsigned int codePosition, const std::string& code) {
	std::stringstream finalCode;
	finalCode << code;
	m_code.at(codePosition) = finalCode.str();
}

void CodeGenerator::changeCode(unsigned int codePosition, const std::string& code, unsigned int value) {
	std::stringstream finalCode;
	finalCode << code << " " << value;
	m_code.at(codePosition) = finalCode.str();
}

unsigned int CodeGenerator::addValueToAccumulator(Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	Variable* accumulator = m_memory->getVariableFromMemory(0);
	accumulator->setValue(accumulator->getValue() + variable->getValue());

	writeCode("ADD", variable->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::subValueFromAccumulator(Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	Variable* accumulator = m_memory->getVariableFromMemory(0);
	accumulator->setValue(accumulator->getValue() - variable->getValue());

	writeCode("SUB", variable->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::loadValueToAccumulator(Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	unsigned int value = variable->getValue();
	m_memory->changeVariableValue(0, value);

	writeCode("LOAD", variable->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::setValueToAccumulator(Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	if(!variable->getName().empty()) {
		return loadValueToAccumulator(variable);
	}

	unsigned int value = variable->getValue();
	m_memory->changeVariableValue(0, value);
	
	writeCode("SET", value);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::setValueToAccumulator(unsigned int value) {
	unsigned int commandStart = m_commandPointer;

	m_memory->changeVariableValue(0, value);

	writeCode("SET", value);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::storeValueFromAccumulator(Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	Variable* accumulator = m_memory->getVariableFromMemory(0);
	variable->setValue(accumulator->getValue());

	writeCode("STORE", variable->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::storeValueFromAccumulatorToPointedVariable(Variable* pointer) {
	unsigned int commandStart = m_commandPointer;

	Variable* accumulator = m_memory->getVariableFromMemory(0);
	pointer->getPointedVariable()->setValue(accumulator->getValue());

	writeCode("STOREI", pointer->getPointedVariable()->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::assignValueToVariable(const std::string& name, const std::string& value) {
	unsigned int commandStart = m_commandPointer;

	if(!value.empty()) {
		unsigned int intValue = std::stoi(value);
		assignValueToVariable(name, intValue);
	} else {
		unsigned int intValue = 0;
		assignValueToVariable(name, intValue);
	}

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::assignValueToVariable(const std::string& name, unsigned int value) {
	unsigned int commandStart = m_commandPointer;

	m_memory->changeVariableValue(name, value);
	
	unsigned int variableMemoryPointer = m_memory->getVariable(name)->getMemoryPosition();
	writeCode("STORE", variableMemoryPointer);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::assignValueToVariable(const std::string& name, Variable* variable) {
	unsigned int commandStart = m_commandPointer;

	unsigned int value = variable->getValue();
	m_memory->changeVariableValue(name, value);
	unsigned int variableMemoryPointer = m_memory->getVariable(name)->getMemoryPosition();
	
	writeCode("STORE", variableMemoryPointer);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::divideAccumulatorByHalf() {
	unsigned int commandStart = m_commandPointer;

	Variable* accumulator = m_memory->getVariableFromMemory(0);
	accumulator->setValue(accumulator->getValue() / 2);

	writeCode("HALF");

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::generateInitialCodeForProcedure() {
	unsigned int commandStart = m_commandPointer;

	writeCode("JUMP", m_commandPointer);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::generateProcedureEndCode(Procedure* procedure) {
	unsigned int commandStart = m_commandPointer;
	
	procedure->setProcedureStartPoint(commandStart - procedure->getCodeSize());

	std::vector<Variable*>& procedureVariables = procedure->getProcedureVariables();
	for(Variable* variable : procedureVariables) {
		if(variable->isPointer()) {
			unsigned int pointedVariableMemoryPosition = variable->getPointedVariable()->getMemoryPosition();
			loadValueToAccumulator(variable);
			storeValueFromAccumulatorToPointedVariable(variable);
		}
	}

	writeCode("JUMPI", procedure->getProcedureVariables()[0]->getMemoryPosition());
	procedure->setProcedureEndingJumpPosition(procedure->getProcedureVariables()[0]->getMemoryPosition());
	
	changeCode(procedure->getProcedureStartPoint() - 1, "JUMP", m_commandPointer);
	
	return m_commandPointer - commandStart + procedure->getCodeSize();
}

unsigned int CodeGenerator::executeProcedure(const std::string& procedureName, const std::vector<Variable*>& procedureExecutionVariables) {
	unsigned int commandStart = m_commandPointer;
	
	Procedure* procedure = nullptr;
	std::vector<Procedure*>& procedures = m_memory->getProcedures();
	for(Procedure* proc : procedures) {
		if(proc->getName() == procedureName) {
			procedure = proc;
			break;
		}
	}

	if(procedure != nullptr) {
		std::vector<Variable*>* procedurePointers = procedure->getProcedurePointers();
		
		unsigned int i = 0;
		for(std::vector<Variable*>::iterator it = procedurePointers->begin(); it != procedurePointers->end(); it++) {
			Variable* pointer = *it;
			Variable* procExecVar = procedureExecutionVariables[i];
			setValueToAccumulator(procExecVar->getMemoryPosition());
			storeValueFromAccumulator(pointer->getPointedVariable());
			loadValueToAccumulator(procExecVar);
			storeValueFromAccumulator(pointer);
			
			i++;
		}
		
		setValueToAccumulator(m_commandPointer + 3);
		storeValueFromAccumulator(procedure->getProcedureVariables()[0]);

		writeCode("JUMP", procedure->getProcedureStartPoint());
		
	} else {
		printf("Procedure doesn't exist\n");
		exit(1);
	}

	m_memory->clearProcedureExecutionVariables();

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::ifCondition(Condition* condition, unsigned int commandsLength) {
	unsigned int commandStart = m_commandPointer;

	// change value of "if false" jump in condition's code
	std::string codeToChange = m_code.at(condition->jumpIfFalsePosition);
	std::istringstream iss(codeToChange);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		changeCode(condition->jumpIfFalsePosition, "JUMP", commandStart);
	} else if(starts == "JPOS") {
		changeCode(condition->jumpIfFalsePosition, "JPOS", commandStart);
	} else  {
		changeCode(condition->jumpIfFalsePosition, "JZERO", commandStart);
	}

	return m_commandPointer - commandStart + condition->conditionCodeSize;
}

unsigned int CodeGenerator::ifElseCondition(Condition* condition, unsigned int commands1Length, unsigned int commands2Length) {
	unsigned int commandStart = m_commandPointer;
	changeCode(commandStart - commands2Length - 1, "JUMP", commandStart);
	
	unsigned int commandIfFalseStart = m_commandPointer;

	std::string jumpIfFalseCodeToChange = m_code.at(condition->jumpIfFalsePosition);
	std::istringstream iss1(jumpIfFalseCodeToChange);
	std::string starts;
	iss1 >> starts;
	if(starts == "JUMP") {
		changeCode(condition->jumpIfFalsePosition, "JUMP", commandIfFalseStart - commands2Length);
	} else if(starts == "JPOS") {
		changeCode(condition->jumpIfFalsePosition, "JPOS", commandIfFalseStart - commands2Length);
	} else  {
		changeCode(condition->jumpIfFalsePosition, "JZERO", commandIfFalseStart - commands2Length);
	}

	return m_commandPointer - commandStart + condition->conditionCodeSize + 1;
}

unsigned int CodeGenerator::generateMiddleIfElseJump() {
	unsigned int commandStart = m_commandPointer;

	writeCode("JUMP", m_commandPointer);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::whileLoop(Condition* condition, unsigned int commandsLength) {
	unsigned int commandStart = m_commandPointer;

	writeCode("JUMP", commandStart - commandsLength - condition->conditionCodeSize);

	std::string codeToChange = m_code.at(condition->jumpIfFalsePosition);
	std::istringstream iss(codeToChange);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		changeCode(condition->jumpIfFalsePosition, "JUMP", m_commandPointer);
	} else if(starts == "JPOS") {
		changeCode(condition->jumpIfFalsePosition, "JPOS", m_commandPointer);
	} else  {
		changeCode(condition->jumpIfFalsePosition, "JZERO", m_commandPointer);
	}

	return m_commandPointer - commandStart + condition->conditionCodeSize;
}

unsigned int CodeGenerator::repeatUntilLoop(Condition* condition, unsigned int commandsLength) {
	unsigned int commandStart = m_commandPointer;

	std::string codeToChange = m_code.at(condition->jumpIfFalsePosition);
	std::istringstream iss(codeToChange);
	std::string starts;
	iss >> starts;
	if(starts == "JUMP") {
		changeCode(condition->jumpIfFalsePosition, "JUMP", m_commandPointer - commandsLength - condition->conditionCodeSize);
	} else if(starts == "JPOS") {
		changeCode(condition->jumpIfFalsePosition, "JPOS", m_commandPointer - commandsLength - condition->conditionCodeSize);
	} else  {
		changeCode(condition->jumpIfFalsePosition, "JZERO", m_commandPointer - commandsLength - condition->conditionCodeSize);
	}

	return m_commandPointer - commandStart + condition->conditionCodeSize;
}

unsigned int CodeGenerator::readValue(const std::string& variableName) {
	unsigned int commandStart = m_commandPointer;
	Variable* variable = m_memory->getVariable(variableName);

	writeCode("GET", variable->getMemoryPosition());

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::printOutValue(Variable* variable) {
	unsigned int commandStart = m_commandPointer;
	unsigned int variableMemoryPointer = variable->getMemoryPosition();
	
	if(variable->getName().empty()) {
		setValueToAccumulator(variable->getValue());
		writeCode("PUT", 0);
		return m_commandPointer - commandStart;
	}

	writeCode("PUT", variableMemoryPointer);

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::add(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = aVal + bVal;

	if(a->getName().empty() && b->getName().empty()) {
		Variable* accumulator = m_memory->getVariableFromMemory(0);
		setValueToAccumulator(result);

	} else if(a->getName().empty()) {
		setValueToAccumulator(a);
		addValueToAccumulator(b);

	} else if(b->getName().empty()) {
		setValueToAccumulator(b);
		addValueToAccumulator(a);

	} else {
		loadValueToAccumulator(a);
		addValueToAccumulator(b);

	}

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::sub(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;

	if(a->getName().empty() && b->getName().empty()) {
		unsigned int aVal = a->getValue();
		unsigned int bVal = b->getValue();
		unsigned int result = bVal > aVal ? 0 : aVal - bVal;

		Variable* accumulator = m_memory->getVariableFromMemory(0);
		setValueToAccumulator(result);

	} else if(a->getName().empty()) {
		setValueToAccumulator(a);
		subValueFromAccumulator(b);

	} else if(b->getName().empty()) {
		Variable* tempVariable = m_memory->getVariableFromMemory(1);
		tempVariable->setValue(b->getValue());
		setValueToAccumulator(tempVariable);
		storeValueFromAccumulator(tempVariable);
		loadValueToAccumulator(a);
		subValueFromAccumulator(tempVariable);

	} else {
		loadValueToAccumulator(a);
		subValueFromAccumulator(b);

	}

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::mul(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;

	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		unsigned int result = aVal * bVal;
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);
		Variable* temp3Variable = m_memory->getVariableFromMemory(3);
		Variable* temp4Variable = m_memory->getVariableFromMemory(4);
		Variable* temp5Variable = m_memory->getVariableFromMemory(5);
		Variable* temp6Variable = m_memory->getVariableFromMemory(6);
		Variable* oneVariable = m_memory->getVariableFromMemory(7);
		
		// set up required variables
		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
		} else {
			loadValueToAccumulator(a);
		}
		storeValueFromAccumulator(temp1Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
		} else {
			loadValueToAccumulator(b);
		}
		storeValueFromAccumulator(temp2Variable);

		setValueToAccumulator(zero);
		storeValueFromAccumulator(temp3Variable);

		unsigned int startOfTheLoop = m_commandPointer;
		loadValueToAccumulator(temp2Variable);
		writeCode("JZERO", m_commandPointer + 24);

		// check if Y is odd
		subValueFromAccumulator(oneVariable);
		writeCode("JZERO", m_commandPointer + 19);

		loadValueToAccumulator(temp2Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp4Variable);
		addValueToAccumulator(temp4Variable);
		storeValueFromAccumulator(temp4Variable);
		loadValueToAccumulator(temp2Variable);
		subValueFromAccumulator(temp4Variable);
		writeCode("JZERO", m_commandPointer + 4);

		//if Y is odd, then add X to the result
		loadValueToAccumulator(temp3Variable);
		addValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp1Variable);
		addValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp1Variable);

		loadValueToAccumulator(temp2Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp2Variable);
		writeCode("JUMP", startOfTheLoop);

		loadValueToAccumulator(temp3Variable);
		addValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp3Variable);
	}

	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::div(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal % bVal : 0;

	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);
		Variable* temp3Variable = m_memory->getVariableFromMemory(3);
		Variable* temp4Variable = m_memory->getVariableFromMemory(4);
		Variable* temp5Variable = m_memory->getVariableFromMemory(5);
		Variable* temp6Variable = m_memory->getVariableFromMemory(6);
		Variable* oneVariable = m_memory->getVariableFromMemory(7);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
		} else {
			loadValueToAccumulator(a);
		}
		storeValueFromAccumulator(temp2Variable);
		storeValueFromAccumulator(temp5Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
		} else {
			loadValueToAccumulator(b);
		}
		storeValueFromAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);
		
		// current power of 2
		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);
		
		// result
		setValueToAccumulator(zero);
		storeValueFromAccumulator(temp6Variable);

		// check if divisor is 0 or bigger than dividend
		loadValueToAccumulator(temp1Variable);
		unsigned int jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 54);
		subValueFromAccumulator(temp2Variable);
		writeCode("JZERO", jumpVariable + 5);
		setValueToAccumulator(zero);
		writeCode("JUMP", jumpVariable + 54);

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		loadValueToAccumulator(temp3Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp4Variable);
		addValueToAccumulator(temp4Variable);
		storeValueFromAccumulator(temp4Variable);

		// go back to the start of the loop
		writeCode("JUMP", startOfTheMultiplyLoop);

		loadValueToAccumulator(temp4Variable);
		subValueFromAccumulator(temp5Variable);

		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 31);
		
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		storeValueFromAccumulator(temp5Variable);

		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp6Variable);
		jumpVariable = m_commandPointer;
		writeCode("JUMP", jumpVariable + 31);

		unsigned int addToResultJumpPosition = m_commandPointer;
		loadValueToAccumulator(temp4Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp4Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		loadValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		storeValueFromAccumulator(temp5Variable);

		loadValueToAccumulator(temp3Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp3Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);
		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp6Variable);

		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);

		writeCode("JUMP", startOfTheMultiplyLoop);
		
		loadValueToAccumulator(temp3Variable);
		subValueFromAccumulator(oneVariable);
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 5);
		writeCode("JUMP", addToResultJumpPosition);

		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp4Variable);
		storeValueFromAccumulator(temp6Variable);

		loadValueToAccumulator(temp6Variable);
	}
	 
	return m_commandPointer - commandStart;
}

unsigned int CodeGenerator::mod(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (bVal != 0)? aVal % bVal : 0;

	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);
		Variable* temp3Variable = m_memory->getVariableFromMemory(3);
		Variable* temp4Variable = m_memory->getVariableFromMemory(4);
		Variable* temp5Variable = m_memory->getVariableFromMemory(5);
		Variable* temp6Variable = m_memory->getVariableFromMemory(6);
		Variable* oneVariable = m_memory->getVariableFromMemory(7);

		// set up required variables
		// multiplicand and current power of 2 multiplicand equivalent
		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
		} else {
			loadValueToAccumulator(a);
		}
		storeValueFromAccumulator(temp2Variable);
		storeValueFromAccumulator(temp5Variable);

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
		} else {
			loadValueToAccumulator(b);
		}
		storeValueFromAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);
		
		// current power of 2
		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);
		
		// result
		setValueToAccumulator(zero);
		storeValueFromAccumulator(temp6Variable);

		// check if divisor is 0 or bigger than dividend
		loadValueToAccumulator(temp1Variable);
		unsigned int jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 54);
		subValueFromAccumulator(temp2Variable);
		writeCode("JZERO", jumpVariable + 5);
		loadValueToAccumulator(temp2Variable);
		writeCode("JPOS", jumpVariable + 54);

		// start of the loop
		unsigned int startOfTheMultiplyLoop = m_commandPointer;

		// check if current value >= remainding multiplier
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		
		// jump to position where we can check if value > or == remainding multiplier
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 8);

		// multiply by 2 current power of 2 and it's multiplicand equivalent 
		loadValueToAccumulator(temp3Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp4Variable);
		addValueToAccumulator(temp4Variable);
		storeValueFromAccumulator(temp4Variable);

		// go back to the start of the loop
		writeCode("JUMP", startOfTheMultiplyLoop);

		loadValueToAccumulator(temp4Variable);
		subValueFromAccumulator(temp5Variable);

		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 31);
		
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		storeValueFromAccumulator(temp5Variable);

		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp6Variable);
		jumpVariable = m_commandPointer;
		writeCode("JUMP", jumpVariable + 31);

		unsigned int addToResultJumpPosition = m_commandPointer;
		loadValueToAccumulator(temp4Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp4Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		loadValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);
		loadValueToAccumulator(temp5Variable);
		subValueFromAccumulator(temp4Variable);
		storeValueFromAccumulator(temp5Variable);

		loadValueToAccumulator(temp3Variable);
		divideAccumulatorByHalf();
		storeValueFromAccumulator(temp3Variable);
		jumpVariable = m_commandPointer;
		writeCode("JPOS", jumpVariable + 3);
		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);
		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp3Variable);
		storeValueFromAccumulator(temp6Variable);

		setValueToAccumulator(1);
		storeValueFromAccumulator(temp3Variable);

		loadValueToAccumulator(temp1Variable);
		storeValueFromAccumulator(temp4Variable);

		writeCode("JUMP", startOfTheMultiplyLoop);
		
		loadValueToAccumulator(temp3Variable);
		subValueFromAccumulator(oneVariable);
		jumpVariable = m_commandPointer;
		writeCode("JZERO", jumpVariable + 5);
		writeCode("JUMP", addToResultJumpPosition);

		loadValueToAccumulator(temp6Variable);
		addValueToAccumulator(temp4Variable);
		storeValueFromAccumulator(temp6Variable);

		loadValueToAccumulator(temp5Variable);
	}

	return m_commandPointer - commandStart;
}

Condition* CodeGenerator::equal(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal == bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition, jumpIfFalsePosition2, jumpIfTruePosition;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
			storeValueFromAccumulator(temp1Variable);
		} else {
			loadValueToAccumulator(a);
			storeValueFromAccumulator(temp1Variable);
		}

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
			storeValueFromAccumulator(temp2Variable);
		} else {
			loadValueToAccumulator(b);
			storeValueFromAccumulator(temp2Variable);
		}

		subValueFromAccumulator(temp1Variable);
		writeCode("JPOS", m_commandPointer + 5);

		loadValueToAccumulator(temp1Variable);
		subValueFromAccumulator(temp2Variable);
		
		writeCode("JPOS", m_commandPointer + 2);
		
		jumpIfTruePosition = m_commandPointer;
		writeCode("JUMP", jumpIfTruePosition + 2);
		
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JUMP", jumpIfFalsePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

Condition* CodeGenerator::nequal(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal != bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition, jumpIfTruePosition;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
			storeValueFromAccumulator(temp1Variable);
		} else {
			loadValueToAccumulator(a);
			storeValueFromAccumulator(temp1Variable);
		}

		// multiplier and remainder of multiplier
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
			storeValueFromAccumulator(temp2Variable);
		} else {
			loadValueToAccumulator(b);
			storeValueFromAccumulator(temp2Variable);
		}

		subValueFromAccumulator(temp1Variable);
		writeCode("JPOS", m_commandPointer + 4);

		loadValueToAccumulator(temp1Variable);
		subValueFromAccumulator(temp2Variable);
		jumpIfTruePosition = m_commandPointer;
		writeCode("JPOS", jumpIfTruePosition + 2);
		
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JUMP", jumpIfFalsePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

Condition* CodeGenerator::greater(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal > bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition, jumpIfTruePosition;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
			storeValueFromAccumulator(temp2Variable);
		} else {
			loadValueToAccumulator(b);
			storeValueFromAccumulator(temp2Variable);
		}

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
		} else {
			loadValueToAccumulator(a);
		}

		subValueFromAccumulator(temp2Variable);
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JZERO", jumpIfFalsePosition + 2);
		jumpIfTruePosition = m_commandPointer;
		writeCode("JUMP", jumpIfTruePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

Condition* CodeGenerator::less(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal < bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition, jumpIfTruePosition;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
			storeValueFromAccumulator(temp2Variable);
		} else {
			loadValueToAccumulator(a);
			storeValueFromAccumulator(temp2Variable);
		}

		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
		} else {
			loadValueToAccumulator(b);
		}

		subValueFromAccumulator(temp2Variable);
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JZERO", jumpIfFalsePosition + 2);
		jumpIfTruePosition = m_commandPointer;
		writeCode("JUMP", jumpIfTruePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

Condition* CodeGenerator::greq(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal >= bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition, jumpIfTruePosition;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
			storeValueFromAccumulator(temp1Variable);
		} else {
			loadValueToAccumulator(a);
			storeValueFromAccumulator(temp1Variable);
		}
		
		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
		} else {
			loadValueToAccumulator(b);
		}
		
		subValueFromAccumulator(temp1Variable);
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JPOS", jumpIfFalsePosition + 2);
		jumpIfTruePosition = m_commandPointer;
		writeCode("JUMP", jumpIfTruePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

Condition* CodeGenerator::leq(Variable* a, Variable* b) {
	unsigned int commandStart = m_commandPointer;
	unsigned int aVal = a->getValue();
	unsigned int bVal = b->getValue();
	unsigned int result = (aVal >= bVal)? 1 : 0;

	unsigned int jumpIfFalsePosition = 0, jumpIfTruePosition = 0;
	unsigned int zero = 0;
	Variable* accumulator = m_memory->getVariableFromMemory(0);
	if(a->getName().empty() && b->getName().empty()) {
		setValueToAccumulator(result);
	} else {
		Variable* temp1Variable = m_memory->getVariableFromMemory(1);
		Variable* temp2Variable = m_memory->getVariableFromMemory(2);

		if(b->getName().empty()) {
			setValueToAccumulator(bVal);
			storeValueFromAccumulator(temp2Variable);
		} else {
			loadValueToAccumulator(b);
			storeValueFromAccumulator(temp2Variable);
		}

		if(a->getName().empty()) {
			setValueToAccumulator(aVal);
		} else {
			loadValueToAccumulator(a);
		}
		
		subValueFromAccumulator(temp2Variable);
		jumpIfFalsePosition = m_commandPointer;
		writeCode("JPOS", jumpIfFalsePosition + 2);
		jumpIfTruePosition = m_commandPointer;
		writeCode("JUMP", jumpIfTruePosition + 1);
	}

	Condition* condition = new Condition{m_commandPointer - commandStart, jumpIfTruePosition, jumpIfFalsePosition};
	return condition;
}

std::string CodeGenerator::getCode() {
	std::stringstream code;
	unsigned int i = 0;
	for(std::string s : m_code) {
		#if CODE_GENERATOR_DEBUG_COMMAND_LINES_NO 1
		code << i << ". ";
		#endif
		code << s << "\n";
		i++;
	}

	return code.str();
}