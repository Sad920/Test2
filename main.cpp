#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

namespace matrix_app {
constexpr int kMaxSize = 10;

struct Matrix {
    int rows{0};
    int cols{0};
    std::vector<int> data;

    Matrix() = default;
    Matrix(int r, int c) : rows(r), cols(c), data(static_cast<std::size_t>(r * c), 0) {}

    int &at(int r, int c) { return data[static_cast<std::size_t>(r * cols + c)]; }
    int at(int r, int c) const { return data[static_cast<std::size_t>(r * cols + c)]; }
};

int promptInt(const std::string &label, int min, int max) {
    int value{};
    while (true) {
        std::cout << label;
        if (std::cin >> value && value >= min && value <= max) {
            return value;
        }
        std::cout << "Please enter an integer between " << min << " and " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Matrix readMatrix(char name) {
    std::cout << "\nEnter size for Matrix " << name << " (up to " << kMaxSize << "x" << kMaxSize << ")\n";
    int rows = promptInt("Rows: ", 1, kMaxSize);
    int cols = promptInt("Columns: ", 1, kMaxSize);

    Matrix matrix(rows, cols);
    std::cout << "Enter values row by row for Matrix " << name << ":\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            matrix.at(r, c) = promptInt("  Element [" + std::to_string(r) + ", " + std::to_string(c) + "]: ",
                                        std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
    }
    return matrix;
}

Matrix multiply(const Matrix &a, const Matrix &b) {
    Matrix result(a.rows, b.cols);
    for (int r = 0; r < a.rows; ++r) {
        for (int c = 0; c < b.cols; ++c) {
            int sum = 0;
            for (int k = 0; k < a.cols; ++k) {
                sum += a.at(r, k) * b.at(k, c);
            }
            result.at(r, c) = sum;
        }
    }
    return result;
}

void printMatrix(const Matrix &matrix, char name) {
    std::cout << "\nMatrix " << name << " (" << matrix.rows << "x" << matrix.cols << "):\n";
    for (int r = 0; r < matrix.rows; ++r) {
        for (int c = 0; c < matrix.cols; ++c) {
            std::cout << std::setw(8) << matrix.at(r, c) << ' ';
        }
        std::cout << '\n';
    }
}

void showButtonPrompt() {
    std::cout << "\n[Multiply] -> press 'm' and Enter to multiply the matrices." << '\n'
              << "[Quit]     -> press 'q' and Enter to exit.\n";
}

}  // namespace matrix_app

int main() {
    using namespace matrix_app;

    std::cout << "Simple Matrix Multiplier (up to 10x10)\n";
    Matrix a = readMatrix('A');
    Matrix b = readMatrix('B');

    if (a.cols != b.rows) {
        std::cout << "\nMatrix multiplication is not possible because columns of A (" << a.cols
                  << ") do not match rows of B (" << b.rows << ").\n";
        return 0;
    }

    showButtonPrompt();
    char command{};
    while (std::cin >> command) {
        if (command == 'm' || command == 'M') {
            Matrix result = multiply(a, b);
            printMatrix(result, 'R');
            showButtonPrompt();
        } else if (command == 'q' || command == 'Q') {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Unknown option. Please press 'm' to multiply or 'q' to quit.\n";
        }
    }

    return 0;
}
