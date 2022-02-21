#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

constexpr auto ARGUMENTS_COUNT = 2;
constexpr auto MATRIX_DIMENSION = 3;
constexpr double WEAK_DBL_EPSILON = DBL_EPSILON * 100.0;

typedef std::array<std::array<double, MATRIX_DIMENSION>, MATRIX_DIMENSION> Matrix3x3;

void LogError(const std::string& msg)
{
	std::cout << msg;
}

std::optional<std::string> ParseArg(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		LogError("Invalid arguments count. Usage: 1-invert.exe <input file path>\n");
		return std::nullopt;
	}

	return argv[1];
}

bool ReadMatrix(std::istream& input, Matrix3x3& mat)
{
	for (std::array<double, MATRIX_DIMENSION>& row : mat)
	{
		for (double& elt : row)
		{
			if (!(input >> elt))
			{
				LogError("Error: Failed to read matrix from file. Invalid numeric data.\n");
				return false;
			}
		}
	}

	char ch;
	if (!(input >> ch).eof())
	{
		LogError("Error: Wrong matrix file format. It's three numbers in each of three lines delimited by spaces or tabs.\n");
		return false;
	}

	return true;
}

bool ReadMatrixFromFile(const std::string& fileName, Matrix3x3& matrix)
{
	std::ifstream file;
	file.open(fileName, std::ios::in);

	if (!file.is_open())
	{
		LogError("Error: Failed to open \"" + fileName + "\" input file.\n");
		return false;
	}

	return ReadMatrix(file, matrix);
}

void PrintMatrix(Matrix3x3& matrix)
{
	for (std::array<double, MATRIX_DIMENSION> row : matrix)
	{
		printf("%.3f\t%.3f\t%.3f\n", row[0], row[1], row[2]);
	}
}

double GetDeterminant(const Matrix3x3& mat)
{
	return 
		mat[0][0] * mat[1][1] * mat[2][2] + 
		mat[0][1] * mat[1][2] * mat[2][0] + 
		mat[0][2] * mat[1][0] * mat[2][1] - 
		mat[2][0] * mat[1][1] * mat[0][2] - 
		mat[2][1] * mat[1][2] * mat[0][0] - 
		mat[2][2] * mat[1][0] * mat[0][1];
}

Matrix3x3 GetTransposedAdjugateMatrix(const Matrix3x3& mat)
{
	return {
		{
			{
				mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1], 
				mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2], 
				mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]
			},
			{
				mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2], 
				mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0], 
				mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]
			},
			{
				mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0], 
				mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1], 
				mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]
			}
		}
	};
}

Matrix3x3 DivideMatrix(const Matrix3x3& mat, double divisor)
{
	Matrix3x3 resMat = {};
	
	for (int i = 0; i < MATRIX_DIMENSION; ++i)
	{
		for (int j = 0; j < MATRIX_DIMENSION; ++j)
		{
			resMat[i][j] = mat[i][j] / divisor;
		}
	}

	return resMat;
}

bool InvertMatrix(const Matrix3x3& mat, Matrix3x3& invMat)
{
	double det = GetDeterminant(mat);

	if (abs(det - 0.0) <= WEAK_DBL_EPSILON)
	{
		LogError("Invert matrix does not exist. Matrix is degenerate and uninvertible.\n");
		return false;
	}

	Matrix3x3 adjMat = GetTransposedAdjugateMatrix(mat);
	invMat = DivideMatrix(adjMat, det);

	return true;
}

int main(int argc, char* argv[])
{
	std::optional<std::string> filePath = ParseArg(argc, argv);

	if (!filePath.has_value())
	{
		return 1;
	}

	Matrix3x3 matrix = {};

	if (!ReadMatrixFromFile(filePath.value(), matrix))
	{
		return 1;
	}

	Matrix3x3 invertedMatrix = {};

	if(!InvertMatrix(matrix, invertedMatrix))
	{
		return 1;
	}

	PrintMatrix(invertedMatrix);

	return 0;
}
