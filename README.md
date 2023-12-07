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
    //... populate values
    
    const auto result = vec + otherVec;
    const auto result = vec - otherVec;
    //Element-wise multiplication and division
    const auto result = vec * otherVec;
    const auto result = vec / otherVec;
```
#### One can use the in-place versions of the above operators
```cpp
    vec += otherVec;
    vec -= otherVec;
    vec *= otherVec;
    vec /= otherVec;
```

## 5. Matrix arithmetic
#### Note that all operators will throw if the dimensions of the 2 matrices are incompatible.
```cpp
    const auto mat = Matrix<int>(3,4);
    const auto otherMat = Matrix<int>(3,4 );
    //... populate values
    
    const auto result = mat + otherMat;
    const auto result = mat - otherMat;
    //Element-wise multiplication and division
    const auto result = mat * otherMat; // not matrix multiplication !
    const auto result = mat / otherMat;
```
#### One can use the in-place versions of the above operators
```cpp
    mat += otherMat;
    mat -= otherMat;
    mat *= otherMat;
    mat /= otherMat;
```

## 6. Broadcasting a scalar to all elements of the Vector/Matrix
```cpp
    const auto vec = Vector<float>(3);
    const auto mat = Matrix<float>(5,3);
    //... populate values
    
    const float value = 3.14f;

    const auto vecResult = vec + value;
    const auto vecResult = vec - value;
    const auto vecResult = vec * value;
    const auto vecResult = vec / value;

    const auto matResult = mat + value;
    const auto matResult = mat - value;
    const auto matResult = mat * value;
    const auto matResult = mat / value;
```

#### For + and * There are also the non-member operators which allow putting the scalar first
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
#### One can use the in-place versions of the above operators, e.g:
```cpp
    mat += value;
    vec -= value;
    mat /= value
    vec *= value;
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
    const auto vec  = Vector<double>(5);
    const auto otherVec = Vector<double>(5);
    
    const double dot = vec.dot(otherVec);
```

## 9. Matrix multiplication (matrices must have compatible dimensions)
```cpp
    const auto mat_A    = Matrix<int>(2, 5);
    const auto mat_B    = Matrix<int>(5, 2);

    const auto resultAB = mat_A.multiply(mat_B);
    const auto resultBA = mat_B.multiply(mat_A);
```

## 10. LU decomposition
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto [lower, upper] = matrix.LU();
```

## 11. Computing matrix inverse  (NOT IMPLEMENTED YET)
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto inverse = matrix.inverse();
```


## 12. Solving A*x = b   (NOT IMPLEMENTED YET)
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto b = Vector<double>(3);

    const auto solution = matrix.solve(b);
```