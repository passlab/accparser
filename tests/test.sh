#!/bin/bash

set -e

INPUT=$1
OUTPUT=${INPUT##*/}.output
REFERENCE=$2
./acc_tester.out ${INPUT}
diff ${OUTPUT} ${REFERENCE}

