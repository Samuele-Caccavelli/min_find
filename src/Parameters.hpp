#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Fun_wrapper.hpp"

using json = nlohmann::json;



typedef std::function<double(const Vector &)> Function;
typedef std::vector<Function> Gradient;

enum alpha_strategies { Exponential = 0, Inverse = 1, Armijo = 2};

// everything is inizialized with a default value exept for the functions and the strategy, that are inizialized in the main
struct Parameters
{
    // dimensions of the domain
    unsigned int dim = 2;

    // string for the function
    std::string myfun = "x*y+4*x^4+y^2+3*x";

    // string for the partial derivatives
    std::string mygrad1 = "y+16*x^3+3";
    std::string mygrad2 = "x+2*y";
    std::string mygrad3 = "";

    // function f
    Function fun;

    // gradient of the function f
    Gradient dfun;

    // initial condition
    Vector init_cond{};

    // tolerance on the step length
    double tol_step = 1e-6;

    // tolerance on the residual
    double tol_res = 1e-6;

    // stretegy adopted for finding alpha
    alpha_strategies strategy;

    // mu (used for updating alpha when using exponential or inverse decay)
    double mu = 0.2;

    // sigma (used for updating alpha in Armijo rule)
    double sigma = 0.025;

    // initial value of alpha
    double alpha_0 = 0.5;

    // maximum number of iterations
    unsigned int max_iter = 1000;

    // default constructor that inizializes the initial condition
    Parameters() : init_cond(dim, 0.0) {}
};
// utility function for printing the coordinates of a point
void print_point(const Vector &x);

// utility function for preinting the parameters
void print_params(const Parameters &p);

// utility function for reading the parameters from file
Parameters read_parameters(std::string const & filename);

#endif /* PARAMETERS_H */