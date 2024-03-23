#ifndef GRADIENT_H
#define GRADIENT_H

#include <cmath>
#include <functional>
#include <vector>

#include "Parameters.hpp"

// check for the step length condition (return true if verified)
bool check_step_length(const Vector &x1, const Vector &x2,
                       const double &tol_step, const unsigned int dim);

// check for the residual condition (return true if verified)
bool check_residual(Function fun, const Vector &x1, const Vector &x2,
                    const double &tol_res);

// update rule for alpha
template <alpha_strategies strategy>
double update_rule(Function fun, Gradient dfun, const double &mu,
                   const double &sigma, const double &alpha_0,
                   const unsigned int &iter, const Vector &x,
                   const unsigned int dim) {
    // exponential case
    if constexpr (strategy == Exponential) {
        return alpha_0 * exp(-mu * iter);
    }
    // inverse case
    if constexpr (strategy == Inverse) {
        return alpha_0 / (1 + mu * iter);
    }
    // Armijo case
    if constexpr (strategy == Armijo) {
        double alpha = alpha_0;

        while (true) {
            // left hand side of the condition
            double lhs = 0.0;
            // right hand side of the condition
            double rhs = 0.0;
            // point where the function has to be evaluated in the left hand
            // side
            Vector lhs_argument(dim);

            // iteration for each component
            for (size_t i = 0; i < dim; ++i) {
                lhs_argument[i] = x[i] - alpha * dfun[i](x);
                rhs += dfun[i](x) * dfun[i](x);
            }

            rhs *= (sigma * alpha);
            lhs = fun(x) - fun(lhs_argument);

            if (lhs >= rhs) {
                break;
            }

            alpha /= 2;
        }

        return alpha;
    }
}

template <alpha_strategies strategy>
std::pair<Vector, unsigned int> gradient_method(const Parameters &p) {
    // initialization of x_new and x_old for the first iteration
    Vector x_old = p.init_cond;
    Vector x_new(p.dim);

    double alpha_k = p.alpha_0;
    // iterations of the method
    unsigned int iter = 0;

    do {
        // updating alpha_k
        double alpha_k = update_rule<strategy>(p.fun, p.dfun, p.mu, p.sigma,
                                               p.alpha_0, iter, x_old, p.dim);

        // gradient rule method applied to each component
        for (size_t i = 0; i < p.dim; ++i) {
            x_new[i] = x_old[i] - alpha_k * p.dfun[i](x_old);
        }

        // updating x_old for the next iteration
        std::swap(x_old, x_new);
        ++iter;

    } while ((!check_step_length(x_old, x_new, p.tol_step, p.dim)) &&
             (!check_residual(p.fun, x_old, x_new, p.tol_res)) &&
             (iter < p.max_iter));

    std::pair<Vector, unsigned int> result = std::pair(x_old, iter);

    return result;
}

#endif /* GRADIENT_H */