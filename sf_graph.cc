/** @file sf_graph.cc
 * Routines for working with sparserow types as graphs
 */

/*
 * David F. Gleich
 * Copyright, Microsoft Corporation, 2008
 */

#include <unordered_set>
#include "sparfun.h"
#include "sparvec.h"  // include macros to make working with tr1 better

/** Compute the volume of a set of vertices.
 * 
 * For a given set of vertices, the volume is the sum of their
 * degrees.  This function will compute that quantity for
 * an array of vertices.
 * 
 * @param c the graph
 * @param verts an array of vertices numbers in the set
 * @param nverts the number of vertices in the set (size of verts)
 * @return the volume of the set
 */ 
int sr_graph_volume(const sparserow* c, int* verts, size_t nverts) {
    int vol = 0;
    for (size_t i=0; i<nverts; i++) {
        int v = verts[i];
        vol += c->ai[v+1]-c->ai[v];
    }
    return vol;
}

/** Compute the cut-size (boundary-size) of a set of vertices.
 * 
 * For a given set of vertices, the volumen is the sum of their
 * degrees.  This function will compute that quantity for
 * an array of vertices.
 * 
 * @param c the graph
 * @param verts an array of vertices numbers in the set
 * @param nverts the number of vertices in the set (size of verts)
 */ 
int sr_graph_cutsize(const sparserow* c, int* verts, size_t nverts) {
    int cut = 0;
    tr1ns::unordered_set<int> verts_set;
    for (size_t i=0; i<nverts; i++) {
        verts_set.insert(verts[i]);
    }
    for (size_t i=0; i<nverts; i++) {
        // look at all neighbors
        for (int nzi=c->ai[i]; nzi<c->ai[i+1]; ++i) {
            int neighbor = c->aj[nzi];
            if (verts_set.count(neighbor) == 0) {
                cut += 1;
            }
        }
    }
    return cut;
}
