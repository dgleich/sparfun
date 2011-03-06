/**
 * @file sf_perm.hpp
 * Simple codes to work with permutations
 */

/**
 * History
 * -------
 * :2011-03-05: Initial version based on overlapping/hypercluster.cc
 */ 

// TODO add tests for this code
// TODO add documentation for inverse_permutation
// TODO add sparfun.h headers for these functions

#include <vector>
#include <algorithm>

template <typename T, typename index_type = int>
class sort_order_comparison {
  const std::vector<T>& items;
public:
  sort_order_comparison(const std::vector<T>& i) : items(i) {}
  bool operator() (index_type i, index_type j) {
    return items[i] > items[j];
  }
};

/**
 * This function sorts in descending order
 * @param order this parameter is an output and will be initialized
 */
template <typename T>
void sort_permutation(const std::vector<T>& a, std::vector<int>& order) {
  order.resize(a.size());
  for (size_t i=0; i<a.size(); ++i) {
    order[i] = (int)i;
  }
  sort_order_comparison<T> comp(a);
  std::sort( order.begin(), order.end(), comp );
}

template <typename Index>
void inverse_permutation(const std::vector<Index>& perm, std::vector<Index>& inv) {
  inv.resize(perm.size());
  for (size_t i=0; i<perm.size(); ++i) {
    inv[perm[i]] = i;
  }
}
