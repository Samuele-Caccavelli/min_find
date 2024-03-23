#ifndef WRAPPER_H
#define WRAPPER_H

#include "../include/muparserx/mpParser.h"

using namespace mup;

typedef std::vector<double> Vector;

//! dim is a global variable

struct fun_wrapper {
    std::string myString;
    unsigned int dim;

    double operator()(const Vector & x) const {

        ParserX p(pckALL_NON_COMPLEX);

        Value xVal(0.0);
        Value yVal(0.0);
        Value zVal(0.0);

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