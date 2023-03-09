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
void classical(vector<vector<int>>, vector<vector<int>>);
void divideConquer();
vector<vector<int>> divider();
//void strassen();

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

void classical(vector<vector<int>> m1, vector<vector<int>> m2)
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
}

void divideConquer(vector<vector<int>> a, vector<vector<int>> b)
{
    vector<vector<int>> resultMatrix;

    //Dividing phase
    vector<vector<int>> a11 = divider(a, 0, a.size()/2, 0, a.at(0).size()/2);
    vector<vector<int>> a12 = divider(a, (a.size() / 2) + 1, a.size(), 0, a.at(0).size() / 2);
    vector<vector<int>> a21 = divider(a, 0, a.size() / 2, (a.at(0).size() / 2) + 1, a.at(0).size());
    vector<vector<int>> a22 = divider(a, (a.size() / 2) + 1, a.size(), (a.at(0).size() / 2) + 1, a.at(0).size());

    vector<vector<int>> b11 = divider(b, 0, b.size() / 2, 0, b.at(0).size() / 2);
    vector<vector<int>> b12 = divider(b, (b.size() / 2) + 1, b.size(), 0, b.at(0).size() / 2);
    vector<vector<int>> b21 = divider(b, 0, b.size() / 2, (b.at(0).size() / 2) + 1, b.at(0).size());
    vector<vector<int>> b22 = divider(b, (b.size() / 2) + 1, b.size(), (b.at(0).size() / 2) + 1, b.at(0).size());
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