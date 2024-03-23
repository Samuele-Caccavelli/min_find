#include "Gradient.hpp"

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
    fun_wrapper fun{params.myfun, params.dim};
    fun_wrapper grad1{params.mygrad1, params.dim};
    fun_wrapper grad2{params.mygrad2, params.dim};
    fun_wrapper grad3{params.mygrad3, params.dim};

    params.fun = fun;
    params.dfun.emplace_back(grad1);
    params.dfun.emplace_back(grad2);
    params.dfun.emplace_back(grad3);

    // the strategy defined here is copied inside the parameters since it is useful for the print
    params.strategy = strategy;

    print_params(params);

    // computetion of the minimum
    std::pair<Vector, unsigned int> result = gradient_method<strategy>(params);

    print_result(result, params.max_iter);

    return 0;
}