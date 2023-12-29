mkdir build
cd build
cmake ..
cmake --build .
cd ..
copy .\Debug\* .
copy .\build\Debug . 