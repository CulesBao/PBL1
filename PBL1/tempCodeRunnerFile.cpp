//Buoc 5: Tim tri rieng cua ma tran
MatrixXd findEigenValues(MatrixXd matrixProduct) {
    JacobiSVD<MatrixXd> svd(matrixProduct, ComputeFullU | ComputeFullV);

    return svd.singularValues();
}