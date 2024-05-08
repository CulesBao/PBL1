#include <bits/stdc++.h>
#include "./eigen-3.4.0/Eigen/Dense"
#include <windows.h>

using namespace Eigen;
using namespace std;

#define ESP 1e-3
#define endl '\n'
#define ll long long
#define fori(x, v)     for (auto &x : v)
#define foru(i, a, b) for (int i = a; i <= b; i++)
#define ford(i, a, b) for (int i = a; i >= b; i--)

bool isPrintToConsole = true;
ifstream input;
ofstream output;

//Doc du lieu
void readData(int &N, int &M, MatrixXd &dataMatrix, int choose) {
    if (choose == 1 || choose == 2 || choose == 3) {
        input >> N >> M;
        dataMatrix.resize(N, M);
        foru(i, 0, N - 1) {
            foru(j, 0, M - 1) input >> dataMatrix(i, j);
        }
    }
    else{
        cin >> N >> M;
        dataMatrix.resize(N, M);
        foru(i, 0, N - 1) {
            foru(j, 0, M - 1) cin >> dataMatrix(i, j);
        }
    }
}

void welcome() {
    cout << "********************************************************************************" << endl;
    cout << "*                         DO AN LAP TRINH TINH TOAN 1                          *" << endl;
    cout << "*                    PHAN TICH TRUC TIEP CAC THANH PHAN PCA                    *" << endl;
    cout << "********************************************************************************" << endl << endl;

    cout << "Thong tin ve chuong trinh: " << endl;
    cout << "-  Giang vien huong dan: PGS.TS Nguyen Tan Khoi" << endl;
    cout << "-  Sinh vien thuc hien: Duong Van Chi Bao va Vo Hoang Thai Bao" << endl;
    cout << "-  Lop sinh hoat: 23T-DT4" << endl << endl;
}

void inputSeclection(int &N, int &M, MatrixXd &dataMatrix) {
    cout << "********************************************************************************" << endl;
    cout << "*                            CHON DU LIEU TUY CHINH                            *" << endl;
    cout << "********************************************************************************" << endl << endl;

    cout << "An 1: Chon du lieu tu tep data1.inp (du lieu duoc lay tu file word cua Le Hoang Thanh)" << endl;
    cout << "An 2: Chon du lieu tu tep data2.inp (du lieu duoc lay tu Github cua toosyou)" << endl;
    cout << "An 3: Chon du lieu tu tep data3.inp (du lieu duoc lay tu Wikipedia)" << endl;
    cout << "An 4: Nhap du lieu tu ban phim" << endl;
    int c;
    do{
        c = 0;
        cout << endl << "Moi chon: ";
        cout << flush;
        cin >> c;
        if (c < 1 || c > 4) {
            cout << "So vua nhap khong phu hop. Vui long chon lai!" << endl;
        }
    }
    while (c < 1 || c > 4);
    switch (c) {
        case 1:
            input.open("data1.inp");
            cout << "Ban da chon: bo du lieu data1.inp!" << endl;
            break;
        case 2:
            input.open("data2.inp");
            cout << "Ban da chon: bo du lieu data2.inp!" << endl;
            break;
        case 3:
            input.open("data3.inp");
            cout << "Ban da chon: bo du lieu data3.inp!" << endl;
            break;
        case 4:
            cout << "Ban da chon: Nhap du lieu tu ban phim" << endl << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "|                          QUY DINH CACH NHAP DU LIEU                          |" << endl;
            cout << "|  Dong dau tien: 2 so nguyen N va M.                                          |" << endl;
            cout << "|  N dong tiep theo: Moi dong gom M , cac so cach nhau boi mot khoang trang    |" << endl;
            cout << "|  Vui long nhap du lieu o ben duoi.                         |" << endl; 
            cout << "--------------------------------------------------------------------------------" << endl << endl;
            break;
    }
    cout << flush;
    readData(N, M, dataMatrix, c);
    if (c == 1 || c == 2 || c == 3){
        input.close();
    }
    cout << "Du lieu da duoc nhap xong!" << endl << endl;
}

void outputSeclection() {
    cout << "********************************************************************************" << endl;
    cout << "*                            LUA CHON DINH DANG XUAT                           *" << endl;
    cout << "********************************************************************************" << endl << endl;

    cout << "An 1: Xuat du lieu ra tep data.out" << endl;
    cout << "An 2: Xuat du lieu ra Terminal" << endl;

    int choose;
    do{
        choose = 0;
        cout << endl << "Moi chon kieu du lieu: ";
        cout << flush;
        cin >> choose;
        if (choose < 1 || choose > 2) {
            cout << "So vua nhap khong phu hop. Vui long chon lai!" << endl;
        }
    }
    while (choose < 1 || choose > 2);
    switch (choose) {
        case 1:
            cout << "Ban da chon: Du lieu se duoc xuat ra o tep data.out" << endl;
            output.open("data.out");
            isPrintToConsole = false;
            break;
        case 2:
            cout << "Ban da chon: Du lieu se duoc xuat ra o Terminal" << endl << endl;
            break;
    }
}

void instruction() {
    cout << "********************************************************************************" << endl;
    cout << "*                               KET QUA TINH TOAN                              *" << endl;
    cout << "********************************************************************************" << endl << endl;

    cout << "Viec tinh toan da hoan tat! Sau day la cac buoc ma chuong trinh da thuc hien:" << endl << endl;
    cout << "Buoc 1: Doc du lieu" << endl;
    cout << "Buoc 2: Tinh vector trung binh" << endl;
    cout << "Buoc 3: Tinh su chenh lech giua dataMatrix va avgVector" << endl;
    cout << "Buoc 4: Tinh tich 2 ma tran" << endl;
    cout << "Buoc 5: Tim tri rieng cua ma tran" << endl;
    cout << "Buoc 6: Tinh cac vector tuong ung voi cac tri rieng" << endl;
    cout << "Buoc 7: Tinh tich 2 ma tran ansVector = matrixProduct * eigenVectors" << endl;
    cout << "Buoc 8: Rut gon ansVector" << endl;
    cout << "Buoc 9: Xuat ket qua tuy theo lua chon" << endl << endl;
}

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

//Buoc 0: Lua chon dau vao
void inputoutputSetup(int &N, int &M, MatrixXd &dataMatrix) {
    welcome();
    Sleep(1000);
    inputSeclection(N, M, dataMatrix);
    Sleep(500);
    outputSeclection();
    Sleep(500);
    instruction();
    Sleep(500);
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

MatrixXd findEigenValues(MatrixXd matrixProduct) {
    JacobiSVD<MatrixXd> svd(matrixProduct, ComputeFullU | ComputeFullV);

    // Số lượng giá trị riêng khác không
    int nonZeroEigenValues = 0;
    for (int i = 0; i < svd.singularValues().size(); ++i) {
        if (svd.singularValues()(i) != 0) {
            nonZeroEigenValues++;
        }
    }

    // Tạo ma trận chứa giá trị riêng
    MatrixXd eigenValuesMatrix(nonZeroEigenValues, 1);
    int index = 0;
    for (int i = 0; i < svd.singularValues().size(); ++i) {
        if (svd.singularValues()(i) != 0) {
            eigenValuesMatrix(index++, 0) = svd.singularValues()(i);
        }
    }

    return eigenValuesMatrix;
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

//Buoc 9: Xuat ket qua
void printOutput(int N, int M, MatrixXd dataMatrix, MatrixXd avgVector, MatrixXd diffMatrix, MatrixXd matrixProduct, MatrixXd eigenValues, MatrixXd eigenVectors, MatrixXd ansVector) {
    ofstream output;
    output.open("data.out");
    cout << "Nhan tu 2 toi 8 de in ra ket qua o cac buoc tuong ung. Nhan 1 de in ra toan bo qua trinh. Nhan 0 de thoat: " << endl;

    cout << endl << "********************************************************************************" << endl;

    int choose;
    do{
        cout << "Vui long chon: ";
        cout << flush;
        cin >> choose;
        if (choose < 0 || choose > 8) {
            cout << "Vui long chon lai!" << endl;
        }        else{
            if (isPrintToConsole) {
                switch (choose) {  
                    case 0:
                        cout << "Ket thuc chuong trinh, xin cam on!" << endl;
                        break;
                    case 1:
                        cout << "Buoc 2: Vector trung binh: " << endl << avgVector << endl;
                        cout << "Buoc 3: Su chenh lech giua dataMatrix va avgVector: " << endl << diffMatrix << endl;
                        cout << "Buoc 4: Tich 2 ma tran: " << endl << matrixProduct << endl;
                        cout << "Buoc 5: Tri rieng cua ma tran: " << endl << eigenValues << endl;
                        cout << "Buoc 6: Cac vector tuong ung voi cac tri rieng: " << endl << eigenVectors << endl;
                        cout << "Buoc 7: Tich 2 ma tran ansVector = matrixProduct * eigenVectors: " << endl << matrixProduct * eigenVectors << endl;
                        cout << "Buoc 8: Rut gon ansVector, ket qua cuoi cung la: " << endl << normalizeVector(ansVector) << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 2:
                        cout << "Buoc 2: Vector trung binh: " << endl << avgVector << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 3:
                        cout << "Buoc 3: Su chenh lech giua dataMatrix va avgVector: " << endl << diffMatrix << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 4:
                        cout << "Buoc 4: Tich 2 ma tran: " << endl << matrixProduct << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 5:
                        cout << "Buoc 5: Tri rieng cua ma tran: " << endl << eigenValues << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 6:
                        cout << "Buoc 6: Cac vector tuong ung voi cac tri rieng: " << endl << eigenVectors << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 7:
                        cout << "Buoc 7: Tich 2 ma tran ansVector = matrixProduct * eigenVectors: " << endl << matrixProduct * eigenVectors << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 8:
                        cout << "Buoc 8: Rut gon ansVector, ket qua cuoi cung la: " << endl << normalizeVector(ansVector) << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                }
            }
            else {
                switch (choose) {
                    case 0:
                        cout << "Ket thuc chuong trinh, xin vui long mo file data.out de xem ket qua" << endl;
                        break;
                    case 1:
                        cout << "Ban da chon: In ra toan bo qua trinh" << endl;
                        output << "Buoc 2: Vector trung binh: " << endl << avgVector << endl;
                        output << "Buoc 3: Su chenh lech giua dataMatrix va avgVector: " << endl << diffMatrix << endl;
                        output << "Buoc 4: Tich 2 ma tran: " << endl << matrixProduct << endl;
                        output << "Buoc 5: Tri rieng cua ma tran: " << endl << eigenValues << endl;
                        output << "Buoc 6: Cac vector tuong ung voi cac tri rieng: " << endl << eigenVectors << endl;
                        output << "Buoc 7: Tich 2 ma tran ansVector = matrixProduct * eigenVectors: " << endl << matrixProduct * eigenVectors << endl;
                        output << "Buoc 8: Rut gon ansVector, ket qua cuoi cung la: " << endl << normalizeVector(ansVector) << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 2:
                        cout << "Ban da chon: In ra buoc 2" << endl;
                        output << "Buoc 2: Vector trung binh: " << endl << avgVector << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 3:
                        cout << "Ban da chon: In ra buoc 3" << endl;
                        output << "Buoc 3: Su chenh lech giua dataMatrix va avgVector: " << endl << diffMatrix << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 4:
                        cout << "Ban da chon: In ra buoc 4" << endl;
                        output << "Buoc 4: Tich 2 ma tran: " << endl << matrixProduct << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 5:
                        cout << "Ban da chon: In ra buoc 5" << endl;
                        output << "Buoc 5: Tri rieng cua ma tran: " << endl << eigenValues << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 6:
                        cout << "Ban da chon: In ra buoc 6" << endl;
                        output << "Buoc 6: Cac vector tuong ung voi cac tri rieng: " << endl << eigenVectors << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 7:
                        cout << "Ban da chon: In ra buoc 7" << endl;
                        output << "Buoc 7: Tich 2 ma tran ansVector = matrixProduct * eigenVectors: " << endl << matrixProduct * eigenVectors << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                    case 8:
                        cout << "Ban da chon: In ra buoc 8" << endl;
                        output << "Buoc 8: Rut gon ansVector, ket qua cuoi cung la: " << endl << normalizeVector(ansVector) << endl;
                        cout << "********************************************************************************" << endl;
                        break;
                }
            }
        }
        Sleep(500);
    }
    while (choose != 0); 
    output.close();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    MatrixXd dataMatrix;
    //Buoc 0: Cai dat thong tin
    inputoutputSetup(N, M, dataMatrix);

    // Buoc 1: Doc du lieu
    MatrixXd  avgVector(N, 1), diffMatrix(N, M), matrixProduct(N, M), tranMatrix(N, M), eigenValues(N, 1), eigenVectors(N, M);
    
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

    //Buoc 9: Xuat ket qua
    printOutput(N, M, dataMatrix, avgVector, diffMatrix, matrixProduct, eigenValues, eigenVectors, ansVector);

    //Buoc 10: An phim bat ki de thoat chuong trinh
    cout << flush << endl;
    system("pause");

    return 0;
}