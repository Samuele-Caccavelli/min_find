#ifndef GRADIENT_HH
#define GRADIENT_HH

#include <vector>
#include <functional>
#include <cmath>
#include "Parameters.hpp"

bool check_step_length(const Vector & x1, const Vector & x2, const double & tol_step, const unsigned int dim);

bool check_residual(Function fun, const Vector & x1, const Vector & x2, const double & tol_res);

template<alpha_strategies strategy>
double update_rule(Function fun, Gradient dfun, const double & mu, const double & sigma, const double & alpha_0, const unsigned int & iter, const Vector & x, const unsigned int dim);

template <alpha_strategies strategy>
std::pair<Vector, unsigned int> gradient_method(const Parameters &p);

#endif /* GRADIENT_HH */