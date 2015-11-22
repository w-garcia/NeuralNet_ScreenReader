#pragma once

#include <vector>
#include "TrainingDataSet.h"
#include "RandomHelper.h"

using namespace std;

class Neuron
{
public:
	double output;
	double error;

	Neuron(double o, double eo)
	{
		output = o;
		error = eo;
	}



};

class Weight
{
public:
	double value;
	double currentChange;
	double lastChange;
};

class NeuralNetwork
{
public:
	vector< vector<Neuron> > layerToNeuron;
	vector< vector< vector<Weight> > > VVVweight;
	vector<double> expectedOutput;

	unsigned int outputLayerIndex;
	const int inputLayerIndex = 0;
	int errorCount = 0;
	int expectedNumber = 0;
	int pickedNumber = 0;
	double trainingNoise = 0.03;
	double testNoise = 0.06;
	double learningRate = 0.01;
	double weightDecay = 1.0;
	double momentumFactor = 0.1;

	TrainingDataSet dataSet;

	NeuralNetwork(vector<unsigned int> sizeOfLayers)
	{
		dataSet = TrainingDataSet();

		unsigned int layerI;
		for (layerI = 0; layerI < sizeOfLayers.size(); layerI++)
		{
			layerToNeuron.push_back(vector<Neuron>());
			for (unsigned int neuronI = 0; neuronI < sizeOfLayers[layerI]; neuronI++)
			{
				//layerToNeuron[layerI].push_back(Neuron(layerI + 0.01, neuronI + 0.2));
				layerToNeuron[layerI].push_back(Neuron(0.01, 0.2));

			}
		}

		// now the weights [toLayer][toNeuron][fromInput/Neuron]

		VVVweight.clear();

		for (layerI = 0; layerI < layerToNeuron.size(); layerI++)
		{
			VVVweight.push_back(vector< vector< Weight >>());
			if (layerI != 0)
			{
				for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[layerI].size(); toNeuronI++)
				{
					VVVweight[layerI].push_back(vector< Weight >());
					for (unsigned int i = 0; i < layerToNeuron[layerI - 1].size() + 1; i++)
					{
						VVVweight[layerI][toNeuronI].push_back( Weight() );
					}
				}
			}
		}

		outputLayerIndex = layerToNeuron.size() - 1;
		expectedOutput.clear();
		for (unsigned int i = 0; i < layerToNeuron[outputLayerIndex].size(); i++)
		{
			expectedOutput.push_back(0.0);
		}
		
		randomizeWeights();
	}

	void randomizeWeights()
	{
		for (unsigned int toLayerI = 1; toLayerI < layerToNeuron.size(); toLayerI++)
		{
			for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[toLayerI].size(); toNeuronI++)
			{
				for (unsigned int fromNeuronI = 0; fromNeuronI < layerToNeuron[toLayerI - 1].size() + 1; fromNeuronI++)
				{
					VVVweight[toLayerI][toNeuronI][fromNeuronI].value = randD(-1.0, 1.0);
				}
			}
		}
	}

	void Train(int dataSetNumber)
	{
		expectedNumber = dataSetNumber;
		getInputsAndExpectedValuesFrom(dataSetNumber);
		randomizeInputs(trainingNoise);
		feedForward();
		if (pickedNumber != expectedNumber) errorCount++;
		backProp();
	}
	
	void Test(int dataSetNumber)
	{
		expectedNumber = dataSetNumber;
		getInputsAndExpectedValuesFrom(dataSetNumber);
		randomizeInputs(testNoise);
		feedForward();
		if (pickedNumber != expectedNumber) errorCount++;
	}

	void randomizeInputs(double p)
	{
		for (unsigned int i = 0; i < layerToNeuron[inputLayerIndex].size(); i++)
		{
			if (chance(p))
			{
				Neuron ne = layerToNeuron[inputLayerIndex][i];
				if (ne.output == 0.8)
				{
					ne.output = 0.2;
				}
				else
				{
					ne.output = 0.8;
				}
			}
		}
	}

	void feedForward()
	{
		double total;
		for (unsigned int toLayerI = 1; toLayerI < layerToNeuron.size(); toLayerI++)
		{
			for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[toLayerI].size(); toNeuronI++)
			{
				total = 0.0;
				unsigned int fromNeuronI;
				for (fromNeuronI = 0; fromNeuronI < layerToNeuron[toLayerI - 1].size(); fromNeuronI++)
				{
					total += layerToNeuron[toLayerI - 1][fromNeuronI].output * VVVweight[toLayerI][toNeuronI][fromNeuronI].value;
				}
				//total += 1.0 * VVVweight[toLayerI][toNeuronI][fromNeuronI].value;
				layerToNeuron[toLayerI][toNeuronI].output = sigmoid(total);
			}
		}

		pickedNumber = 0;
		double biggest = layerToNeuron[outputLayerIndex][0].output;
		for (unsigned int neuronI = 0; neuronI < layerToNeuron[outputLayerIndex].size(); neuronI++)
		{
			if (layerToNeuron[outputLayerIndex][neuronI].output > biggest)
			{
				biggest = layerToNeuron[outputLayerIndex][neuronI].output;
				pickedNumber = neuronI;
			}
		}
	}

	void backProp()
	{
		unsigned int layerI = outputLayerIndex;

		for (unsigned int iNeuron = 0; iNeuron < layerToNeuron[outputLayerIndex].size(); iNeuron++)
		{
			// chained sigmoidPrime to sigmoid
			layerToNeuron[layerI][iNeuron].error = (expectedOutput[iNeuron] - layerToNeuron[layerI][iNeuron].output) * sigmoidPrime(layerToNeuron[layerI][iNeuron].output);
		}

		for (layerI = outputLayerIndex - 1; layerI >= 1; layerI--)
		{
			for (unsigned int neuronI = 0; neuronI < layerToNeuron[layerI].size(); neuronI++)
			{
				double totalE = 0.0;
				for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[layerI + 1].size(); toNeuronI++)
				{
					totalE += layerToNeuron[layerI + 1][toNeuronI].error * VVVweight[layerI + 1][toNeuronI][neuronI].value;
				}
				// chained sigmoidPrime to sigmoid
				//ne.error = totalE * sigmoid(ne.output);
				layerToNeuron[layerI][neuronI].error = totalE * sigmoidPrime(layerToNeuron[layerI][neuronI].output);

			}
		}

		for (layerI = outputLayerIndex; layerI >= 1; layerI--)
		{
			for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[layerI].size(); toNeuronI++)
			{
				for (unsigned int fromNeuronI = 0; fromNeuronI < layerToNeuron[layerI - 1].size() + 1; fromNeuronI++)
				{
					VVVweight[layerI][toNeuronI][fromNeuronI].currentChange += learningRate * layerToNeuron[layerI][toNeuronI].error;
				}
			}
		}

		for (layerI = outputLayerIndex; layerI >= 1; layerI--)
		{
			for (unsigned int toNeuronI = 0; toNeuronI < layerToNeuron[layerI].size(); toNeuronI++)
			{
				for (unsigned int fromNeuronI = 0; fromNeuronI < layerToNeuron[layerI - 1].size() + 1; fromNeuronI++)
				{
					VVVweight[layerI][toNeuronI][fromNeuronI].currentChange += (momentumFactor * VVVweight[layerI][toNeuronI][fromNeuronI].lastChange);
					VVVweight[layerI][toNeuronI][fromNeuronI].value += VVVweight[layerI][toNeuronI][fromNeuronI].currentChange;
					VVVweight[layerI][toNeuronI][fromNeuronI].lastChange = VVVweight[layerI][toNeuronI][fromNeuronI].currentChange;
					VVVweight[layerI][toNeuronI][fromNeuronI].currentChange = 0.0;
					VVVweight[layerI][toNeuronI][fromNeuronI].value *= weightDecay;
				}
			}
		}
	}

	void getInputsAndExpectedValuesFrom(int dataSetNumber)
	{
		for (unsigned int i = 0; i < layerToNeuron[inputLayerIndex].size(); i++)
		{
			layerToNeuron[inputLayerIndex][i].output = dataSet.dataList[dataSetNumber].doubleList[i];
		}
		expectedOutput.clear();
		for (unsigned int neuronI = 0; neuronI < layerToNeuron[outputLayerIndex].size(); neuronI++)
		{
			if (neuronI == dataSet.expectedValue[dataSetNumber])
			{
				expectedOutput.push_back(0.8);
			}
			else
			{
				expectedOutput.push_back(0.2);
			}
		}
	}


	~NeuralNetwork()
	{

	}
};



