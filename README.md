# Compiler of a simple imperative language
## Description
A program that compiles an imperative language into virtual machine code. More detailed language and machine specifications are included in the labor4.pdf file with some example code. The compiler is written in C++ and uses Flex and Bison. I also added some unit tests for memory management of the virtual machine prototype in my code and test written in bash that checks if the output for the test files is correct.

## Language specification

Quick tour through language specification:
- arithmetic operations are performed on natural numbers. The result of subtracting a larger number from a smaller one is 0. In addition, dividing by zero should give a result 0 and the remainder is also 0,
- language includes implementation of procedures: procedures cannot contain recursive calls, formal parameters are passed through references (IN-OUT), variables used in a procedure must be it's formal parameters or be declared inside the procedure, only procedures defined earlier in the program code can be called in a procedure, other procedures can be called only with variables defined in the current procedure,
- you can use IF and IF ELSE conditions, WHILE and REPEAT UNTIL loops, 
- REPEAT UNTIL breaks when the condition is met and the loop will execute at least once,
- instruction READ takes the input from the user and assigns it to the specified variable and WRITE command prints out variable or constant value,
- variables and procedures identifiers are described by the regular expression [_a-z]+,
- lowercase and uppercase letters are distinguished,
- you can use [comments] in the code, which cannot be nested,
More on the grammar of the language in the labor4.pdf file.

Example code:
```
PROCEDURE swap(a,b) IS
VAR c
BEGIN
  c:=a;
  a:=b;
  b:=c;
END

PROCEDURE gcd(a,b,c) IS
VAR x,y
BEGIN
  x:=a;
  y:=b;
  WHILE y!=0 DO
    IF x>=y THEN 
      x:=x-y;
    ELSE 
      swap(x,y);
    ENDIF
  ENDWHILE
  c:=x;
END

PROGRAM IS
VAR a,b,c,d,x,y,z
BEGIN
  READ a;
  READ b;
  READ c;
  READ d;
  gcd(a,b,x);
  gcd(c,d,y);
  gcd(x,y,z);
  WRITE z;
END
```

## How to run the project
 To use the project, you need to run the Makefile for the compiler and the virtual machine (which are located in the main folder and the virtual-machine/), then write some code, save it in ie. "test_file", run the compiler with `./kompilator {test_file} {output_file}` which will generate machine code to the output file and the last step is to run the virtual machine with `./maszyna-wirtualna {output_file}` command.
 
## Description of tests

I added unit tests for Memory class which creates Memory mockup, perform some operations on it (adds many variables and procedures), then checks if returned values of chosen variables and procedures are correct. Second test is written in bash and involves running three test programs through the process of compiling and running it on the virtual machine, then checks if the output is correct (correct output is defined in ie. {test_program_name}_correct.out).

## Quick overview of files and folders structure

### src

Source folder contains compiler code:
- codeGenerator (contains machine code generator),
- memory (code for virtual machine memory mockup with some extensions like procedures and more complex variables),
- parser (Flex and Bison code),
- variables (code for variable implementation).

### tests
Folder that contains example code for testing, code that should give errors and correct output files.

### tools
Folder with Flex and Bison version used in the compiler.

### virtual-machine
Folder with virtual-machine files and code.

## Contributors
* [Mateusz Gancarz](https://github.com/magancarz) - compiler code
* [Dr Maciej Gębala](https://cs.pwr.edu.pl/gebala/) - virtual machine and assignment