# GRADIENT METHOD

The code implement the gradient method to find (when possible) the argmin of a function with up to 3 variables (x, y, z).

**ATTENTION:** If more than this 3 variables are passed, the code throw a `mup::ParserError`.

The executable can be made by typing `make`.

In the Makefile there also are two utilities functions:
1. `clean`: remove all the object file.
2. `distclean`: remove all object file and executable file.

Without any argument, the executable run with the default values of the parameters.

Otherwise, other values for the parameters can be given with a json file.
In this case the filename has to be passed as a parameter in the terminal directly during the call.

In this case a successful call will look like: `./main nondefault.json`

Also if a wrong file name is given, the executable will run with the default parameters.

The default value of the default parameters are:
- dim: 2
- myfun: "x * y+4 * x^4+y^2+3 * x"
- mygrad: ["y+16 * x^3+3", "x+2 * y", ""]
- init_cond: [0.0, 0.0, 0.0]
- tol_step: 1e-6
- tol_res: 1e-6
- mu: 0.2
- sigma: 0.025
- alpha_0: 0.5
- max_iter: 1000

So by default the function implemented is: $x_1x_2+4x_1^4+x_2^2+3x_1$.

By just typing `./main` a working test case will be run.

**ATTENTION:** MuparserX need a __*__ sign to be put in between a coefficient and a variable, otherwise again a `mup::ParserError` will be thrown.

The strategy used for updating $\alpha_k$ is the *Armijo rule* and the choice of the strategy is defined in the main (in particular at line 39) and can't be changed inside the parameters. This is because to avoid check on which strategy to use on each iteration of the gradient method, the strategy has been implemented as a `constexpr`. Anyway, if the value of the variable `strategy` is changed, another choice can be made (in particular other then `Armijo`, also `Inverse` and `Exponential` are available), but the code needs to be compiled again.

About the included external library, while for *JSON for Modern C++* only one header file has been copied inside the include folder, for *muParserX* an installation was necessary.