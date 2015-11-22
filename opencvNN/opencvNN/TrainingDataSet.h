#pragma once

#include <vector>
#include <string>

using namespace std;

class Data
{
public:

	string sData[8];
	vector<double> doubleList;

	Data(string s0, string s1, string s2, string s3, string s4, string s5, string s6, string s7)
	{
		sData[0] = s0;
		sData[1] = s1;
		sData[2] = s2;
		sData[3] = s3;
		sData[4] = s4;
		sData[5] = s5;
		sData[6] = s6;
		sData[7] = s7;
		setupDoubleList();
	}

	void setupDoubleList()
	{
		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j<8; j++)
			{
				if (sData[i][j] == 'X')
				{
					doubleList.push_back(0.8);
				}
				else
				{
					doubleList.push_back(0.2);
				}
			}
		}
	}

};
class TrainingDataSet
{
public:

	vector<Data> dataList;
	vector<int> expectedValue;

	TrainingDataSet()
	{
		Data d0(
			"--XXXX--",
			"-XX--XX-",
			"XX----XX",
			"X------X",
			"X------X",
			"XX----XX",
			"-XX--XX-",
			"--XXXX--"
			);
		Data d1(
			"---XX---",
			"---XX---",
			"---XX---",
			"---XX---",
			"---XX---",
			"---XX---",
			"---XX---",
			"---XX---"
			);
		Data d2(
			"--XXX---",
			"-XX--XX-",
			"X-----XX",
			"-------X",
			"-----XX-",
			"---XX---",
			"-XX-----",
			"XXXXXXXX"
			);
		Data d3(
			"--XXXXX-",
			"-X----XX",
			"-X----XX",
			"----XXX-",
			"-------X",
			"XX-----X",
			"-X----XX",
			"--XXXXX-"
			);
		Data d4(
			"-----XX-",
			"----X-X-",
			"---X--X-",
			"--X---X-",
			"-X----X-",
			"XXXXXXXX",
			"------X-",
			"------X-"
			);
		Data d5(
			"XXXXXXXX",
			"X-------",
			"X-------",
			"XXXXX---",
			"-----XX-",
			"------XX",
			"-----XX-",
			"XXXXXX--"
			);
		Data d6(
			"--XXXXX-",
			"-XX---XX",
			"XX------",
			"X XXXXX-",
			"XX----XX",
			"XX----XX",
			"-XX--XX-",
			"--XXXX--"
			);
		Data d7(
			"XXXXXXXX",
			"------X-",
			"-----X--",
			"----X---",
			"---X----",
			"--X-----",
			"-X------",
			"X-------"
			);
		Data d8(
			"--XXXX--",
			"XX----XX",
			"X------X",
			"-XXXXXX-",
			"X------X",
			"X------X",
			"XX----XX",
			"-XXXXXX-"
			);
		Data d9(
			"--XXXXX-",
			"-XX---XX",
			"XX----XX",
			"-XX---XX",
			"--XXXXXX",
			"------XX",
			"------XX",
			"------XX"
			);

		dataList.push_back(d0);
		dataList.push_back(d1);
		dataList.push_back(d2);
		dataList.push_back(d3);
		dataList.push_back(d4);
		dataList.push_back(d5);
		dataList.push_back(d6);
		dataList.push_back(d7);
		dataList.push_back(d8);
		dataList.push_back(d9);

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

