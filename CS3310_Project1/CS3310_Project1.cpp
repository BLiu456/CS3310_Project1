/*
    Name: Benjamin Liu
    Class: CS3310.01
    Assignment: Project 1 
    Due Date: 04/06/2023
    Summary: This program containts the classical matrix multiplication, divide and conquer, and strassen algorithms.
             The program allows the user to manually enter the matrices, enter the matrices with files, or to randomly generate the matrices.
             At the end of the program, it will how long each of the aglorithms took to do the calculations. 
             To get the average timings, I will simply just run this program m times and make note of the timings and do the calculations by hand.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Function Prototypes here
void getMatrixMan(vector<vector<int>>&, vector<vector<int>>&);
bool getMatrixFile(vector<vector<int>>&, vector<vector<int>>&);
void getMatrixRand(vector<vector<int>>&, vector<vector<int>>&);
vector<vector<int>> classical(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> divideConquer(vector<vector<int>>, vector<vector<int>>);
void strassen(vector<vector<int>>, vector<vector<int>>, vector<vector<int>>&);
vector<vector<int>> divider(vector<vector<int>>, int, int, int, int);
vector<vector<int>> adder(vector<vector<int>>, vector<vector<int>>, int);
void printMatrix(vector<vector<int>>);

int main()
{
    vector<vector<int>> a, b, r1, r2, r3;
    //Print out the menu and get the option the user selects
    int op;
    cout << "---Square Matrix Multiplication Algorithms---\n";
    cout << "Choose an option:\n"
        << "(1) Enter the matrices manually\n"
        << "(2) Load a file of the matrices\n"
        << "(3) Generate random matrices\n"
        << "(4) Exit\n"
        << "Enter: ";
    cin >> op;

    switch (op) //Doing the chosen option
    {
    case 1:
        getMatrixMan(a, b);
        break;
    case 2:
        if (getMatrixFile(a, b))
        {
            cout << "Contents of matrix A:\n";
            printMatrix(a);
            cout << "\nContents of matrix B:\n";
            printMatrix(b);
        }
        else
        {
            return 0;
        }
        break;
    case 3:
        getMatrixRand(a, b);
        cout << "Contents of matrix A:\n";
        printMatrix(a);
        cout << "\nContents of matrix B:\n";
        printMatrix(b);
        break;
    case 4:
        cout << "Exit has been selected, ending program\n";
        return 0;
    default:
        cout << "Valid option not selected, ending program.\n";
        return 0;
    }

    //Timing the classical algorithm 
    auto start = high_resolution_clock::now();
    r1 = classical(a, b);
    auto end = high_resolution_clock::now();
    auto timeClassic = duration_cast<microseconds>(end - start);
    cout << "\nClassical Matrix Multiplication result:\n";
    printMatrix(r1);
    cout << endl;
    r1 = vector<vector<int>>(); //Freeing up space

    //Timing the Divide and Conquer algorithm
    start = high_resolution_clock::now();
    r2 = divideConquer(a, b);
    end = high_resolution_clock::now();
    auto timeDaC = duration_cast<microseconds>(end - start);
    cout << "\nDivide and Conquer result:\n";
    printMatrix(r2);
    cout << endl;
    r2 = vector<vector<int>>(); //Freeing up space

    //Timing the Strassen's algorithm
    start = high_resolution_clock::now();
    strassen(a, b, r3);
    end = high_resolution_clock::now();
    auto timeStrassen = duration_cast<microseconds>(end - start);
    cout << "\nStrassen result:\n";
    printMatrix(r3);
    cout << endl;
    r3 = vector<vector<int>>(); //Freeing up space

    //Displaying each of the algorithm's times
    cout << "Time elapsed for Classical: " << timeClassic.count() << " microseconds" << endl;
    cout << "Time elapsed for Divide and Conquer: " << timeDaC.count() << " microseconds" << endl;
    cout << "Time elapsed for Strassen: " << timeStrassen.count() << " microseconds" << endl;
    return 0; //End of program
}

/*Gets the manual input from the user for the two matrices. The matrices are stored in the a and b matrices that was passed*/
void getMatrixMan(vector<vector<int>>& a, vector<vector<int>>& b)
{
    int n = 2; //2 as default size
    cout << "\nEnter size of square matrices: ";
    cin >> n;
    cin.clear(); //Clearing the std input so we can use the getline function later
    cin.ignore(INT_MAX, '\n');
    //Getting values for matrix a
    a.resize(n);
    string rowData, hold;
    cout << "Enter the values of matrix A row by row:\n";
    for (int i = 0; i < n; i++)
    {
        a.at(i).resize(n);
        getline(cin, rowData); //Gets the entire row the user inputs as a string, and assumes the user seperates each number with a space
        istringstream ss(rowData); //This will seperate each of the values by spaces 
        for (int j = 0; j < n; j++)
        {
            ss >> hold; //Pulling one of the values that the user inputted
            a.at(i).at(j) = stoi(hold); //Convert the string into an int and store it in the matrix
        }
    }
    //Getting the values of matrix b, performs the same logic as above with matrix a
    b.resize(n);
    cout << "Enter the values of matrix B row by row:\n";
    for (int i = 0; i < n; i++)
    {
        b.at(i).resize(n);
        getline(cin, rowData);
        istringstream ss(rowData);
        for (int j = 0; j < n; j++)
        {
            ss >> hold;
            b.at(i).at(j) = stoi(hold);
        }
    }
}

/*Asks the user for the two files that has the matrices and stores it in matrix a and b that was passed
  Function returns a bool based on if it was able to open the files or not. True if both files are able to be opened. Dalse if one of the files could not open*/
bool getMatrixFile(vector<vector<int>>& a, vector<vector<int>>& b)
{
    string filenameA = "", filenameB = "", rowData = "", hold = "";

    cout << "\nEnter file name for matrix A: ";
    cin >> filenameA;
    cout << "Enter file name for matrix B: ";
    cin >> filenameB;
    //Getting the file input for matrix a
    ifstream matrixFile;
    matrixFile.open(filenameA);
    if (!matrixFile) //Ends program if file could not be opened
    {
        cout << "Could not open file for matrix A, ending program." << endl;
        return false;
    }

    while (!matrixFile.eof()) 
    {
        getline(matrixFile, rowData); //Getting a row from the file
        istringstream ss(rowData); //Seperating each value by spaces
        vector<int> temp;

        while (ss >> hold) //Getting one of the values from the row
        {
            temp.push_back(stoi(hold)); //Converting the value into an int
        }

        a.push_back(temp); //Pushing the whole row of values into matrix a
    }

    matrixFile.close();
    //Getting the values for matrix b, follows the same logic above as matrix a
    matrixFile.open(filenameB);
    if (!matrixFile)
    {
        cout << "Could not open file for matrix B, ending program." << endl;
        return false;
    }

    while (!matrixFile.eof())
    {
        getline(matrixFile, rowData);
        istringstream ss(rowData);
        vector<int> temp;

        while (ss >> hold)
        {
            temp.push_back(stoi(hold));
        }

        b.push_back(temp);
    }

    matrixFile.close();
    return true;
}

/*Asks user to enter a size for the nxn matrix. Then randomly generates the nxn matrix with values between 0 to 9 and stores them in matrix a and b that was passed.
  The function will also stored the randomly generated matrices into two files, named randMatrixA.txt and randMatrixB.txt for the respective matrices.
  Note, that user should rename those files if they would like to use them later*/
void getMatrixRand(vector<vector<int>>& a, vector<vector<int>>& b)
{
    int n = 2; //2 as default size
    cout << "Enter size of square matrices: ";
    cin >> n;

    srand(time(0));
    
    ofstream matrixFile("randMatrixA.txt"); //Creating and writing to file randMatrixA.txt
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        a.at(i).resize(n);
        for (int j = 0; j < n; j++)
        {
            int r = rand() % 10; //Generating a random number from 0 to 9
            a.at(i).at(j) = r; //Setting that value to matrix a

            matrixFile << r; //Write that value to the file

            if (j != n - 1) //Write a space to the file, unless it is the end of the row, in which don't write anything here
            {
                matrixFile << " ";
            }
        }

        if (i != n - 1) //End of row so write the new line. If we are at the last row then don't write anything.
        {
            matrixFile << "\n";
        }   
    }
    matrixFile.close();
    //Now randomly generating matrix b. Follows the same logic above as matrix a
    matrixFile.open("randMatrixB.txt");
    b.resize(n);
    for (int i = 0; i < n; i++)
    {
        b.at(i).resize(n);
        for (int j = 0; j < n; j++)
        {
            int r = rand() % 10; //Generating a random number from 0 to 99
            b.at(i).at(j) = r;

            matrixFile << r;

            if (j != n - 1)
            {
                matrixFile << " ";
            }
        }

        if (i != n - 1)
        {
            matrixFile << "\n";
        }
    }
    matrixFile.close();
}

/*This is the classical matrix multiplication, returns the result in resultMatrix*/
vector<vector<int>> classical(vector<vector<int>> m1, vector<vector<int>> m2)
{
    vector<vector<int>> resultMatrix;
    resultMatrix.resize(m1.size());
    for (int i = 0; i < m1.size(); i++)
    {
        resultMatrix.at(i).resize(m2.at(i).size());
        for (int j = 0; j < m2.at(i).size(); j++)
        {
            resultMatrix.at(i).at(j) = 0;
            for (int k = 0; k < m2.size(); k++)
            {
                resultMatrix.at(i).at(j) += m1.at(i).at(k) * m2.at(k).at(j);
            }
        }
    }
   
    return resultMatrix;
}

/*This is the divide and conquer matrix multiplication, returns the result in c.
  This algorithm utilizes recursion*/
vector<vector<int>> divideConquer(vector<vector<int>> a, vector<vector<int>> b)
{
    int n = a.size();
    vector<vector<int>> c;

    if (n == 1) //Base case is a matrix size of 1
    {
        c.resize(n);
        c.at(0).push_back(a.at(0).at(0) * b.at(0).at(0)); //Multiply the only values in the matrices
    }
    else
    {
        //Dividing phase, seperating a into 4 quadrants
        vector<vector<int>> a11 = divider(a, 0, n / 2, 0, n / 2);
        vector<vector<int>> a21 = divider(a, (n / 2), n, 0, n / 2);
        vector<vector<int>> a12 = divider(a, 0, n / 2, (n / 2), n);
        vector<vector<int>> a22 = divider(a, (n / 2), n, (n / 2), n);

        //Dividing phase, seperating b into 4 quadrants
        vector<vector<int>> b11 = divider(b, 0, n / 2, 0, n / 2);
        vector<vector<int>> b21 = divider(b, (n / 2), n, 0, n / 2);
        vector<vector<int>> b12 = divider(b, 0, n / 2, (n / 2), n);
        vector<vector<int>> b22 = divider(b, (n / 2), n, (n / 2), n);
        
        //Computing each of the c quadrants
        vector<vector<int>> c11 = adder(divideConquer(a11, b11), divideConquer(a12, b21), 1);
        vector<vector<int>> c12 = adder(divideConquer(a11, b12), divideConquer(a12, b22), 1);
        vector<vector<int>> c21 = adder(divideConquer(a21, b11), divideConquer(a22, b21), 1);
        vector<vector<int>> c22 = adder(divideConquer(a21, b12), divideConquer(a22, b22), 1);

        //Merge all the c quadrants back into c
        for (int i = 0; i < n/2; i++)
        {
            vector<int> temp;
            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c11.at(i).at(j));
            }

            for (int j = 0; j < n/2; j++)
            {
                temp.push_back(c12.at(i).at(j));
            }
            c.push_back(temp);
        }

        for (int i = 0; i < n/2; i++)
        {
            vector<int> temp;
            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c21.at(i).at(j));
            }

            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c22.at(i).at(j));
            }
            c.push_back(temp);
        }
    }
 
    return c;
}

/*This is strassen's matrix multiplication. The result is stored in c which was passed.
  This function utilizes recursion*/
void strassen(vector<vector<int>> a, vector<vector<int>> b, vector<vector<int>>& c)
{
    int n = a.size();

    if (n == 2) //Base case is a matrix of size 2
    {
        c.resize(2);
        c.at(0).resize(2);
        c.at(1).resize(2);
        //Since its size 2, the 4 quadrants can be easily accessed by their indexes
        c.at(0).at(0) = (a.at(0).at(0) * b.at(0).at(0)) + (a.at(0).at(1) * b.at(1).at(0));
        c.at(0).at(1) = (a.at(0).at(0) * b.at(0).at(1)) + (a.at(0).at(1) * b.at(1).at(1));
        c.at(1).at(0) = (a.at(1).at(0) * b.at(0).at(0)) + (a.at(1).at(1) * b.at(1).at(0));
        c.at(1).at(1) = (a.at(1).at(0) * b.at(0).at(1)) + (a.at(1).at(1) * b.at(1).at(1));
        
    }
    else
    {
        //Dividing phase, seperating a into 4 quadrants
        vector<vector<int>> a11 = divider(a, 0, n / 2, 0, n / 2);
        vector<vector<int>> a21 = divider(a, (n / 2), n, 0, n / 2);
        vector<vector<int>> a12 = divider(a, 0, n / 2, (n / 2), n);
        vector<vector<int>> a22 = divider(a, (n / 2), n, (n / 2), n);

        //Dividing phase, seperating b into 4 quadrants
        vector<vector<int>> b11 = divider(b, 0, n / 2, 0, n / 2);
        vector<vector<int>> b21 = divider(b, (n / 2), b.size(), 0, n / 2);
        vector<vector<int>> b12 = divider(b, 0, n / 2, (n / 2), n);
        vector<vector<int>> b22 = divider(b, (n / 2), n, (n / 2), n);
        //Calculating the values of p, q, r, s, t, u, and v by recursivley calling the strassen function
        vector<vector<int>> p, q, r, s, t, u, v;
        strassen(adder(a11, a22, 1), adder(b11, b22, 1), p);
        strassen(adder(a21, a22, 1), b11, q);
        strassen(a11, adder(b12, b22, -1), r);
        strassen(a22, adder(b21, b11, -1), s);
        strassen(adder(a11, a12, 1), b22, t);
        strassen(adder(a21, a11, -1), adder(b11, b12, 1), u);
        strassen(adder(a12, a22, -1), adder(b21, b22, 1), v);
        //Using the 7 variables to calculate each of the c quadrants
        vector<vector<int>> c11 = adder(adder(adder(p, s, 1), t, -1), v, 1); //This is doing c11 = ((p + s) - t) + v
        vector<vector<int>> c12 = adder(r, t, 1); //c12 = r + t
        vector<vector<int>> c21 = adder(q, s, 1); //c21 = q + s
        vector<vector<int>> c22 = adder(adder(adder(p, r, 1), q, -1), u, 1); //This is doing c22 = ((p + r) - q) + u
        
        //Merge all the c quadrants back into c
        for (int i = 0; i < n / 2; i++)
        {
            vector<int> temp;
            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c11.at(i).at(j));
            }

            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c12.at(i).at(j));
            }
            c.push_back(temp);
        }

        for (int i = 0; i < n / 2; i++)
        {
            vector<int> temp;
            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c21.at(i).at(j));
            }

            for (int j = 0; j < n / 2; j++)
            {
                temp.push_back(c22.at(i).at(j));
            }
            c.push_back(temp);
        }
    }
}

/*The divider function is a helper function for divideConquer and strassen functions.
  It partitions the given matrix by copying the data of the section into a smaller matrix.
  The section taken is based on the indexes passed to the fucntion*/
vector<vector<int>> divider(vector<vector<int>> a, int iStart, int iEnd, int jStart, int jEnd)
{
    vector<vector<int>> smallMatrix;

    for (int i = iStart; i < iEnd; i++)
    {
        vector<int> temp;
        for (int j = jStart; j < jEnd; j++)
        {
            temp.push_back(a.at(i).at(j));
        }
        smallMatrix.push_back(temp);
    }

    return smallMatrix;
}

/*The adder function is a helper function for divideConquer and strassen functions.
  It simply performs matrix additions on the two give matrices it was passed.
  Mult is used to determine is we should add or subtract. Typically 1 is passed for adition and -1 for subtraction*/
vector<vector<int>> adder(vector<vector<int>> a, vector<vector<int>> b, int mult)
{
    vector<vector<int>> sumMatrix;

    sumMatrix.resize(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        sumMatrix.at(i).resize(a.size());
        for (int j = 0; j < a.at(i).size(); j++)
        {
            sumMatrix.at(i).at(j) = a.at(i).at(j) + (mult * b.at(i).at(j));
        }
    }

    return sumMatrix;
}

/*A simple function to print a matrix*/
void printMatrix(vector<vector<int>> m)
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m.at(i).size(); j++)
        {
            cout << m.at(i).at(j) << " ";
        }
        cout << endl;
    }
}