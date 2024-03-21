# min_find

The code implement the gredient method to find the minimum of a function.

The executable can be me by typing
`make`.

In the Makefile there also are two utiliteis functions:
1. `clean`: remove all the object file.
2. `distclean`: remove all object file and executable file.

To function the code requires the call of the executable with a file name given as a parameter, otherwise an error will be given.

A succesful call will look like: `./main nondefault.json`

If instead a wrong file name will be given, the executable will run anyway with the default parameters.

The default value of the default parameters are:
- dim: 2
- init_cond: [0.0, 0.0]
- tol_step: 1e-6
- tol_res: 1e-6
- mu: 0.2
- sigma: 0.025
- alpha_0: 0.5
- max_iter: 1000

The function to be minimized and its gradient are instead implemented in the main.

In particular the function implemented is: $x_1x_2+4x_1^4+x_2^2+3x_1$.

Also the strategy to be used for updating $\alpha_k$ is defined in the main and can't be changed inside the parameters. This is because to avoid check on which strategy to use on each iteration, the strategy as to be implemented as a `constexpr`