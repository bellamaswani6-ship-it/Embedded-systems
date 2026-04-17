#include <iostream>
#include <Eigen/Sparse>
using namespace std;
int main()
{
    //  Define a 10x10 sparse matrix
    Eigen::SparseMatrix<double> mat(10, 10);

    //  Insert non-zero elements
    mat.insert(3, 4) = 5.0;
    mat.insert(6, 2) = 3.0;

    //  Finalize internal structure
    mat.makeCompressed();

    // Print basic info
    std::cout << "Matrix size: "
              << mat.rows() << " x "
              << mat.cols() << "\n";

    std::cout << "Non-zero elements: "
              << mat.nonZeros() << "\n\n";

    //  Iterate over non-zero elements
    for (int k = 0; k < mat.outerSize(); ++k)
    {
        for (Eigen::SparseMatrix<double>::InnerIterator it(mat, k); it; ++it)
        {
            std::cout << "Value at ("
                      << it.row() << ", "
                      << it.col() << ") = "
                      << it.value() << "\n";
        }
    }

    return 0;
}


