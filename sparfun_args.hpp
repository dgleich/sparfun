/**
 * @file sparfun_args.h
 * Utility functions for the command line argument processing
 * 
 */

/**
 * @author David F. Gleich
 * Copyright, 2010
 *  
 * History
 * --------
 * :2008-09-01: Initial coding
 * :2010-02-05: Added argument parser
 */

#ifndef SPARFUN_ARGS_H
#define SPARFUN_ARGS_H

struct sf_args {
    int argc;
    char **argv;
    int *used;
    
    sf_args(int _argc, char **_argv) 
    : argc(_argc), argv(_argv)
    {
        assert(argc>0);
        used = new int[argc];
        for (int i=0; i<argc; i++) { used[i] = 0; }
        used[0] = 1; // always set the command name to be used
    }
    
    int mark_used(int argi) {
        assert(argi < argc);
        used[argi] = 1;
    }
    
    int find_arg(const char *arg) {
        int rval = -1;
        for (int i=0; i<argc; i++) {
            if (used[i] == 0) {
                if (strcmp(argv[i],arg)==0) {
                    return i;
                }
            }
        }
        return rval;
    }
    
    double double_arg(const char *arg, double d) {
        int argi = find_arg(arg);
        double rval = d;
        if (argi > 0) {
            const char *a = argv[argi];
            if (strcmp(a,"_")!=0) {
                rval = atof(a);
            }
        } 
        return rval;
    }
    
    const char* string_arg(const char *arg, const char *d) {
        int argi = find_arg(arg);
        const char* rval = d;
        if (argi > 0) {
            rval = argv[argi];
        } 
        return rval;
    }
    
    int int_arg(const char *arg, int d)  {
        int argi = find_arg(arg);
        int rval = d;
        if (argi > 0) {
            const char *a = argv[argi];
            if (strcmp(a,"_")!=0) {
                rval = atoi(a);
            }
        } 
        return rval;
    }
};

#endif // SPARFUN_ARGS_H 
