//
//  main.cpp
//  perceptron
//
//  Created by Stasia on 14.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Class Neuron
class Neuron {
protected:
    double input;
    double output;
    double thresholdValue;
    
public:
    Neuron() {
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    
    Neuron(double thresholdValue) {
        input = 0;
        output = 0;
        this->thresholdValue = thresholdValue;
    }
    
    double getInput();
    double getOutput();
};

// Class Synapse
class Synapse {
protected:
    double weight;
    Neuron source;
    
public:
    Synapse(double weight, Neuron source) {
        this->weight = weight;
        this->source = source;
    }
    
    void setWeight(double value);
    double getWeight();
    Neuron getSource();
};

// Class Sensor Neuron
class Sensor: public Neuron {
public:
    void setInput(double input);
    void setOutput();
};

// Class Association Neuron
class Association: public Neuron {
protected:
    std::vector <Synapse> synapse;
    
public:
    void addSynapse(Synapse synapse);
    void setInput();
    void setOutput();
};


// Functions for class Neuron
double Neuron::getInput() {
    return input;
}

double Neuron::getOutput() {
    return output;
}

// Functions for class Synapse
void Synapse::setWeight(double weight) {
    this->weight = weight;
}

double Synapse::getWeight() {
    return weight;
}

Neuron Synapse::getSource() {
    return source;
}

// Functions for class Sensor
void Sensor::setInput(double input) {
    this->input = input;
}

void Sensor::setOutput() {
    output = input - thresholdValue;
}

// Functions for class Association
void Association::addSynapse(Synapse synapse) {
    this->synapse.insert(this->synapse.end(), synapse);
}

void Association::setInput() {
    for (std::vector<Synapse>::iterator it = synapse.begin() ; it != synapse.end(); ++it) {
        input += it->getSource().getInput()*it->getWeight();
    }
}

void Association::setOutput() {
    output = 1/(1+exp(-input + thresholdValue));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
