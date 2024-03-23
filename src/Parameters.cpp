#include "Parameters.hpp"

//! something strange when using dim = 3
void print_point(const Vector &x) {
  for (auto component : x) {
    std::cout << component << "\t";
  }
  std::cout << "\n";
}

void print_params(const Parameters &p) {
  std::cout << "PARAMETER VALUES:" << "\n";
  std::cout << "dimensions = " << p.dim << "\n"
            << "function = " << p.myfun << "\n";
  // based on the dimensions of the problem, only the gradient with the correct dimension wil, be printed
  switch (p.dim)
  {
    case 1:
      std::cout << "grad[1] = " << p.mygrad1 << "\n";
      break;
        
    case 2:
      std::cout << "grad[1] = " << p.mygrad1 << "\n";
      std::cout << "grad[2] = " << p.mygrad2 << "\n";
      break;
    case 3:
      std::cout << "grad[1] = " << p.mygrad1 << "\n";
      std::cout << "grad[2] = " << p.mygrad2 << "\n";
      std::cout << "grad[3] = " << p.mygrad3 << "\n";
      break;
  }
  std::cout << "initial conditions = ";
  print_point(p.init_cond);
  std::cout << "tolerance for the step length = " << p.tol_step << "\n"
            << "tolerance for the residual = " << p.tol_res << "\n"
            << "strategy for alpha = ";
  // based on the strategy you are using, only the parameters utilized by that strategy are shown
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
    std::cerr << "The default values will be used\n\n";
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

  values.dim = jfile.value("dim", defaults.dim);
  values.myfun = jfile.value("myfun", defaults.myfun);
  values.mygrad1 = jfile.value("mygrad1", defaults.mygrad1);
  values.mygrad2 = jfile.value("mygrad2", defaults.mygrad2);
  values.mygrad3 = jfile.value("mygrad3", defaults.mygrad3);
  values.init_cond = jfile.value("init_cond", defaults.init_cond);
  values.tol_step = jfile.value("tol_step", defaults.tol_step);
  values.tol_res = jfile.value("tol_res", defaults.tol_res);
  values.sigma = jfile.value("sigma", defaults.sigma);
  values.mu = jfile.value("mu", defaults.mu);
  values.alpha_0 = jfile.value("alpha_0", defaults.alpha_0);
  values.max_iter = jfile.value("max_iter", defaults.max_iter);

  return values;
}