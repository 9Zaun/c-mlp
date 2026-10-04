#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "mnist.h"

#define PI 3.14159265358979323846

struct neuron{
    double *weights;

    double weightCount;


    double z;
    double activation_curr;
    double bias;


    double error_signal;

    double *counterweights;



};


struct layer{
    struct neuron **neurons;
    double neuronCount;
};

struct network{
    struct layer **layer;
};


double z_comp(double weight, double activation_prev){ //since it requires to be called repeatedly, bias is added separately in function call
    return ((weight*activation_prev));
}

double ReLU(double z){
    if(z<=0) return 0;
    else return z;
}

double ReLUdash(double z){
    if(z>0){
        return 1;
    } else return 0;
}

double random_gaussian(){
    double u1 = 0, u2 = 0;

    while(u1 == 0){
        u1 = rand() / (RAND_MAX + 1.0);
    }
    while(u2 == 0){
        u2 = rand() / (RAND_MAX + 1.0);
    }

    return (sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2));
}

int main(void){
srand(time(NULL));
load_mnist();

    struct layer inputLayer;
    struct layer l1;
    struct layer l2;
    struct layer l3;

    

    int inputCount = 3;
    double *input;

    



    /*
    struct neuron n1 = {0};
    n1.weightCount = 3;
    n1.weights = malloc(n1.weightCount * sizeof(double));
    n1.counterweights = malloc(n1.weightCount * sizeof(double));
    struct neuron n2 = {0};
    n2.weightCount = 3;
    n2.weights = malloc(n2.weightCount * sizeof(double));
    n2.counterweights = malloc(n2.weightCount * sizeof(double));

    struct neuron n3 = {0};
    n3.weightCount = 2;
    n3.weights = malloc(n3.weightCount * sizeof(double));
    n3.counterweights = malloc(n3.weightCount * sizeof(double));
    struct neuron n4 = {0};
    n4.weightCount = 2;
    n4.weights = malloc(n4.weightCount * sizeof(double));
    n4.counterweights = malloc(n4.weightCount * sizeof(double));
    struct neuron n5 = {0};
    n5.weightCount = 2;
    n5.weights = malloc(n5.weightCount * sizeof(double));
    n5.counterweights = malloc(n5.weightCount * sizeof(double));

    struct neuron n6 = {0};
    n6.weightCount = 3;
    n6.weights = malloc(n6.weightCount * sizeof(double));
    n6.counterweights = malloc(n6.weightCount * sizeof(double));
    struct neuron n7 = {0};
    n7.weightCount = 3;
    n7.weights = malloc(n7.weightCount * sizeof(double));
    n7.counterweights = malloc(n7.weightCount * sizeof(double));
    */


    struct neuron *l1_neurons = calloc(512, sizeof(struct neuron));
    for(int i = 0; i < 512; i++){
        l1_neurons[i].weightCount = 784;
        l1_neurons[i].weights = malloc(784 * sizeof(double));
        l1_neurons[i].counterweights = malloc(784 * sizeof(double));
    }
    struct neuron *l2_neurons = calloc(256, sizeof(struct neuron));
    for(int i = 0; i < 256; i++){
        l2_neurons[i].weightCount = 512;
        l2_neurons[i].weights = malloc(512 * sizeof(double));
        l2_neurons[i].counterweights = malloc(512 * sizeof(double));
    }
    struct neuron *l3_neurons = calloc(10, sizeof(struct neuron));
    for(int i = 0; i < 10; i++){
        l3_neurons[i].weightCount = 256;
        l3_neurons[i].weights = malloc(256 * sizeof(double));
        l3_neurons[i].counterweights = malloc(256 * sizeof(double));
    }


    inputLayer.neuronCount = 784;
    l1.neuronCount = 512;
    l2.neuronCount = 256;
    l3.neuronCount = 10;

    inputLayer.neurons = NULL;
    l1.neurons = malloc(l1.neuronCount * sizeof(struct neuron *));
    l2.neurons = malloc(l2.neuronCount * sizeof(struct neuron *));
    l3.neurons = malloc(l3.neuronCount * sizeof(struct neuron *));

    for(int i = 0; i < 512; i++){
        l1.neurons[i] = &l1_neurons[i];
    }
    for(int i = 0; i < 256; i++){
        l2.neurons[i] = &l2_neurons[i];
    }
    for(int i = 0; i < 10; i++){
        l3.neurons[i] = &l3_neurons[i];
    }

    struct network net;



    net.layer = malloc(3*(sizeof(struct layer *)));
    net.layer[0] = &l1;
    net.layer[1] = &l2;
    net.layer[2] = &l3;

    





    for(int k = 0; k < 3; k++){
        for(int i = 0; i < net.layer[k]->neuronCount; i++){
            for(int j = 0; j < net.layer[k]->neurons[i]->weightCount; j++){
                net.layer[k]->neurons[i]->weights[j] = random_gaussian() * sqrt(2.0/net.layer[k]->neurons[i]->weightCount);
            }
            net.layer[k]->neurons[i]->bias = 0;
        }
        
    }

    /*
    n1.weights[0] = 1;
    n1.weights[1] = 2;
    n1.weights[2] = 3;
    n1.bias = -1;
    l1.neurons[0] = &n1;
    n2.weights[0] = 1.5;
    n2.weights[1] = 2.5;
    n2.weights[2] = 3.5;
    n2.bias = -2;
    l1.neurons[1] = &n2;
    
    n3.weights[0] = 1;
    n3.weights[1] = 2;
    n3.bias = -3;
    l2.neurons[0] = &n3;
    n4.weights[0] = 2;
    n4.weights[1] = 3;
    n4.bias = -2;
    l2.neurons[1] = &n4;
    n5.weights[0] = 3;
    n5.weights[1] = 4;
    n5.bias = -1;
    l2.neurons[2] = &n5;
    

    n6.weights[0] = 3;
    n6.weights[1] = 2;
    n6.weights[2] = 1;
    n6.bias = -2;   
    l3.neurons[0] = &n6;
    n7.weights[0] = 3;
    n7.weights[1] = 3;
    n7.weights[2] = 3;
    n7.bias = 0;
    l3.neurons[1] = &n7;

    */
    
    double *correction;
    int correctionCount = 10;
    correction = malloc(correctionCount*sizeof(double));


    int number_of_hidden_layers = 3;

    printf("Weight[0] = %f, Weight[1] = %f, Weight[2] = %f\n", 
       net.layer[0]->neurons[0]->weights[0],
       net.layer[0]->neurons[0]->weights[1],
       net.layer[0]->neurons[0]->weights[2]);

// forward, backward cycle
for(int epoch = 0; epoch < 5; epoch++){
    for(int g = 0; g<1000; g++){

        // forward pass

        // load inputs
        input = train_image[g];
        for(int i = 0; i < net.layer[0]->neuronCount; i++){
            net.layer[0]->neurons[i]->z = 0;
            for(int j = 0; j < inputLayer.neuronCount; j++){
                net.layer[0]->neurons[i]->z += z_comp(net.layer[0]->neurons[i]->weights[j],input[j]);

            }
            net.layer[0]->neurons[i]->z += net.layer[0]->neurons[i]->bias;
            net.layer[0]->neurons[i]->activation_curr = ReLU(net.layer[0]->neurons[i]->z);
            
        }

        

        
        for(int k = 1; k < number_of_hidden_layers; k++){
        // if NOT in final layer; otherwise, you need to run separate loops
            if(k!=number_of_hidden_layers-1){
                for(int i = 0; i < net.layer[k]->neuronCount; i++){
                    net.layer[k]->neurons[i]->z = 0;
                    for(int j = 0; j < net.layer[k-1]->neuronCount; j++){
                        net.layer[k]->neurons[i]->z += z_comp(net.layer[k]->neurons[i]->weights[j], net.layer[k-1]->neurons[j]->activation_curr);
                    }
                    net.layer[k]->neurons[i]->z += net.layer[k]->neurons[i]->bias;
                    net.layer[k]->neurons[i]->activation_curr = ReLU(net.layer[k]->neurons[i]->z);
                    
                }
            } else {
                for(int i = 0; i < net.layer[k]->neuronCount; i++){
                    net.layer[k]->neurons[i]->z = 0;
                    for(int j = 0; j < net.layer[k-1]->neuronCount; j++){
                        net.layer[k]->neurons[i]->z += z_comp(net.layer[k]->neurons[i]->weights[j], net.layer[k-1]->neurons[j]->activation_curr);
                    }
                    net.layer[k]->neurons[i]->z += net.layer[k]->neurons[i]->bias;
                }

                double max_z = net.layer[k]->neurons[0]->z;

                for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
                    if(net.layer[number_of_hidden_layers-1]->neurons[i]->z > max_z){
                        max_z = net.layer[number_of_hidden_layers-1]->neurons[i]->z;
                    }
                }

                double denominator = 0;

                for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
                    denominator += (exp(net.layer[number_of_hidden_layers-1]->neurons[i]->z - max_z));
                }

                for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
                    double pi = exp(net.layer[number_of_hidden_layers-1]->neurons[i]->z - max_z) / denominator;
                    net.layer[number_of_hidden_layers-1]->neurons[i]->activation_curr = pi;
                }

            }
        }

        /*
        for(int k = 0; k <number_of_hidden_layers; k++){
            for(int i = 0; i < net.layer[k]->neuronCount; i++){
                printf(" %f ", net.layer[k]->neurons[i]->activation_curr);
            }
            printf("\n");
        }
        */

        // backward pass

        
        // load correction (yi)
        for(int c = 0; c < 10; c++){
            correction[c] = (train_label[g] == c ? 1.0 : 0.0);
        }


        double learning_rate = 0.001;

        

        // to obtain error signal, take error signal of every next layer neuron, multiply with corresponding weight and add to running sum
        // unless you're the final layer- then its just the difference
        // once error signal obtained, multiply into ReLU derivative and da/dw for every single weight in array
        // store result in counterweight array

        for(int k = 0; k < number_of_hidden_layers; k++){
            if(k == 0){ // if final layer

                for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
                    net.layer[number_of_hidden_layers-1]->neurons[i]->error_signal = net.layer[number_of_hidden_layers-1]->neurons[i]->activation_curr - correction[i];
                }

                for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
                    for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                        net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j] = net.layer[number_of_hidden_layers-1-k]->neurons[i]->error_signal * (net.layer[number_of_hidden_layers-2-k]->neurons[j]->activation_curr * ReLUdash(net.layer[number_of_hidden_layers-1-k]->neurons[i]->activation_curr));
                    }

                    for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    net.layer[number_of_hidden_layers-1-k]->neurons[i]->weights[j] -= (learning_rate * net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j]);
                }

                


                /*
                printf("\n K count: %d\n",k);
                printf("i count: %d\n",i);
                printf("-------------------\nCounter weights: \n");
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    printf(" %f ", net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j]);
                } printf("\n\nModified weights: \n");
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    printf(" %f ", net.layer[number_of_hidden_layers-1-k]->neurons[i]->weights[j]);
                } printf("\n\n");
                */

                    

                }

                
                continue;
                
            }
            for(int i = 0; i < net.layer[number_of_hidden_layers-1-k]->neuronCount; i++){
                if(k == 0){ // if final layer, calc error signal directly
                    // loop through all neurons in final layer to 1) find maximum z out of all neurons,
                    // 2) (in a second loop) calculate a running sum of the denominator (you need to add to the running total the exponent)
                    // dont forget to reset the denominator sum after calculating pi
                    // 3) in a third loop, calculate pi for each neuron and pi - yi, store that as the first error signal
                    
                    // net.layer[number_of_hidden_layers-1]->neurons[i]->error_signal = net.layer[number_of_hidden_layers-1]->neurons[i]->activation_curr - correction[i];
                } else { // else use the future layer sum
                    net.layer[number_of_hidden_layers-1-k]->neurons[i]->error_signal = 0;
                    for(int x = 0; x < net.layer[number_of_hidden_layers-k]->neuronCount; x++){
                        net.layer[number_of_hidden_layers-1-k]->neurons[i]->error_signal += (net.layer[number_of_hidden_layers-k]->neurons[x]->weights[i] * net.layer[number_of_hidden_layers-k]->neurons[x]->error_signal);
                    }

                }
                if(k != number_of_hidden_layers-1){ // if we're not at the first layer yet
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j] = net.layer[number_of_hidden_layers-1-k]->neurons[i]->error_signal * (net.layer[number_of_hidden_layers-2-k]->neurons[j]->activation_curr * ReLUdash(net.layer[number_of_hidden_layers-1-k]->neurons[i]->activation_curr));
                }
                } else { // if we are at the first layer, we need to address the input array directly
                    for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j] = net.layer[number_of_hidden_layers-1-k]->neurons[i]->error_signal * (input[j] * ReLUdash(net.layer[number_of_hidden_layers-1-k]->neurons[i]->activation_curr));
                }
                }
                
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    net.layer[number_of_hidden_layers-1-k]->neurons[i]->weights[j] -= (learning_rate * net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j]);
                }
                /*
                printf("\n K count: %d\n",k);
                printf("i count: %d\n",i);
                printf("-------------------\nCounter weights: \n");
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    printf(" %f ", net.layer[number_of_hidden_layers-1-k]->neurons[i]->counterweights[j]);
                } printf("\n\nModified weights: \n");
                for(int j = 0; j < net.layer[number_of_hidden_layers-1-k]->neurons[i]->weightCount; j++){
                    printf(" %f ", net.layer[number_of_hidden_layers-1-k]->neurons[i]->weights[j]);
                } printf("\n\n");
                */
            }
        }
        if(g%200==199){
            int predicted = 0;
            double max_prob = net.layer[2]->neurons[0]->activation_curr;
            for(int i = 1; i < 10; i++){
                if(net.layer[2]->neurons[i]->activation_curr > max_prob){
                    max_prob = net.layer[2]->neurons[i]->activation_curr;
                    predicted = i;
                }
            }

            printf("True label: %d, Predicted: %d, Confidence: %f\n", train_label[g],predicted,max_prob);
        }

    }


}

    



    // final forward pass evaluation + printing
    int k = 2;
    for(int i = 0; i < net.layer[k]->neuronCount; i++){
        net.layer[k]->neurons[i]->z = 0;
        for(int j = 0; j < net.layer[k-1]->neuronCount; j++){
            net.layer[k]->neurons[i]->z += z_comp(net.layer[k]->neurons[i]->weights[j], net.layer[k-1]->neurons[j]->activation_curr);
        }
        net.layer[k]->neurons[i]->z += net.layer[k]->neurons[i]->bias;
    }

    double max_z = net.layer[k]->neurons[0]->z;

    for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
        if(net.layer[number_of_hidden_layers-1]->neurons[i]->z > max_z){
            max_z = net.layer[number_of_hidden_layers-1]->neurons[i]->z;
        }
    }

    double denominator = 0;

    for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
        denominator += (exp(net.layer[number_of_hidden_layers-1]->neurons[i]->z - max_z));
    }

    for(int i = 0; i < net.layer[number_of_hidden_layers-1]->neuronCount; i++){
        double pi = exp(net.layer[number_of_hidden_layers-1]->neurons[i]->z - max_z) / denominator;
        net.layer[number_of_hidden_layers-1]->neurons[i]->activation_curr = pi;
    }

    /*
    for(int k = 0; k <number_of_hidden_layers; k++){
        for(int i = 0; i < net.layer[k]->neuronCount; i++){
            printf(" %f ", net.layer[k]->neurons[i]->activation_curr);
        }
        printf("\n");
    }
    */
   printf("\n");
   for(int i = 0; i < net.layer[2]->neuronCount; i++){
            printf(" %f ", net.layer[2]->neurons[i]->activation_curr);
        }
    printf("\n");

    






    





     





    










}