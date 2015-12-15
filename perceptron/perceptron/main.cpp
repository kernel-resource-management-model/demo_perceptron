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
  /*  Neuron() {
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    
    Neuron(double thresholdValue) {
        input = 0;
        output = 0;
        this->thresholdValue = thresholdValue;
    }*/
    
    virtual double getInput();
    virtual double getOutput();
};

// Class Sensor Neuron
class Sensor: public Neuron {
public:
    Sensor() {
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    Sensor(double thresholdValue) {
        input = 0;
        output = 0;
        this->thresholdValue = thresholdValue;
    }
    void setInput(double input);
    void setOutput();
    void print(void) {
        setOutput();
        std::cout << "in " << input << " out " << output << " thr " << thresholdValue << endl;
    }
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
    void print(void) {
        double in = source.getInput();
        double out = source.getInput();
        std::cout << "w " << weight << " in " << in << " out " << out << endl;
    }
};



// Class Association Neuron
class Association: public Neuron {
protected:
    std::vector <Synapse> synapse;
    
public:
    Association() {
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    Association(double thresholdValue) {
        input = 0;
        output = 0;
        this->thresholdValue = thresholdValue;
    }
    void addSynapse(Synapse synapse);
    void setInput();
    void setOutput();
    void print(void) {
        setInput();
        setOutput();
        std::cout << "in " << input << " out " << output << " thr " << thresholdValue << endl;
        std::cout << "Synapses" << endl;
        for (std::vector<Synapse>::iterator it = synapse.begin() ; it != synapse.end(); ++it) {
            it->print();
        }
    }
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
    if (input - thresholdValue > 0) {
        output = input - thresholdValue;
    } else {
        output = 0;
    }
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

void Association::setOutput() { // activation
    if (input >= thresholdValue) {
        output = input;
    } else {
        output = 0;
    }
}

// Class Network

class Network {
public:
    Sensor *sensorLayer;
    Association *firstLayer;
    Association *secondLayer;
    Association *reactionLayer;
    int zCount;
    int fCount;
    int sCount;
    int rCount;
    
    Network() {
        zCount = 3;
        fCount = 3;
        sCount = 3;
        rCount = 3;
        
        sensorLayer = new Sensor[zCount];
        firstLayer = new Association[fCount];
        secondLayer = new Association[sCount];
        reactionLayer = new Association[rCount];
        
        sensorLayer[0] = Sensor(0.2);
        sensorLayer[1] = Sensor(0.3);
        sensorLayer[2] = Sensor(0.4);
        
        for (int i = 0; i < zCount; i++) {
            sensorLayer[i].setInput(i);
        }
        
        for (int i = 0; i < fCount; i++) {
            for (int j = 0; j < zCount; j++) {
                
                Synapse newSynapse = Synapse(i + j, sensorLayer[j]);
            
                firstLayer[i].addSynapse(newSynapse);
            }
        }
        
        for (int i = 0; i < sCount; i++) {
            for (int j = 0; j < fCount; j++) {
                Synapse newSynapse = Synapse(i + j, firstLayer[j]);
                
                secondLayer[i].addSynapse(newSynapse);
            }
        }
        
        for (int i = 0; i < sCount; i++) {
            for (int j = 0; j < fCount; j++) {
                Synapse newSynapse = Synapse(i + j, secondLayer[j]);
                
                reactionLayer[i].addSynapse(newSynapse);
            }
        }
        
      /*
        this->sensorLayer.insert(this->sensorLayer.end(), Sensor(0.2)); // disk
        this->sensorLayer.insert(this->sensorLayer.end(), Sensor(0.3)); // memory
        this->sensorLayer.insert(this->sensorLayer.end(), Sensor(0.4)); // cpu
        
        for (int i = 0; i < fCount; i++) {
            this->firstLayer.insert(this->firstLayer.end(), Association(0.2));
        }
        for (int i = 0; i < sCount; i++) {
            this->firstLayer.insert(this->firstLayer.end(), Association(0.2));
        }
        for (int i = 0; i < rCount; i++) {
            this->reactionLayer.insert(this->reactionLayer.end(), Sensor());
        }
        
        for (std::vector<Association>::iterator itf = firstLayer.begin() ; itf != firstLayer.end(); ++itf) {
            std::vector <Synapse> synapse;
            for (std::vector<Neuron>::iterator its = sensorLayer.begin() ; its != sensorLayer.end(); ++its) {
                synapse.insert(synapse.end(), Synapse(2, its));
            }
            Synapse newsynaps(0.2, sensorLayer.end());*/
        
    }
    
    void print() {
        for (int i = 0; i < zCount; i++) {
            std::cout << "Sensor " << i << endl;
            sensorLayer[i].print();
            std::cout << "Ass1 " << i << endl;
            firstLayer[i].print();
            std::cout << "Ass2 " << i << endl;
            sensorLayer[i].print();
            std::cout << "React " << i << endl;
            reactionLayer[i].print();
        }
    }
    
};

int main(int argc, const char * argv[]) {
    Network first = Network();
    
    first.print();
    std::cout << "Hello, World!\n";
    return 0;
}
