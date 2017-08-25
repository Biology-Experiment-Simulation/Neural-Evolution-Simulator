#pragma once
#include "Net.h"


namespace NN{

Net::Net(int inputSize, int hiddenLayers, int hiddenLayersSize, int outputSize)
: m_InputlayerSize(inputSize), m_hiddenLayers(hiddenLayers), m_hiddenLayerSize(hiddenLayersSize), m_outputLayerSize(outputSize)
{
    /// ////// input layer ////////////////////////////
    for(int i=0; i<m_InputlayerSize;i++)
    {
        m_Neurons.push_back(Neuron(0,0));
    }
        m_Neurons.push_back(Neuron(0,0)); /// bias

    /// ////// hidden layer create neurons //////////////////////
    for(int i=0; i<m_hiddenLayers;i++)
    {
         for(int j=0; j<m_hiddenLayerSize;j++)
         {
             if(i==0)
            m_Neurons.push_back( Neuron(m_InputlayerSize+1,i+1) );
            else
            m_Neurons.push_back( Neuron(m_hiddenLayerSize+1,i+1) );
         }
         m_Neurons.push_back(Neuron(0,i+1)); /// bias
    }
   /// ////// output layer create neurons  /////////////////////
    for(int i=0; i<m_outputLayerSize;i++)
        {
            m_Neurons.push_back(Neuron(m_hiddenLayerSize+1,m_hiddenLayers + 1));
        }

        fitnessScore = 0;
        closestFood = 0;

}

std::vector<float> Net::feedForward(std::vector<float>& input)
{
    unsigned cN = 0; /// current Neuron to be activated;
    std::vector<float> last_layer_output;
    std::vector<float> temp_input;

    /// ////// pass input to inputLayer, activate neurons; ///////////////////////////////
    temp_input.resize(1);
    for(int i=0;i<m_InputlayerSize;i++)
        {

             last_layer_output.push_back(input[cN]);
            cN++;
        }
        last_layer_output.push_back(-1.0f);
        cN++;


    /// ////////// perform activations on hidden layers ///////////////////////////////////



    for(int i=1; i<=m_hiddenLayers;i++)
    {
        temp_input.clear();
         for(int j=0; j<m_hiddenLayerSize;j++)
         {
            m_Neurons[cN].SetInputs(last_layer_output);
            m_Neurons[cN].Activate();
            temp_input.push_back( m_Neurons[cN].GetOutput());
            //std::cout <<  "neuron output number: " << cN << " " << m_Neurons[cN].GetOutput()  << std::endl;
            cN++;
         }
         ///m_Neurons[cN].Activate();  /// bias
         //last_layer_output.clear();
         temp_input.push_back(-1.0f);
         last_layer_output = temp_input;
        // std::cout <<  "neuron output number: " << cN << " " << m_Neurons[cN].GetOutput()  << std::endl;
         cN++;
    }

    /// ////// output layer create neurons  /////////////////////
    temp_input.clear();
    for(int i=0; i<m_outputLayerSize;i++)
        {
            m_Neurons[cN].SetInputs(last_layer_output);
            m_Neurons[cN].Activate();
            temp_input.push_back( m_Neurons[cN].GetOutput());
          //  std::cout <<  "neuron output number: " << cN << " " << m_Neurons[cN].GetOutput()  << std::endl;
            cN++;
        }

    return temp_input;


}


void Net::backPropagation(float error, float learningRate)
{
    float zero_error = 0.0f;
    for(int i=0; i<m_Neurons.size(); i++)
    {
        m_Neurons[i].SetError(zero_error);
    }

    unsigned cN = m_Neurons.size()-1; /// current neuron -starts with last one;
    std::vector<float> weights_temp;
    float error_temp;


    /// set error of output layer and last hidden
    unsigned cN_temp = cN-m_outputLayerSize-m_hiddenLayerSize; /// points to bias of last hidden layer
      for(int i =0; i<m_outputLayerSize;i++) /// each input neuron
        {

         //  std::cout << "dziala " << cN -i <<"cntest" << cN_temp  << std::endl;
          m_Neurons[cN-i].SetError(error);
          m_Neurons[cN-i].GetWeights(weights_temp);/// each hidden to input neuron weights
           for(int j=0;j<=m_hiddenLayerSize;j++){
               m_Neurons[cN_temp+j].GetError(error_temp);
               error_temp += error*weights_temp[j];
               m_Neurons[cN_temp+j].SetError(error_temp); /// set error to last hidden layer
              // std::cout << "petla " << cN -i <<"cntest" << cN_temp +j  << std::endl;
           }
           //cN--;
        }

    cN = cN_temp; /// points to bias of last hidden layer


           //std::cout << "dziala " << cN<<"cntest" << cN_temp  << std::endl;
    /// /////////////////////////////////////////////////////////////////////// /////////////////
    /// /////////// calculate/set error of other hidden layers - gradient ///////////////////////
    /// /////////////////////////////////////////////////////////////////////// /////////////////

    unsigned layerLeft = m_hiddenLayers-1;
    while(layerLeft>0){
         cN_temp = cN_temp -(m_hiddenLayerSize+ 1);
        for(int i =0; i<m_hiddenLayerSize;i++) /// each input neuron
            {
           //std::cout << "dziala " << cN +i<<"cntest" << cN_temp  << std::endl;
              m_Neurons[cN+i].GetError(error);
              m_Neurons[cN+i].GetWeights(weights_temp);/// each hidden to (hidden-1) neuron weights
               for(int j=0;j<=m_hiddenLayerSize;j++){
                   m_Neurons[cN_temp+j].GetError(error_temp);
                   error_temp += error*weights_temp[j];
                   m_Neurons[cN_temp+j].SetError(error_temp); /// set error to last hidden layer
               }
            }
        cN= cN_temp;
        layerLeft--;
    }


/// /////////////////////////////////////////////////////////////////////// /////////////////
/// /////////// from input to output, update weights      ///////////////////////
/// /////////////////////////////////////////////////////////////////////// /////////////////


    cN = 0; /// current Neuron to be updated;
    std::vector<float> last_layer_output;
    std::vector<float> temp_input;
    temp_input.resize(1);
    for(int i=0;i<m_InputlayerSize;i++)
        {
            cN++;
        }
        cN++; ///bias


    /// ////////// perform activations on hidden layers ///////////////////////////////////


    for(int i=1; i<=m_hiddenLayers;i++)
    {
        temp_input.clear();
         for(int j=0; j<m_hiddenLayerSize;j++)
         {
            m_Neurons[cN].UpdateWeights_BP();
            cN++;
         }
       cN++; ///bias
    }

    /// ////// output layer create neurons  /////////////////////
    temp_input.clear();
    for(int i=0; i<m_outputLayerSize;i++)
        {
            m_Neurons[cN].UpdateWeights_BP();
          //  std::cout <<  "neuron output number: " << cN << " " << m_Neurons[cN].GetOutput()  << std::endl;
            cN++;
        }



}

 void Net::setWeights(std::vector<float>& newWeights)
 {
     std::vector<float> oldWeights;
     int position=0;
         for(int i=0; i < m_Neurons.size(); i++)
         {
             m_Neurons[i].GetWeights(oldWeights);
             for(int j=0;j<oldWeights.size();j++)
                {
                oldWeights[j] = newWeights[position];
                position++;
                }
             m_Neurons[i].SetWeights(oldWeights);
        }
 }

 void Net::getWeights(std::vector<float>& allWeights) /// to finish
 {
     allWeights.clear();
     std::vector<float> temp;
     for(int i=0; i < m_Neurons.size(); i++)
     {
         m_Neurons[i].GetWeights(temp);
         allWeights.insert( allWeights.end(), temp.begin(), temp.end() );
///        allWeights.insert(); to finish

     }
 }
 }
