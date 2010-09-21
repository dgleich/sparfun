#!/bin/bash


orig_dir=$(pwd)
cd ${0%/*}/
mydir=$(pwd)
cd ../
sparfun_dir=$(pwd)
cd ${orig_dir}

# test the sparse_set array
echo '
#include <sparse_containers.hpp>
#include <stdio.h>

int main(int argc, char **argv) {
    sparse_set_array<int> a(10);
    a.insert(5);
    a.insert(6);
    a.insert(7);
    a.insert(1);
    a.remove(6);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.remove(6);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.insert(6);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.insert(0);
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    a.insert(6);
    a.insert(7);
    a.insert(8);
    a.insert(9);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.remove(0);
    a.remove(1);
    a.remove(2);
    a.remove(3);
    a.remove(4);
    a.remove(5);
    a.remove(6);
    a.remove(7);
    a.remove(8);
    a.remove(9);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.insert(5);
    a.remove(5);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.insert(5);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    a.insert(0);
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    a.insert(6);
    a.insert(7);
    a.insert(8);
    a.insert(9);
    for (int i=0;i<a.size();i++) {
        printf("%i\n",a.elements[i]);
    }
    return (0);
}
' | cat > $mydir/test.cc
g++ -I$sparfun_dir $mydir/test.cc -o $mydir/test
$mydir/test > $mydir/test.out
echo '5
1
7
5
1
7
5
1
7
6
5
1
7
6
0
2
3
4
8
9
5
5
0
1
2
3
4
6
7
8
9' | diff - $mydir/test.out


