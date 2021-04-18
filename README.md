# MatrixedCpp

Little library implementing matrices in C++.

### Usage

```c++
// Initialise matrices at 0
CMatrix<int> matrix1 = CMatrix<int>(3, 3);
CMatrix<int> matrix2 = CMatrix<int>(3, 3);
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        matrix1.MATSetItemAt(i, j, 1);
        matrix2.MATSetItemAt(i, j, 2);
    }
}
// Playaround
CMatrix<int> result;
result = matrix1 + matrix2;
result.MATPrint();
result = matrix1 * matrix2;
result.MATPrint();
result = matrix1 * 3;
result.MATPrint();
result = matrix2 / 6;
result.MATPrint();
result = *matrix1.MATTranspose();
result.MATPrint();
// ...
```

A *main function* is included in the project so that you can test out the library. 
Program arguments must be serialized matrix files in the following format:

```
TypeMatrice=double
NBLignes=[int]
NBColonnes=[int]
Matrice=[
a b c ...
d e f ...
...
]
```

For examples, see [Information](#information) 

### Information

- Sources under `src/`
- Headers under `include/`
- Serialized matrices test files under `tests/`

> Made with CLion and CMake under Ubuntu 20.04 KER 5.8.0.50 by Garofalo Lucas and Tardieu Eliott