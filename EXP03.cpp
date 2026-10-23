
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

using Matrix = vector<vector<int>>;

Matrix add(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

Matrix subtract(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}

Matrix conventionalMultiply(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

Matrix strassen(Matrix A, Matrix B) {
    int n = A.size();

    // Base case
    if (n <= 2)
        return conventionalMultiply(A, B);

    int k = n / 2;

    Matrix A11(k, vector<int>(k));
    Matrix A12(k, vector<int>(k));
    Matrix A21(k, vector<int>(k));
    Matrix A22(k, vector<int>(k));

    Matrix B11(k, vector<int>(k));
    Matrix B12(k, vector<int>(k));
    Matrix B21(k, vector<int>(k));
    Matrix B22(k, vector<int>(k));

    // Divide matrices into four submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Calculate the seven products
    Matrix M1 = strassen(add(A11, A22),
                         add(B11, B22));

    Matrix M2 = strassen(add(A21, A22), B11);

    Matrix M3 = strassen(A11, subtract(B12, B22));

    Matrix M4 = strassen(A22, subtract(B21, B11));

    Matrix M5 = strassen(add(A11, A12), B22);

    Matrix M6 = strassen(subtract(A21, A11),
                         add(B11, B12));

    Matrix M7 = strassen(subtract(A12, A22),
                         add(B21, B22));

    // Calculate the four result submatrices
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    // Combine the submatrices
    Matrix C(n, vector<int>(n));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

Matrix multiply(Matrix A, Matrix B) {
    int n = A.size();

    if (n == 0 || B.size() != n)
        throw invalid_argument("Invalid matrix dimensions");

    for (int i = 0; i < n; i++) {
        if (A[i].size() != n || B[i].size() != n)
            throw invalid_argument("Matrices must be square");
    }

    // Pad to the next power of two
    int size = 1;
    while (size < n)
        size *= 2;

    Matrix Ap(size, vector<int>(size, 0));
    Matrix Bp(size, vector<int>(size, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            Ap[i][j] = A[i][j];
            Bp[i][j] = B[i][j];
        }

    Matrix Cp = strassen(Ap, Bp);

    // Remove padding
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = Cp[i][j];

    return C;
}

int main() {
    int n;
    cout << "Enter matrix size: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid matrix size\n";
        return 1;
    }

    Matrix A(n, vector<int>(n));
    Matrix B(n, vector<int>(n));

    cout << "Enter elements of matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter elements of matrix B:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    Matrix C = multiply(A, B);

    cout << "Product matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << C[i][j] << " ";
        cout << '\n';
    }

    return 0;
}
