/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include "evalstate.h"
#include <set>
#include <string>

#include "../StanfordCPPLib/map.h"
using namespace std;

/* A set of key words */

set<string> words = {"REM", "LET", "PRINT", "INPUT", "END", "GOTO", "IF", "THEN", "RUN", "LIST", "CLEAR", "QUIT", "HELP"};

/* Implementation of the EvalState class */

EvalState::~EvalState()
{
    symbolTable.clear();
}

void EvalState::setValue(string var, int value)
{
    if (words.count(var)==1)
    {
        cout << "SYNTAX ERROR" << endl;
        return;
    }
    if (symbolTable.containsKey(var))
        symbolTable[var] = value;
    else
        symbolTable.put(var, value);
}

int EvalState::getValue(string var)
{
    return symbolTable.get(var);
}

bool EvalState::isDefined(string var)
{
    return symbolTable.containsKey(var);
}

void EvalState::clear()
{
    symbolTable.clear();
}