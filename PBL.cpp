#include <bits/stdc++.h>
#include "G:/Nam 1/Ki 2/PBL1/eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
using namespace std;

#define ESP 1e-3
#define endl '\n'
#define INF 1e9
#define ll long long
typedef double db;
#define fori(x, v)     for (auto &x : v)
#define foru(i, a, b) for (int i = a; i <= b; i++)
#define ford(i, a, b) for (int i = a; i >= b; i--)

//Giai he phuong trinh
MatrixXd solveLinearEquation(MatrixXd matrix) {
    FullPivHouseholderQR<MatrixXd> qr(matrix.transpose());
    MatrixXd nullspaceBasis = qr.matrixQ().rightCols(matrix.rows() - qr.rank());

    return nullspaceBasis;
}

//Ham tinh tich co huong 2 ma tran
MatrixXd multipleMatrix(MatrixXd matrix1, MatrixXd matrix2) {
    MatrixXd matrixProduct(matrix1.rows(), matrix2.cols());
    matrixProduct = matrix1 * matrix2;
    return matrixProduct;
}

//Ma tran chuyen vi
MatrixXd transposeMatrix(MatrixXd matrix) {
    MatrixXd transposedMatrix(matrix.cols(), matrix.rows());
    transposedMatrix = matrix.transpose();
    return transposedMatrix;
}

//Buoc 2: Tinh vector trung binh
MatrixXd averageVector(int N, int M, MatrixXd dataMatrix) {
    MatrixXd avgVector(N, 1);
    foru(i, 0, N - 1){
        double sum = 0;
        foru(j, 0, M - 1){
            sum += dataMatrix(i, j);
        }
        avgVector(i, 0) = sum / M;
    }
    return avgVector;
}

//Buoc 3: Tinh su chenh lech giua dataMatrix va avgVector
MatrixXd differenceMatrix(int N, int M, MatrixXd dataMatrix, MatrixXd avgVector) {
    MatrixXd diffMatrix(N, M);
    foru(i, 0, N - 1){
        foru(j, 0, M - 1){
            diffMatrix(i, j) = dataMatrix(i, j) - avgVector(i, 0);
        }
    }
    return diffMatrix;
}

//Buoc 5: Tim tri rieng cua ma tran
MatrixXd findEigenValues(MatrixXd matrixProduct) {
    vector<double> eigenValues;

    JacobiSVD<MatrixXd> svd(matrixProduct, ComputeFullU | ComputeFullV);
    
    // Loc cac gia tri rieng
    for (int i = 0; i < svd.singularValues().size(); ++i) {
        if (svd.singularValues()(i) >= ESP) {
            eigenValues.push_back(svd.singularValues()(i));
        }
    }
    
    // Tao ra ma tran moi chua cac tri rieng
    MatrixXd newEigenValues(eigenValues.size(), 1);
    for (int i = 0; i < eigenValues.size(); ++i) {
        newEigenValues(i, 0) = eigenValues[i];
    }

    return newEigenValues;
}

//Buoc 6: Tinh cac vector tuong ung voi cac tri rieng
MatrixXd findEigenVectors(MatrixXd matrixProduct, MatrixXd eigenValues) {
    MatrixXd eigenVectors(matrixProduct.rows(), eigenValues.size()), tempMatrix(matrixProduct.rows(), matrixProduct.cols());
    foru (k, 0, eigenValues.size() - 1) {
        foru(i, 0, matrixProduct.rows() - 1) {
            foru(j, 0, matrixProduct.cols() - 1) {
                tempMatrix(i, j) = matrixProduct(i, j);
                if (i == j)
                    tempMatrix(i, j) -= eigenValues(k, 0);
            }
        }
        MatrixXd equation = solveLinearEquation(tempMatrix);
        //Day vao eigenVectors
        eigenVectors.col(k) = equation.col(0);
    }

    return eigenVectors;
}

//Buoc 8: Rut gon ansVector
MatrixXd normalizeVector(MatrixXd ansVector) {
    vector <double> normVector;
    foru(i, 0, ansVector.cols() - 1) {
        double norm = 0;
        foru(j, 0, ansVector.rows() - 1) {
            norm += ansVector(j, i) * ansVector(j, i);
        }
        normVector.push_back(sqrt(norm));
    }

    foru(i, 0, ansVector.cols() - 1) {
        foru(j, 0, ansVector.rows() - 1) {
            ansVector(j, i) /= normVector[i];
        }
    }

    return ansVector;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef online_judge
        freopen("data1.inp", "r", stdin);
        freopen("data.out", "w", stdout);
    #endif

    int N, M;

    // Buoc 1: Doc du lieu
    cin >> M >> N;
    MatrixXd dataMatrix(N, M), avgVector(N, 1), diffMatrix(N, M), matrixProduct(N, M), tranMatrix(N, M), eigenValues(N, 1), eigenVectors(N, M);
    foru(i, 0, N - 1)
        foru(j, 0, M - 1)
            cin >> dataMatrix(i, j);
    
    //Buoc 2: Tinh vector trung binh
    avgVector = averageVector(N, M, dataMatrix);

    //Buoc 3: Tinh su chenh lech giua dataMatrix va avgVector
    diffMatrix = differenceMatrix(N, M, dataMatrix, avgVector);

    //Buoc 4: Tinh tich 2 ma tran
    tranMatrix = transposeMatrix(diffMatrix);
    matrixProduct = multipleMatrix(tranMatrix, diffMatrix);

    //Buoc 5: Tim tri rieng cua ma tran
    eigenValues = findEigenValues(matrixProduct);

    //Buoc 6: Tinh cac vector tuong ung voi cac tri rieng
    eigenVectors = findEigenVectors(matrixProduct, eigenValues);

    //Buoc 7: Tinh tich 2 ma tran ansVector = matrixProduct * eigenVectors
    MatrixXd ansVector = multipleMatrix(diffMatrix, eigenVectors);

    //Buoc 8: Rut gon ansVector
    ansVector = normalizeVector(ansVector);

    //Buoc 9: Xuat ket qua
    cout << ansVector << endl;

    return 0;
}