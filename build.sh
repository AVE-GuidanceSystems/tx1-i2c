#!/bin/bash
g++ ./src/i2c-tx1.cpp -Wall -o ./i2c-tx1 `pkg-config --cflags glib-2.0 --libs glib-2.0` ./src/drv2605.cpp ./src/jetsonGPIO.c
