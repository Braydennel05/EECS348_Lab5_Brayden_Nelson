// File Name: main.cpp
// Author: Brayden Nelson
// Purpose: Load two NxN matrices from a file and perform addition, multiplication, swapping, and element updates
// Created: Sep 29 2026

// Headers

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>
#include <limits>

// Forward declaration -- I want to keep main function at the top of the file (I just like it that way)

int* readSingleMatrix(std::ifstream& file, int n);
void printMatrixDynamicZeros(const int* matrix, int n);
void mat_add(const int* matA, const int* matB, int n);
void mat_mult(const int* matA, const int* matB, int n);
void sum_diag(const int* matrix, int n);
void swap_rows(int* matrix, int n, int r1, int r2);
void swap_cols(int* matrix, int n, int c1, int c2);
void upd_elem(int* matrix, int n, int row, int col, int val);


// Main function

int main() {

	std::string filename;					// string variable for user inputted file name to be saved to
	std::cout << "Enter the input file name (.txt file): ";	// prompt user to enter input file name
	std::cin >> filename;					// save inputted string to varible

	std::ifstream file(filename);			// open file for reading using input file stream

	if (!file.is_open()) {				// if the file is open, pass over this block
		std::cerr << "Error opening file.\n";	// error propmt when user inputted file cannot be opened
		return 1;				// terminates program
	}

	int n = 0;							// initialize an integer "n" to zero. This value denotes the size of the nxn matrix
	if (!(file >> n) || n <= 0) {					// reads next formatted value from file and checks that it is greater than 0
		std::cerr << "Error reading matrix dimensions.\n";	// error prompt when n doesnt pass if statement check
		return 1;						// terminates program
	}

	int* matA = readSingleMatrix(file, n);	// allocates space for first matrix in file and passes the file and size of matrix to readSingleMatrix function
	int* matB = readSingleMatrix(file, n);	// ^ same as last call but for the second matrix

	if (matA != nullptr && matB != nullptr) {			// if either matrix is pointing at null pointer (somewhere they shouldnt be), pass over this block

		std::cout << "\nMatrix A (" << n << "x" << n << "):\n";	// specify matrix A and its size to be printed on next line
		printMatrixDynamicZeros(matA, n);			// print matrix A (dynamic zero is to keep column alignment)

		std::cout << "\nMatrix B (" << n << "x" << n << "):\n";	// same as above
		printMatrixDynamicZeros(matB, n);			// same as above

		int choice = 0;						// initialize an integer variable "choice" to zero to later set to user input

		// this while loop runs until either the user enters "4" to exit program or an error is thrown
		while (choice != 4) {

			// user menu to select what to do with matrices, or to exit the program
			std::cout << "\n--- Matrix Actions ---\n";
			std::cout << "1. Update a matrix element\n";
			std::cout << "2. Display matrix operations\n";
			std::cout << "3. Swap rows/columns of matrix\n";
			std::cout << "4. Exit\n";
			std::cout << "Enter your choice (1-4): ";
			std::cin >> choice;	// user inputed choice is set to "choice" variable

			// update a matrix element
			if (choice == 1) {
				char matChoice;		// allocate space for variable that decides which matrix is being updated
				int row, col, val;	// allocates space for three integer variables - the row and column indicies that wil be updated, and the new value for that location in the matrix

				// prompt user for which matrix will be updated, row and column indicies, and new value. then save input to previously defined variables
				std::cout << "Which matrix do you want to update? (A/B): ";
				std::cin >> matChoice;
				std::cout << "Enter row index (starts at 0): ";
				std::cin >> row;
				std::cout << "Enter column index (starts at 0): ";
				std::cin >> col;
				std::cout << "Enter new value: ";
				std::cin >> val;

				// if user enters wrong data type for new matrix value, clear the fail flag, clear invalid input and jump back to the start of the while loop
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Error: Indicies and values must be numbers.\n";
					continue;
				}

				// checks user input for valid matrix choice and passes parameters to update element update function
				if (matChoice == 'A' || matChoice == 'a') {
					upd_elem(matA, n, row, col, val);
				} else if (matChoice == 'B' || matChoice == 'b') {
					upd_elem(matB, n, row, col, val);
				} else {
					std::cout << "Invalid matrix selection.\n";
				}

			// display matrix operations
			} else if (choice == 2) {

				// displays resulting matrix of both adding and multiplying matrix A and matrix B
				mat_add(matA, matB, n);
				mat_mult(matA, matB, n);

				// displays both diagonal sums for both matrices
				std::cout << "\nDiagonal Sums for Matrix A:";
				sum_diag(matA, n);
				std::cout << "\nDiagonal Sums for Matrix B:";
				sum_diag(matB, n);

			// swap rows/columns of matrix
			} else if (choice == 3){

				// allocate space for four variables that specify how swap rows or swap columns is carried out
				char matChoice;
				char rcChoice;
				int val1, val2;

				// more user prompts and saving to previously allocated variables
				std::cout << "What matrix do you want to swap rows/columns in? (A/B): ";
				std::cin >> matChoice;
				std::cout << "Do you want to swap rows or columns? (R/C): ";
				std::cin >> rcChoice;
				std::cout << "Enter index for first row/column (starts at 0): ";
				std::cin >> val1;
				std::cout << "Enter index for second row/column (starts at 0): ";
				std::cin >> val2;

				// if user enters wrong data type for new matrix value, clear the fail flag, clear invalid input and jump back to the start of the while loop
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Error: Indicies and values must be numbers.\n";
					continue;
				}

				// block for passing parameters to either swap_row or swap_cols functions for matrix A
				if (matChoice == 'A' || matChoice == 'a') {
					if (rcChoice == 'R' || rcChoice == 'r') {
						swap_rows(matA, n, val1, val2);
					} else if (rcChoice == 'C' || rcChoice == 'c') {
						swap_cols(matA, n, val1, val2);
					} else {
						std::cout << "Invalid choice.\n";	// error catching for invalid input
					}

				// block for passing parameters to either swap_row or swap_cols functions for matrix B
				} else if (matChoice == 'B' || matChoice == 'b') {
					if (rcChoice == 'R' || rcChoice == 'r') {
						swap_rows(matB, n, val1, val2);
					} else if (rcChoice == 'C' || rcChoice == 'c') {
						swap_cols(matB, n, val1, val2);
					} else {
						std::cout << "Invalid choice.\n";	// error catching for invalid input
					}

				} else {
					std::cout << "Invalid matrix selection.\n";	// error catching for invalid input
				}

			// exit program
			} else if (choice != 4) {
				std::cout << "Invalid choice. Please try again.\n";	// error catching for invalid input
			}
		}

	} else {
		std::cerr << "Error: Could not read both matrices from file.\n";	// error catching for invalid input file formatting
	}

	// deallocating stored matrices to prevent memory leakage
	delete[] matA;
	delete[] matB;

	return 0;
}


// Read Matrix function

int* readSingleMatrix(std::ifstream& file, int n) {
	if (n <= 0) return nullptr;			// return null pointer for error handling in main function
	int* matrix = new int[n * n];			// allocate an array of size n^2 to store matrix (since input SHOULD always be a square matrix)
	for (int i = 0; i < n * n; ++i) {		// iterate through each value in input file and store in matrix array
		if (!(file >> matrix[i])) {		// catch incorrectly formatted matrix in input file
			delete[] matrix;		// deallocate saved matrix to prevent memory leakage
			return nullptr;			// return null pointer for error handling in main function
		}
	}
	return matrix;	// returns matrix array to main function
}


// Print Matrix function

void printMatrixDynamicZeros(const int* matrix, int n) {
	if (!matrix || n <= 0) return;	// null pointer or invalid size check

	int max_len = 0;

	// iterate through the entire 1D array to find the longest number
	for (int i = 0; i < n * n; ++i) {
		// convert the integar to a string to count its length
		int len = static_cast<int>(std::to_string(matrix[i]).length());
		if (len > max_len) {
			max_len = len;	// store the length of the longest number
		}
	}

	// iterate through "simulated" 2D rows and columns of matrix
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int val = matrix[i * n + j];	// map the 2D location to 1D array index - (row * total columns) + current column

			// print the value value with leading 0s to make value length the same as the longest number (to keep columns aligned nicely)
			std::cout << std::internal
				  << std::setfill('0')
				  << std::setw(max_len)
				  << val << " ";
		}
		std::cout << '\n';
	}
	std::cout << std::setfill(' ') << std::right;
}


// Matrix Addition function

void mat_add(const int* matA, const int* matB, int n) {
	std::cout << "\nMatrix Addition (A + B):\n";
	int* result = new int[n * n];

	// iterate thorugh matrix values, adding the cooresponding values from both matrices and storing them in a new result matrix
	for (int i = 0; i < n * n; ++i) {
		result[i] = matA[i] + matB[i];
	}
	printMatrixDynamicZeros(result, n);	// pass result matrix to print matrix function
	delete[] result;			// deallocate result matrix to prevent memory leakage
}


// Matrix Multiplication function

void mat_mult(const int* matA,const int* matB, int n) {
	std::cout << "\nMatrix Multiplication (A * B):\n";
	int* result = new int[n * n];

	for (int i = 0; i < n * n; ++i) result[i] = 0;	// set all values in new result matrix to zero

	// matrix multiplication algorith
	for (int i = 0; i < n; ++i) {		// iterate through rows of A
		for (int j = 0; j < n; ++j) {		//iterate through columns of B
			for (int k = 0; k < n; ++k) {
				result[i * n + j] += matA[i * n + k] * matB[k * n + j];	// dot product calculation
			}
		}
	}
	printMatrixDynamicZeros(result, n);	// pass result matrix to print matrix function
	delete[] result;			// deallocate result matrix to prevent memory leakage
}


// Sum Diagonals function

void sum_diag(const int* matrix, int n) {
	int main_sum = 0, sec_sum = 0;

	// loops through the number of times equal to the size of the matrix
	for (int i = 0; i < n; ++i) {
		main_sum += matrix[i * n + i];	// sums matrix values starting at top left and next increment moves addition down one row and right one column
		sec_sum += matrix[i * n + (n - 1 - i)];	// sums matrix values starting at top left and next increment moves addition down one row and left one column
	}
	std::cout << "\nSum of main diagonal: " << main_sum << "\n";
	std::cout << "Sum of second diagonal: " << sec_sum << "\n";
}


// Swap Rows function

void swap_rows(int* matrix, int n, int r1, int r2) {
	// error catching invalid row input
	if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) {
		std::cout << "Invalid row index.\n";
		return;
	}

	// iterates through all columns of matrix
	for (int col = 0; col < n; ++col) {
		std::swap(matrix[r1 * n + col], matrix[r2 * n + col]);	// swaps elements of selected column row by row
	}

	std::cout << "\nMatrix after swapping rows " << r1 << " and " << r2 << ":\n";
	printMatrixDynamicZeros(matrix, n);	// passes matrix to print matrix function
}


// Swap Columns function

void swap_cols(int* matrix, int n, int c1, int c2) {
	// error catching invalid column inputs
	if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) {
		std::cout << "Invalid column index.\n";
		return;
	}

	// iterates trhough all rows of matrix
	for (int row = 0; row < n; ++row) {
		std::swap(matrix[row * n + c1], matrix[row * n + c2]); // swaps elements of selected rows column by column
	}

	std::cout << "\nMatrix after swapping columns " << c1 << " and " << c2 << ":\n";
	printMatrixDynamicZeros(matrix, n);	// passes matrix to print matrix function
}


// Update Matrix Element function

void upd_elem(int* matrix, int n, int row, int col, int val) {
	// error catching for invalid row or column inputs
	if (row < 0 || row >= n || col < 0 || col >= n) {
		std::cout << "Invalid row or column index.\n";
		return;
	}

	matrix[row * n + col] = val;	// replaces user selected location in a matrix with new value entered by user

	std::cout << "\nMatrix after updating element at (" << row << ", " << col << ") to " << val << ":\n";
	printMatrixDynamicZeros(matrix, n);	// passes matrix to print matrix function
}
