#pragma once

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class Data
{
public:

	cv::Mat image;
	vector<double> doubleList;
	int expectedIndex;

	Data()
	{

	}

	Data(cv::Mat d)
	{
		image = cv::Mat(d);
		setupDoubleList();
	}

	void setupDoubleList()
	{
		doubleList.clear(); 

		vector<uchar> temp;
		temp.assign(image.datastart, image.dataend);

		for (int i = 0; i < temp.size(); i++)
		{
			if ((int)temp[i] > 128)
			{
				doubleList.push_back(0.8); 
			}
			else
			{
				doubleList.push_back(0.2);
			}
		}
	}

};
class TrainingDataSet
{
public:

	vector<int> expectedValue;
	Data data;

	TrainingDataSet()
	{

		expectedValue.push_back(0);
		expectedValue.push_back(1);
		expectedValue.push_back(2);
		expectedValue.push_back(3);
		expectedValue.push_back(4);
		expectedValue.push_back(5);
		expectedValue.push_back(6);
		expectedValue.push_back(7);
		expectedValue.push_back(8);
		expectedValue.push_back(9);

	}

	~TrainingDataSet()
	{

	}



};

