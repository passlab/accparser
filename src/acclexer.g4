lexer grammar acclexer;

// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.
@lexer::header {/* lexer header section */}

// Appears before any #include in h + cpp files.
@lexer::preinclude {/* lexer precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@lexer::postinclude {
/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).
@lexer::context {/* lexer context section */}

// Appears in the public part of the lexer in the h file.
@lexer::members {/* public lexer declarations section */
bool canTestFoo() { return true; }
bool isItFoo() { return true; }
bool isItBar() { return true; }

void myFooLexerAction() { /* do something*/ };
void myBarLexerAction() { /* do something*/ };
}

// Appears in the private part of the lexer in the h file.
@lexer::declarations {/* private lexer declarations/members section */}

// Appears in line with the other class member definitions in the cpp file.
@lexer::definitions {/* lexer definitions section */}

channels { CommentsChannel, DirectiveChannel }

tokens {
    EXPR
}

PRAGMA: '#'[ ]*'pragma' -> skip;
ACC: 'acc' | [!c]'$acc';
PARALLEL: 'parallel';
D_LEFT_PAREN: '(';
D_RIGHT_PAREN: ')';
D_BLANK: [ ]+ -> skip;
PRIVATE: 'private' -> pushMode(expr_clause);
FIRSTPRIVATE: 'firstprivate' -> pushMode(expr_clause);
PRESENT: 'present' -> pushMode(expr_clause);
ATTACH: 'attach' -> pushMode(expr_clause);
NO_CREATE: 'no_create' -> pushMode(expr_clause);
DEVICEPTR: 'deviceptr' -> pushMode(expr_clause);
COPY: 'copy' -> pushMode(expr_clause);

D_LINE_END: [\n\r] -> skip;

mode expr_clause;
LEFT_PAREN: '(';
RIGHT_PAREN: ')' -> popMode;
COMMA: ',' -> skip;
BLANK: [ ]+ -> skip;
EXPR: [a-zA-Z_][a-zA-Z0-9_]*;
LINE_END: [\n\r] -> skip;

