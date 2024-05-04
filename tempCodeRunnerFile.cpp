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