/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.h"
#include "program.h"
#include <set>
#include <string>
using namespace std;

/* Implementation of the Statement class */

/*
 * Implementation notes: the SeqREM
 * ----------------------------------------------
 * The ConstantExp subclass stores the REM lines.
 */

StatementType SeqREM::getType()
{
    return REM;
}

/*
 * Implementation notes: the SeqLET subclass
 * ----------------------------------------------
 * The SeqLET subclass helps with the eval of identifier.
 */

SeqLET::SeqLET(Expression *exp)
{
    this->exp = exp;
}

SeqLET::~SeqLET()
{
    if (!exp)
        delete exp;
}

void SeqLET::execute(EvalState &state)
{
    if (exp->getType() != COMPOUND)
    {
        cout << "Compund expression expected" << endl;
    }
    int flag;
    (CompoundExp *)exp->eval(state, flag);
}

StatementType SeqLET::getType()
{
    return LET;
}

/*
 * Implementation notes: the SeqPRINT subclass
 * ----------------------------------------------
 * The SeqPRINT subclass helps to print the value.
 */

SeqPRINT::SeqPRINT(Expression *exp)
{
    this->exp = exp;
}

SeqPRINT::~SeqPRINT()
{
    if (!exp)
        delete exp;
}

void SeqPRINT::execute(EvalState &state)
{
    int flag;
    int ans = exp->eval(state, flag);
    if (flag)
        cout << ans << endl;
    return;
}

StatementType SeqPRINT::getType()
{
    return PRINT;
}

/*
 * Implementation notes: the SeqINPUT subclass
 * ----------------------------------------------
 * The SeqINPUT subclass helps to set a new variable.
 */

SeqINPUT::SeqINPUT(string var)
{
    this->var = var;
}

void SeqINPUT::execute(EvalState &state)
{
    int value;
    while (true)
    {
        cout << " ? ";
        string tmp;
        getline(cin, tmp);
        stringstream ss(tmp);
        ss >> value;
        if (!ss.fail())
        {
            ss >> tmp;
            if (ss.fail())
                break;
        }
        cout << "INVALID NUMBER\n";
        cin.clear();
    }
    state.setValue(var, value);
}

StatementType SeqINPUT::getType()
{
    return INPUT;
}

/*
 * Implementation notes: the SeqEND subclass
 * ----------------------------------------------
 * The SeqEND subclass indicates that the programs 
 * reaches its end.
 */

StatementType SeqEND::getType()
{
    return END;
}

/*
 * Implementation notes: the ControlGOTO subclass
 * ----------------------------------------------
 * The ControlGOTO subclass reset the executeLine 
 * of a program.
 */

ControlGOTO::ControlGOTO(int line, Program *program)
{
    this->line = line;
    this->p = program;
}

ControlGOTO::~ControlGOTO()
{
    if (!p)
        delete p;
}

void ControlGOTO::execute(EvalState &state)
{
    p->setexecuteLine(line);
}

StatementType ControlGOTO::getType()
{
    return GOTO;
}

/*
 * Implementation notes: the SeqIF subclass
 * ----------------------------------------------
 * The SeqIF subclass reset the executeLine of a 
 * program if it is true.
 */

ControlIF::ControlIF(char cmp, Expression *lhs, Expression *rhs, int line, Program *p)
{
    this->cmp = cmp;
    this->lhs = lhs;
    this->rhs = rhs;
    this->line = line;
    this->p = p;
}

ControlIF::~ControlIF()
{
    delete lhs;
    delete rhs;
    delete p;
}

void ControlIF::executeLine(int line)
{
    p->setexecuteLine(line);
}

void ControlIF::execute(EvalState &state)
{
    int flag;
    int left = lhs->eval(state, flag);
    int right = rhs->eval(state, flag);

    switch (cmp)
    {
    case '>':
        if (left > right)
            executeLine(line);
        break;
    case '<':
        if (left < right)
            executeLine(line);
        break;
    case '=':
        if (left == right)
            executeLine(line);
        break;
    default:
        cout << "SYNTAX ERROR" << endl;
    }
}

StatementType ControlIF::getType()
{
    return IF;
}

/*
 * Implementation notes: the CommandRUN subclass
 * ----------------------------------------------
 * The CommandRUN subclass helps to execute the program.
 */

CommandRUN::CommandRUN(Program *program)
{
    this->p = program;
}

CommandRUN::~CommandRUN()
{
    if (!p)
        delete p;
}

CommandType CommandRUN::getType()
{
    return RUN;
}

void CommandRUN::execute(EvalState &state, Program &p)
{
    if (p.getFirstLineNumber() == -1)
        return;
    Statement *tmp;
    int i = p.getexecuteLineNumber();
    if (i == -1)
        return;
    tmp = p.getParsedStatement(i);
    while (tmp->getType() != END)
    {
        if (tmp->getType() == REM)
        {
            i = p.getexecuteLineNumber();
            if (i == -1)
            {
                break;
            }
            tmp = p.getParsedStatement(i);
            continue;
        }
        tmp->execute(state);
        i = p.getexecuteLineNumber();
        if (i == -1)
        {
            break;
        }
        tmp = p.getParsedStatement(i);
    }
    p.renewexecuteLine();
}

/*
 * Implementation notes: the CommandLIST subclass
 * ----------------------------------------------
 * The CommandLIST subclass helps print all the 
 * lines of a program.
 */

CommandLIST::CommandLIST(Program *p)
{
    this->p = p;
}

CommandLIST::~CommandLIST()
{
    if (!p)
        delete p;
}

CommandType CommandLIST::getType()
{
    return LIST;
}

void CommandLIST::execute(EvalState &state, Program &p)
{
    if (p.getFirstLineNumber() == -1)
        return;
    string temp;
    int i = p.getFirstLineNumber();
    do
    {
        string tmp = p.getSourceLine(i);
        cout << tmp << endl;
        i = p.getNextLineNumber(i);
    } while (i != -1);
    p.initexecuteLine();
}

/*
 * Implementation notes: the CommandCLEAR subclass
 * ----------------------------------------------
 * The CommandCLEAR subclass helps clear the state
 * and program.
 */

CommandCLEAR::~CommandCLEAR()
{
    if (!p)
        delete p;
}

CommandCLEAR::CommandCLEAR(Program *p)
{
    this->p = p;
}

CommandType CommandCLEAR::getType()
{
    return CLEAR;
}

void CommandCLEAR::execute(EvalState &state, Program &p)
{
    p.clear();
    state.clear();
}

/*
 * Implementation notes: the CommandQUIT subclass
 * ----------------------------------------------
 * The CommandQUIT subclass helps quit the program
 * by calling exit(0).
 */

CommandType CommandQUIT::getType()
{
    return QUIT;
}

void CommandQUIT::execute(EvalState &state, Program &p)
{
    state.clear();
    p.clear();
    exit(0);
}

/*
 * Implementation notes: the CommandHELP subclass
 * ----------------------------------------------
 * The CommandHELP subclass helps print the helpful
 * messages.
 */

CommandType CommandHELP::getType()
{
    return HELP;
}

void CommandHELP::execute(EvalState &state, Program &p)
{
    cout << "-------------------------------This is a minimal BASIC interpreter-------------------------------" << endl;
    cout << "(1)Sequential Statements:\n1.REM\n2.LET\n3.PRINT\n4.INPUT\n5.END" << endl;
    cout << "(2)Control Statements:\n1.IF...THEN...\n2.GOTO" << endl;
    cout << "(3)BASIC Interpreter:\n1.RUN\n2.LIST\n3.CLEAR\n4.QUIT\n5.HELP" << endl;
    cout << "----------------------------------------Have fun with it-----------------------------------------" << endl;
}