/*
    Name: Benjamin Liu
    Class: CS3310.01
    Assignment: Project 1 
    Due Date: 04/06/2023
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Function Prototypes here
vector<vector<int>> classical(vector<vector<int>>, vector<vector<int>>);
void divideConquer();
vector<vector<int>> divider();
vector<vector<int>> adder();
//void strassen();
void printMatrix(vector<vector<int>>);

int main()
{

    vector<vector<int>> m;
    for (int i = 1; i <= 3; i++)
    {
        vector<int> temp;
        for (int j = 1; j <= 3; j++)
        {
            temp.push_back(j * i);
        }
        m.push_back(temp);
    }

    classical(m, m);

    return 0;
}

vector<vector<int>> classical(vector<vector<int>> m1, vector<vector<int>> m2)
{
    vector<vector<int>> resultMatrix;

    for (int i = 0; i < m1.size(); i++)
    {
        resultMatrix.resize(m1.size());
        for (int j = 0; j < m2.at(i).size(); j++)
        {
            resultMatrix.at(i).resize(m2.at(i).size());
            resultMatrix.at(i).at(j) = 0;
            for (int k = 0; k < m2.size(); k++)
            {
                resultMatrix.at(i).at(j) += m1.at(i).at(k) * m2.at(k).at(j);
            }
        }
    }

    for (int i = 0; i < resultMatrix.size(); i++)
    {
        for (int j = 0; j < resultMatrix.size(); j++)
        {
            cout << resultMatrix.at(i).at(j) << " ";;
        }

        cout << endl;
    }

    return resultMatrix;
}

void divideConquer(vector<vector<int>> a, vector<vector<int>> b)
{
    int n = a.size();
    vector<vector<int>> resultMatrix;
    
    //Dividing phase, seperating a into 4 quadrants
    vector<vector<int>> a11 = divider(a, 0, n/2, 0, a.at(0).size()/2);
    vector<vector<int>> a12 = divider(a, (a.size() / 2) + 1, a.size(), 0, a.at(0).size() / 2);
    vector<vector<int>> a21 = divider(a, 0, a.size() / 2, (a.at(0).size() / 2) + 1, a.at(0).size());
    vector<vector<int>> a22 = divider(a, (a.size() / 2) + 1, a.size(), (a.at(0).size() / 2) + 1, a.at(0).size());
    
    //Dividing phaes, seperating b into 4 quadrants
    vector<vector<int>> b11 = divider(b, 0, b.size() / 2, 0, b.at(0).size() / 2);
    vector<vector<int>> b12 = divider(b, (b.size() / 2) + 1, b.size(), 0, b.at(0).size() / 2);
    vector<vector<int>> b21 = divider(b, 0, b.size() / 2, (b.at(0).size() / 2) + 1, b.at(0).size());
    vector<vector<int>> b22 = divider(b, (b.size() / 2) + 1, b.size(), (b.at(0).size() / 2) + 1, b.at(0).size());

    //Computing each of the c quadrants
    vector<vector<int>> c11 = adder(classical(a11, b11), classical(a12, b21), 1);
    vector<vector<int>> c12 = adder(classical(a11, b12), classical(a12, b22), 1);
    vector<vector<int>> c21 = adder(classical(a21, b11), classical(a22, b21), 1);
    vector<vector<int>> c22 = adder(classical(a21, b12), classical(a22, b22), 1);

    //Merging each of the quadrants in the resultMatrix
    

}

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