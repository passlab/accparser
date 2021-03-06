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
    OPENACC_DIRECTIVE(atomic)
    OPENACC_DIRECTIVE(cache)
    OPENACC_DIRECTIVE(data)
    OPENACC_DIRECTIVE(declare)
    OPENACC_DIRECTIVE(end)
    OPENACC_DIRECTIVE(enter_data)
    OPENACC_DIRECTIVE(exit_data)
    OPENACC_DIRECTIVE(host_data)
    OPENACC_DIRECTIVE(init)
    OPENACC_DIRECTIVE(kernels)
    OPENACC_DIRECTIVE(kernels_loop)
    OPENACC_DIRECTIVE(loop)
    OPENACC_DIRECTIVE(parallel)
    OPENACC_DIRECTIVE(parallel_loop)
    OPENACC_DIRECTIVE(routine)
    OPENACC_DIRECTIVE(serial)
    OPENACC_DIRECTIVE(serial_loop)
    OPENACC_DIRECTIVE(set)
    OPENACC_DIRECTIVE(shutdown)
    OPENACC_DIRECTIVE(update)
    OPENACC_DIRECTIVE(wait)

    OPENACC_DIRECTIVE(unknown)
#undef OPENACC_DIRECTIVE
};

// OpenACC clauses.
enum OpenACCClauseKind {
#define OPENACC_CLAUSE(Name) ACCC_##Name,
    OPENACC_CLAUSE(async)
    OPENACC_CLAUSE(attach)
    OPENACC_CLAUSE(auto)
    OPENACC_CLAUSE(bind)
    OPENACC_CLAUSE(capture)
    OPENACC_CLAUSE(collapse)
    OPENACC_CLAUSE(copy)
    OPENACC_CLAUSE(copyin)
    OPENACC_CLAUSE(copyout)
    OPENACC_CLAUSE(create)
    OPENACC_CLAUSE(default_async)
    OPENACC_CLAUSE(default)
    OPENACC_CLAUSE(delete)
    OPENACC_CLAUSE(detach)
    OPENACC_CLAUSE(device)
    OPENACC_CLAUSE(device_num)
    OPENACC_CLAUSE(device_resident)
    OPENACC_CLAUSE(device_type)
    OPENACC_CLAUSE(deviceptr)
    OPENACC_CLAUSE(finalize)
    OPENACC_CLAUSE(firstprivate)
    OPENACC_CLAUSE(gang)
    OPENACC_CLAUSE(host)
    OPENACC_CLAUSE(if)
    OPENACC_CLAUSE(if_present)
    OPENACC_CLAUSE(independent)
    OPENACC_CLAUSE(link)
    OPENACC_CLAUSE(nohost)
    OPENACC_CLAUSE(no_create)
    OPENACC_CLAUSE(num_gangs)
    OPENACC_CLAUSE(num_workers)
    OPENACC_CLAUSE(present)
    OPENACC_CLAUSE(private)
    OPENACC_CLAUSE(reduction)
    OPENACC_CLAUSE(read)
    OPENACC_CLAUSE(self)
    OPENACC_CLAUSE(seq)
    OPENACC_CLAUSE(tile)
    OPENACC_CLAUSE(update)
    OPENACC_CLAUSE(use_device)
    OPENACC_CLAUSE(vector)
    OPENACC_CLAUSE(vector_length)
    OPENACC_CLAUSE(wait)
    OPENACC_CLAUSE(worker)
    OPENACC_CLAUSE(write)

    OPENACC_CLAUSE(unknown)
#undef OPENACC_CLAUSE
};

// OpenACC attributes for 'cache' directive.
enum OpenACCCacheDirectiveModifier {
#define OPENACC_CACHE_MODIFIER(Name) ACCC_CACHE_##Name,
    OPENACC_CACHE_MODIFIER(unspecified)
    OPENACC_CACHE_MODIFIER(readonly)
    OPENACC_CACHE_MODIFIER(unknown)
#undef OPENACC_CACHE_MODIFIER
};

// OpenACC attributes for 'copyin' clause.
enum OpenACCCopyinClauseModifier {
#define OPENACC_COPYIN_MODIFIER(Name) ACCC_COPYIN_##Name,
    OPENACC_COPYIN_MODIFIER(unspecified)
    OPENACC_COPYIN_MODIFIER(readonly)
    OPENACC_COPYIN_MODIFIER(unknown)
#undef OPENACC_COPYIN_MODIFIER
};

// OpenACC attributes for 'copyout' clause.
enum OpenACCCopyoutClauseModifier {
#define OPENACC_COPYOUT_MODIFIER(Name) ACCC_COPYOUT_##Name,
    OPENACC_COPYOUT_MODIFIER(unspecified)
    OPENACC_COPYOUT_MODIFIER(zero)
    OPENACC_COPYOUT_MODIFIER(unknown)
#undef OPENACC_COPYOUT_MODIFIER
};

// OpenACC attributes for 'create' clause.
enum OpenACCCreateClauseModifier {
#define OPENACC_CREATE_MODIFIER(Name) ACCC_CREATE_##Name,
    OPENACC_CREATE_MODIFIER(unspecified)
    OPENACC_CREATE_MODIFIER(zero)
    OPENACC_CREATE_MODIFIER(unknown)
#undef OPENACC_CREATE_MODIFIER
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

// OpenACC attributes for 'reduction' clause.
enum OpenACCReductionClauseOperator {
#define OPENACC_REDUCTION_OPERATOR(Name) ACCC_REDUCTION_##Name,
    OPENACC_REDUCTION_OPERATOR(unspecified)
    OPENACC_REDUCTION_OPERATOR(readonly)
    OPENACC_REDUCTION_OPERATOR(add)
    OPENACC_REDUCTION_OPERATOR(mul)
    OPENACC_REDUCTION_OPERATOR(max)
    OPENACC_REDUCTION_OPERATOR(min)
    OPENACC_REDUCTION_OPERATOR(bitand)
    OPENACC_REDUCTION_OPERATOR(bitor)
    OPENACC_REDUCTION_OPERATOR(bitxor)
    OPENACC_REDUCTION_OPERATOR(logand)
    OPENACC_REDUCTION_OPERATOR(logor)
    OPENACC_REDUCTION_OPERATOR(unknown)
#undef OPENACC_REDUCTION_OPERATOR
};

// OpenACC attributes for 'vector' clause.
enum OpenACCVectorClauseModifier {
#define OPENACC_VECTOR_MODIFIER(Name) ACCC_VECTOR_##Name,
    OPENACC_VECTOR_MODIFIER(unspecified)
    OPENACC_VECTOR_MODIFIER(length)
    OPENACC_VECTOR_MODIFIER(unknown)
#undef OPENACC_VECTOR_MODIFIER
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

