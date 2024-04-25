#include <bits/stdc++.h>
using namespace std;

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

//Bước 5: Tìm trị riêng của ma trận, trả về một vector các kết quả lamda. Sử dụng thuật toán QR
FloatMatrix step5(FloatMatrix matrix, FloatVector vector, int N, int M){
}

//Bước 4: Tính tích 2 ma trận
FloatMatrix step4(FloatMatrix matrix1, FloatMatrix matrix2, int N, int M){
	FloatMatrix matrixProduct;
	matrixProduct.resize(M, FloatVector(M));

	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++){
			matrixProduct[i][j] = 0;
			for (int k = 0; k < N; k++)
				matrixProduct[i][j] += matrix1[i][k] * matrix2[k][j];
		}

	return matrixProduct;
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
    FloatVector avgVector;

    readData(N, M, dataMatrix, tempDataMatrix);

    avgVector = step2(N, M, dataMatrix);
    tempDataMatrix = step3(N, M, dataMatrix, avgVector);
	matrixProduct = step4(transpose(tempDataMatrix), tempDataMatrix, N, M);

    // In dữ liệu tạm thời ra
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++)
            cout << matrixProduct[i][j] << "		";
        cout << endl;
    }

    return 0;
}