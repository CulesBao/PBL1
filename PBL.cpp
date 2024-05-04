#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

const long MAX_ARRAY_SIZE = 1e3;
typedef vector<vector<float>> FloatMatrix;
typedef vector<float> FloatVector;

// Hàm đọc dữ liệu từ file
void readData(int &N, int &M, FloatMatrix &dataMatrix, FloatMatrix &tempDataMatrix) {
    // Đọc dữ liệu từ file data.inp và xuất ra file data.out
    freopen("data.inp", "r", stdin);
    freopen("data.out", "w", stdout);

    // Đọc số hàng và số cột
    cin >> M >> N;

    // Cấp phát bộ nhớ
    dataMatrix.resize(N, FloatVector(M));
    tempDataMatrix.resize(N, FloatVector(M));

    // Đọc giá trị cho ma trận dataMatrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> dataMatrix[i][j];
}

// Ma trận chuyển vị
FloatMatrix transpose(FloatMatrix matrix) {
    FloatMatrix transposedMatrix;
    transposedMatrix.resize(matrix[0].size(), FloatVector(matrix.size()));

    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[0].size(); j++)
            transposedMatrix[j][i] = matrix[i][j];

    return transposedMatrix;
}

//Bước 4: Tính tích 2 ma trận
FloatMatrix step4(FloatMatrix matrix1, FloatMatrix matrix2) {
    // Lấy kích thước của các ma trận
    int N = matrix1.size(); // Số hàng của ma trận 1
    int K = matrix1[0].size(); // Số cột của ma trận 1 (phải bằng số hàng của ma trận 2)
    int M = matrix2[0].size(); // Số cột của ma trận 2

    // Tạo ma trận kết quả và cấp phát bộ nhớ cho nó
    FloatMatrix matrixProduct(N, FloatVector(M, 0.0));

    // Thực hiện phép nhân ma trận
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                matrixProduct[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return matrixProduct;
}

//Bước 5: Tìm trị riêng của ma trận, trả về một vector các kết quả lamda. Sử dụng thuật toán QR
FloatVector findEigenValues(const FloatMatrix &matrix, int maxIterations, float epsilon) {
    int n = matrix.size();

    // Tạo ma trận đơn vị ban đầu
    FloatMatrix Q(n, FloatVector(n, 0.0));
    for (int i = 0; i < n; ++i) {
        Q[i][i] = 1.0;
    }

    FloatMatrix A = matrix;

    // Áp dụng phương pháp QR
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Phân tích QR
        FloatMatrix Q_next = Q;
        FloatMatrix R(n, FloatVector(n, 0.0));
        for (int j = 0; j < n - 1; ++j) {
            for (int i = j + 1; i < n; ++i) {
                // Tính góc quay theta
                float theta = atan2(A[i][j], A[j][j]);
                float c = cos(theta);
                float s = sin(theta);

                // Xây dựng ma trận xoay G
                FloatMatrix G(n, FloatVector(n, 0.0));
                for (int p = 0; p < n; ++p) {
                    for (int q = 0; q < n; ++q) {
                        G[p][q] = (p == q) ? 1.0 : 0.0;
                    }
                }
                G[j][j] = c;
                G[i][i] = c;
                G[j][i] = s;
                G[i][j] = -s;

                // Cập nhật A và Q_next
                A = step4(G, A);
                Q_next = step4(Q_next, G); // Chú ý rằng ta cập nhật Q_next bằng cách nhân G, không phải là ma trận chuyển vị của G
            }
        }

        // Kiểm tra điều kiện hội tụ
        FloatMatrix A_prev = A; // Không cần step4(Q_next, A) ở đây, vì A đã được cập nhật trực tiếp
        float frobeniusNorm = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                frobeniusNorm += (A[i][j] - A_prev[i][j]) * (A[i][j] - A_prev[i][j]);
            }
        }

        if (sqrt(frobeniusNorm) < epsilon) {
            break;
        }

        // Cập nhật ma trận Q
        Q = Q_next;
    }

    // Trích xuất các trị riêng từ ma trận A
    FloatVector eigenValues(n);
    for (int i = 0; i < n; ++i) {
        eigenValues[i] = A[i][i];
    }

    return eigenValues;
}

// Bước 3: Tính sự chênh lệch giữa biến ban đầu và giá trị trung bình tìm được ở bước 2
FloatMatrix step3(int N, int M, FloatMatrix dataMatrix, FloatVector avgVector) {
    FloatMatrix diffMatrix;
    diffMatrix.resize(N, FloatVector(M));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            diffMatrix[i][j] = dataMatrix[i][j] - avgVector[i];

    return diffMatrix;
}

// Bước 2: Tính vector trung bình
FloatVector step2(int N, int M, FloatMatrix dataMatrix) {
    FloatVector avgVector;

    for (int i = 0; i < N; i++) {
        float sum = 0;
        for (int j = 0; j < M; j++)
            sum += dataMatrix[i][j];
        avgVector.push_back(sum / (float)(M));
    }

    return avgVector;
}

// Bước 1: Đọc dữ liệu
int main() {
    // Khai báo
    int N, M;
    FloatMatrix dataMatrix, tempDataMatrix, matrixProduct;
    FloatVector avgVector, eigenValues;

    readData(N, M, dataMatrix, tempDataMatrix);

    avgVector = step2(N, M, dataMatrix);
    tempDataMatrix = step3(N, M, dataMatrix, avgVector);
	matrixProduct = step4(transpose(tempDataMatrix), tempDataMatrix);
    eigenValues = findEigenValues(matrixProduct, 100, 1e-6);
    // In dữ liệu tạm thời ra
    for (int i = 0; i < eigenValues.size(); i++)
        cout << eigenValues[i] << "     ";

    return 0;
}