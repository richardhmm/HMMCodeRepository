HMMCodeRepository
==============
personal code repository


Compile environment
-----------
1. Linux (Ubuntu 10.04.4 LTS x86_64), G++, Makefile.
2. install log4cplus.
3. install gtest.

Build instructions
-----------
1. build library && example && unit test
```c
$ cd HMMCodeRepository
$ ./build
```

2. build library
```c
$ cd HMMCodeRepository
$ ./build-lib
```

3. build example
```c
$ cd HMMCodeRepository
$ ./build-example
```

4. build unit test
```c
$ cd HMMCodeRepository
$ ./build-gtest
```

Path tree instructions
-----------
```c
HMMCodeRepository  // library root path
|-- example        // demo code
|   `-- algorithm
|-- lib           // library source code
|   `-- algorithm
|       |-- inc   // interface include files
|       |-- src   // many algorithm source code
|       `-- test  // unit test source code by using gtest
`-- res           // resource
```