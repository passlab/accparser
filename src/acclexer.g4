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
  int colon_count;
}
// Appears in line with the other class member definitions in the cpp file.

@ lexer :: definitions
{ /* lexer definitions section */
}
channels { CommentsChannel , DirectiveChannel }
tokens { EXPR }
C_PREFIX
   : [\p{White_Space}]* '#' [\p{White_Space}]* 'pragma'
   ;

FORTRAN_PREFIX
   : [\p{White_Space}]* [!c*] '$'
   ;

ACC
   : 'acc'
   ;

ATOMIC
   : 'atomic'
   ;

CACHE
   : 'cache' -> pushMode (cache_directive)
   ;

DATA
   : 'data'
   ;

END
   : 'end'
   ;

DECLARE
   : 'declare'
   ;

ENTER
   : 'enter'
   ;

EXIT
   : 'exit'
   ;

HOST_DATA
   : 'host_data'
   ;

INIT
   : 'init'
   ;

KERNELS
   : 'kernels'
   ;

LOOP
   : 'loop'
   ;

PARALLEL
   : 'parallel'
   ;

ROUTINE
   : 'routine' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') {
    pushMode(routine_directive);
  }
  }
   ;

SERIAL
   : 'serial'
   ;

SET
   : 'set'
   ;

SHUTDOWN
   : 'shutdown'
   ;

UPDATE
   : 'update'
   ;

LEFT_PAREN
   : '('
   ;

RIGHT_PAREN
   : ')'
   ;

D_BLANK
   : [\p{White_Space}]+ -> skip
   ;

COLON
   : ':'
   ;

LINE_END
   : [\n\r] -> skip
   ;

ASYNC
   : 'async' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') {
    pushMode(expr_clause);
  }
}
   ;

ATTACH
   : 'attach' -> pushMode (expr_clause)
   ;

AUTO
   : 'auto'
   ;

BIND
   : 'bind' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') {
    pushMode(expr_clause);
  }
}
   ;

CAPTURE
   : 'capture'
   ;

COLLAPSE
   : 'collapse' -> pushMode (expr_clause)
   ;

COPY
   : 'copy' -> pushMode (expr_clause)
   ;

PCOPY
   : 'pcopy' -> type (COPY) , pushMode (expr_clause)
   ;

PRESENT_OR_COPY
   : 'present_or_copy' -> type (COPY) , pushMode (expr_clause)
   ;

COPYIN
   : 'copyin' -> pushMode (copyin_clause)
   ;

PCOPYIN
   : 'pcopyin' -> type (COPYIN) , pushMode (copyin_clause)
   ;

PRESENT_OR_COPYIN
   : 'present_or_copyin' -> type (COPYIN) , pushMode (copyin_clause)
   ;

COPYOUT
   : 'copyout' -> pushMode (copyout_clause)
   ;

PCOPYOUT
   : 'pcopyout' -> type (COPYOUT) , pushMode (copyout_clause)
   ;

PRESENT_OR_COPYOUT
   : 'present_or_copyout' -> type (COPYOUT) , pushMode (copyout_clause)
   ;

CREATE
   : 'create' -> pushMode (create_clause)
   ;

DEFAULT
   : 'default' -> pushMode (default_clause)
   ;

DEFAULT_ASYNC
   : 'default_async' -> pushMode (expr_clause)
   ;

DELETE
   : 'delete' -> pushMode (expr_clause)
   ;

DETACH
   : 'detach' -> pushMode (expr_clause)
   ;

DEVICE
   : 'device' -> pushMode (expr_clause)
   ;

DEVICE_NUM
   : 'device_num' -> pushMode (expr_clause)
   ;

DEVICE_RESIDENT
   : 'device_resident' -> pushMode (expr_clause)
   ;

DEVICE_TYPE
   : 'device_type' -> pushMode (expr_clause)
   ;

DEVICEPTR
   : 'deviceptr' -> pushMode (expr_clause)
   ;

FINALIZE
   : 'finalize'
   ;

FIRSTPRIVATE
   : 'firstprivate' -> pushMode (expr_clause)
   ;

GANG
   : 'gang' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') pushMode(expr_clause);
}
   ;

HOST
   : 'host' -> pushMode (expr_clause)
   ;

IF
   : 'if' [\p{White_Space}]* -> pushMode (expr_clause)
   ;

IF_PRESENT
   : 'if_present'
   ;

INDEPENDENT
   : 'independent'
   ;

LINK
   : 'link' -> pushMode (expr_clause)
   ;

NOHOST
   : 'nohost'
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

READ
   : 'read'
   ;

REDUCTION
   : 'reduction' -> pushMode (reduction_clause)
   ;

SELF
   : 'self' [\p{White_Space}]*
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

USE_DEVICE
   : 'use_device' -> pushMode (expr_clause)
   ;

VECTOR
   : 'vector' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') pushMode(vector_clause);
}
   ;

VECTOR_LENGTH
   : 'vector_length' -> pushMode (expr_clause)
   ;

WAIT
   : 'wait' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(') pushMode(wait_clause);
}
   ;

WORKER
   : 'worker' [\p{White_Space}]*
   {
  if (_input->LA(1) == '(')
    pushMode(worker_clause);
}
   ;

WRITE
   : 'write'
   ;

COMMENT
   : '//' ~ [\r\n]* -> skip
   ;

mode cache_directive;
CACHE_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("readonly") == false) {
    colon_count = 0;
    pushMode(expression_mode);
  }
}
   ;

CACHE_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

CACHE_READONLY
   : 'readonly' [\p{White_Space}]*
   {
   setType(READONLY);
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

CACHE_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

CACHE_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  colon_count = 0;
}
   ;

CACHE_BLANK
   : [\p{White_Space}]+ -> skip
   ;

CACHE_LINE_END
   : [\n\r] -> skip
   ;

mode routine_directive;
ROUTINE_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  pushMode(expression_mode);
}
   ;

ROUTINE_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

ROUTINE_BLANK
   : [\p{White_Space}]+ -> skip
   ;

ROUTINE_LINE_END
   : [\n\r] -> skip
   ;

mode copyin_clause;
COPYIN_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("readonly") == false) {
    colon_count = 0;
    pushMode(expression_mode);
  }
}
   ;

COPYIN_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

READONLY
   : 'readonly' [\p{White_Space}]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

COPYIN_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

COPYIN_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  colon_count = 0;
}
   ;

COPYIN_BLANK
   : [\p{White_Space}]+ -> skip
   ;

COPYIN_LINE_END
   : [\n\r] -> skip
   ;

mode copyout_clause;
COPYOUT_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("zero") == false) {
    colon_count = 0;
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

ZERO
   : 'zero' [\p{White_Space}]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

COPYOUT_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  colon_count = 0;
}
   ;

COPYOUT_BLANK
   : [\p{White_Space}]+ -> skip
   ;

COPYOUT_LINE_END
   : [\n\r] -> skip
   ;

mode create_clause;
CREATE_LEFT_PAREN
   : '(' [\p{White_Space}]*
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
   : 'zero' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
  setType (ZERO);
}
   ;

CREATE_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

CREATE_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

CREATE_BLANK
   : [\p{White_Space}]+ -> skip
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
   : [\p{White_Space}]+ -> skip
   ;

EXPR_LINE_END
   : [\n\r] -> skip
   ;

mode vector_clause;
VECTOR_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("length") == false) {
    colon_count = 0;
    pushMode(expression_mode);
  }
}
   ;

VECTOR_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

LENGTH
   : 'length' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

VECTOR_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

VECTOR_BLANK
   : [\p{White_Space}]+ -> skip
   ;

VECTOR_LINE_END
   : [\n\r] -> skip
   ;

mode reduction_clause;
REDUCTION_LEFT_PAREN
   : '(' [\p{White_Space}]*
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
   : '+' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

MUL
   : '*' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

MAX
   : 'max' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

MIN
   : 'min' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

BITAND
   : '&' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

BITOR
   : '|' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

BITXOR
   : '^' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

LOGAND
   : '&&' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

LOGOR
   : '||' [\p{White_Space}]*
   { 
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    colon_count = 1;
    more();
    pushMode(expression_mode);
  }
}
   ;

REDUCTION_COLON
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

REDUCTION_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
}
   ;

REDUCTION_BLANK
   : [\p{White_Space}]+ -> skip
   ;

REDUCTION_LINE_END
   : [\n\r] -> skip
   ;

mode wait_clause;
WAIT_LEFT_PAREN
   : '(' [\p{White_Space}]*
   {
  setType(LEFT_PAREN);
  bracket_count = 0;
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  if (lookAhead("devnum") == false && lookAhead("queues") == false) {
    colon_count = 0;
    pushMode(expression_mode);
  }
}
   ;

WAIT_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

DEVNUM
   : 'devnum' [\p{White_Space}]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    bracket_count = 0;
    colon_count = 1;
    pushMode(expression_mode);
  }
}
   ;

QUEUES
   : 'queues' [\p{White_Space}]*
   {
  if ((_input->LA(1) == ':' && _input->LA(2) == ':') || (_input->LA(1) != ':')) {
    more();
    bracket_count = 0;
    colon_count = 1;
    pushMode(expression_mode);
  }
}
   ;

WAIT_COLON
   : ':' [\p{White_Space}]*
   {
  if (lookAhead("queues") == false) {
    bracket_count = 0;
    colon_count = 0;
    pushMode(expression_mode);
  } else {
    more();
  }
  setType(COLON);
}
   ;

WAIT_COMMA
   : ',' [\p{White_Space}]*
   {
  skip();
  pushMode(expression_mode);
  parenthesis_global_count = 1;
  parenthesis_local_count = 0;
  bracket_count = 0;
  colon_count = 0;
}
   ;

WAIT_BLANK
   : [\p{White_Space}]+ -> skip
   ;

WAIT_LINE_END
   : [\n\r] -> skip
   ;

mode worker_clause;
WORKER_LEFT_PAREN
   : '(' [\p{White_Space}]*
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
   : 'num' [\p{White_Space}]*
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
   : ':' [\p{White_Space}]*
   {
  if (_input->LA(1) == ':')
    more();
  else {
    colon_count = 0;
    setType(COLON);
    pushMode(expression_mode);
  }
}
   ;

WORKER_BLANK
   : [\p{White_Space}]+ -> skip
   ;

WORKER_LINE_END
   : [\n\r] -> skip
   ;

mode expr_clause;
EXPR_LEFT_PAREN
   : '(' [\p{White_Space}]*
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
   : ',' [\p{White_Space}]*
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
   : . [\p{White_Space}]*
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
  case '[': {
    bracket_count += 1;
    more();
    break;
  }
  case ']': {
    bracket_count -= 1;
    more();
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
  case ':': {
    if (_input->LA(2) != ':' && colon_count == 0 && bracket_count == 0) {
      colon_count = 0;
      setType(EXPR);
      popMode();
    } else {
      if (bracket_count == 0) {
        if (colon_count == 0) {
          colon_count += 1;
        } else {
          colon_count = 0;
        }
      };
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

