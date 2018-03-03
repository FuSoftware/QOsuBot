#include "neuralnet.h"

NeuralNet::NeuralNet(std::vector<int> topology)
{
    this->init(topology);
}

void NeuralNet::init(std::vector<int> topology)
{
    this->topology = topology;

    this->node_count = 0;
    this->weight_count = 0;

    //Nodes initialization
    this->nodes.clear();
    this->weights.clear();

    this->nodes.resize(topology.size());
    this->weights.resize(topology.size()-1);

    //Nodes
    for(unsigned int x=0;x<topology.size();x++)
    {
        //If we are on the input or output layer, we keep the same node number. Else, we add a biad node
        unsigned int n = (x==0 || x==topology.size()-1) ? topology[x] : topology[x]+1;
        this->nodes[x].resize(n);
        this->node_count += n;
    }

    //Weights
    for(unsigned int x=0;x<topology.size()-1;x++)
    {
        unsigned int n = topology[x];
        unsigned int nl = x == topology.size()-1 ? topology[x+1] : topology[x+1] -1 ;

        this->weights[x].resize(n);

        for(unsigned int y=0;y<n;y++)
        {
            this->weights[x][y].resize(nl);
            this->weight_count += nl;
        }
    }

    //Set the bias nodes
    for(unsigned int x=1;x<topology.size()-1;x++)
        this->nodes[x][topology[x]] = BIAS_VALUE;

    this->layer_count = topology.size();
    this->output_layer = this->layer_count-1;

    //Output count
    std::cout << "Network initialized with " << this->node_count << " nodes and " << this->weight_count << " weights";
}

void NeuralNet::setWeights(std::vector<float> weights)
{
    int c = 0;

    for(unsigned x=0; x<this->weights.size();x++)
    {
        for(unsigned y=0; y<this->weights[x].size();y++)
        {
            for(unsigned z=0; z<this->weights[x][y].size();z++)
            {
                this->weights[x][y][z] = weights[c];
                c++;
            }
        }
    }
}

std::vector<float> NeuralNet::getWeights()
{
    std::vector<float> w;

    for(unsigned x=0; x<this->weights.size();x++)
        for(unsigned y=0; y<this->weights[x].size();y++)
            for(unsigned z=0; z<this->weights[x][y].size();z++)
                w.push_back(this->weights[x][y][z]);

    return w;
}

std::vector<float> NeuralNet::process(std::vector<float> inputs)
{
    //Set the inputs
    for(unsigned i=0; i<inputs.size(); i++)
        this->nodes[0][i] = inputs[i];

    //Process each layer except the input one
    for(unsigned x=1; x<this->layer_count; x++)
    {
        //Current Layer Count : Number of nodes to calculate on the current layer
        unsigned clc = topology[x];

        //Current Layer Count : Number of nodes on the previous layer
        unsigned plc = x-1 == 0 ? topology[x-1] : topology[x-1] + 1;

        //For each node in the current layer
        for(unsigned y = 0; y < clc; y++)
        {
            float sum = 0.f;

            //For each node in the previous layer
            for(unsigned z = 0; z < plc; z++)
            {
                sum += nodes[x][z] * weights[x][z][y];
            }

            this->nodes[x][y] = sigmoid(sum);
        }
    }

    //Get the outputs
    return this->getOutputs();
}

float NeuralNet::transferFunction(float x)
{
    return sigmoid(x);
}

float NeuralNet::sigmoid(float x)
{
    return tanh(x);
}

float NeuralNet::relu(float x)
{
    return x <= 0 ? 0 : x;
}

float NeuralNet::transferFunctionh(float x)
{
    return sigmoidh(x);
}

float NeuralNet::sigmoidh(float x)
{
    return 1.f - x*x;
}

float NeuralNet::reluh(float x)
{
    return x <= 0 ? 0 : 1;
}

std::vector<float> NeuralNet::getOutputs()
{
    return this->nodes.back();
}
