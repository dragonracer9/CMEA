#include "midpoint.hpp"

double midpoint_rule(double a, double b, int n, FunctionPointer f)
{
  // (write your solution here)
  const double c = (b - a) / double(n);
  double sum{};

  for (int i{}; i < n; ++i) // \sum_{i=0}^{n-1} (f(a+c*(i+1/2)))
  {
    sum += (*f)(a + c * (i + 1.0 / 2));
  }

  return (c * sum);
}
