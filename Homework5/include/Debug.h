//
// Created by aldin on 12/24/2025.
//

#ifndef DEBUG_H
#define DEBUG_H

struct Debug {
    // add all required Debug fields
    int red_edges;
    int black_edges;

    // create Debug constructors
    Debug() : red_edges(-1), black_edges(-1) {}

    Debug(int red, int black) : red_edges(red), black_edges(black) {}
};

#endif //DEBUG_H