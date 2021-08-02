//===----------------------------------------------------------------------===//
//
// Defines some OpenACC-specific enums and functions.
//
//===----------------------------------------------------------------------===//

#ifndef __OPENACCKINDS_H__
#define __OPENACCKINDS_H__

// OpenACC directives.
enum OpenACCDirectiveKind {
#define OPENACC_DIRECTIVE(Name) ACCD_##Name,
    OPENACC_DIRECTIVE(parallel)
    OPENACC_DIRECTIVE(loop)
    OPENACC_DIRECTIVE(parallel_loop)

    OPENACC_DIRECTIVE(unknown)
#undef OPENACC_DIRECTIVE
};

// OpenACC clauses.
enum OpenACCClauseKind {
#define OPENACC_CLAUSE(Name) ACCC_##Name,
    OPENACC_CLAUSE(collapse)
    OPENACC_CLAUSE(copy)
    OPENACC_CLAUSE(copyin)
    OPENACC_CLAUSE(copyout)
    OPENACC_CLAUSE(default)
    OPENACC_CLAUSE(firstprivate)
    OPENACC_CLAUSE(gang)
    OPENACC_CLAUSE(if)
    OPENACC_CLAUSE(num_gangs)
    OPENACC_CLAUSE(num_workers)
    OPENACC_CLAUSE(vector_length)
    OPENACC_CLAUSE(private)
    OPENACC_CLAUSE(attach)
    OPENACC_CLAUSE(deviceptr)
    OPENACC_CLAUSE(present)
    OPENACC_CLAUSE(no_create)
    OPENACC_CLAUSE(async)
    OPENACC_CLAUSE(wait)
    OPENACC_CLAUSE(worker)

    OPENACC_CLAUSE(unknown)
#undef OPENACC_CLAUSE
};


// OpenACC attributes for 'copyin' clause.
enum OpenACCCopyinClauseModifier {
#define OPENACC_COPYIN_MODIFIER(Name) ACCC_COPYIN_##Name,
    OPENACC_COPYIN_MODIFIER(unspecified)
    OPENACC_COPYIN_MODIFIER(readonly)

    OPENACC_COPYIN_MODIFIER(unknown)
#undef OPENACC_WORKER_MODIFIER
};

// OpenACC attributes for 'default' clause.
enum OpenACCDefaultClauseKind {
#define OPENACC_DEFAULT_KIND(Name) ACCC_DEFAULT_##Name,
    OPENACC_DEFAULT_KIND(unspecified)
    OPENACC_DEFAULT_KIND(none)
    OPENACC_DEFAULT_KIND(present)

    OPENACC_DEFAULT_KIND(unknown)
#undef OPENACC_DEFAULT_KIND
};

// OpenACC attributes for 'worker' clause.
enum OpenACCWorkerClauseModifier {
#define OPENACC_WORKER_MODIFIER(Name) ACCC_WORKER_##Name,
    OPENACC_WORKER_MODIFIER(unspecified)
    OPENACC_WORKER_MODIFIER(num)

    OPENACC_WORKER_MODIFIER(unknown)
#undef OPENACC_WORKER_MODIFIER
};

#endif

