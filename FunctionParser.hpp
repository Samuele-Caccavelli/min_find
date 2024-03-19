#include "include/muparserx/parser/mpParser.h"

using namespace mup;

void tmp_function(void) {

    ParserX  p(pckALL_NON_COMPLEX);

    Value xVal(1.1);
    Value yVal(1.2);
    Value zVal(1.3);

    p.DefineVar("x",  Variable(&xVal));
    p.DefineVar("y",  Variable(&yVal));
    p.DefineVar("z",  Variable(&zVal));

    p.SetExpr("x+y+z");

    Value result = p.Eval();

    console() << result << "\n";
}
