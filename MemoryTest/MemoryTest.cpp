#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include "../../Compiler/src/memory/Memory.h"
#include "../../Compiler/src/memory/Memory.cpp"
#include "../../Compiler/src/variables/Variable.h"
#include "../../Compiler/src/variables/Variable.cpp"
#include "../../Compiler/src/codeGenerator/Procedure.h"
#include "../../Compiler/src/codeGenerator/Procedure.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MemoryTest {
	TEST_CLASS(MemoryTest) {
	public:
		
		TEST_METHOD(MemoryVariablesTest) {
			// we expect variable at position 17 to have these values
			constexpr int expected_variable_memory_position = 17;
			const std::string expected_variable_value = "20";
			const std::string expected_variable_name = "temp15";

			const std::string expected_named_variable_memory_position = "18";

			// test memory
			Memory test_memory;
			test_memory.add_variable_to_memory(0);
			test_memory.add_variable_to_memory(5);
			test_memory.add_variable_to_memory(2);

			test_memory.add_new_procedure();
			test_memory.add_procedure_pointer_variable_to_memory("temp1", test_memory.get_variable_from_memory(5));
			test_memory.set_identifier_to_current_procedure("procedure1");
			test_memory.finish_procedure(0);

			test_memory.add_variable_to_memory(100);
			test_memory.add_variable_to_memory("temp3", 15);

			test_memory.add_new_procedure();
			test_memory.add_procedure_variable_to_memory("a");
			test_memory.set_identifier_to_current_procedure("procedure2");
			test_memory.finish_procedure(0);

			// expected variable
			test_memory.add_variable_to_memory("temp15", 20);

			test_memory.add_variable_to_memory("temp123", 4);

			test_memory.add_variable_to_memory(5);
			test_memory.add_variable_to_memory(2);
			
			test_memory.add_new_procedure();
			test_memory.add_procedure_pointer_variable_to_memory("temp19", test_memory.get_variable_from_memory(10));
			test_memory.set_identifier_to_current_procedure("procedure3");
			test_memory.finish_procedure(0);

			test_memory.add_variable_to_memory(100);
			test_memory.add_variable_to_memory("temp100", 15);

			test_memory.add_new_procedure();
			test_memory.add_procedure_variable_to_memory("b");
			test_memory.set_identifier_to_current_procedure("procedure4");
			test_memory.finish_procedure(0);

			// get variable at position 17 and check the result
			const auto var = test_memory.get_variable_from_memory(expected_variable_memory_position);
			const std::string value_result = std::to_string(var->get_value());

			Assert::AreEqual(expected_variable_name, var->get_name());
			Assert::AreEqual(expected_variable_value, value_result);

			// check if variable named temp100 exists
			Assert::AreEqual(true, test_memory.check_if_variable_exists("temp100"));

			// check if procedure named procedure2 exists
			Assert::AreEqual(true, test_memory.check_if_procedure_exists("procedure2"));
		}
	};
}