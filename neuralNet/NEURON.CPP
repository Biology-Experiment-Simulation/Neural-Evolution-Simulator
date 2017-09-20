#pragma once
#include "Neuron.h"

namespace NN{
Neuron::Neuron(int inputSize, int layer)
{
     m_output = -1; /// default's to bias value
     m_layer = layer; /// layer number
     m_error = 0; /// defualt error

     /// SET random weights ///
     for(int i=0; i<inputSize;i++)
     {
       float ran = randomValue(mt);
         m_weights.push_back(ran);
         m_inputs.push_back(0);
     }

}

Neuron::~Neuron()
{
   ///std::cout << "Neuron destroyed!" << "\n";
}

    void Neuron::Activate()
    {
        if(m_weights.size() != 0) /// if has any inputs, else it's bias with predifened output of -1;
        {
            float in=0;
            for(unsigned i=0; i<m_weights.size();i++)
             {
                 in+=m_weights[i]*m_inputs[i]; /// SUM of(weights * inputs)

             }
              m_output = in / (1 + abs(in));//in / (1 + abs(in));
            // m_output = 1.0f/(1.0f+exp(-in)); /// sigmoid
        }

    }

    void Neuron::UpdateWeights_BP()
    {
        for(int i=0; i<m_inputs.size();i++)
        {
            m_weights[i] = m_weights[i] + 0.3f*m_error*m_output*(1-m_output);
        }


    }

    float Neuron::GetOutput()
    {
        return m_output;
    }

    void Neuron::SetWeights(std::vector<float>& weights)
    {
        m_weights = weights;
    }
    void Neuron::GetWeights(std::vector<float>& weights)
    {
        weights = m_weights;
    }
     void Neuron::SetInputs(std::vector<float>& Inputs)
    {
        m_inputs.clear();
         m_inputs = Inputs;
    }
     void Neuron::GetInputs(std::vector<float>& Inputs)
    {
        Inputs = m_inputs;
    }
     void Neuron::SetError(float& eror)
    {
        m_error = eror;
    }
    void Neuron::GetError(float& eror)
    {
       eror  = m_error;
    }




}
