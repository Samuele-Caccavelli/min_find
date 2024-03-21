#include "Gradient.hpp"

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