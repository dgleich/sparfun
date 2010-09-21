/** @filename sparse_containers
 * Implementations of map and set containers for sparse sets of indexed items.
 */

/**
 * @author David F. Gleich
 * 
 * History
 * -------
 * :2010-02-02: Initial version based on code from cover-combine.cc
 *              Added sparse_map_array
 * :2010-09-20: Added O(1) delete to sparse_set array, and changed it
 *   a bit to accomodate
 */

#include <vector>
#include <assert.h>
#include <limits>
 

/** A sparse set class that permits O(1) membership, O(1) insert, O(1) delete.
 * This class is based on an array.  It presumes that there is a large
 * but finite item space, and that items have indices between 0 and n-1.
 * It allocates two arrays, which are inverse permutations of each other.
 * i.e. elements[indices[i]] = i.  The permutation has the property
 * that elements[0] ... elements[cur_element-1] are in the set.  Thus,
 * we can check membership in O(1) time with indices[i] <= cur_element.
 * Likewise, we can insert an element by permuting its position to the
 * cur_element position and incrementing cur_element.  Deleting
 * an element involves permuting its position to cur_element-1 and
 * decrementing cur_elements.
 * 
 * IndexType should be something like an int or size_t.
 */
template <class IndexType>
class sparse_set_array {
    public:
    std::vector<IndexType> indices;
    std::vector<IndexType> elements;
    size_t cur_elements;
    size_t max_elements;
    
    /** 
     * Construction time is O(n)
     */
    sparse_set_array(size_t _max_elements) 
     : indices(_max_elements), elements(_max_elements),
       cur_elements(0), max_elements(_max_elements)
    {
        for (IndexType i=0; i<_max_elements; ++i) {
            indices[i] = i;
            elements[i] = i;
        }
    }
    
    void insert(IndexType i) {
        assert(i < max_elements);
        if (indices[i] >= cur_elements) {
            assert(cur_elements < max_elements);
            if (indices[i] == cur_elements) {
                // we are done as it's already in position
            } else {
                // move the indices[i] into the cur_elements position
                // and then move elements[cur_elements] into 
                // the indices[i] position
                swap(i,indices[i],cur_elements);
            }
            cur_elements ++;
        } else {
            // it's already here!
        }
    }
    
    void remove(IndexType i) {
        assert(i < max_elements);
        if (indices[i] >= cur_elements) {
            // this element is already deleted
        } else {
            assert(cur_elements > 0);
            if (indices[i] == cur_elements-1) {
                // this node is the last one in the array, and so 
                // we don't have to move it!
            } else {
                // move element i into position cur_elements-1,
                // and move the element in position cur_elements-1 
                // to indices[i]
                swap(i,indices[i],cur_elements-1);
            }
            cur_elements --;
        }   
    }
    
    size_t size() { return cur_elements; }
    
    size_t count(IndexType i) {
        assert(i < max_elements);
        if (indices[i] < cur_elements) {
            return 1;
        } else {
            return 0;
        }
    }
    
private:
    void place(IndexType i, IndexType position) {
        indices[i] = position;
        elements[position] = i;
    }
    
    void swap(IndexType i, IndexType pi, IndexType j, IndexType pj) {
        if (pi != pj) {
            place(i,pj);
            place(j,pi);
        } else {
            assert(i == j);
        }
    }
    
    void swap(IndexType i, IndexType pi, IndexType pj) {
        swap(i,pi,elements[pj],pj);
    }
        
};

/** A sparse set class that permits O(1) membership checking and O(1) insert
 * This class is based on an array.  This presumes that there is a large
 * but finite item space, and that items have indices between 0 and n-1.
 * It allocates two arrays... the first array is the membership array,
 * the second array is the valid set.  This lets us do
 *   i in set in O(1) time
 *   all i in set in O(size) time
 * It's just like a standard iwork array for doing a sparse matrix-matrix
 * product.
 *   The issue is that delete is O(size), not constant time.
 * 
 * IndexType should be something like an int or size_t.
 * 
 * This data structure is bad if the data need deletions.  It currently
 * does not support that operation.
 */
template <class IndexType, class ValueType>
class sparse_map_array {
    public:
    IndexType sentinal_val;
    ValueType default_val;
    std::vector<IndexType> indices;
    std::vector<IndexType> elements;
    std::vector<ValueType> values;
    size_t cur_elements;
    size_t max_elements;
    
    sparse_map_array(size_t _max_elements) 
     : sentinal_val(std::numeric_limits<IndexType>::max()),
       indices(_max_elements, sentinal_val), elements(_max_elements),
       cur_elements(0), max_elements(_max_elements), default_val(),
       values(_max_elements)
    {}
    
    /** Insert an element into the set.
     * If the element is already there, this suceeds, and treats
     * it as a set operation.
     */
    void insert(IndexType i, ValueType v) {
        assert(i < max_elements);
        if (indices[i] == sentinal_val) {
            assert(cur_elements < max_elements);
            elements[cur_elements] = i;
            values[cur_elements] = v;
            indices[i] = cur_elements;
            cur_elements ++;
        } else {
            // it's already here!
            // treat this as a set
            values[indices[i]] = v;
        }
    }
    
    size_t size() { return cur_elements; }
    
    size_t count(IndexType i) {
        assert(i < max_elements);
        if (indices[i] == sentinal_val) {
            return 0;
        } else {
            return 1;
        }
    }
    
    ValueType get(IndexType i) {
        assert(i < max_elements);
        if (indices[i] == sentinal_val) {
            return default_val;
        } else {
            return values[indices[i]];
        }
    }
    
    void set(IndexType i, ValueType v) {
       insert(i,v);
    }
};
