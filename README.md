



### LinearAlgebra

Small LinearAlgebra project. Developed with CLion 2023.2 in Ubuntu 22.04.
Assuming "data" is a vector already populated, the current functionality supports:

### 1. Basic matrix operations

 - Construct from STL vector
 
```cpp
    const auto data = std::vector<double>{1,2,3,4,5,6};
    auto mat 	    = Matrix<double>(data, 3, 2); // 3x2 matrix
```
 - Access individual values
```cpp
    double val	= mat(1,2); //return element from second row, third column
    mat(0,1)	= 3.14; 	//set element from first row, second column
```
 - Matrix arithmetic
```cpp
	const auto mat_A 	= Matrix<double>(data, 4, 5);
	const auto mat_B 	= Matrix<int>(data, 4, 5);
	// result is Matrix<double> in all 4 below examples
	auto result = mat_A + mat_B;
	result = mat_A - mat_B; 
	result = mat_A * mat_B;		// this is element-wise multiplication !
	result = mat_A / mat_B;
```
In place operators can be used as well with the restriction that both operands must have the same type.
 - Broadcast scalar values
```cpp
	const auto mat 		= Matrix<int>(data, 3, 3);
	const float value 	= 3.1415f;
	// result is Matrix<float> in all 4 below examples
	auto result = mat + value;
	result = value + mat; // non-member operator
	result = mat - value;
	result = mat * value;
	result = value * mat; // non-member operator
	result = mat / value;
```
In place operators can be used as well with the restriction that the scalar and the matrix must have the same type.

### 2. Matrix-vector multiplication
Multiply matrix $A$ with vector $x$ to obtain a new vector $y$. The vector $x$ must have dimension equal to the number of columns of $A$, otherwise an exception is thrown.
```cpp
    const auto matrix 	= Matrix<double>(data, 4, 3);
    const auto b        = Vector<int>(3);
    const auto result 	= matrix*b;   //Vector<double> of dim 4
```

### 3. Matrix multiplication
The output of multiplying $A$ and $B$ is computed in the following way : row $i$ of $A*B$ is the linear combination of all the rows of matrix $B$ with coefficients given by the elements of the $i$-th from matrix $A$.

$$
\begin{pmatrix}
a & b\\
c & d\\
\end{pmatrix}
\times
\begin{pmatrix}
x & y & z\\
u & v & w\\
\end{pmatrix}=\begin{pmatrix}
a*[x & y&  z] +b*[u &v &w]\\
c*[x & y&  z] +d*[u &v &w]\\
\end{pmatrix}=\begin{pmatrix}
ax+bu & ay+bv & az+bw\\
cx+du & cy+dv & cz+dw\\
\end{pmatrix}
$$ 

 The multiple scalar-vector products are added directly to the result matrix. No dot products between rows of A and transposed rows of B (that is, columns of B) are required.
```cpp
    const auto mat_A    = Matrix<int>(2, 5);
    const auto mat_B    = Matrix<double>(5, 2);

    const auto resultAB = mat_A.multiply(mat_B);        // 2x2 Matrix<double>
    const auto resultBA = mat_B.multiply(mat_A);        // 5x5 Matrix<double>
```
##### Kind reminder : operator* does elementwise multiplication !

### 4. LU decomposition
Factorize the $M\times N$ matrix in a $M\times M$ lower triangular and a $M\times N$ upper triangular matrix (and an optional $M\times M$ permutation matrix), such that $A = L \times U$ or $P \times A = L \times U$ when row exchanges are required.

LU factorization Example

$$
\begin{pmatrix}
1 & 2 & 3\\
2 & 3 & 1\\
-2 & 3 & -2\\
\end{pmatrix}=
\begin{pmatrix}
1 & 0 & 0\\
2 & 1 & 0\\
-2 & 7 & 1\\
\end{pmatrix}
\times
\begin{pmatrix}
1 & 2 & 3\\
0 & -1 & -5\\
0 & 0 & -31\\
\end{pmatrix}
$$ 

NOTE_1 : For singular or rectangular matrices the function will return as soon as a column is found with zeros below the pivot. The lower and "partial" upper factorization will still reconstruct the input matrix but the U will not be a fully upper matrix (elimination is not complete). Therefore, for singular or rectangular matrices one can use LU_echelon() instead. 
In LU_echelon, the pivots are the first non-zero entries in the rows of the upper-echelon matrix. If the matrix is  $M\times N$ and has $R$ non-zero pivots (the rank) the last $M-R$ rows in the upper echelon matrix will be zeros.

 NOTE_2 : For non-singular square matrices the result is identical with the one provided by LU_factorize().

LU echelon example :

$$
\begin{pmatrix}
1 &3 & 3&2\\
2 &6 & 9&7\\
-1 &-3 & 3&4\\
\end{pmatrix}=
\begin{pmatrix}
1 & 0 & 0\\
2 & 1 & 0\\
-1 & 2 & 1\\
\end{pmatrix}
\times
\begin{pmatrix}
1 &3 & 3&2\\
0 &0 & 3&3\\
0 &0 & 0&0\\
\end{pmatrix}
$$ 

Both methods ``` factorizeLU() ``` and ``` factorizeLU_echelon() ``` return the following struct:
```cpp
    struct LUFactorization
    {
        Matrix<long double>              lower;
        Matrix<long double>              upper;
        std::optional<Matrix<int>>       permutation;
    };
```
Usage example: 
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto result = matrix.factorizeLU();
    // A = LU
    const auto sameMatrix = result.lower.multiply(result.upper);
    
    // If row exchanges are needed during forward elimination, then PA = LU.
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto result = matrix.LU();
    const auto permutation = result.permutation.value();
    // PA = LU
    const auto LU = result.lower.multiply(result.upper);
    const auto PA = permutation.multiply(matrix);
```

### 5. Reduced row echelon form
Compute the reduced row echelon form of the matrix: all pivots are 1 and they are the only entries in their columns (columns of identity). If the matrix is  $M\times N$ and has $R$ non-zero pivots (the rank) the last M-R rows in the row-reduced-echelon matrix will be zeros.

Note: For any square invertible matrix the reduced-row-echelon form is the identity matrix. 

Example for a $3 \times 4$ matrix of rank $2$ : 

$$RRE
\begin{pmatrix}
1 &3&3&2\\
2&6&9&7 \\
-1&-3&3&4\\
\end{pmatrix}
=\begin{pmatrix}
1&3&0&-1\\
0&0&1&1\\
0&0&0&0\\
\end{pmatrix}
$$
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto rre = matrix.reduced_row_echelon();   
```
### 6. Get pivots and rank

The pivots are returned as a vector of the following struct:
```cpp
    struct Pivot
    {
        long double     value;
        unsigned int    rowIndex;
        unsigned int    colIndex;
    };  
```
The rank is a number corresponding to the number of linear independent rows (and columns). It's also equal to the number of pivots.
Usage example: 
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto pivots = matrix.getPivots();
    const unsigned int rank = matrix.rank();
```

### 7. Solving A*x = b
The solution $x$ of $A \times x = b$ is returned in the form of the following struct: 
```cpp
    struct Solution
    {
        bool                                            unique = false;     // indicates if the system has unique solution
        std::optional<Vector<long double>>              uniqueSolution;     // the unique solution: it has value only in one of the following 2 cases:
                                                                            //  1) A is square invertible
                                                                            //  2) A has rank R equal with numCols , R <  numRows and b is in the column space of A 
        std::optional<Vector<long double>>              particularSolution; // A particular solution to Ax = b. It has value only when "unique" is false.
        std::optional<std::vector<Vector<long double>>> specialSolutions;   // STL vector with (numCols - rank) elements, solutions to Ax = 0. It has a value only when the "unique" bool is false.
                                                                            // Any linear combination of the special solutions which is added to the particular solution is also a solution.
    };
        // ----------- NOTE -----------
        // If the "unique" flag is false the Solution will contain one particular solution Xparticular and (numCols - rank) special solutions Xspecial_i.
        // In this case the complete solution is Xcomplete = Xparticular + sum( lambda_i * Xspecial_i), with lambda_i ANY real number.
        // in other words, ANY linear combination of the special solutions added to the particular solution is also a solution.
```
 If the system is not solvable, a std::nullopt is returned. If the system is solvable, there are 4 different scenarios, depending on the matrix rank $R$, its dimensions $M\times N$ and the b-vector:
#####   i)      $R = M$ and $R = N$     :   Matrix is square invertible. In this case the system has unique solution to ANY vector $b$.
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
#####   ii)     $R < M$ and $R = N$     :   System has unique solution if $b$ lies in the column space of $A$ (it must satisfy $M-R$ solvability conditions). It has no solutions otherwise.
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
#####   iii)    $R = M$ and $R < N$     :   System has infinitely many solutions for ANY vector $b$ ( $M - R = 0$ conditions). There will be $N - R$ special solutions.
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
#####   iv)     $R < M$ and $R < N$     :   System has infinitely many solutions if $b$ lies in the column space of $A$ (it must satisfy $M - R$ solvability conditions) and no solutions otherwise. If system is compatible there will be $N - R$ special solutions.
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
For cases iii) and iv) with infinitely many solutions, the complete solution is obtained as the sum between the particular solution $x_p$ (one solution to $A \times x =b$) and any linear combination of the special solutions. This is because the $N-R$ special solutions $x_{special_i}$ are solutions to $A \times x = 0$), therefore:

 $A \times x_{complete} = A \times (x_p + \sum \lambda_i \times x_{special_i})$ = $A \times x_p + A\times \sum \lambda_i \times x_{special_i}$ = $A \times x_p + A\times x_{special_1} + ... A \times x_{special_k} + ...$ = $b + 0 +...+0$ = $b$

### 8. Computing matrix inverse
Gauss-Jordan algorithm is used for computing the inverse. If the matrix is singular (that is, at least one zero pivot is obtained after LU factorization), a null optional is returned.
```cpp
    const auto matrix = Matrix<double>(data, 3, 3);
    const auto inverse = matrix.inverse();
```

> Written with [StackEdit](https://stackedit.io/).
