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

It will produce a library `libaccparser.so` and an executable `main.out`

## Run

To try accparser a bit quickly, a test file `parallel.txt` under `/tests` can be used.

```bash
./main.out ../tests/parallel.txt
```

Input:

```c
#pragma acc parallel private(a, b, c)
```

Output:

```bash
(accparallelprivate(abc)<EOF> acc 
        (parallelprivate(abc) 
            (parallelprivate(abc) parallel 
                (private(abc) 
                    (private(abc) 
                        (private(abc) 
                            (private(abc) private ( 
                                (abc a b c) ))))))) <EOF>)
```

On each line, the output follows the format `(root child_1 child_2 ... child_n)`.
For example, the first line shows that the root is `accparallelprivate(abc)`. Its children include `acc` and `parallelprivate(abc)`.
The latter has its own children that are listed at other lines.
