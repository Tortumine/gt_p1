#!/bin/bash

gcc main.c graphes/graphes.c cavalier/cavalier.c --std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes -DNDEBUG -lm -fopenmp -o test
