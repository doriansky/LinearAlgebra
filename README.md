### LinearAlgebra

Small LinearAlgebra project. Current functionality supports : 

# 1. Constructing Vector/Matrix in various ways:
```cpp

```

# 2. Copy/move constructors and copy/move assignment operators 

# 3. Accessing individual values
```cpp
```

# 4. Vector and Matrix arithmetic
```cpp
```

# 5. Broadcasting a scalar (addition, subtraction, multiplication, division)

# 6. Getting and setting matrix rows

# 7. Matrix multiplication

# 8. LU decomposition

```cpp
    const auto matrix = Matrix<double>(data, 3, 3);

    const auto [lower, upper] = matrix.LU();
```