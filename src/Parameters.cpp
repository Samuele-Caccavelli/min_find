#include "Parameters.hpp"

void print_point(const Vector &x) {
  for (auto component : x) {
    std::cout << component << "\t";
  }
  std::cout << "\n";
}

void print_params(const Parameters &p) {
  std::cout << "PARAMETER VALUES:" << "\n";
  std::cout << "dimensions = " << p.dim << "\n"
            << "initial conditions = ";
  print_point(p.init_cond);
  std::cout << "tolerance for the step length = " << p.tol_step << "\n"
            << "tolerance for the residual = " << p.tol_res << "\n"
            << "strategy for alpha = ";
  switch (p.strategy) {
  case alpha_strategies::Exponential:
    std::cout << "Exponential\n"
              << "mu = " << p.mu << "\n";
    break;
  case alpha_strategies::Inverse:
    std::cout << "Inverse\n"
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

Parameters read_parameters(std::string const & filename) {

  Parameters defaults;

  std::ifstream check(filename);
  if(!check) {
    std::cerr << "The file: " << filename << " does not exist" << std::endl;
    std::cerr << "The default values will be used" << std::endl;
    check.close();
    return defaults;
  }
  else {
    check.close();
  }

  std::ifstream ifile(filename);
  json jfile;
  ifile >> jfile;
  Parameters values;

  // jfile.value("name_of_what_i_want_to_read", deafault_value)
  values.dim = jfile.value("dim", defaults.dim);
  values.init_cond = jfile.value("init_cond", defaults.init_cond);
  values.tol_step = jfile.value("tol_step", defaults.tol_step);
  values.tol_res = jfile.value("tol_res", defaults.tol_res);
  values.strategy = jfile.value("strategy", defaults.strategy);
  switch (values.strategy) {
  case alpha_strategies::Armijo:
    values.sigma = jfile.value("sigma", defaults.sigma);
    break;
  default:
    values.mu = jfile.value("mu", defaults.mu);
    break;
  }
  values.alpha_0 = jfile.value("alpha_0", defaults.alpha_0);
  values.max_iter = jfile.value("max_iter", defaults.max_iter);

  return values;
}