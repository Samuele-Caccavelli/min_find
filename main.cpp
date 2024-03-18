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

void print_point(const Vector & x) {
  for(auto component : x) {
    std::cout << component << "\t";
  }
  std::cout << "\n";
}



int main(int argc, char **argv) {

    Parameters params;
    params.fun = fun;
    params.dfun.emplace_back(dfun1);
    params.dfun.emplace_back(dfun2);
    //! non mi piace questa condizione iniziale
    Vector init_cond(params.dim, 0);
    // print_point(init_cond);
    params.init_cond = init_cond;

    // std::cout << params;

    std::pair<Vector, unsigned int> result = gradient_method(params);

    std::cout << "Minimum found in " << result.second << " iterations in point: \n";
    print_point(result.first);

    return 0;
}