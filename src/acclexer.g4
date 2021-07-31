lexer grammar acclexer;
// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.

@ lexer :: header
{/* lexer header section */}
// Appears before any #include in h + cpp files.

@ lexer :: preinclude
{/* lexer precinclude section */}
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
{/* lexer context section */}
// Appears in the public part of the lexer in the h file.

@ lexer :: members
{/* public lexer declarations section */
bool canTestFoo() { return true; }
bool isItFoo() { return true; }
bool isItBar() { return true; }

void myFooLexerAction() { /* do something*/ };
void myBarLexerAction() { /* do something*/ };
}
// Appears in the private part of the lexer in the h file.

@ lexer :: declarations
{/* private lexer declarations/members section */}
// Appears in line with the other class member definitions in the cpp file.

@ lexer :: definitions
{/* lexer definitions section */}
channels { CommentsChannel , DirectiveChannel }
tokens { EXPR }
PRAGMA
   : '#' [ ]* 'pragma' -> skip
   ;

ACC
   : 'acc'
   | [!c] '$acc'
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

ASYNC
   : 'async' -> pushMode (expr_clause)
   ;
   
VECTOR_LENGTH
   : 'vector_length' -> pushMode (expr_clause)
   ;

WAIT
   : 'wait' -> pushMode (expr_clause)
   ;

NUM_GANGS
   : 'num_gangs' -> pushMode (expr_clause)
   ;

NUM_WORKERS
   : 'num_workers' -> pushMode (expr_clause)
   ;

COPY
   : 'copy' -> pushMode (expr_clause)
   ;

COPYIN
   : 'copyin' -> pushMode (expr_clause)
   ;

COPYOUT
   : 'copyout' -> pushMode (expr_clause)
   ;

NO_CREATE
   : 'no_create' -> pushMode (expr_clause)
   ;

PRESENT
   : 'present' -> pushMode (expr_clause)
   ;

DEVICEPTR
   : 'deviceptr' -> pushMode (expr_clause)
   ;

ATTACH
   : 'attach' -> pushMode (expr_clause)
   ;

PRIVATE
   : 'private' -> pushMode (expr_clause)
   ;

FIRSTPRIVATE
   : 'firstprivate' -> pushMode (expr_clause)
   ;

COLLAPSE
   : 'collapse' -> pushMode (expr_clause)
   ;
   
DEFAULT
   : 'default' -> pushMode (default_clause)
   ;

GANG
   : 'gang'
   ;

WORKER
   : 'worker' [ ]*
   { if (_input->LA(1) == '(') pushMode(worker_clause); }
   ;

NUM
   : 'num'
   ;

COLON
   : ':'
   ;

LINE_END
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
   : '(' -> type (RIGHT_PAREN) , popMode
   ;
   
mode expr_clause;
EXPR_LEFT_PAREN
   : '(' -> type (LEFT_PAREN)
   ;

EXPR_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

COMMA
   : ',' -> skip
   ;

BLANK
   : [ ]+ -> skip
   ;

EXPR
   : EXPRESSION
   ;

EXPR_LINE_END
   : [\n\r] -> skip
   ;

mode worker_clause;
WORKER_LEFT_PAREN
   : '(' -> type (LEFT_PAREN)
   ;

WORKER_RIGHT_PAREN
   : ')' -> type (RIGHT_PAREN) , popMode
   ;

WORKER_NUM
   : 'num' -> type (NUM)
   ;

WORKER_COLON
   : ':' -> type (COLON)
   ;

WORKER_COMMA
   : ',' -> skip
   ;

WORKER_BLANK
   : [ ]+ -> skip
   ;

WORKER_EXPR
   : EXPRESSION -> type (EXPR)
   ;

WORKER_LINE_END
   : [\n\r] -> skip
   ;

fragment EXPRESSION
   : ~ [ ,()]+
   ;

