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
    if (choose == 1) {
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

    cout << "Da co san 3 bo du lieu: " << endl;
    cout << "1. FaceDataset.inp (Bo du lieu khuon mat tham khao tu Le Hoang Thanh)" << endl;
    cout << "2. IrisDataset.inp (Bo du lieu phan tich cac loai hoa, day la bo du lieu huyen thoai trong phan tich PCA)" << endl;
    cout << "3. GithubDataset.inp (du lieu tham khao tu Github cua toosyou)" << endl;
    cout << "4. WikiDataset.inp (du lieu tham khao tu Wikipedia)" << endl;
    cout << "5. SydneyDataset.inp (du lieu tham khao tu truong dai hoc Sydney thong qua Google Dataset Search Engine)" << endl << endl;

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "|                          QUY DINH CACH NHAP DU LIEU                          |" << endl;
    cout << "|  Dong dau tien: 2 so nguyen N va M.                                          |" << endl;
    cout << "|  N dong tiep theo: Moi dong gom M , cac so cach nhau boi mot khoang trang    |" << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;

    cout << "Nhan 1 de chon viec nhap tu file" << endl;
    cout << "Nhan 2 de chon viec nhap tu ban phim" << endl;
    int c;
    do{
        c = 0;
        cout << endl << "Moi chon: ";
        cout << flush;
        cin >> c;
        if (c < 1 || c > 2) {
            cout << "So vua nhap khong phu hop. Vui long chon lai!" << endl;
        }
    }
    while (c < 1 || c > 2);
    string nameFile;
    switch (c) {
        case 1: 
            cout << "Ban da chon: Du lieu se duoc nhap tu file!" << endl;
            do{
                cout << "Moi nhap ten file: ";
                cout << flush;
                cin >> nameFile;
                input.open(nameFile);
                if (input .fail()) {
                    cout << "Khong tim thay file. Vui long nhap lai!" << endl;
                }
            }
            while (input .fail());
            break;
        case 2:
            cout << "Ban da chon: Du lieu se duoc nhap tu ban phim!" << endl;
            cout << "Moi nhap du lieu o ben duoi" << endl;
            break;
    }
    cout << flush;
    readData(N, M, dataMatrix, c);
    if (c == 1){
        input.close();
    }
    cout << "Du lieu da duoc nhap xong!" << endl << endl;
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
//Ham tinh tich co huong 2 ma tran
MatrixXd multipleMatrix(MatrixXd matrix1, MatrixXd matrix2) {
    MatrixXd matrixProduct(matrix1.rows(), matrix2.cols());
    foru(i, 0, matrix1.rows() - 1) {
        foru(j, 0, matrix2.cols() - 1) {
            double sum = 0;
            foru(k, 0, matrix1.cols() - 1) {
                sum += matrix1(i, k) * matrix2(k, j);
            }
            matrixProduct(i, j) = sum;
        }
    }
    return matrixProduct;
}

//Ma tran chuyen vi
MatrixXd transposeMatrix(MatrixXd matrix) {
    MatrixXd transposedMatrix(matrix.cols(), matrix.rows());
    foru(i, 0, matrix.rows() - 1) {
        foru(j, 0, matrix.cols() - 1) {
            transposedMatrix(j, i) = matrix(i, j);
        }
    }
    return transposedMatrix;
}

//Buoc 0: Lua chon dau vao
void inputoutputSetup(int &N, int &M, MatrixXd &dataMatrix) {
    welcome();
    Sleep(1000);
    inputSeclection(N, M, dataMatrix);
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


// Bước 5 và 6: Tìm eigenValues và eigenVectors bằng phương pháp jac
void jacobiEigen(MatrixXd A, MatrixXd &eigenValues, MatrixXd &eigenVectors, int maxIter = 100, double tolerance = 1e-8) {
    int n = A.rows();
    eigenVectors = MatrixXd::Identity(n, n); // Khởi tạo ma trận eigenVectors là ma trận đơn vị

    int iter = 0;
    while (iter < maxIter) {
        double maxOffDiag = 0.0;
        int p, q; // Vị trí của phần tử ngoại đường chéo lớn nhất
        // Tìm phần tử ngoại đường chéo lớn nhất
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(A(i, j)) > maxOffDiag) {
                    maxOffDiag = std::abs(A(i, j));
                    p = i;
                    q = j;
                }
            }
        }

        // Kiểm tra điều kiện dừng
        if (maxOffDiag < tolerance) break;

        // Tính góc xoay
        double theta = 0.5 * std::atan2(2 * A(p, q), A(p, p) - A(q, q));
        double c = std::cos(theta);
        double s = std::sin(theta);

        // Tạo ma trận xoay
        MatrixXd R = MatrixXd::Identity(n, n);
        R(p, p) = c;
        R(q, q) = c;
        R(p, q) = -s;
        R(q, p) = s;

        // Cập nhật ma trận A và ma trận eigenVectors
        A = R.transpose() * A * R;
        eigenVectors = eigenVectors * R;

        iter++;
    }

    // Lấy eigenvalues từ ma trận A (ma trận đường chéo chứa eigenvalues)
    eigenValues.resize(n, 1);
    for (int i = 0; i < n; ++i) {
        eigenValues(i, 0) = A(i, i);
    }
}

//Buoc 7: Loc ra cac eigenValues va eigenVectors phu hop
void filterEigen(MatrixXd& eigenValues, MatrixXd& eigenVectors) {
    for (int i = 0; i < eigenValues.rows() - 1; ++i) {
        for (int j = i + 1; j < eigenValues.rows(); ++j) {
            if (eigenValues(i, 0) < eigenValues(j, 0)) {
                double tempValue = eigenValues(i, 0);
                eigenValues(i, 0) = eigenValues(j, 0);
                eigenValues(j, 0) = tempValue;

                MatrixXd tempVector = eigenVectors.col(i);
                eigenVectors.col(i) = eigenVectors.col(j);
                eigenVectors.col(j) = tempVector;
            }
        }
    }

    // Khai báo các ma trận phụ
    int index = 0;
    MatrixXd tempEigenValues(eigenValues.rows(), 1);
    MatrixXd tempEigenVectors(eigenVectors.rows(), eigenVectors.cols());
    
    for (int i = 0; i < eigenValues.rows() - 1; ++i) {
        if (fabs(eigenValues(i, 0) - 0.0) > ESP && fabs(eigenValues(i, 0) - eigenValues(i + 1, 0)) > ESP) {
            tempEigenValues(index, 0) = eigenValues(i, 0);
            tempEigenVectors.col(index) = eigenVectors.col(i);
            index++;
        }
    }

    // Sao chép kết quả vào ma trận gốc
    eigenValues.resize(index, 1);
    eigenVectors.resize(eigenVectors.rows(), index);
    eigenValues = tempEigenValues.block(0, 0, index, 1);
    eigenVectors = tempEigenVectors.block(0, 0, eigenVectors.rows(), index);
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
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "|  Nhan 1 de in ra toan bo qua trinh                                         |" << endl;
    cout << "|  Nhan cac phim tu 2 toi 7 de in ra ket qua o cac buoc tuonng ung           |" << endl;
    cout << "|  Nhan 8 de in ra ket qua cuoi cung                                         |" << endl;
    cout << "|  Nhan 9 de xuat hinh anh                                                   |" << endl;
    cout << "|  Nhan 0 de thoat chuong trinh                                              |" << endl;
    cout << "-----------------------------------------------------------------------------" << endl << endl;

    int choose;
    do{
        cout << "Vui long chon: ";
        cout << flush;
        cin >> choose;
        if (choose < 0 || choose > 9) {
            cout << "Vui long chon lai!" << endl;
        }        
        else{
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
                    cout << "Buoc 7: Tich 2 ma tran ansVector = diffMatrix * eigenVectors: " << endl << ansVector << endl;
                    cout << "********************************************************************************" << endl;
                    break;
                case 8:
                    cout << "Ket qua cuoi cung la: " << endl << normalizeVector(ansVector) << endl;
                    cout << "********************************************************************************" << endl;
                    break;
                case 9:
                    cout << "Ban da chon: Xuat hinh anh" << endl;
                    ofstream f;
                    f.open("data_img.txt");
                    f << ansVector;
                    f.close();
                    system("python generate_img.py");
                    break;
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

    //Buoc 5: Tim eigenvalues va eigenvectors
    eigenValues.resize(N, 1);
    eigenVectors.resize(N, N);
    jacobiEigen(matrixProduct, eigenValues, eigenVectors);

    //Buoc 6: Loc ra cac eigenValues va eigenVectors phu hop
    filterEigen(eigenValues, eigenVectors);

    //Buoc 7: Tinh tich 2 ma tran ansVector = diffMatrix * eigenVectors
    MatrixXd ansVector = multipleMatrix(diffMatrix, eigenVectors);

    //Buoc 8: Rut gon ansVector

    //Buoc 9: Xuat ket qua
    printOutput(N, M, dataMatrix, avgVector, diffMatrix, matrixProduct, eigenValues, eigenVectors, ansVector);

    system("pause");
    return 0;
}