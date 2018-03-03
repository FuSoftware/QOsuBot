#ifndef NEURALNET_H
#define NEURALNET_H

#include <iostream>
#include <vector>

template <class T>
using Array2D = std::vector<std::vector<T>>;

template <class T>
using Array3D = std::vector<Array2D<T>>;

class NeuralNet
{
public:
    NeuralNet(std::vector<int> topology);
    void init(std::vector<int> topology);

    void setWeights(std::vector<float> weights);
    std::vector<float> process(std::vector<float> inputs);

private:
    std::vector<int> topology;
    Array2D<float> nodes;
    Array3D<float> weights;

    int node_count = 0;
    int weight_count = 0;
};

#endif // NEURALNET_H
