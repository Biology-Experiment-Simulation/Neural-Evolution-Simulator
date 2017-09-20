#pragma once
#include<vector>
#include "Neuron.h"


namespace NN{

class Net{
private:
    int m_InputlayerSize;
    int m_hiddenLayers;
    int m_hiddenLayerSize;
    int m_outputLayerSize;

    std::vector<Neuron> m_Neurons;
public:
    Net(int inputSize, int hiddenLayers, int hiddenLayerSize, int outputSize);
    ~Net();

    std::vector<float> feedForward(std::vector<float>& input);
    void backPropagation(float errors, float learningRate);

    void setWeights(std::vector<float>& newWeights);
    void getWeights(std::vector<float>& allWeights);

 /// Temporary fields
    int fitnessScore;
    int closestFood;

};


}
