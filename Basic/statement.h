/*
 * File: statement.h
 * -----------
 * This interface defines a class hierarchy for statement as well as command,
 * which allows the programs execute.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "program.h"
#include <string>

/*
 * Type: StatementType
 * --------------------
 * This enumerated type is used to differentiate the seven different
 * statement types: REM, LET, PRINT, INPUT, END, GOTO, IF.
 */

enum StatementType
{
  REM,
  LET,
  PRINT,
  INPUT,
  END,
  GOTO,
  IF,
};

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement
{

public:
  /*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

  Statement(){};

  /*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this statement.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

  virtual ~Statement(){};

  /*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

  virtual void execute(EvalState &state) = 0;

  /*
 * Method: getType
 * Usage: stmt->getType();
 * ----------------------------
 * This method returns the type of statement.
 */

  virtual StatementType getType() = 0;
};

/*
 * Class: SeqREM
 * ------------------
 * This subclass represents the REM statement.
 */

class SeqREM : public Statement
{

public:
  /*
 * Constructor: SeqREM
 * Usage: statement *tmp = new SeqREM();
 * ------------------------------------------------
 * The constructor initializes a REM statement.
 */

  SeqREM(){};

  /*
 * Destructor: ~SeqREM
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~SeqREM(){};

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a REM statement.
 */

  virtual void execute(EvalState &state){};

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();
};

/*
 * Class: SeqLET
 * ------------------
 * This subclass represents the REM statement.
 */

class SeqLET : public Statement
{

public:
  /*
 * Constructor: SeqLET
 * Usage: statement *tmp = new SeqLET(exp);
 * ------------------------------------------------
 * The constructor initializes a LET statement.
 */

  SeqLET(Expression *exp);

  /*
 * Destructor: ~SeqLET
 * Usage: delete exp
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~SeqLET();

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a LET statement.
 */

  virtual void execute(EvalState &state);

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();

private:
  Expression *exp;
};

/*
 * Class: SeqPRINT
 * ------------------
 * This subclass represents the PRINT statement.
 */

class SeqPRINT : public Statement
{

public:
  /*
 * Constructor: SeqPRINT
 * Usage: statement *tmp = new SeqLET(exp);
 * ------------------------------------------------
 * The constructor initializes a PRINT statement.
 */

  SeqPRINT(Expression *exp);

  /*
 * Destructor: ~SeqPRINT
 * Usage: delete exp
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~SeqPRINT();

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a PRINT statement.
 */

  virtual void execute(EvalState &state);

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();

private:
  Expression *exp;
};

/*
 * Class: SeqINPUT
 * ------------------
 * This subclass represents the INPUT statement.
 */

class SeqINPUT : public Statement
{

public:
  /*
 * Constructor: SeqINPUT
 * Usage: statement *tmp = new SeqLET(var);
 * ------------------------------------------------
 * The constructor initializes a LET statement.
 */

  SeqINPUT(string var);

  /*
 * Destructor: ~SeqINPUT
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~SeqINPUT(){};

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a INPUT statement.
 */

  virtual void execute(EvalState &state);

  /*
 * Method: getVarName
 * Usage: tmp.getVarName();
 * ----------------------------
 * This method returns the name of variable. 
 */

  string getVarName();

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();

private:
  string var;
};

/*
 * Class: SeqEND
 * ------------------
 * This subclass represents the END statement.
 */

class SeqEND : public Statement
{

public:
  /*
 * Constructor: SeqEND
 * Usage: statement *tmp = new SeqEND();
 * ------------------------------------------------
 * The constructor initializes a END statement.
 */

  SeqEND(){};

  /*
 * Destructor: ~SeqEND
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~SeqEND(){};

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a END statement.
 */

  virtual void execute(EvalState &state){};

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();
};

/*
 * Class: ControlGOTO
 * ------------------
 * This subclass represents the GOTO control statement.
 */

class ControlGOTO : public Statement
{

public:
  /*
 * Constructor: ControlGOTO
 * Usage: statement *tmp = new ControlGOTO(line, p);
 * ------------------------------------------------
 * The constructor initializes a GOTO control statement.
 */

  ControlGOTO(int line, Program *p);

  /*
 * Destructor: ~SeqEND
 * Usage: delete p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~ControlGOTO();

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a GOTO statement.
 */

  virtual void execute(EvalState &state);

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();

private:
  int line;
  Program *p;
};

/*
 * Class: ControlIF
 * ------------------
 * This subclass represents the IF control statement.
 */

class ControlIF : public Statement
{

public:
  /*
 * Constructor: ControlIF
 * Usage: statement *tmp = new ControlIF(cmp, lhs, rhs, line, p);
 * ------------------------------------------------
 * The constructor initializes a IF control statement.
 */

  ControlIF(char cmp, Expression *lhs, Expression *rhs, int line, Program *p);

  /*
 * Destructor: ~ControlIF
 * Usage: delete lhs, rhs, p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~ControlIF();

  /*
 * Method: execute
 * Usage: tmp.execute(state);
 * ----------------------------
 * This method executes a IF statement.
 */

  virtual void execute(EvalState &state);

  /*
 * Method: executeLine
 * Usage: tmp.execute(line);
 * ----------------------------
 * This method sets line as executeLine.
 */

  void executeLine(int line);

  /*
 * Method: getType
 * Usage: tmp.getType();
 * ----------------------------
 * This method returns the type of statement. 
 */

  virtual StatementType getType();

private:
  char cmp;
  Expression *lhs;
  Expression *rhs;
  int line;
  Program *p;
};

/*
 * Type: CommandType
 * --------------------
 * This enumerated type is used to differentiate the five different
 * statement types: RUN, LIST, CLEAR, QUIT, HELP.
 */

enum CommandType
{
  RUN,
  LIST,
  CLEAR,
  QUIT,
  HELP
};

class Command
{

public:
  /*
 * Constructor: Command
 * ----------------------
 * The base class constructor is empty. Each subclass must provide
 * its own constructor.
 */

  Command(){};

  /*
 * Destructor: ~Command
 * -------------------
 * The destructor deallocates the storage for this command.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a command.
 */

  virtual ~Command(){};

  /*
 * Method: execute
 * Usage: cmd->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

  virtual void execute(EvalState &state, Program &program) = 0;

  /*
 * Method: getType
 * Usage: stmt->getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType() = 0;
};

/*
 * Class: ControlIF
 * ------------------
 * This subclass represents the RUN command.
 */

class CommandRUN : public Command
{
public:
  /*
 * Constructor: CommandRUN
 * Usage: CommandRUN cmd = CommandRUN(p);
 * ------------------------------------------------
 * The constructor initializes a RUN command.
 */

  CommandRUN(Program *p);

  /*
 * Destructor: ~CommandRUN
 * Usage: delete p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~CommandRUN();

  /*
 * Method: execute
 * Usage: cmd.execute(state, program);
 * ----------------------------
 * This method executes a RUN command.
 */

  virtual void execute(EvalState &state, Program &program);

  /*
 * Method: getType
 * Usage: cmd.getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType();

private:
  Program *p;
};

/*
 * Class: CommandLIST
 * ------------------
 * This subclass represents the LIST command.
 */

class CommandLIST : public Command
{
public:
  /*
 * Constructor: CommandLIST
 * Usage: CommandLIST cmd = CommandLIST(p);
 * ------------------------------------------------
 * The constructor initializes a RUN command.
 */

  CommandLIST(Program *p);

  /*
 * Destructor: ~CommandLIST
 * Usage: delete p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~CommandLIST();

  /*
 * Method: execute
 * Usage: cmd.execute(state, program);
 * ----------------------------
 * This method executes a LIST command.
 */

  virtual void execute(EvalState &state, Program &program);

  /*
 * Method: getType
 * Usage: cmd.getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType();

private:
  Program *p;
};

/*
 * Class: CommandCLEAR
 * ------------------
 * This subclass represents the CLEAR command.
 */

class CommandCLEAR : public Command
{
public:
  /*
 * Constructor: CommandCLEAR
 * Usage: CommandCLEAR cmd = CommandCLEAR(p);
 * ------------------------------------------------
 * The constructor initializes a CLEAR command.
 */

  CommandCLEAR(Program *p);

  /*
 * Destructor: ~CommandCLEAR
 * Usage: delete p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~CommandCLEAR();

  /*
 * Method: execute
 * Usage: cmd.execute(state, program);
 * ----------------------------
 * This method executes a CLEAR command.
 */

  virtual void execute(EvalState &state, Program &program);

  /*
 * Method: getType
 * Usage: cmd.getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType();

private:
  Program *p;
};

/*
 * Class: CommandQUIT
 * ------------------
 * This subclass represents the QUIT command.
 */

class CommandQUIT : public Command
{
public:
  /*
 * Constructor: CommandQUIT
 * Usage: CommandQUIT cmd = CommandQUIT(p);
 * ------------------------------------------------
 * The constructor initializes a CLEAR command.
 */

  CommandQUIT(){};

  /*
 * Destructor: ~CommandQUIT
 * Usage: delete p
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~CommandQUIT(){};

  /*
 * Method: execute
 * Usage: cmd.execute(state, program);
 * ----------------------------
 * This method executes a QUIT command.
 */

  virtual void execute(EvalState &state, Program &program);

  /*
 * Method: getType
 * Usage: cmd.getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType();
};

/*
 * Class: CommandHELP
 * ------------------
 * This subclass represents the HELP command.
 */

class CommandHELP : public Command
{
public:
  /*
 * Constructor: CommandHELP
 * Usage: CommandHELP cmd = CommandHELP(p);
 * ------------------------------------------------
 * The constructor initializes a HELP command.
 */

  CommandHELP(){};

  /*
 * Destructor: ~CommandHELP
 * -------------------
 * The destructor deallocates the storage for this statement.
 */

  ~CommandHELP(){};

  /*
 * Method: execute
 * Usage: cmd.execute(state, program);
 * ----------------------------
 * This method executes a HELP command.
 */

  virtual void execute(EvalState &state, Program &program);

  /*
 * Method: getType
 * Usage: cmd.getType();
 * ----------------------------
 * This method returns the type of command.
 */

  virtual CommandType getType();
};

#endif