#include "OpenACCASTConstructor.h"
#include "OpenMPIR.h"

OpenMPDirective *convertParallelLoop(OpenACCDirective *);

void convertOpenACCClauses(OpenACCDirective *, OpenMPDirective *);

OpenMPDirective *generateOpenMP(OpenACCDirective *);
