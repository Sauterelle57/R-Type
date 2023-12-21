rm -rf build
rm -rf rtype_client
mkdir build
cmake -B build
cd build
make
cd ../
./rtype_client
