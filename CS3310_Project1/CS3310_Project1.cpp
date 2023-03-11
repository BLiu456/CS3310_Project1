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
vector<vector<int>> divideConquer(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> divider(vector<vector<int>>, int, int, int, int);
vector<vector<int>> adder(vector<vector<int>>, vector<vector<int>>);
//void strassen();
void printMatrix(vector<vector<int>>);

int main()
{

    vector<vector<int>> m;
    for (int i = 1; i <= 4; i++)
    {
        vector<int> temp;
        for (int j = 1; j <= 4; j++)
        {
            temp.push_back(j * i);
        }
        m.push_back(temp);
    }

    classical(m, m);
    cout << endl;
    printMatrix(divideConquer(m, m));

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

vector<vector<int>> divideConquer(vector<vector<int>> a, vector<vector<int>> b)
{
    int n = a.size();
    vector<vector<int>> c;

    if (n == 1)
    {
        c.resize(n);
        c.at(0).push_back(a.at(0).at(0) * b.at(0).at(0));
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

        //Computing each of the c quadrants
        vector<vector<int>> c11 = adder(divideConquer(a11, b11), divideConquer(a12, b21));
        vector<vector<int>> c12 = adder(divideConquer(a11, b12), divideConquer(a12, b22));
        vector<vector<int>> c21 = adder(divideConquer(a21, b11), divideConquer(a22, b21));
        vector<vector<int>> c22 = adder(divideConquer(a21, b12), divideConquer(a22, b22));

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

vector<vector<int>> adder(vector<vector<int>> a, vector<vector<int>> b)
{
    vector<vector<int>> sumMatrix;

    sumMatrix.resize(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        sumMatrix.at(i).resize(a.size());
        for (int j = 0; j < a.at(i).size(); j++)
        {
            sumMatrix.at(i).at(j) = a.at(i).at(j) + b.at(i).at(j);
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