#!/bin/bash

gcc main.c graphes.c --std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes -DNDEBUG -lm -g -o test
