FROM ubuntu:23.04 as builder

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /build

RUN apt-get update -y
RUN apt-get install -y g++ gcc wget make git

RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-x86_64.sh
RUN chmod +x cmake-3.27.9-linux-x86_64.sh
RUN ./cmake-3.27.9-linux-x86_64.sh --prefix=/usr/local --exclude-subdir

RUN apt-get install libxi-dev libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev -y
RUN apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev libvorbis-dev libogg-dev libxcursor-dev libxinerama-dev -y

COPY . .

WORKDIR /build/build

RUN cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..

RUN make