#!/bin/bash
cmake -DCMAKE_VERBOSE_MAKEFILE=ON -B build -S . && cd build && make && cd ..