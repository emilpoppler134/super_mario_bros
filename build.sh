#!/bin/bash
cc main.c level.c `pkg-config --libs --cflags raylib` -o Game