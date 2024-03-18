#include "Gradient.hpp"

double fun(const Vector & x) {
    // std::cout << "Sto chiamando fun" << std::endl;
    // std::cout << "Value of x[1]: " << x[0] << " Value of x[2]: " << x[1] << std::endl;
    return x[0] * x[1] + 4 * x[0] * x[0] * x[0] * x[0] + x[1] * x[1] + 3 * x[0];
}

double dfun1(const Vector & x) {
    return x[1] + 16 * x[0] * x[0] * x[0] + 3;
}

double dfun2(const Vector & x) {
    return x[0] + 2* x[1];
}

void print_result(const std::pair<Vector, unsigned int> &result,
                  const unsigned int &max_iter) {
  for (auto component : result.first) {
    if ((component != component) || !std::isfinite(component)) {
      std::cout << "The results found by the alghoritm are not ok" << std::endl;
      return;
    }
  }

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

    Parameters params;
    params.fun = fun;
    params.dfun.emplace_back(dfun1);
    params.dfun.emplace_back(dfun2);
    //! non mi piace questa condizione iniziale
    Vector init_cond(params.dim, 0);
    params.init_cond = init_cond;

    print_params(params);
    std::pair<Vector, unsigned int> result =
        gradient_method<alpha_strategies::Armijo>(params);

    print_result(result, params.max_iter);

    return 0;
}