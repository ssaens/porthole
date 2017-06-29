//
// Created by Dillon Yao on 6/7/17.
//

#include <iostream>

#include "display/view.h"
#include "display/porthole.h"

int main(int argc, char **argv) {
    View view;
    Porthole porthole;

    view.bind_application(&porthole);
    view.init();
    view.begin();
}

