lexer grammar acclexer;
// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.

@ lexer :: header
{ /* lexer header section */
}
// Appears before any #include in h + cpp files.

@ lexer :: preinclude
{ /* lexer precinclude section */
}
// Follows directly after the standard #includes in h + cpp files.

@ lexer :: postinclude
{
/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}
// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).

@ lexer :: context
{ /* lexer context section */
}
// Appears in the public part of the lexer in the h file.

@ lexer :: members
{ /* public lexer declarations section */
  bool lookAhead(std::string word) {
    size_t i;
    for (i = 0; i < word.size(); i++) {
      if (_input->LA(i + 1) != (size_t)word[i]) {
        return false;
      }
    }
    return true;
  }
}
// Appears in the private part of the lexer in the h file.

@ lexer :: declarations
{ /* private lexer declarations/members section */
  int parenthesis_local_count, parenthesis_global_count, bracket_count;
  int brace_count;
}
// Appears in line with the other class member definitions in the cpp file.

@ lexer :: definitions
{ /* lexer definitions section */
}
channels { CommentsChannel , DirectiveChannel }
tokens { EXPR }
PRAGMA
   : '#' [ ]* 'pragma' -> skip
   ;

ACC
   : 'acc'
   | [!c] '$acc'
   ;

DATA
   : 'data'
   ;
   
PARALLEL
   : 'parallel'
   ;

LOOP
   : 'loop'
   ;

LEFT_PAREN
   : '('
   ;

RIGHT_PAREN
   : ')'
   ;

D_BLANK
   : [ ]+ -> skip
   ;

COLON
   : ':'
   ;

LINE_END
   : [\n\r] -> skip
   ;

ASYNC
   : 'async' [ ]*
   {
  if (_input->LA(1) == '(') pushMode(expr_clause);
}
   ;

ATTACH
   : 'attach' -> pushMode (expr_clause)
   ;

AUTO
   : 'auto'
   ;

COLLAPSE
   : 'collapse' -> pushMode (expr_clause)
   ;

COPY
   : 'copy' -> pushMode (expr_clause)
   ;

COPYIN
   : 'copyin' -> pushMode (copyin_clause)
   ;

COPYOUT
   : 'copyout' -> pushMode (copyout_clause)
   ;

CREATE
   : 'create' -> pushMode (create_clause)
   ;

DEFAULT
   : 'default' -> pushMode (default_clause)
   ;

DEVICE_TYPE
   : 'device_type' -> pushMode (expr_clause)
   ;

DEVICEPTR
   : 'deviceptr' -> pushMode (expr_clause)
   ;

FIRSTPRIVATE
   : 'firstprivate' -> pushMode (expr_clause)
   ;

GANG
   : 'gang' [ ]*
   {
  if (_input->LA(1) == '(') pushMode(expr_clause);
}
   ;

IF
   : 'if' -> pushMode (expr_clause)
   ;

INDEPENDENT
   : 'independent'
   ;

NO_CREATE
   : 'no_create' -> pushMode (expr_clause)
   ;

NUM
   : 'num'
   ;

NUM_GANGS
   : 'num_gangs' -> pushMode (expr_clause)
   ;

NUM_WORKERS
   : 'num_workers' -> pushMode (expr_clause)
   ;

PRESENT
   : 'present' -> pushMode (expr_clause)
   ;

PRIVATE
   : 'private' -> pushMode (expr_clause)
   ;

REDUCTION
   : 'reduction' -> pushMode (reduction_clause)
   ;

SELF
   : 'self' [ ]*
   {
  if (_input->LA(1) == '(') pushMode(expr_clause);
}
   ;

SEQ
   : 'seq'
   ;

TILE
   : 'tile' -> pushMode (expr_clause)
   ;

VECTOR
   : 'vector' [ ]*
   {
  if (_input->LA(1) == '(') pushMode(vector_clause);
}
   ;

VECTOR_LENGTH
   : 'vector_length' -> pushMode (expr_clause)
   ;

WAIT
   : 'wait' [ ]*
   {
  if (_input->LA(1) == '(') pushMode(expr_clause);
}
   ;

WORKER
   : 'worker' [ ]*
   {
  if (_input->LA(1) == '(')
    pushMode(worker_clause);
}
   ;

mode copyin_clause;
COPYIN_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("readonly") == false) {
    pushMode(expression_mode);
  }
}
   ;

COPYIN_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

READONLY
   : 'readonly' [ ]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

COPYIN_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

COPYIN_COMMA
   : ',' [ ]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

COPYIN_BLANK
   : [ ]+ -> skip
   ;

COPYIN_LINE_END
   : [\n\r] -> skip
   ;

mode copyout_clause;
COPYOUT_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("zero") == false) {
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

ZERO
   : 'zero' [ ]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_COMMA
   : ',' [ ]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

COPYOUT_BLANK
   : [ ]+ -> skip
   ;

COPYOUT_LINE_END
   : [\n\r] -> skip
   ;

mode create_clause;
CREATE_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("zero") == false) {
    pushMode(expression_mode);
  }
}
   ;

CREATE_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

CREATE_ZERO
   : 'zero' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
  setType (ZERO);
}
   ;

CREATE_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

CREATE_COMMA
   : ',' [ ]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

CREATE_BLANK
   : [ ]+ -> skip
   ;

CREATE_LINE_END
   : [\n\r] -> skip
   ;

mode default_clause;
NONE
   : 'none'
   ;

DEFAULT_PRESENT
   : 'present' -> type (PRESENT)
   ;

DEFAULT_LEFT_PAREN
   : '(' -> type (LEFT_PAREN)
   ;

DEFAULT_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

BLANK
   : [ ]+ -> skip
   ;

EXPR_LINE_END
   : [\n\r] -> skip
   ;

mode vector_clause;
VECTOR_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("length") == false) {
    pushMode(expression_mode);
  }
}
   ;

VECTOR_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

LENGTH
   : 'length' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

VECTOR_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

VECTOR_BLANK
   : [ ]+ -> skip
   ;

VECTOR_LINE_END
   : [\n\r] -> skip
   ;

mode reduction_clause;
REDUCTION_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

REDUCTION_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

ADD
   : '+' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

MUL
   : '*' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

MAX
   : 'max' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

MIN
   : 'min' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

BITAND
   : '&' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

BITOR
   : '|' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

BITXOR
   : '^' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

LOGAND
   : '&&' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

LOGOR
   : '||' [ ]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  }
}
   ;

REDUCTION_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

REDUCTION_COMMA
   : ',' [ ]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

REDUCTION_BLANK
   : [ ]+ -> skip
   ;

REDUCTION_LINE_END
   : [\n\r] -> skip
   ;

mode worker_clause;
WORKER_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("num") == false) {
    pushMode(expression_mode);
  }
}
   ;

WORKER_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

WORKER_NUM
   : 'num' [ ]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    pushMode(expression_mode);
  } else if (_input->LA(1) == ':' && _input->LA(2) != ':') {
    setType(NUM);
  }
}
   ;

WORKER_COLON
   : ':' [ ]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

WORKER_BLANK
   : [ ]+ -> skip
   ;

WORKER_LINE_END
   : [\n\r] -> skip
   ;

mode expr_clause;
EXPR_LEFT_PAREN
   : '(' [ ]*
   {
  setType(LEFT_PAREN);
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

EXPR_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

COMMA
   : ',' [ ]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

mode expression_mode;
EXPRESSION_LEFT_PAREN
   : '('
   {
  parenthesis_local_count++;
  parenthesis_global_count++;
  more();
}
   ;

EXPRESSION_RIGHT_PAREN
   : ')'
   {
  parenthesis_local_count--;
  parenthesis_global_count--;
  if (parenthesis_global_count == 0) {
    popMode();
    setType(RIGHT_PAREN);
    parenthesis_local_count = 0;
    parenthesis_global_count = 0;
    bracket_count = 0;
  } else {
    more();
  };
}
   ;

EXPRESSION_CHAR
   : . [ ]*
   {
  switch (_input->LA(1)) {
  case ')': {
    if (parenthesis_global_count - 1 == 0) {
      popMode();
      setType(EXPR);
      parenthesis_local_count = 0;
      bracket_count = 0;
    } else {
      parenthesis_global_count--;
      parenthesis_local_count--;
      more();
    };
    break;
  }
  case ',': {
    if (parenthesis_local_count == 0) {
      setType(EXPR);
      popMode();
    } else {
      more();
    };
    break;
  }
  default: {
    more();
  }
  }
}
   ;

