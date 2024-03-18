#include "Parameters.hpp"

void print_point(const Vector &x) {
  for (auto component : x) {
    std::cout << component << "\t";
  }
  std::cout << "\n";
}

void print_params(const Parameters &p) {
  std::cout << "PARAMETER VALUES:"
            << "\n";
  std::cout << "dimensions = " << p.dim << "\n"
            << "initial conditions = ";
  print_point(p.init_cond);
  std::cout << "tolerance for the step length = " << p.tol_step << "\n"
            << "tolerance for the residual = " << p.tol_res << "\n"
            << "strategy for alpha = ";
  switch (p.strategy) {
  case alpha_strategies::Exponential:
    std::cout << "exponential\n"
              << "mu = " << p.mu << "\n";
    break;
  case alpha_strategies::Inverse:
    std::cout << "inverse\n"
              << "mu = " << p.mu << "\n";
    break;
  default:
    std::cout << "Armijo\n"
              << "sigma = " << p.sigma << "\n";
    break;
  }
  std::cout << "alpha_0 = " << p.alpha_0 << "\n"
            << "maximum iterations = " << p.max_iter << "\n\n";
}