#!/bin/bash

# EXPORT COMPILE COMMANDS is for clangd
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
cmake --build build
