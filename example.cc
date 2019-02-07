#include "basic_counting.hpp"
#include <iostream>
#include <random>


int main(){
  unsigned int window_size = 4096;
  double relative_error = 0.1;
  BasicCounting bc(window_size, relative_error);

  std::default_random_engine generator;
  std::exponential_distribution<double> distribution(0.25);

  const unsigned int T = window_size * 100;
  for(unsigned int t = 0;t < T;) {
    double number = distribution(generator);
    t += (unsigned int)(std::ceil(number));
    bc.insert(t);
    if(t >= 10 * window_size && (t % window_size == 0))
    {
      std::cout << bc.query() << std::endl;
    }
  }

  return 0;
}
