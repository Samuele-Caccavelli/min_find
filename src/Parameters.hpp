#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <fstream>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <vector>

#include "Mup_wrapper.hpp"
#include "json.hpp"

using json = nlohmann::json;

typedef std::function<double(const Vector &)> Function;
typedef std::vector<Function> Gradient;

enum alpha_strategies { Exponential = 0, Inverse = 1, Armijo = 2 };

// everything is initialized with a default value except for the the strategy,
// that is initialized in the main
struct Parameters {
    // dimensions of the domain
    unsigned int dim = 2;

    // string for the function
    std::string myfun = "x*y+4*x^4+y^2+3*x";

    // vector where each string is a partial derivative
    std::vector<std::string> mygrad{"y+16*x^3+3", "x+2*y", ""};

    // wrapper for the function
    Function fun;

    // wrapper for the gradient
    Gradient dfun;

    // initial condition
    Vector init_cond{0.0, 0.0, 0.0};

    // tolerance on the step length
    double tol_step = 1e-6;

    // tolerance on the residual
    double tol_res = 1e-6;

    // strategy adopted for finding alpha
    alpha_strategies strategy;

    // mu (used for updating alpha when using exponential or inverse decay)
    double mu = 0.2;

    // sigma (used for updating alpha in Armijo rule)
    double sigma = 0.025;

    // initial value of alpha
    double alpha_0 = 0.5;

    // maximum number of iterations
    unsigned int max_iter = 1000;
};

// utility function for printing the coordinates of a point
void print_point(const Vector &x, const unsigned int &dim);

// utility function for printing the parameters
void print_params(const Parameters &p);

// utility function for reading the parameters from file
Parameters read_parameters(std::string const &filename);

#endif /* PARAMETERS_H */