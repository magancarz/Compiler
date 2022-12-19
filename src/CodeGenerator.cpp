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

std::string CodeGenerator::getCode() {
	std::stringstream code;
	for(std::string s : m_code) {
		code << s << "\n";
	}

	return code.str();
}