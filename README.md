### LinearAlgebra

Small LinearAlgebra project. Current functionality supports : 

```cpp
        const auto data = std::vector<double>{  1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                9.0, 8.0, 7.0};
```

## 1. Constructing Vector/Matrix in various ways:
```cpp
    const auto vec = Vector<int>(3);    // empty vector of dimension 3
    const auto mat = Matrix<int>(3,4);  // empty 3x4 matrix
    
    // Init with STL vector (for now data is copied)
    const auto vec_1 = Vector<double>(data);
    const auto mat_1 = Matrix<double>(data, 3, 3); //will throw if specified dimensions are incompatible with data.size()
```

## 2. Copy/move constructors and copy/move assignment operators 
```cpp
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


## 3. Accessing individual values
```cpp
    const auto vec = Vector<double>(data);
    const auto mat = Matrix<double>(data, 3, 3);
    
    std;:cout << vec[2] << std::endl; //will print 3
    vec[2] = 4;
    
    std::cout << mat(0,2) << std::endl; // will print 3
    mat(0,2) = 4;
```

## 4. Vector arithmetic
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

## 5. Matrix arithmetic
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

## 6. Broadcasting a scalar to all elements of the Vector/Matrix
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
  
## 7. Getting and setting matrix rows
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

## 8. Vector dot product (vectors of course must have the same dimension)
```cpp
    const auto vec  = Vector<int>(5);
    const auto otherVec = Vector<double>(5);
    
    const double dot = vec.dot(otherVec);
```

## 9. Matrix multiplication (matrices must have compatible dimensions)
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

## 10. LU decomposition
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto result = matrix.LU();
    // A = LU
    const auto sameMatrix = result.lower.multiply(result.upper);
    
    // If row exchanges are needed during forward elimination, the LU result will contain the permutation matrix as well.
    // In this case, PA = LU
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto result = matrix.LU();
    
    const auto LU = result.lower.multiply(result.upper);
    const auto PA = result.permutation.multiply(matrix);
    
    // For singular matrices this decomposition is a good test since in that case the upper matrix will contain zero pivots
    const auto singular_mat = Matrix<double>(data, 7,7);
    const auto LU_result = singular_mat.LU();
    // LU_result.upper will have (at least one) zero on the diagonal !!
```

## 11. Computing matrix inverse  (NOT IMPLEMENTED YET)
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto inverse = matrix.inverse();
```

## 12. Matrix-vector multiplication
```cpp
    const auto matrix = Matrix<double>(data, 4, 3);
    const auto b = Vector<int>(3);
    
    const auto result = matrix*b;   //Vector<double> of dim 4
```

## 14. Solving A*x = b   (NOT IMPLEMENTED YET)
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto b = Vector<double>(3);

    const auto solution = matrix.solve(b);
```