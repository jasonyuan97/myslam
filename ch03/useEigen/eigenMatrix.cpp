#include <iostream>
#include <ctime>

#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

using namespace std;

int main() {
    /*** definitions ***/

    // a 2x3 float matrix
    Eigen::Matrix<float, 2, 3> matrix_2_3;

    // Matrix<double, 3, 1>
    Eigen::Vector3d v_3d;

    // initialize with zeros
    Eigen::Matrix3d matrix_3_3 = Eigen::Matrix3d::Zero();

    // dynamic matrix
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;

    // dynamic matrix, same as the previous one
    Eigen::MatrixXd matrix_x;

    /*** operations ***/

    #if 0
    matrix_2_3 << 1, 2, 3, 4, 5, 6;
    cout << matrix_2_3 << endl;

    // for(int i=0; i<2; ++i) {
    //     for(int j=0; j<3; ++j) {
    //         cout << matrix_2_3(i, j) << "\t";
    //     }
    //     cout << endl;
    // }
    

    v_3d << 3, 2, 1;
    cout << v_3d << endl;

    // multiply two matrices, they must have the same type  
    Eigen::Matrix<double, 2, 1> res = matrix_2_3.cast<double>()*v_3d;
    cout << res << endl;
    # endif

    // fill the matrix with random values 
    matrix_3_3 = Eigen::Matrix3d::Random();
    cout << "Original Matrix: " << endl;
    cout << matrix_3_3 << endl;
    cout << " " << endl;

    cout << "Transpose: " << endl;
    cout << matrix_3_3.transpose() << endl;
    cout << " " << endl;

    cout << "Sum: " << endl;
    cout << matrix_3_3.sum() << endl;
    cout << " " << endl;

    cout << "Trace: " << endl;
    cout << matrix_3_3.trace() << endl;
    cout << " " << endl;

    cout << "Multiply by 10: " << endl;
    cout << 10*matrix_3_3 << endl;
    cout << " " << endl;

    cout << "Reverse: " << endl;
    cout << matrix_3_3.reverse() << endl;
    cout << " " << endl;

    cout << "Determinant: " << endl;
    cout << matrix_3_3.determinant() << endl;
    cout << " " << endl;

    // eigen-values and eigen-vectors
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_3_3.transpose()*matrix_3_3);
    cout << "Eigen values: \n" << eigen_solver.eigenvalues() << endl;
    cout << " " << endl;
    cout << "Eigen vectors: \n" << eigen_solver.eigenvectors() << endl;
    cout << " " << endl;

    // solve equation set  
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd; 
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_start = clock();
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse()*v_Nd;
    cout << "time elapsed when using inversion: " << 1000*(clock()-time_start)/(double)CLOCKS_PER_SEC << "ms" << endl;

    time_start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time elapsed when using Qr decompsition: " << 1000*(clock()-time_start)/(double)CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
