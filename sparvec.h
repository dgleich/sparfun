/** 
 * @file sparvec.h
 * Prototypes for the sparvec library functions.
 */

/*
 * David F. Gleich
 * Copyright, Microsoft Corporation, 2008
 */

/** History
 *  2008-07-03: Initial coding
 */

#include "vecfun.h"
#include <unordered_map>
#include <limits>

#if defined(_WIN32) || defined(_WIN64)
#define tr1ns std::tr1
#else
#define tr1ns std
#endif

struct sparsevec {
  typedef tr1ns::unordered_map<int,double> map_type;
  map_type map;
  /** Get an element and provide a default value when it doesn't exist
   * This command does not insert the element into the vector
   */
  double get(int index, double default_value=0.0) {
    map_type::iterator it = map.find(index);
    if (it == map.end()) {
      return default_value;
    } else {
      return it->second;
    }
  }

  /** Compute the sum of all the elements
   * Implements compensated summation
   */
  double sum() {
    double t,y,s[2]={0};
    for (map_type::iterator it=map.begin(),itend=map.end();it!=itend;++it) {
      CSUMA(it->second,s);
    }
    return FCSUM(s);
  }
  
  /** Compute the max of the element values 
   * This operation returns the first element if the vector is empty.
   */
  int max_index() {
    int index=0;
    double maxval=std::numeric_limits<double>::max();
    for (map_type::iterator it=map.begin(),itend=map.end();it!=itend;++it) {
      if (it->second>maxval) { maxval = it->second; index = it->first; }
    }
    return index;
  }
};






