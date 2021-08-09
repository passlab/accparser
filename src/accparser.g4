parser grammar accparser;


options { tokenVocab = acclexer; }
// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.

@ parser :: header
{/* parser/listener/visitor header section */}
// Appears before any #include in h + cpp files.

@ parser :: preinclude
{/* parser precinclude section */}
// Follows directly after the standard #includes in h + cpp files.

@ parser :: postinclude
{
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}
// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).

@ parser :: context
{/* parser context section */}
// Appears in the private part of the parser in the h file.

// The function bodies could also appear in the definitions section, but I want to maximize

// Java compatibility, so we can also create a Java parser from this grammar.

// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).

@ parser :: members
{
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}
// Appears in the public part of the parser in the h file.

@ parser :: declarations
{/* private parser declarations section */}
// Appears in line with the other class member definitions in the cpp file.

@ parser :: definitions
{/* parser definitions section */}
// Additionally there are similar sections for (base)listener and (base)visitor files.

@ parser :: listenerpreinclude
{/* listener preinclude section */}
@ parser :: listenerpostinclude
{/* listener postinclude section */}
@ parser :: listenerdeclarations
{/* listener public declarations/members section */}
@ parser :: listenermembers
{/* listener private declarations/members section */}
@ parser :: listenerdefinitions
{/* listener definitions section */}
@ parser :: baselistenerpreinclude
{/* base listener preinclude section */}
@ parser :: baselistenerpostinclude
{/* base listener postinclude section */}
@ parser :: baselistenerdeclarations
{/* base listener public declarations/members section */}
@ parser :: baselistenermembers
{/* base listener private declarations/members section */}
@ parser :: baselistenerdefinitions
{/* base listener definitions section */}
@ parser :: visitorpreinclude
{/* visitor preinclude section */}
@ parser :: visitorpostinclude
{/* visitor postinclude section */}
@ parser :: visitordeclarations
{/* visitor public declarations/members section */}
@ parser :: visitormembers
{/* visitor private declarations/members section */}
@ parser :: visitordefinitions
{/* visitor definitions section */}
@ parser :: basevisitorpreinclude
{/* base visitor preinclude section */}
@ parser :: basevisitorpostinclude
{/* base visitor postinclude section */}
@ parser :: basevisitordeclarations
{/* base visitor public declarations/members section */}
@ parser :: basevisitormembers
{/* base visitor private declarations/members section */}
@ parser :: basevisitordefinitions
{/* base visitor definitions section */}
// Actual grammar start.

acc
   : ACC openacc_directive EOF
   ;

openacc_directive
   : data_directive
   | enter_data_directive
   | exit_data_directive
   | loop_directive
   | parallel_directive
   | parallel_loop_directive
   ;

data_directive
   : DATA data_clause_list
   ;

data_clause_list
   : data_clauses*
   ;

data_clauses
   : attach_clause
   | copy_clause
   | copyin_clause
   | copyout_clause
   | create_clause
   | default_clause
   | deviceptr_clause
   | if_clause
   | no_create_clause
   | present_clause
   ;

enter_data_directive
   : ENTER DATA enter_data_clause_list
   ;

enter_data_clause_list
   : enter_data_clauses+
   ;

enter_data_clauses
   : async_clause
   | attach_clause
   | copyin_no_modifier_clause
   | create_clause
   | if_clause
   | wait_argument_clause
   ;

exit_data_directive
   : EXIT DATA exit_data_clause_list
   ;

exit_data_clause_list
   : exit_data_clauses+
   ;

exit_data_clauses
   : async_clause
   | copyout_no_modifier_clause
   | delete_clause
   | detach_clause
   | finalize_clause
   | if_clause
   | wait_argument_clause
   ;

loop_directive
   : LOOP loop_clause_list
   ;

loop_clause_list
   : loop_clauses*
   ;

loop_clauses
   : auto_clause
   | collapse_clause
   | device_type_clause
   | gang_clause
   | independent_clause
   | private_clause
   | reduction_clause
   | seq_clause
   | tile_clause
   | vector_clause
   | worker_clause
   ;

parallel_directive
   : PARALLEL parallel_clause_list
   ;

parallel_clause_list
   : parallel_clauses*
   ;

parallel_clauses
   : async_clause
   | attach_clause
   | copy_clause
   | copyin_clause
   | copyout_clause
   | create_clause
   | default_clause
   | device_type_clause
   | deviceptr_clause
   | firstprivate_clause
   | if_clause
   | no_create_clause
   | num_gangs_clause
   | num_workers_clause
   | present_clause
   | private_clause
   | reduction_clause
   | self_clause
   | vector_length_clause
   | wait_clause
   ;

parallel_loop_directive
   : PARALLEL LOOP parallel_loop_clause_list
   ;

parallel_loop_clause_list
   : parallel_loop_clauses*
   ;

parallel_loop_clauses
   : async_clause
   | collapse_clause
   | copy_clause
   | copyin_clause
   | copyout_clause
   | firstprivate_clause
   | gang_clause
   | num_gangs_clause
   | num_workers_clause
   | private_clause
   | wait_clause
   | worker_clause
   ;

async_clause
   : ASYNC
   | ASYNC LEFT_PAREN int_expr RIGHT_PAREN
   ;

attach_clause
   : ATTACH LEFT_PAREN var_list RIGHT_PAREN
   ;

auto_clause
   : AUTO
   ;

collapse_clause
   : COLLAPSE LEFT_PAREN const_int RIGHT_PAREN
   ;

copy_clause
   : COPY LEFT_PAREN var_list RIGHT_PAREN
   ;

copyin_clause
   : COPYIN LEFT_PAREN var_list RIGHT_PAREN
   | COPYIN LEFT_PAREN copyin_clause_modifier COLON var_list RIGHT_PAREN
   ;

copyin_clause_modifier
   : READONLY
   ;

copyin_no_modifier_clause
   : COPYIN LEFT_PAREN var_list RIGHT_PAREN
   ;

copyout_clause
   : COPYOUT LEFT_PAREN var_list RIGHT_PAREN
   | COPYOUT LEFT_PAREN copyout_clause_modifier COLON var_list RIGHT_PAREN
   ;

copyout_clause_modifier
   : ZERO
   ;

copyout_no_modifier_clause
   : COPYOUT LEFT_PAREN var_list RIGHT_PAREN
   ;

create_clause
   : CREATE LEFT_PAREN var_list RIGHT_PAREN
   | CREATE LEFT_PAREN create_clause_modifier COLON var_list RIGHT_PAREN
   ;

create_clause_modifier
   : ZERO
   ;

default_clause
   : DEFAULT LEFT_PAREN default_kind RIGHT_PAREN
   ;

default_kind
   : NONE
   | PRESENT
   ;

delete_clause
   : DELETE LEFT_PAREN var_list RIGHT_PAREN
   ;

detach_clause
   : DETACH LEFT_PAREN var_list RIGHT_PAREN
   ;

device_type_clause
   : DEVICE_TYPE LEFT_PAREN device_type_list RIGHT_PAREN
   ;

device_type_list
   : (var COMMA | var)+
   ;

deviceptr_clause
   : DEVICEPTR LEFT_PAREN var_list RIGHT_PAREN
   ;

finalize_clause
   : FINALIZE
   ;

firstprivate_clause
   : FIRSTPRIVATE LEFT_PAREN var_list RIGHT_PAREN
   ;

gang_clause
   : GANG
   | GANG LEFT_PAREN gang_arg_list RIGHT_PAREN
   ;

gang_arg_list
   : (var COMMA | var)+
   ;

if_clause
   : IF LEFT_PAREN condition RIGHT_PAREN
   ;

independent_clause
   : INDEPENDENT
   ;

no_create_clause
   : NO_CREATE LEFT_PAREN var_list RIGHT_PAREN
   ;

num_gangs_clause
   : NUM_GANGS LEFT_PAREN int_expr RIGHT_PAREN
   ;

num_workers_clause
   : NUM_WORKERS LEFT_PAREN int_expr RIGHT_PAREN
   ;

present_clause
   : PRESENT LEFT_PAREN var_list RIGHT_PAREN
   ;

private_clause
   : PRIVATE LEFT_PAREN var_list RIGHT_PAREN
   ;

reduction_clause
   : REDUCTION LEFT_PAREN reduction_operator COLON var_list RIGHT_PAREN
   ;

reduction_operator
   : ADD
   | MUL
   | MAX
   | MIN
   | BITAND
   | BITOR
   | BITXOR
   | LOGAND
   | LOGOR
   ;

self_clause
   : SELF
   | SELF LEFT_PAREN condition RIGHT_PAREN
   ;

condition
   : EXPR
   ;

seq_clause
   : SEQ
   ;

tile_clause
   : TILE LEFT_PAREN size_expr_list RIGHT_PAREN
   ;

size_expr_list
   : (var COMMA | var)+
   ;

vector_clause
   : VECTOR
   | VECTOR vector_clause_args
   ;

vector_clause_args
   : LEFT_PAREN vector_clause_modifier COLON int_expr RIGHT_PAREN
   | LEFT_PAREN int_expr RIGHT_PAREN
   ;

vector_clause_modifier
   : LENGTH
   ;

vector_length_clause
   : VECTOR_LENGTH LEFT_PAREN int_expr RIGHT_PAREN
   ;

wait_clause
   : WAIT
   | WAIT LEFT_PAREN int_expr_list RIGHT_PAREN
   ;

wait_argument_clause
   : WAIT
   | WAIT LEFT_PAREN wait_argument RIGHT_PAREN
   ;

wait_argument
   : DEVNUM COLON wait_argument_int_expr COLON wait_argument_queues COLON int_expr_list
   | DEVNUM COLON wait_argument_int_expr COLON int_expr_list
   | wait_argument_queues COLON int_expr_list
   | int_expr_list
   ;

wait_argument_queues
   : QUEUES
   ;

wait_argument_int_expr
   : EXPR
   ;

worker_clause
   : WORKER
   | WORKER worker_clause_args
   ;

worker_clause_args
   : LEFT_PAREN worker_clause_modifier COLON int_expr RIGHT_PAREN
   | LEFT_PAREN int_expr RIGHT_PAREN
   ;

worker_clause_modifier
   : NUM
   ;

const_int
   : EXPR
   ;

int_expr_list
   : (int_expr COMMA | int_expr)+
   ;

int_expr
   : EXPR
   ;

var_list
   : (var COMMA | var)+
   ;

var
   : EXPR
   ; finally
   {
  cleanUp();
}

