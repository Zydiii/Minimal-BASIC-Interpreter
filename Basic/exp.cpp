/*
 * File: exp.cpp
 * -------------
 * This file implements the Expression class and its subclasses.
 */

#include "exp.h"
#include "evalstate.h"
#include "../StanfordCPPLib/strlib.h"
#include <set>
#include <string>

using namespace std;

/*
 * Implementation notes: the ConstantExp subclass
 * ----------------------------------------------
 * The ConstantExp subclass declares a single instance variable that
 * stores the value of the constant.  The eval method doesn't use the
 * value of state but needs it to match the general prototype for eval.
 */

ConstantExp::ConstantExp(int value)
{
    this->value = value;
}

int ConstantExp::eval(EvalState &state, int &flag)
{
    flag = 1;
    return value;
}

string ConstantExp::toString()
{
    return integerToString(value);
}

ExpressionType ConstantExp::getType()
{
    return CONSTANT;
}

int ConstantExp::getValue()
{
    return value;
}

/*
 * Implementation notes: the IdentifierExp subclass
 * ------------------------------------------------
 * The IdentifierExp subclass declares a single instance variable that
 * stores the name of the variable.  The implementation of eval must
 * look this variable up in the evaluation state.
 */

IdentifierExp::IdentifierExp(string name)
{
    this->name = name;
}

int IdentifierExp::eval(EvalState &state, int &flag)
{
    if (!state.isDefined(name))
    {
        cout << "VARIABLE NOT DEFINED\n";
        flag = 0;
        return 0;
    }
    flag = 1;
    return state.getValue(name);
}

string IdentifierExp::toString()
{
    return name;
}

ExpressionType IdentifierExp::getType()
{
    return IDENTIFIER;
}

string IdentifierExp::getName()
{
    return name;
}

/*
 * Implementation notes: the CompoundExp subclass
 * ----------------------------------------------
 * The CompoundExp subclass declares instance variables for the operator
 * and the left and right subexpressions.  The implementation of eval 
 * evaluates the subexpressions recursively and then applies the operator.
 */

CompoundExp::CompoundExp(string op, Expression *lhs, Expression *rhs)
{
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

CompoundExp::~CompoundExp()
{
    delete lhs;
    delete rhs;
}

/*
 * Implementation notes: eval
 * --------------------------
 * The eval method for the compound expression case must check for the
 * assignment operator as a special case.  Unlike the arithmetic operators
 * the assignment operator does not evaluate its left operand.
 */

int CompoundExp::eval(EvalState &state, int &flag)
{
    if (op == "=")
    {
        if (lhs->getType() != IDENTIFIER)
        {
            cout << "SYNTAX ERROR\n";
            flag = 0;
            return 0;
        }
        int val = rhs->eval(state, flag);
        state.setValue(((IdentifierExp *)lhs)->getName(), val);
        flag = 1;
        return val;
    }
    int left = lhs->eval(state, flag);
    int right = rhs->eval(state, flag);
    if (op == "+")
        return left + right;
    if (op == "-")
        return left - right;
    if (op == "*")
        return left * right;
    if (op == "/")
    {
        if (right == 0)
        {
            cout << "DIVIDE BY ZERO\n";
            flag = 0;
            return 0;
        }
        flag = 1;
        return left / right;
    }
    cout << "SYNTAX ERROR\n";
    flag = 0;
    return 0;
}

string CompoundExp::toString()
{
    return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

ExpressionType CompoundExp::getType()
{
    return COMPOUND;
}

string CompoundExp::getOp()
{
    return op;
}

Expression *CompoundExp::getLHS()
{
    return lhs;
}

Expression *CompoundExp::getRHS()
{
    return rhs;
}
