// basic_counting.hpp
/*
 * Problem: Given a stream of data elements, consisting of only 0's and 1's,
 *          maintain the counting of 1's in the last N element.
 *
 */

#ifndef BASIC_COUNTING_HPP
#define BASIC_COUNTING_HPP
#include <list>
#include <cmath>
#include <cassert>

template <typename Integer=unsigned int>
struct Bucket {
  // counter: number of 1's in this bucket
  Integer _cnt;
  // timestamp: arrival "time" of the last 1's
  Integer _ts;
  Bucket(Integer timestamp): _cnt(1U), _ts(timestamp){}
  Integer size() const {return _cnt;}
  Integer timestamp() const {return _ts;}
  void timestamp(Integer timestamp) { _ts = timestamp; }
  void merge(const Bucket<Integer>& other) {
    _cnt += other.size();
    _ts = std::max(_ts, other.timestamp());
  }
};// bucket


template <typename Integer=unsigned int, typename Container=std::list<Bucket<Integer>>>
struct BasicCounting {
  using IT = typename Container::iterator;
  BasicCounting(unsigned int window_size, double relative_error):
  _window(window_size),
  _rel_error(relative_error),
  _k_half_plus_one(1U + unsigned(std::ceil(0.5*std::ceil(1.0/relative_error)))){
        assert(_window > 1);
  }
  void insert(Integer timestamp){
    check_expiry(timestamp);
    _buckets.emplace_front(timestamp);
    ++ _total;
    if(_buckets.size() > _k_half_plus_one) merge_if_necessary();
  }
  Integer query() const {
    return _total - (_last / 2);
  }
 private:
  void merge_if_necessary(){
    Integer c = 1;
    IT pre = _buckets.begin(), cur = (pre ++);
    for(;cur != _buckets.end();pre = cur, ++cur){
      if((*cur).size() == (*pre).size()) ++ c;
      else {
        if(c > _k_half_plus_one) {
          IT temp = pre;
          -- temp;
          (*pre).merge(*temp);
          _buckets.erase(temp);
          c = 1;
        } else return;
      }
    }
    // check whether need to merge the last two
    if(c > _k_half_plus_one) {
      IT temp = pre;
      --temp;
      (*pre).merge(*temp);
      _buckets.erase(temp);
      _last = (*pre).size();
    }
  }

  void check_expiry(Integer timestamp){
      if(_buckets.empty()) return;
      auto& last = _buckets.back();
      if(timestamp - last.timestamp() >= _window) {
        // expire
        _total -= last.size();
        _buckets.pop_back();
        _last = _buckets.back().size();
      }
  }
  // (sliding) window size
  const unsigned int _window;
  // relative error required
  const double _rel_error;
  // value of k
  const unsigned int _k_half_plus_one;
  // size of the last bucket
  Integer _last{0};
  // total number of 1's
  Integer _total{0};
  // buckets
  Container _buckets;
};// basic counting
#endif // BASIC_COUNTING_HPP
