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

    //Output count
    std::cout << "Network initialized with " << this->node_count << " nodes and " << this->weight_count << " weights";
}

void NeuralNet::setWeights(std::vector<float> weights)
{
    int c = 0;

    for(int x=0; x<this->weights.size();x++)
    {
        for(int y=0; y<this->weights[x].size();y++)
        {
            for(int z=0; z<this->weights[x][y].size();z++)
            {
                this->weights[x][y][z] = weights[c];
                c++;
            }
        }
    }
}

std::vector<float> NeuralNet::process(std::vector<float> inputs)
{
    //Process each layer
}
