#include <iostream>
#include <string>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "NeuralNetwork.h"
#include <stdio.h>
#include <dirent.h>
#include <unordered_map>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

using namespace std;
using namespace cv;

bool getFileNamesFromDir(string dirName, string parentDir, unordered_map<string, vector<string>> & results)
{
	char slash = '\\';
	DIR *dir;
	struct dirent *ent;
	char *NulPosition = &dirName[dirName.length()];
	if ((dir = opendir(dirName.c_str())) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			
			if (ent->d_type == DT_DIR)
			{
				
				if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				{

					printf(NulPosition, "%c%s", slash, ent->d_name);
					if (getFileNamesFromDir(dirName + ent->d_name, ent->d_name, results))
					{
						closedir(dir);
						return 1;
					}
					*NulPosition = '\0';
				}
			}
			else
			{
				if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				{
					printf("Loaded %s\n", ent->d_name);
					results[parentDir].push_back(dirName + slash + ent->d_name);
				}
			}
		}
	}
	closedir(dir);
	return 0;
}



int main(int argc, char** argv)
{
	srand((unsigned int) time(NULL));

	vector<unsigned int> sizes = { 64, 64, 64, 10 };
	NeuralNetwork nn(sizes);

	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	string trainingPath = "E://Owner//My Documents//c_CAP4630//NeuralNet_ScreenReader//Training Data//";

	unordered_map<string, vector<string>> expectedToImageFilePaths;

	cout << "Initiating training data at ";
	//trainingPath += "/Training Data/";
	cout << trainingPath << endl;
	//printf("The current working directory is %s", cCurrentPath);

	getFileNamesFromDir(trainingPath, "", expectedToImageFilePaths);


	// map expected values to vector for later
	vector<string> expectedValueKeys;

	unordered_map<string, vector<string> >::iterator iter = expectedToImageFilePaths.begin();

	while (iter != expectedToImageFilePaths.end())
	{
		expectedValueKeys.push_back(iter->first);
		iter++;
	}


	cout << "Ready." << endl;

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
				int randLetterIndex = rand() % expectedValueKeys.size();
				string expectedLetter = expectedValueKeys[randLetterIndex];
				int imageFileNameCount = expectedToImageFilePaths[expectedLetter].size();
				string randPath = expectedToImageFilePaths[expectedLetter][rand() % imageFileNameCount];
				
				Mat rawImage = imread( randPath , IMREAD_GRAYSCALE) > 128;

				Size size(16, 16);
				Mat transformedImage;
				resize(rawImage, transformedImage, size);

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