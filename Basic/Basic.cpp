/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */

int main()
{
    EvalState state;
    Program program;
    while (true)
    {
        try
        {
            processLine(getLine(), program, state);
        }
        catch (ErrorException &ex)
        {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state)
{
    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    string first = scanner.nextToken();
    int flag = 1;
    for (int i = 0; i < first.size(); i++)
    {
        if (first[i] < '0' || first[i] > '9')
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        stringstream ss(first);
        int lineNumber;
        ss >> lineNumber;
        program.addSourceLine(lineNumber, line, scanner);
    }
    else
    {
        string CommandType = first;
        if (CommandType == "LET")
        {
            Expression *exp = parseExp(scanner);
            if (exp->getType() != COMPOUND)
            {
                cout << "SYNTAX ERROR" << endl;
            }
            SeqLET aLET = SeqLET(exp);
            aLET.execute(state);
            if (!exp)
                delete exp;
        }
        else if (CommandType == "PRINT")
        {
            Expression *exp = parseExp(scanner);
            SeqPRINT aPRINT = SeqPRINT(exp);
            aPRINT.execute(state);
            if (!exp)
                delete exp;
        }
        else if (CommandType == "INPUT")
        {
            string var = scanner.nextToken();
            SeqINPUT aINPUT = SeqINPUT(var);
            aINPUT.execute(state);
            return;
        }
        else if (CommandType == "RUN")
        {
            Program *p = &program;
            CommandRUN run = CommandRUN(p);
            run.execute(state, program);
            if (!p)
                delete p;
        }
        else if (CommandType == "LIST")
        {
            Program *p = &program;
            CommandLIST list = CommandLIST(p);
            list.execute(state, program);
            if (!p)
                delete p;
        }
        else if (CommandType == "CLEAR")
        {
            Program *p = &program;
            CommandCLEAR clear = CommandCLEAR(p);
            clear.execute(state, program);
            if (!p)
                delete p;
        }
        else if (CommandType == "QUIT")
        {
            Program *p = &program;
            CommandQUIT quit = CommandQUIT();
            quit.execute(state, program);
            if (!p)
                delete p;
        }
        else if (CommandType == "HELP")
        {
            CommandHELP help = CommandHELP();
            help.execute(state, program);
        }
    }
}