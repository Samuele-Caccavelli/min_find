#include "Gradient.hpp"

// function for which we need to find the minimum
double fun(const Vector & x) {
    return x[0] * x[1] + 4 * x[0] * x[0] * x[0] * x[0] + x[1] * x[1] + 3 * x[0];
}

// partial derivative w.r.t. the first component
double dfun1(const Vector & x) {
    return x[1] + 16 * x[0] * x[0] * x[0] + 3;
}

// partial derivative w.r.t. the second component
double dfun2(const Vector & x) {
    return x[0] + 2* x[1];
}

// utility function that prints the results of the method
void print_result(const std::pair<Vector, unsigned int> &result,
                  const unsigned int &max_iter) {
  // check that each component of the solution is not respectivly NaN or infinity
  for (auto component : result.first) {
    if ((component != component) || !std::isfinite(component)) {
      std::cout << "The results found by the alghoritm are not ok" << std::endl;
      return;
    }
  }

  // check if the method has stopped because it reached the maximum number of iterations
  //! actually you are not compleatly sure that you exit the method beacuse of iterations and not because of convergence at the last iteration
  if (result.second == max_iter) {
    std::cout << "The alghoritm has ended due to reaching the max number of "
                 "iterations\n"
              << "The value of the solution so far is:\n";
    print_point(result.first);
    return;
  }

  std::cout << "Minimum found in " << result.second
            << " iterations in point:\n";
  print_point(result.first);

  return;
}

int main(int argc, char **argv) {

    if(argc == 1) {
        std::cerr << "A name for the paramter file is needed, but none was given" << std::endl;
        return 1;
    }

    // since the code uses if constexpr for deciding which strategy to use, it can't be defined at runtime
    constexpr alpha_strategies strategy = Armijo;
    
    // read parameters from file
    Parameters params = read_parameters(argv[1]);

    // inizialization of the functions needed
    params.fun = fun;
    params.dfun.emplace_back(dfun1);
    params.dfun.emplace_back(dfun2);

    // the strategy defined here is copied inside the parameters since it is useful for the print
    params.strategy = strategy;

    print_params(params);

    // computetion of the minimum
    std::pair<Vector, unsigned int> result = gradient_method<strategy>(params);

    print_result(result, params.max_iter);

    return 0;
}