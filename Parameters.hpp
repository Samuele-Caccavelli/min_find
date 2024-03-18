#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>
#include <functional>
#include <iosfwd>
#include <iostream>

typedef std::vector<double> Vector;
typedef std::function<double(const Vector &)> Function;
typedef std::vector<Function> Gradient;

enum alpha_strategies { Exponential = 0, Inverse = 1, Armijo = 2};

struct Parameters
{
    // dimensions of the problem
    unsigned int dim = 2;

    // function f
    Function fun;

    //gradient of the function f
    Gradient dfun;

    // initial condition
    std::vector<double> init_cond{};

    // tolerance on the step lenght
    double tol_step = 1e-6;

    // tolerance on the residual
    double tol_res = 1e-6;

    // stretegy adopted for finding alpha
    const alpha_strategies strategy = Armijo;

    // mu (used for updating alpha when using exponential or inverse decay)
    double mu = 0.2;

    // sigma (used in Armijo rule)
    double sigma = 0.025;

    // initial value of alpha
    double alpha_0 = 0.5;

    // maximum number of iterations
    unsigned int max_iter = 1000;    
};
// Function to print the parameters
//! probabilmente anche questo non va
// std::ostream &operator<<(std::ostream &, const Parameters &);

//! non so perchè non va
// void print_point(const Vector & x);

#endif /* PARAMETERS_H */