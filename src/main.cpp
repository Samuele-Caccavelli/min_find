#include "Gradient.hpp"

// utility function that prints the results of the method
void print_result(const std::pair<Vector, unsigned int> &result,
                  const unsigned int &max_iter, const unsigned int &dim) {
    // check that each component of the solution is not respectively NaN or
    // infinity
    for (auto component : result.first) {
        if ((component != component) || !std::isfinite(component)) {
            std::cout << "The results found by the algorithm are not ok"
                      << std::endl;
            return;
        }
    }

    // check if the method has stopped because it reached the maximum number of
    // iterations
    //! actually you are not completely sure that you exit the method because of
    //! iterations and not because of convergence at the last iteration
    if (result.second == max_iter) {
        std::cout
            << "The algorithm has ended due to reaching the max number of "
               "iterations\n"
            << "The value of the solution so far is:\n";
        print_point(result.first, dim);
        return;
    }

    std::cout << "Minimum found in " << result.second
              << " iterations in point:\n";
    print_point(result.first, dim);

    return;
}

int main(int argc, char **argv) {
    // since the code uses if constexpr for deciding which strategy to use, it
    // can't be defined at runtime
    constexpr alpha_strategies strategy = Armijo;

    Parameters params;

    if (argc == 1) {
        std::cout << "A name for the parameter file was not give, so the "
                     "default values will be used"
                  << std::endl;
    } else if (argc == 2) {
        // read parameters from file
        params = read_parameters(argv[1]);
    } else {
        std::cerr << "Too many argument were given" << std::endl;
    }

    // initialization of the functors that use muparserx
    mup_wrapper fun{params.myfun, params.dim};
    mup_wrapper grad1{params.mygrad[0], params.dim};
    mup_wrapper grad2{params.mygrad[1], params.dim};
    mup_wrapper grad3{params.mygrad[2], params.dim};

    // initialization of the function wrapper with the functors
    params.fun = fun;
    params.dfun.emplace_back(grad1);
    params.dfun.emplace_back(grad2);
    params.dfun.emplace_back(grad3);

    // the strategy defined here is copied inside the parameters since it is
    // useful for the print_params function
    params.strategy = strategy;

    print_params(params);

    // computation of the minimum
    std::pair<Vector, unsigned int> result = gradient_method<strategy>(params);

    print_result(result, params.max_iter, params.dim);
    return 0;
}