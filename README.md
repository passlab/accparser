# accparser
accparser (ACCP): a standalone OpenACC parser based on ANTLR 4.
It supports both C and Fortran. The generated OpenACC AST can be converted to OpenMP AST.
The OpenMP AST is represented by OpenMPIR from [ompparser](https://github.com/passlab/ompparser).


## Prerequisite

accparser requires ANTLR 4 and its C++ runtime, which are available on Ubuntu 20.04 or later.
For other systems, they may need to be manually built.

```bash
sudo apt update
sudo apt install -y \
    antlr4 \
    libantlr4-runtime-dev \
    build-essential \
    g++ \
    cmake
```

`clang`/`clang++` and `gcc`/`g++` are both fine.

## Build

```bash
mkdir build
cd build
cmake ..
make
```

It will produce a library `libaccparser.so` and an executable `acc_demo.out`

Optionally, we can also enable the OpenMP translator.

```bash
git submodule update --init
mkdir build
cd build
cmake -DOMPPARSER=true -DCMAKE_INSTALL_PREFIX=../accparser-install ..
make install
```

## Run

Given a test file `foo.txt` with the following content to try accparser.

Input:

```c
#pragma acc parallel private(a, b, c)
```

```bash
./acc_demo.out ./foo.txt
```
The output includes the OpenACC source code, recognized tokens, parse tree, and the OpenACC code unparsed from the generated OpenACC IR.

Output:

```bash
======================================
Line: 1
GIVEN INPUT: #pragma acc parallel private(a, b, c)
======================================
TOKEN : TOKEN_STRING
ACC : "acc"
PARALLEL : "parallel"
PRIVATE : "private"
LEFT_PAREN : "("
EXPR : "a"
EXPR : "b"
EXPR : "c"
RIGHT_PAREN : ")"
EOF : "<EOF>"
======================================
PARSE TREE:
(accparallelprivate(abc)<EOF> acc 
        (parallelprivate(abc) 
            (parallelprivate(abc) parallel 
                (private(abc) 
                    (private(abc) 
                        (private(abc) private ( 
                            (abc 
                                (a a) 
                                (b b) 
                                (c c)) )))))) <EOF>)
======================================
GENERATED OUTPUT: #pragma acc parallel private (a, b, c)
======================================
```

At each line of the parse tree section, the output follows the format `(root child_1 child_2 ... child_n)`.
For example, the first line shows that the root is `accparallelprivate(abc)`. Its children include `acc` and `parallelprivate(abc)`.
The latter has its own children that are listed at other lines.
