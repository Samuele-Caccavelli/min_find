#include "include/muparserx/parser/mpParser.h"

using namespace mup;

int main() {
    // ParserX  p(pckALL_NON_COMPLEX);

    // Value xVal(1.1);
    // Value yVal(1.2);
    // Value zVal(1.3);

    // p.DefineVar("x",  Variable(&xVal));
    // p.DefineVar("y",  Variable(&yVal));
    // p.DefineVar("z",  Variable(&zVal));

    // p.SetExpr("x+y+z");

    // Value result = p.Eval();

    // console() << result << "\n";

    // Create the parser instance
ParserX  p;

// Create an array of mixed type
Value arr(3, 0);
arr.At(0) = 2.0;
arr.At(1) = "this is a string";

// Create some basic values
Value cVal(cmplx_type(1, 1));
Value sVal("Hello World");
Value fVal(1.1);

// Now add the variable to muParser
p.DefineVar("va", Variable(&arr));
p.DefineVar("a",  Variable(&cVal));
p.DefineVar("b",  Variable(&sVal));
p.DefineVar("c",  Variable(&fVal));

p.SetExpr("va[0]+a*strlen(b)-c");
for (int i=0; i<<10; ++i)
{
  // evaluate the expression and change the value of
  // the variable c in each turn
  cVal = 1.1 * i;
  Value result = p.Eval();

  // print the result
  console() << result << "\n";
}
}
