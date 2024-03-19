#include "Gradient.hpp"

std::pair<Vector, unsigned int> gradient_method(const Parameters &p) {

  // inizialization of x_new and x_old for the first iteration
  Vector x_old = p.init_cond;
  Vector x_new(p.dim);

  double alpha_k = p.alpha_0;
  unsigned int iter = 0;

  do {
    double alpha_k = update_rule(p.fun, p.dfun, p.mu, p.sigma, p.alpha_0, iter,
                                 x_old, p.dim, p.strategy);

    for (size_t i = 0; i < p.dim; ++i) {
      x_new[i] = x_old[i] - alpha_k * p.dfun[i](x_old);
    }

    std::swap(x_old, x_new);
    ++iter;

  } while ((!check_step_length(x_old, x_new, p.tol_step, p.dim)) &&
           (!check_residual(p.fun, x_old, x_new, p.tol_res)) &&
           (iter < p.max_iter));

  std::pair<Vector, unsigned int> result = std::pair(x_old, iter);

  return result;
}

bool check_step_length(const Vector &x1, const Vector &x2,
                       const double &tol_step, const unsigned int dim) {

  double norm = 0.0;
  double diff = 0.0;

  for (size_t i = 0; i < dim; ++i) {
    diff = x2[i] - x1[i];
    norm += diff * diff;
  }

  norm = sqrt(norm);

  return (norm < tol_step);
}

bool check_residual(Function fun, const Vector &x1, const Vector &x2,
                    const double &tol_res) {

  return (fabs(fun(x1) - fun(x2)) < tol_res);
}

double update_rule(Function fun, Gradient dfun, const double &mu,
                   const double &sigma, const double &alpha_0,
                   const unsigned int &iter, const Vector &x,
                   const unsigned int dim, alpha_strategies strategy) {

  if (strategy == Armijo) {
    bool found = false;
    double alpha = alpha_0;

    while (!found)
    {
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

  if (strategy == Exponential) {
    return alpha_0 * exp(-mu * iter);
  }

  // strategy == Inverse
  return alpha_0 / (1 + mu * iter);
}