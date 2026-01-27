#!/bin/bash

> result_of_script

for t in {1..100}; do
    /usr/bin/time -f "threads = $t time = %e" ./mdu -j ${t} "/pkg/" 2>> "result_of_script"
done
