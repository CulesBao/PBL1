    // // Lọc các giá trị riêng
    // for (int i = 0; i < svd.singularValues().size(); ++i) {
    //     if (svd.singularValues()(i) >= threshold) {
    //         eigenValues.push_back(svd.singularValues()(i));
    //     }
    // }
    
    // // Tạo ma trận mới chứa các giá trị riêng đã lọc
    // MatrixXd newEigenValues(eigenValues.size(), 1);
    // for (int i = 0; i < eigenValues.size(); ++i) {
    //     newEigenValues(i, 0) = eigenValues[i];
    // }