/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "parser.h"
#include "statement.h"
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
using namespace std;

/*
 * Implementation notes: the Program class
 * ----------------------------------------------
 * The Program class stores the input lines of program.
 */

Program::Program()
{
    this->executeLine = -1;
}

Program::~Program()
{
    programs.clear();
    parsedStatements.clear();
}

void Program::clear()
{
    executeLine = -1;
    programs.clear();
    parsedStatements.clear();
}

void Program::addSourceLine(int lineNumber, string line, TokenScanner &ts)
{
    ts.ignoreWhitespace();
    if (ts.hasMoreTokens())
    {
        this->programs[lineNumber] = line;
        Statement *tmp;
        string str = ts.nextToken();
        if (str == "REM")
        {
            tmp = new SeqREM();
        }
        else if (str == "LET")
        {
            Expression *exp = parseExp(ts);
            tmp = new SeqLET(exp);
        }
        else if (str == "PRINT")
        {
            Expression *exp = parseExp(ts);
            tmp = new SeqPRINT(exp);
        }
        else if (str == "INPUT")
        {
            string var = ts.nextToken();
            tmp = new SeqINPUT(var);
        }
        else if (str == "END")
        {
            tmp = new SeqEND();
        }
        else if (str == "GOTO")
        {
            stringstream ss(ts.nextToken());
            int line;
            ss >> line;
            tmp = new ControlGOTO(line, this);
        }
        else if (str == "IF")
        {
            Expression *lhs = readE(ts, 1);
            char cmp = ts.nextToken()[0];
            Expression *rhs = readE(ts, 1);
            if (ts.nextToken() != "THEN")
            {
                cout << "SYNTAX ERROR" << endl;
            }
            stringstream ss(ts.nextToken());
            int line;
            ss >> line;
            tmp = new ControlIF(cmp, lhs, rhs, line, this);
        }
        else
            cout << "SYNTAX ERROR" << endl;
        setParsedStatement(lineNumber, tmp);
        this->executeLine = this->programs.begin()->first;
    }
    else
    {
        if (programs.count(lineNumber) == 1)
        {
            map<int, string>::iterator it = this->programs.find(lineNumber);
            this->programs.erase(it);
        }
    }
}

void Program::removeSourceLine(int lineNumber)
{
    if (this->programs.count(lineNumber) != 0)
    {
        map<int, string>::iterator it = this->programs.find(lineNumber);
        this->programs.erase(it);
    }
}

string Program::getSourceLine(int lineNumber)
{
    if (this->programs.count(lineNumber) != 0)
    {
        return this->programs[lineNumber];
    }
    return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt)
{
    if (this->programs.count(lineNumber) == 0)
        error("ERROR");
    else
        parsedStatements[lineNumber] = stmt;
}

Statement *Program::getParsedStatement(int lineNumber)
{
    if (this->parsedStatements.count(lineNumber) != 0)
        return parsedStatements[lineNumber];
    return NULL;
}

int Program::getFirstLineNumber()
{
    if (this->programs.size() == 0)
        return -1;
    map<int, string>::iterator it = this->programs.begin();
    return it->first;
}

int Program::getexecuteLineNumber()
{
    int line = executeLine;
    map<int, string>::iterator i = programs.find(line);
    i++;
    if (i != programs.end())
    {
        executeLine = i->first;
    }
    else
    {
        executeLine = -1;
    }
    return line;
}

int Program::getNextLineNumber(int lineNumber)
{
    map<int, string>::iterator it = programs.find(lineNumber);
    it++;
    if (it == programs.end())
        return -1;
    else
    {
        return it->first;
    }
}

void Program::setexecuteLine(int lineNumber)
{
    if (this->programs.count(lineNumber) == 0)
        cout << "LINE NUMBER ERROR" << endl;
    else
    {
        executeLine = lineNumber;
    }
}

void Program::initexecuteLine()
{
    executeLine = -1;
}

void Program::renewexecuteLine()
{
    this->executeLine = this->programs.begin()->first;
}