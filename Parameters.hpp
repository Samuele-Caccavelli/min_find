#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>
#include <functional>
#include <iosfwd>

typedef std::vector<double> Vector;

enum alpha_strategies { Exponential = 0, Inverse = 1, Armijo = 2};

struct Parameters
{
    // function f
    std::function<double(const Vector &)> fun;

    //gradient of the function f
    std::function<double(const Vector &)> dfun;

    // initial condition
    Vector init_cond;

    // tolerance on the step lenght
    double tol_step = 1e-6;

    // tolerance on the residual
    double tol_res = 1e-6;

    // stretegy adopted for finding alpha
    alpha_strategies strategy = Armijo;

    // mu (used for updating alpha when using exponential or inverse decay)
    double mu = 0.2;

    // sigma (used in Armijo rule)
    double sigma = 0.25;

    // initial value of alpha
    double alpha_0;

    // maximum number of iterations
    unsigned max_iter;    
};
// Function to print the parameters
std::ostream &operator<<(std::ostream &, const Parameters &);

#endif /* PARAMETERS_H */