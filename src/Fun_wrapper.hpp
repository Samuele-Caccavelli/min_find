#ifndef WRAPPER_H
#define WRAPPER_H

#include "../include/muparserx/mpParser.h"

using namespace mup;

typedef std::vector<double> Vector;

struct mup_wrapper {
    // string to hold the function
    std::string myString;
    // dimension of the domain
    unsigned int dim;

    // operator() to make seamless the call of a regualr c++ function or of this functor
    double operator()(const Vector & x) const {

        ParserX p(pckALL_NON_COMPLEX);

        Value xVal(0.0);
        Value yVal(0.0);
        Value zVal(0.0);

        // needed to avoid segmentation faults since the vector x has the dimensions of the domain
        switch (dim)
        {
        case 1:
            xVal = x[0];

            p.DefineVar("x",  Variable(&xVal));
            break;        
        case 2:
            xVal = x[0];
            yVal = x[1];

            p.DefineVar("x",  Variable(&xVal));
            p.DefineVar("y",  Variable(&yVal));
            break;
        case 3:
            xVal = x[0];
            yVal = x[1];
            zVal = x[2];

            p.DefineVar("x",  Variable(&xVal));
            p.DefineVar("y",  Variable(&yVal));
            p.DefineVar("z",  Variable(&zVal));
            break;
        }

        p.SetExpr(myString);

        Value result = p.Eval();
        double result_d = result;
        return result_d;
    }
};

#endif /* WRAPPER_H */