#!/bin/sh

pushd $PWD
cd ../src

for i in {2..24}
do 
    cp day1.cpp "day$i.cpp"
    sed -i "s\Day1\Day$i\g" "day$i.cpp"
done

popd
