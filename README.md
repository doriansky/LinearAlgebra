### LinearAlgebra

Small LinearAlgebra project. Developed with CLion 2023.2 in Ubuntu 22.04.
Assuming "data" is a vector already populated, the current functionality supports:

## 1. Constructing Vector/Matrix in various ways:
```cpp
    const auto vec = Vector<int>(3);    // empty vector of dimension 3
    const auto mat = Matrix<int>(3,4);  // empty 3x4 matrix
    
    // Init with STL vector (for now data is copied)
    const auto vec_1 = Vector<double>(data);
    const auto mat_1 = Matrix<double>(data, 3, 3); //will throw if specified dimensions are incompatible with data.size()
```

```cpp
    //Copy & move constructors
    const auto vec = Vector<int>(3);
    const auto mat = Matrix<int>(3,4);

    const auto otherVec(vec);
    ....
    const auto otherVec(std::move(vec));
    ....
    auto otherVec = Vector<double>(2);
    otherVec = testVec;
    otherVec = std::move(testVec);
    
    ....
    const auto otherMat(mat);
    const auto otherMat(std::move(testMat));
    
    ....
    auto otherMat = Matrix<float>(2, 2);
    otherMat = testMat;
    otherMat = std::move(testMat);
```

```cpp
    // Accessing individual values
    const auto vec = Vector<double>(data);
    const auto mat = Matrix<double>(data, 3, 3);
    
    std;:cout << vec[2] << std::endl;
    vec[2] = 4;
    
    std::cout << mat(0,2) << std::endl;
    mat(0,2) = 4;
```

## 2. Vector arithmetic
#### Note that all operators will throw if the dimensions of the 2 vectors are incompatible.
```cpp
    const auto vec = Vector<int>(3);
    const auto otherVec = Vector<int>(3);
    const auto floatVec = Vector<float>(3);
    const auto doubleVec = Vector<double>(3);
    //... populate values
    
    const auto result = vec + otherVec; // result is Vector<int>
    const auto result = vec - otherVec; // result is Vector<int>
    const auto result = vec + floatVec; // result is a Vector<float>
    const auto result = vec - doubleVec;// result is a Vector<double>
    
    //Element-wise multiplication and division
    const auto result = vec * otherVec; // result is Vector<int>
    const auto result = vec * floatVec; // result is Vector<float>

    const auto result = vec / otherVec; // result is Vector<int> !!!
    const auto result = vec / floatVec; // now is a Vector<float>
    const auto result = vec / doubleVec;// and now is a Vector<double> 
```
#### One can use the in-place versions of the above operators, however the "other" operand must have the same type !
```cpp
    vec += otherVec;
    vec -= otherVec;
    vec *= otherVec;
    vec /= otherVec;
    
    // These will not compile !
    vec += floatVec;
    vec *= doubleVec;
    floatVec /= vec;
    doubleVec -= floatVec;
```

## 3. Matrix arithmetic
#### Note that all operators will throw if the dimensions of the 2 matrices are incompatible.
```cpp
    const auto mat = Matrix<int>(3,4);
    const auto otherMat = Matrix<int>(3,4 );
    const auto floatMat = Matrix<float>(3,4 );
    const auto doubleMat = Matrix<double>(3,4 );
    //... populate values
    
    const auto result = mat + otherMat;     // result is int mat
    const auto result = mat - otherMat;     // result is int mat
    const auto result = mat - floatMat;     // result is float mat
    const auto result = mat - doubleMat;    // result is double mat
    const auto result = floatMat - doubleMat;    // result is double mat
    
    //Element-wise multiplication and division
    const auto result = mat * otherMat; // not matrix multiplication ! Result is int mat.
    const auto result = mat / otherMat; // result is int mat !
    const auto result = mat / floatMat; // now is float mat 
    const auto result = mat / doubleMat; // and now is double mat
```
#### One can use the in-place versions of the above operators however the "other" operand must have the same type !
```cpp
    mat += otherMat;
    mat -= otherMat;
    mat *= otherMat;
    mat /= otherMat;
    
    // These will not compile !
    mat += floatMat;
    mat -= doubleMat;
    floatMat *= mat;
    doubleMat /= floatMat;
```

## 4. Broadcasting a scalar to all elements of the Vector/Matrix
```cpp
    const auto vec = Vector<int>(3);
    const auto floatVec = Vector<float>(3);
    const auto doubleVec = Vector<double>(3);
    
    const auto mat = Matrix<int>(5,3);
    const auto floatMat = Matrix<float>(5,3);
    const auto doubleMat = Matrix<double>(5,3);
    //... populate values

    const int intValue = 3;
    const float floatValue = 3.14f;
    const float doubleValue = 3.14;

    const auto vecResult = vec + intValue;          // result is int vec
    const auto vecResult = vec - floatValue;        // result is float vec
    const auto vecResult = vec * doubleValue;       // result is double vec
    const auto vecResult = vec / intValue;          // result is int vec
    const auto vecResult = vec / floatValue;        // result is float vec
    const auto vecResult = floatVec + doubleValue;  // result is double vec

    const auto matResult = mat + intValue;          // result is int mat
    const auto matResult = mat - floatValue;        // result is float mat
    const auto matResult = mat * doubleValue;       // result is double mat
    const auto matResult = mat / intValue;          // result is int mat
    const auto matResult = mat / doubleValue;       // result is double mat
    const auto matResult = floatMat / intValue;     // result is float mat
    const auto matResult = floatMat / doubleValue;  // result is double mat
```

#### For + and * There are also the non-member operators which allow putting the scalar first. The rules for types exemplified above are still valid.
```cpp
    const auto vec = Vector<float>(3);
    const auto mat = Matrix<float>(5,3);
    //... populate values
    
    const float value = 3.14f;

    const auto vecResult = value + vec;
    const auto vecResult = value * vec;

    const auto matResult = value + mat;
    const auto matResult = value * mat;
```
#### One can use the in-place versions of the above operators but the scalar must have the same type as the Vector/Matrix :
```cpp
    mat += value;
    vec -= value;
    mat /= value
    vec *= value;
    
    // This will not compile
    const auto intVec = Vector<int>(5);
    intVec += 3.14f;
```
  
## 5. Getting and setting matrix rows
##### Both getRow and setRow throw if the row index is bigger than the number of rows or if the dimension of the provided row is bigger than the number of columns
```cpp
    auto mat = Matrix<int>(2, 5);
    //.. populate values
    
    const auto row = mat.getRow(1); // returns vector of dimension 5

    // Set row from STL vector
    mat.setRow({0, 1, -2, 6, 3}, 0); // set first row
    // Set row from other Vector
    const auto vec = Vector<int>(5);
    mat.setRow(vec, 1);  // set second row
```

## 6. Vector dot product
```cpp
    const auto vec  = Vector<int>(5);
    const auto otherVec = Vector<double>(5);
    
    const double dot = vec.dot(otherVec);   //will throw is vectors have different dimensions
```

## 7. Matrix-vector multiplication
```cpp
    const auto matrix = Matrix<double>(data, 4, 3);
    const auto b = Vector<int>(3);
    
    const auto result = matrix*b;   //Vector<double> of dim 4
```

## 8. Matrix multiplication (matrices must have compatible dimensions)
#### The output of multiplying A and B is computed in the following way : row i of A*B is the linear combination of all the rows of matrix B with coefficients given by the elements of the i-th from matrix A.

```cpp
        |  a    b |     | x  y   z  |       | a*[x y z] + b[u v w]  |       | ax + bu   ay + bv     az + bw |
        |         |  *  |           |    =  |                       |   =   |                               |
        |  c    d |     | u  v   w  |       | c*[x y z] + d[u v w]  |       | cx + du   cy + dv     cz + dw |    
```

####    The multiple scalar-vector products are added directly to the result matrix. No dot products between rows of A and transposed rows of B (that is, columns of B) are required.
```cpp
    const auto mat_A    = Matrix<int>(2, 5);
    const auto mat_B    = Matrix<double>(5, 2);

    const auto resultAB = mat_A.multiply(mat_B);        // 2x2 Matrix<double>
    const auto resultBA = mat_B.multiply(mat_A);        // 5x5 Matrix<double>
```
##### Kind reminder : operator* does elementwise multiplication !

## 9. LU decomposition
##### Factorize the MxN matrix in a lower M x M triangular and a M x N upper triangular matrix (and an optional M X M permutation matrix), such that A = L*U or P*A = L*U when row exchanges are required.
#####        * NOTE : For singular or rectangular matrices the function will return as soon as a column is found with zeros below the pivot. The lower and "partial" upper factorization will still reconstruct the input matrix but the U will not be a fully upper matrix (elimination is not complete). Therefore, for singular or rectangular matrices one can use LU_echelon() instead.

```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto result = matrix.factorizeLU();
    // A = LU
    const auto sameMatrix = result.lower.multiply(result.upper);
    
    // If row exchanges are needed during forward elimination, the LU result will contain the permutation matrix as well.
    // In this case, PA = LU
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto result = matrix.LU();
    
    const auto LU = result.lower.multiply(result.upper);
    // will be equal with
    const auto permutation = result.permutation.value();
    const auto PA = permutation.multiply(matrix);  
    
    // For singular matrices this decomposition is a good test since in that case the upper matrix will contain zero pivots
    const auto singular_mat = Matrix<double>(data, 7,7);
    const auto LU_result = singular_mat.LU();
    // LU_result.upper will have (at least one) zero on the diagonal !!
```

## 10. LU-echelon decomposition
##### Factorize the MxN matrix in a lower M x M triangular and a M x N upper-echelon triangular matrix (and an optional M X M permutation matrix). such that A = L*U_echelon or P*A = L*U_echelon when row exchanges are required.
##### The pivots are the first non-zero entries in the rows of the upper-echelon matrix. If the matrix is MxN and has R non-zero pivots (the rank) the last M-R rows in the upper echelon matrix will be zeros.
#####        * NOTE : For non-singular square matrices the result is identical with the one provided by LU_factorize().
#####
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto result = matrix.factorizeLU_echelon();
    
```

## 11. Reduced row echelon form
##### Compute the reduced row echelon form of the matrix: all pivots are 1 and they are the only entries in their columns (columns of identity). If the matrix is MxN and has R non-zero pivots (the rank) the last M-R rows in the row-reduced-echelon matrix will be zeros.
##### 
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto rre = matrix.reduced_row_echelon();
    
```

## 12. Solving A*x = b
#####   Solve Ax = b and return the following optional struct:
```cpp
    struct Solution
    {
        bool                                            unique = false;     // indicates if the system has unique solution
        std::optional<Vector<long double>>              uniqueSolution;     // the unique solution: it has value only in one of the following 2 cases:
                                                                            //  1). A is square invertible
                                                                            //  2). A has rank R equal with numCols , R <  numRows and b is in the column space of A 
        std::optional<Vector<long double>>              particularSolution; // A particular solution to Ax = b. It has value only when "unique" is false.
        std::optional<std::vector<Vector<long double>>> specialSolutions;   // STL vector with (numCols - rank) elements, solutions to Ax = 0. It has a value only when the "unique" bool is false.
                                                                            // Any linear combination of the special solutions which is added to the particular solution is also a solution.
    };
        // ----------- NOTE -----------
        // If the "unique" flag is false the Solution will contain one particular solution Xparticular and (numCols - rank) special solutions Xspecial_i.
        // In this case the complete solution is Xcomplete = Xparticular + sum( lambda_i * Xspecial_i), with lambda_i ANY real number.
        // in other words, ANY linear combination of the special solutions added to the particular solution is also a solution.
```
#####   If the system is not solvable, a std::nullopt is returned. If the system is solvable, there are 4 different scenarios, depending on the matrix rank R, its dimensions (numRows, numCols) and the b-vector:
#####   i)      R = numRows and R = numCols     :   In this case the system has unique solution to ANY vector b.
```cpp
    const auto data = std::vector<int>{ 1,0,1,
                                        1,1,0,
                                        1,1,1};
    const auto matrix = Matrix<int>(data, 3, 3);
    const auto b = Vector<int>({4,3,6});

    const auto solution = matrix.solve(b).value();
    ASSERT_TRUE(solution.unique);
    //Get unique solution
    const auto x = solution.uniqueSolution.value();    // x = {1,2,3};
```
#####   ii)     R < numRows and R = numCols     :   System has unique solution if b lies in the column space of A (it must satisfy (numRows - R) solvability conditions). It has no solutions otherwise.
```cpp
    const auto data = std::vector<int>{ 1,2,
                                        2,4,
                                        2,5,
                                        3,9};
    const auto matrix = Matrix<int>(data, 4, 2);
    const auto b = Vector<int>({1,2,3,6});

    const auto solution = matrix.solve(b).value();
    ASSERT_TRUE(solution.unique);
    //Get unique solution
    const auto x = solution.uniqueSolution.value();    // x = {-1,1};
    
    // If b is not in the column space of A the system is incompatible and a std::nullopt is returned.
    const auto b = Vector<int>({1,2,3,3});

    const auto solution = matrix.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
```
#####   iii)    R = numRows and R < numCols     :   System has infinitely many solutions for ANY vector b ( numRows - R = 0 conditions). There will be (numCols - R) special solutions.
```cpp
    const auto data = std::vector<int>{ 1,0,2,3,
                                        1,3,2,0,
                                        2,0,4,9};


    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<int>({2,5,10});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value(); // x_particular is {-4,3,0,2}.

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variable
    const auto specialSolution = specialSolutions[0];   // x_special is {-2, 0, 1, 0}
    
    // Any linear combination of x_special added to x_particular is a solution !
    const auto completeSolution = particularSolution + 1.3455 * specialSolution;
```
#####   iv)     R < numRows and R < numCols     :   System has infinitely many solutions if b lies in the column space of A (it must satisfy (numRows - R) solvability conditions) and no solutions otherwise. If system is compatible there will be (numCols - R) special solutions.
```cpp
    const auto data = std::vector<int>{ 1,3,1,2,
                                        2,6,4,8,
                                        0,0,2,4};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({1,3,1});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value(); // x_particular is {0.5, 0, 0.5, 0};
    
    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables
    
    const auto specialSolution_1 = specialSolutions[0]; // x_special_1 = {-3,1,0,0};
    const auto specialSolution_2 = specialSolutions[1]; // x_special_2 = {0,0,-2,0};

    // Any linear combination of the special solutions added to x_particular is a solution !
    const auto completeSolution = particularSolution + 1.3455 * specialSolution_1 + 3.1415 * specialSolution_2;
    
    // Incompatible system is b is not in the column space of A
    const auto b = Vector<double>({1,2,1});
    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
```



## 14. Computing matrix inverse
##### Gauss-Schmidt algorithm is used for computing the inverse. If the matrix is singular (that is, at least one zero pivot is obtained after LU factorization), a null optional is returned.
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto inverse = matrix.inverse();
```