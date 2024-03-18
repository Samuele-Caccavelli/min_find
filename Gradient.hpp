#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include <functional>
#include <cmath>
#include "Parameters.hpp"

bool check_step_length(const Vector & x1, const Vector & x2, const double & tol_step, const unsigned int dim);

bool check_residual(Function fun, const Vector & x1, const Vector & x2, const double & tol_res);

template<alpha_strategies strategy>
double update_rule(Function fun, Gradient dfun, const double & mu, const double & sigma, const double & alpha_0, const unsigned int & iter, const Vector & x, const unsigned int dim);

std::pair<Vector, unsigned int> gradient_method(const Parameters &p);



std::pair<Vector, unsigned int> gradient_method(const Parameters &p) {

    std::cout << "Ho iniziato il metodo del gradiente" << std::endl;
    
    // inizialization of x_new and x_old for the first iteration
    Vector x_old = p.init_cond;
    Vector x_new(p.dim);
    double alpha_k = p.alpha_0;
    unsigned int iter = 0;

    do {
        //! the update rule can work only with the template already defined
        double alpha_k = update_rule<alpha_strategies::Armijo>(p.fun, p.dfun, p.mu, p.sigma, p.alpha_0, iter, x_old, p.dim);

        for(size_t i=0; i<p.dim; ++i) {
            x_new[i] = x_old[i] - alpha_k * p.dfun[i](x_old);
        }

        std::swap(x_old, x_new);
        ++iter;

    } while ((!check_step_length(x_old, x_new, p.tol_step, p.dim)) && 
             (!check_residual(p.fun, x_old, x_new, p.tol_res)) && 
             (iter <= p.max_iter));

    //! print point in parameters non va
    // std::cout << "Minimum found in " << iter << " iterations in point: \n";
    // print_point(x_old);

    std::pair<Vector, unsigned int> result = std::pair(x_old, iter);

    return result; 
}

bool check_step_length(const Vector & x1, const Vector & x2, const double & tol_step, const unsigned int dim) {

    double norm = 0.0;
    double diff = 0.0;

    for(size_t i=0; i<dim; ++i) {
        diff = x2[i] - x1[i];
        norm += diff * diff;
    }

    norm = sqrt(norm);

    return (norm < tol_step);
}

bool check_residual(Function fun, const Vector & x1, const Vector & x2, const double & tol_res) {
    
    return (fabs(fun(x1) - fun(x2)) < tol_res);
}

template<alpha_strategies strategy>
double update_rule(Function fun, Gradient dfun, const double & mu, const double & sigma, const double & alpha_0,
                   const unsigned int & iter, const Vector & x, const unsigned int dim) {
    if constexpr(strategy == Exponential) {

        std::cout << "new alpha is: " << alpha_0 * exp( -mu * iter) << std::endl;

        return alpha_0 * exp( -mu * iter);
    }

    if constexpr(strategy == Inverse) {

        std::cout << "new alpha is: " << alpha_0 / (1 + mu * iter) << std::endl;

        return alpha_0 / (1 + mu * iter);
    }

    if constexpr(strategy == Armijo) {
        bool found = false;
        double alpha = alpha_0;

        while (!found)
        {
            //! non sono sicuro di come ho implementato questo while: lo runna sempre finchè non fa un return
            double lhs = 0.0;
            double rhs = 0.0;
            Vector lhs_argument(dim);

            for(size_t i=0; i<dim; ++i) {
                lhs_argument[i] = x[i] - alpha * dfun[i](x);
                rhs += dfun[i](x) * dfun[i](x);
            }

            rhs *= (sigma * alpha);
            lhs = fun(x) - fun(lhs_argument);

            if(lhs >= rhs) {
                return alpha;
            }

            alpha /= 2;
        }
    }    
}

#endif /* GRADIENT_H */