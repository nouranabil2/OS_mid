// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
void issafe(float*& work, bool*& finish, int**& max, int**& allocation, int n, int m, int** &Need, int input,int preq)
{

	
	int* safe;
	safe = new int[n];
	for (int i = 0; i < m; i++)
	{
		safe[i] = 0;
	}
	
	int flag1 = 0;
	int h = 0;
	int x = 0;
	int i = 0;
	for (int j = 0; j < n; j++)
	{
		i = 0;
		while (i < n)
		{

			// for (int i = 0; i < n; i++)
			 //{
				 //for (int j = 0; j < m; j++)
				 //{
			for (int w = 0; w < m; w++)
			{
				if (Need[i][w] <= work[w])
				{
					x++;
				}
			}

			if (finish[i] == false && x == m)
			{
				for (int k = 0; k < m; k++)
				{
					work[k] = work[k] + allocation[i][k];
					finish[i] = true;

				}
				safe[h] = i;
				h++;
				//i++;
				//i = 0;
			}
			//else { i++; }
			/*if(i==n-1&&flag1==0)
			{
				i = 0;
				flag1 = 1;
			}*/
			else { i++; }

			//}
			x = 0;
		}
	}
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (finish[i] == true)
		{
			count++;
		}
	}
	if (count == n)
	{
		
		
		if (input == 0) { cout << "yes, request can be granded with safe state <"<<"P" << preq<< "req"<<","; }
		if (input == 1)
		{
			cout << "yes, safe state <";
		}
		for (int i = 0; i < n; i++)
		{
			if (i == n - 1) { cout << "P" << safe[i] << ">"; }
			else { cout << "P" << safe[i] << ","; };
		}
	}
	else cout << "No";

}
int main()
{
	int m;
	int n;
	cout << "enter no of processes" << endl;
	cin >> n;
	cout << "enter no of Resources" << endl;
	cin >> m;

	float* work;
	work = new float[m];
	float* available;
	available = new float[m];
	float* safe;
	safe = new float[n];
	int** Need = new int* [n];
	for (int i = 0; i < n; ++i) {
		Need[i] = new int[m];
	}

	int** allocation = new int* [n];
	for (int i = 0; i < n; ++i) {
		allocation[i] = new int[m];
	}
	/* int** Need = new int* [n];
	 for (int i = 0; i < n; ++i) {
		 Need[i] = new int[m];
	 }*/
	int** max = new int* [n];
	for (int i = 0; i < n; ++i) {
		max[i] = new int[m];
	}
	// allocation = new float[n][m];
	bool* finish;
	finish = new bool[n];
	for (int i = 0; i < n; i++)
	{
		finish[i] = false;
	}

	cout << "enter available matrix" << endl;
	for (int i = 0; i < m; i++)
	{
		cin >> work[i];
		available[i] = work[i];
	}
	cout << "enter allocation matrix" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "P" << i << ":";
		for (int j = 0; j < m; j++)
		{

			cin >> allocation[i][j];

		}

	}
	cout << "enter Max matrix" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "P" << i << ":";
		for (int j = 0; j < m; j++)
		{

			cin >> max[i][j];
		}

	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Need[i][j] = max[i][j] - allocation[i][j];
		}

	}
	cout << "Need matrix:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "P" << i << ":";
		for (int j = 0; j < m; j++)
		{
			cout << Need[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	int prequest = 0;
	int input;
	while(1)
	{
	cout << "To use the Safety algorithm let input=1 ,but if you want to use the request algorithm let input=0" << endl << "input=";
	cin >> input;
	if (input == 1) {
		for(int f = 0; f < m;f++)
		{
			work[f] = available[f];
		} 
		for (int i = 0; i < n; i++)
		{
			finish[i] = false;
		}
		issafe(work, finish, max, allocation, n, m, Need, input, prequest); 
	}
	else if (input == 0)
	{
		for (int f = 0; f < m; f++)
		{
			work[f] = available[f];
		}
		for (int i = 0; i < n; i++)
		{
			finish[i] = false;
		}
		//int prequest;
		cout << "enter the process number who ask for request " << endl;
		cin >> prequest;
		int* req;
		req = new int[m];
		cout << "enter the request" << endl;
		for (int i = 0; i < m; i++)
		{
			cin >> req[i];
		}
		int x = 0;
		int y = 0;
		for (int w = 0; w < m; w++)
		{
			if (req[w] <= Need[prequest][w])
			{
				x++;
			}
		}
		for (int j = 0; j < m; j++)
		{
			if (req[j] <= work[j])
			{
				y++;
			}
		}
		if (x == m && y == m)
		{
			for (int j = 0; j < m; j++)
			{
				work[j] = work[j] - req[j];
				available[j] = work[j];
				allocation[prequest][j] = allocation[prequest][j] + req[j];
				Need[prequest][j] = Need[prequest][j] - req[j];
			}
			issafe(work, finish, max, allocation, n, m, Need, input, prequest);

		}
		else { cout << " No the request cant be granted"; }


	}
	else { cout << "Something went wrong make sure that the input= 1 or 0"; }
	cout << endl;
	
}
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
