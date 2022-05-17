#!/bin/bash

cd ~/BootCampMidTermLab/build
cmake -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_CXX_FLAGS_DEBUG="-g -O0" ..
if (make -j8)
then
    echo "-------------Build succeeded-----------"
fi
