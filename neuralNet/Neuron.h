#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED
#pragma once
#include <math.h>
#include<iostream>
#include <vector>
#include <random>
#include <ctime>



namespace NN{

         static std::random_device rd;
         static std::mt19937 mt(rd());
         static std::uniform_real_distribution<float> randomValue(-3.2, 3.4);



    class Neuron{
    private:
        int m_layer; /// not used yet
        float m_output;
        float m_error;
        std::vector<float> m_weights;
        std::vector<float> m_inputs;
    public:
        Neuron(int inputSize, int layer);
        ~Neuron();

        void SetWeights(std::vector<float>& weights);
        void GetWeights(std::vector<float>& weights);


        void SetInputs(std::vector<float>& inputs);
        void GetInputs(std::vector<float>& inputs);

        void SetError(float& eror);
        void GetError(float& eror);
        void UpdateWeights_BP();

        void Activate(); ///sigmoid function of [ sum(weigths * inputs) ].
        float GetOutput(); /// return m_output of neuron

    };


}




#endif // NEURON_H_INCLUDED
