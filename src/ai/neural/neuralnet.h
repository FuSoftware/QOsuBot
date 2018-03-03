#ifndef NEURALNET_H
#define NEURALNET_H

#include <iostream>
#include <vector>
#include <cmath>

template <class T>
using Array2D = std::vector<std::vector<T>>;

template <class T>
using Array3D = std::vector<Array2D<T>>;

#define BIAS_VALUE 1.0f

class NeuralNet
{
public:
    NeuralNet(std::vector<int> topology);
    void init(std::vector<int> topology);

    void setWeights(std::vector<float> weights);
    std::vector<float> getWeights();
    std::vector<float> process(std::vector<float> inputs);

    std::vector<float> getOutputs();

    static float transferFunction(float x);
    static float sigmoid(float x);
    static float relu(float x);

    static float transferFunctionh(float x);
    static float sigmoidh(float x);
    static float reluh(float x);

private:
    std::vector<int> topology;
    Array2D<float> nodes;
    Array3D<float> weights;

    Array2D<float> gradients;
    Array3D<float> delta_weights;

    int node_count = 0;
    int weight_count = 0;

    unsigned layer_count = 0;
    unsigned output_layer = 0;
};

#endif // NEURALNET_H
