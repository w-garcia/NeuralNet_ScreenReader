#include <iostream>
#include <string>
#include "NeuralNetwork.h"
#include <random>

using namespace std;

int main()
{
	srand((unsigned int) time(NULL));

	vector<unsigned int> sizes = { 64, 64, 64, 10 };
	NeuralNetwork nn(sizes);



	while (true)
	{
		string n;
		cin >> n;

		if (n == "train")
		{
			int trainingSize = 0;
			cin >> trainingSize;

			nn.errorCount = 0;

			for (int i = 0; i < trainingSize; i++)
			{ 
				nn.Train(rand() % 10);
				if (i % 100 == 0)
				{
					cout << "Expected Num: " << nn.expectedNumber << " " << "NN Guess: " << nn.pickedNumber << endl;
				}
			}

			

			cout << nn.errorCount << endl;

		}
		else if (n == "test")
		{
			nn.errorCount = 0;
			int testingCount;
			cin >> testingCount;
			for (int i = 0; i < testingCount; i++)
			{
				nn.Test(rand() % 10);
				if (i % 100 == 0)
				{
					cout << "Expected Num: " << nn.expectedNumber << " " << "NN Guess: " << nn.pickedNumber << endl;
				}
			}
			cout << nn.errorCount << endl;

		}
		else if (n == "q" || n == "quit")
		{
			break;
		}

	}
	





	return 0;
}