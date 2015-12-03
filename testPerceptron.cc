#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Implement the methods in the given class definition.

// Class interface OR definition (header file).
class Perceptron {
public:
  // Once implemented this **custom constructor will allocate the array (using new), and populate it with PRGNs from 0.0f to 1.0f.
  // This takes a parameter. (Here they are called parameters. A function call takes arguments.)
  Perceptron(int size = 10);
  
  // Once implemented this destructor will use delete [].
  ~Perceptron();
  
  // Once implemented this member function will print the array.
  void ShowYourself();
  
  // Supervised training (learning) algorithm.
  void TrainYourself(double xx[], double yy[], double dd[]);
  
  // Create a public wrapper for the private DotProduct that
  // communicates input defined in main to this private DotProduct method.
  // ref: Chapter 3***
  double PublicDotProduct(double [], double [], int);

private:
  // Private method that actually computes the dot product. This method is to
  // be invoked by its public wrapper, i.e. PublicDotProduct.
  double DotProduct(double *, double *, int);
  
  // https://en.wikipedia.org/wiki/Sigmoid_function
  // f
  double ActivationGate(double tt);
  
  int size_;        // Size of the array of weights.
  
  double *weights_; // Array holding the weights.
  
  double bias_;     // The bias shifts the decision boundary away from the origin and does not depend on any input value.
};

// Class implementation (source file).
// **Use same parameter name as our custom constructor?
Perceptron::Perceptron(int size) {
    // Allocate storage space for the array.
    size_ = size;
    weights_ = new double[size_]; // New must be assigned to something. Here it's allocating storage space for array weights_.
    
    // **Are we seeding?
    // Pseudo-Random Numbers in the interval from 0.0f to 1.0f.
    for (int ii = 0; ii < size_; ++ii) {
        weights_[ii] = ((double) rand())/((double) RAND_MAX);
    }
}

void Perceptron::ShowYourself() {
    // Print the array.
    for (int ii = 0; ii < size_; ++ii) {
      std::cout << weights_[ii] << " ";
    }
    std::cout << std::endl;
}

double Perceptron::ActivationGate(double tt) {
    
    return 1.0/(1.0 + exp(-tt));
}

void Perceptron::TrainYourself(double xx[], double yy[], double dd[]) {
    // I don't see how DotProduct and ActivationGate work together. xx?
    // Use the activation gate to compute:
    // https://upload.wikimedia.org/math/b/4/9/b498c043912384e5208e9f4427d2f815.png
    float formula_result = ActivationGate(DotProduct(weights_, xx, size_));
    
    std::cout << formula_result << std::endl;
}

// Compute the dot product.
double Perceptron::DotProduct(double *aa, double *bb, int size) {
    
    double result = 0;
    for (int ii = 0; ii < size; ++ii) {
        result += aa[ii]*bb[ii];
    }

    return result;
}
    // Public wrapper implementation.
double Perceptron::PublicDotProduct(double aa[], double bb[], int size) {
    
    return DotProduct(aa, bb, size);
}

Perceptron::~Perceptron() {
    
    delete [] weights_;
}

int main() {
    
    Perceptron nn;
    
    nn.ShowYourself();
    
    double *xx = new double[10];; // = {0, 0, 1, 0, 1, 0, 1, 0}
    double *yy = new double[10]; // = {1, 0, 1, 0, 1, 0, 1, 0}
    
    // Generate random 0's and 1's for array xx.
    for (int ii = 0; ii < 10; ++ii) {
        xx[ii] = ((int) rand() % 2 + 0);
    }
    // Generate random 0's and 1's for array yy.
    for (int ii = 0; ii < 10; ++ii) {
        yy[ii] = ((int) rand() % 2 + 0);
    }
    
    // Print xx.
    for (int ii = 0; ii < 10; ++ii) {
      std::cout << xx[ii] << " ";
    }
    std::cout << std::endl;
    
    // Print yy.
    for (int ii = 0; ii < 10; ++ii) {
      std::cout << yy[ii] << " ";
    }
    std::cout << std::endl;
    
    // Think about the notes. Think about learning the AND. How would you
    // initialize the dd array (desired output) to show the perceptron, what
    // to learn? That is, how would you code the truth table, and feed it to
    // the perceptron. ***Also, please refactor the class, so that it is called
    // "Perceptron".
    
    // For this HW follow: https://en.wikipedia.org/wiki/Perceptron#Example
    
    // See if you can update the weights... as in:
    // https://upload.wikimedia.org/math/a/0/4/a04f856c6b62711012dcbf0ac6c918b6.png
    
    // Truth table: AND. Comparing *xx and *yy? <--- What's input.
    // If I am comparing arrays xx and yy should I enclose this in a for loop?
    // A new member function of class Perceptron?
    
    // Logically combine xx and yy into dd via AND.
    double *dd = new double[10];
    for (int ii = 0; ii < 10; ++ii) {
        dd[ii] = ( xx[ii] && yy[ii] );
    }
    // Print dd.
    for (int ii = 0; ii < 10; ++ii) {
      std::cout << dd[ii] << " ";
    }
    
    std::cout << std::endl;
    
    nn.TrainYourself(xx, yy, dd);
    
    delete [] xx;
    delete [] dd;
    
    // https://www.youtube.com/watch?v=S3iQgcoQVbc
}
