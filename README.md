# Sparse-Matrix-with-linked-list
You are required to add the following public methods to this class:
1. read(string filename):
This method should be able to read an M x N matrix from a text file. Each line in the file
contains all the entries in that row (including the zeros) separated by spaces. There is one
row per line. Following is how the matrix shown in the previous picture will be stored in
the file:
00304
00570
00000
02600
This file contains 4 lines. The characters in each line are separated by a space. Your
function should be able to load this matrix as an object of SparseMatrix, as described
above.

2. SparseMatrix(string filename)
Constructor. Simply uses read to read the matrix from the specified file.
3. SparseMatrix(const SparseMatrix& obj)
A regular copy constructor creates a deep copy.
4. const SparseMatrix & operator = (const
SparseMatrix & obj) A regular assignment operator
creates a deep copy.
5. ~SparseMatrix()
Destructor cleans up all the allocated memory.

6. SparseMatrix operator + (const SparseMatrix & obj)
Adds two Sparse Matrices of same dimensions and returns the result in a third Sparse
Matrix
7. SparseMatrix operator * (const SparseMatrix & obj)
Multiplies two Sparse Matrices with compatible dimensions for multiplication; say, M1
X N1 and N1 X L1, and returns their M1xL1 resultant product Sparse Matrix.
8. bool isSubMatrix(const SparseMatrix & obj)
Returns true if the matrix obj is completely contained in the current matrix.
Returns false otherwise.
For example, the matrix [ ] is a sub-matrix of [ ] .
Again, note that your matrices are stored in the space efficient manner described
above and must never be reconstructed into MxN arrays at any point in your
program.
9. Inverse of a sparse matrix(minimum of 3 x 3)
10. Check whether the sparse matrix is symmetric or skew symmetric.
