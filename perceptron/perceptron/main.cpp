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
#define MEMORY 0
#define CPU 1
#define DISK 2
#define MEMORY_DIFF 0.1
#define CPU_DIFF 0.05
#define DISK_DIFF 0.2
#define LC 0.25
#define N 11
#define M 8
using namespace std;

enum TYPE {
    memory = 0,
    cpu,
    disk
};

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

typedef struct Data {
    double memory;
    double cpu;
    double disk;
} parameters;

typedef struct Sample {
    parameters in;
    parameters out;
} sample;

// Class Neuron
class Neuron {
protected:
    double input;
    double output;
    double thresholdValue;
    
public:
    double errorIn = 0;
    double errorOut = 0;
    int type;
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
    Sensor(int type) {
        this->type = type;
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    Sensor(int type, double thresholdValue) {
        this->type = type;
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
    Neuron *source;
    
public:
    Synapse(double weight, Neuron *source) {
        this->weight = weight;
        this->source = source;
    }
    
    void setWeight(double value);
    double getWeight();
    Neuron *getSource();
    void print(void) {
        double in = source->getInput();
        double out = source->getInput();
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
    Association(int type) {
        this->type = type;
        input = 0;
        output = 0;
        thresholdValue = 0;
    }
    Association(int type, double thresholdValue) {
        this->type = type;
        input = 0;
        output = 0;
        this->thresholdValue = thresholdValue;
    }
    void addSynapse(Synapse synapse);
    void setInput();
    void setOutput();
    void setError();
    void updateWeight();
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

Neuron *Synapse::getSource() {
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
    input = 0;
    for (std::vector<Synapse>::iterator it = synapse.begin() ; it != synapse.end(); ++it) {
        input += it->getSource()->getOutput()*it->getWeight();
    }
}

void Association::setOutput() { // activation
    if (input >= thresholdValue) {
        output = input;
    } else {
        output = 0;
    }
}

void Association::setError() {
    for (std::vector<Synapse>::iterator it = synapse.begin() ; it != synapse.end(); ++it) {
        it->getSource()->errorIn += this->errorOut*it->getWeight();
    }
}

void Association::updateWeight() {
    for (std::vector<Synapse>::iterator it = synapse.begin() ; it != synapse.end(); ++it) {
        //if (it->getSource()->type != this->type) {
            it->setWeight(it->getWeight() + LC*errorOut*it->getSource()->getOutput());
        //}
    }
}

// Class Network

class Network {
public:
    Sensor sensorLayer[3];
    Association firstLayer[3];
    //Association secondLayer[3];
    Association reactionLayer[3];
    int zCount;
    int fCount;
    int sCount;
    int rCount;
    
    Network() {
        zCount = 3;
        fCount = 3;
        sCount = 3;
        rCount = 3;
    
        //sensorLayer = new Sensor[zCount];
       // firstLayer = new Association[fCount];
       // secondLayer = new Association[sCount];
       // reactionLayer = new Association[rCount];
        
        sensorLayer[MEMORY] = Sensor(memory);
        sensorLayer[CPU] = Sensor(cpu);
        sensorLayer[DISK] = Sensor(disk);
       
        /*
        for (int i = 0; i < zCount; i++) {
            sensorLayer[i].setInput(i);
        }*/
        
        for (int i = 0; i < fCount; i++) {
            firstLayer[i] = Association(i);
           /* for (int j = 0; j < zCount; j++) {
                
                Synapse newSynapse = Synapse(fRand(-1, 1), &sensorLayer[j]);
            
                firstLayer[i].addSynapse(newSynapse);
            }*/
            Synapse newSynapse = Synapse(1, &sensorLayer[i]);
            
            firstLayer[i].addSynapse(newSynapse);
            
        }
        
        /*for (int i = 0; i < sCount; i++) {
            secondLayer[i] = Association();
            for (int j = 0; j < fCount; j++) {
                Synapse newSynapse = Synapse(fRand(-1, 1), &firstLayer[j]);
                
                secondLayer[i].addSynapse(newSynapse);
            }
        }*/
        
        for (int i = 0; i < rCount; i++) {
            reactionLayer[i] = Association(i);
            for (int j = 0; j < fCount; j++) {
               // Synapse newSynapse = Synapse(fRand(-1, 1), &secondLayer[j]);
                Synapse *newSynapse = NULL;
                if (i == j) {
                    newSynapse = new Synapse(1, &firstLayer[j]);
                } else if (j != CPU) {
                    newSynapse = new Synapse(fRand(-1, 1), &firstLayer[j]);
                }
                
                if (newSynapse != NULL) {
                    reactionLayer[i].addSynapse(*newSynapse);
                }
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
    
    parameters getReaction(parameters data) {
        parameters result;
        
        // set input
        sensorLayer[MEMORY].setInput(data.memory);
        sensorLayer[CPU].setInput(data.cpu);
        sensorLayer[DISK].setInput(data.disk);
        
        for (int i = 0; i < zCount; i++) {
            sensorLayer[i].setOutput();
        }
        
        for (int i = 0; i < fCount; i++) {
            firstLayer[i].setInput();
            firstLayer[i].setOutput();
        }
        
     /*   for (int i = 0; i < sCount; i++) {
            secondLayer[i].setInput();
            secondLayer[i].setOutput();
        }*/
        
        for (int i = 0; i < rCount; i++) {
            reactionLayer[i].setInput();
            reactionLayer[i].setOutput();
        }
        
        result.memory = reactionLayer[MEMORY].getOutput();
        result.cpu = reactionLayer[CPU].getOutput();
        result.disk = reactionLayer[DISK].getOutput();
        
        return result;
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
    
    bool check(parameters result, parameters out) {
        if ((abs(out.memory - result.memory) > MEMORY_DIFF)
            || (abs(out.cpu - result.cpu) > CPU_DIFF)
            || (abs(out.disk - result.disk) > DISK_DIFF)) {
            return false;
        }
        return true;
    }
    
    double error(double er, double o) {
        //return er*o*(1-o);
        return er;
    }
    
    bool learning(sample data) {
        parameters out = {0, 0, 0};
        
        out = getReaction(data.in);
        if (check(out, data.out) == true) {
            return true;
        } else {
            
            for (int i = 0; i < zCount; i++) {
                sensorLayer[i].errorIn = 0;
                sensorLayer[i].errorOut = 0;
            }
            for (int i = 0; i < fCount; i++) {
                firstLayer[i].errorIn = 0;
                firstLayer[i].errorOut = 0;
            }
           /* for (int i = 0; i < sCount; i++) {
                secondLayer[i].errorIn = 0;
                secondLayer[i].errorOut = 0;
            }*/
            for (int i = 0; i < rCount; i++) {
                reactionLayer[i].errorIn = 0;
                reactionLayer[i].errorOut = 0;
            }
            
            reactionLayer[MEMORY].errorIn = data.out.memory - out.memory;
            reactionLayer[CPU].errorIn = data.out.cpu - out.cpu;
            reactionLayer[DISK].errorIn = data.out.disk - out.disk;
            
            reactionLayer[MEMORY].errorOut = error(reactionLayer[MEMORY].errorIn, out.memory);
            reactionLayer[CPU].errorOut = error(reactionLayer[CPU].errorIn, out.cpu);
            reactionLayer[DISK].errorOut = error(reactionLayer[DISK].errorIn, out.disk);
            
            for (int j = 0; j < rCount; j++) {
                reactionLayer[j].setError();
                reactionLayer[j].updateWeight();
            }
            
          /*  for (int i = 0; i < sCount; i++) {
                secondLayer[i].errorOut = error(secondLayer[i].errorIn, secondLayer[i].getOutput());
                secondLayer[i].setError();
                secondLayer[i].updateWeight();
            }*/
            
          /*  for (int i = 0; i < fCount; i++) {
                firstLayer[i].errorOut = error(firstLayer[i].errorIn, firstLayer[i].getOutput());
                firstLayer[i].setError();
                firstLayer[i].updateWeight();
            }*/
        }
        
        return false;
    }
    
   
    
};

int main(int argc, const char * argv[]) {
    Network first = Network();
    parameters data;
    parameters result;
    FILE *input;
    int n;
    sample *mySamples;
    sample myControl[M];
    
    input = fopen("samples.txt", "r");
    fscanf(input, "%d\n", &n);
    mySamples = (sample *)malloc(n*sizeof(sample));
    for (int i = 0; i < n; i++) {
        fscanf(input, "{{%lf, %lf, %lf}, {%lf, %lf, %lf}}\n", &mySamples[i].in.memory, &mySamples[i].in.cpu, &mySamples[i].in.disk,
               &mySamples[i].out.memory, &mySamples[i].out.cpu, &mySamples[i].out.disk);
    }
    fclose(input);
    
   /* for (int i = 0; i < n; i++) {
        printf("{{%lf, %lf, %lf}, {%lf, %lf, %lf}}\n",mySamples[i].in.memory, mySamples[i].in.cpu, mySamples[i].in.disk,
               mySamples[i].out.memory, mySamples[i].out.cpu, mySamples[i].out.disk);
    }*/
    
    data.memory = 1;
    data.cpu = 0;
    data.disk = 0;
    
    result = first.getReaction(data);
    
    first.print();
    std::cout << "Result:" << endl << "memory: " << result.memory << endl << "cpu: " << result.cpu << endl << "disk: " << result.disk << endl;
    
  

    // samples
    
   /* mySamples[0] = {{0, 1, 0}, {0, 1, 0}};
    mySamples[1] = {{0.19, 0, 0}, {0.14, 0.07, 0}};
    mySamples[2] = {{0.38, 0, 0}, {0.28, 0.24, 0}};
    mySamples[3] = {{0.57, 0, 0}, {0.42, 0.20, 0}};
    mySamples[4] = {{0.66, 0, 0}, {0.49,  0.23, 0}};
    mySamples[5] = {{0.68, 0, 0}, {0.498, 0.20, 0}};
    mySamples[6] = {{0.69, 0, 0}, {0.51, 0.20, 0}};
    mySamples[7] = {{0, 0, 1}, {0, 0.2, 0.90}};
    mySamples[8] = {{1, 0, 0}, {0.58, 0.16, 0.99}};
    mySamples[9] = {{0.5, 0, 0}, {0.523, 0.993, 0}};
    mySamples[10] = {{0.75, 0, 0}, {0.57, 0.2, 0.99}};*/
    
    bool exit = false;
    
    while (exit == false) {
        exit = true;
        for (int i = 0; i < N; i++) {
          
            bool curr = first.learning(mySamples[i]);
            if (curr == false) {
                exit = false;
            }
            //first.print();
        }
    }
    
    myControl[0] = {{0, 1, 0}, {0, 1, 0}};
    myControl[1] = {{0.19, 0, 0}, {0.14, 0.07, 0}};
    myControl[2] = {{0.38, 0, 0}, {0.28, 0.24, 0}};
    myControl[3] = {{0.57, 0, 0}, {0.42, 0.20, 0}};
    myControl[4] = {{0.66, 0, 0}, {0.49,  0.23, 0}};
    myControl[5] = {{0.68, 0, 0}, {0.498, 0.20, 0}};
    myControl[6] = {{0.69, 0, 0}, {0.51, 0.20, 0}};
    myControl[7] = {{0, 0, 1}, {0, 0.2, 0.90}};

    
    first.print();
    for (int i = 0; i < M; i++) {
        std::cout << "Sample " << i << endl;
        result = first.getReaction(myControl[i].in);
        std::cout << "Result:" << endl << "memory: " << result.memory << endl << "cpu: " << result.cpu << endl << "disk: " << result.disk << endl;
    }
    
    return 0;
}
