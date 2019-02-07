// basic_counting.hpp
/*
 * Problem: Given a stream of data elements, consisting of only 0's and 1's,
 *          maintain the counting of 1's in the last N element.
 *
 */

#ifndef BASIC_COUNTING_HPP
#define BASIC_COUNTING_HPP

template <typename Integer=unsigned int>
struct Bucket {
  // counter: number of 1's in this bucket
  Integer _cnt{0};
  // timestamp: arrival "time" of the last 1's
  Integer _ts;{0}
  Bucket(Integer timestamp): _cnt(1U), _ts(timestamp){}
};// bucket

template <typename Integer=unsigned int, class Container=std::vector<Bucket<Integer>>>
struct BasicCounting {
  BasicCounting(unsigned int window_size, double relative_error):
  _window(window_size),
  _rel_error(relative_error),
  _k_half(unsigned(std::ceil(0.5*std::ceil(1.0/relative_error)))){

  }
  void insert(Ineteger timestamp){
    _buckets.emplace_back(timestamp);
  }
  Integer query() const {
    return _total - (_last / 2);
  }
 private:
  void merge(){

  }
  void expire(){

  }
  // (sliding) window size
  const unsigned int _window;
  // relative error required
  const double _rel_error;
  // value of k
  const unsigned int _k_half;
  // size of the last bucket
  Integer _last{0};
  // total number of 1's
  Integer _total{0};
  // buckets
  Container _buckets;
};// basic counting
#endif // BASIC_COUNTING_HPP
