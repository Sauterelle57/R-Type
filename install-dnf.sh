echo "Installing SFML Packages..."

echo "Updating dnf..."
sudo dnf update -y

echo "Installing GIT..."
sudo dnf install git -y

echo "Installing SFML Packages..."
sudo dnf install libXi-devel freetype-devel libX11-devel libXrandr-devel libudev-devel mesa-libGL-devel flac-devel libogg-devel libvorbis-devel libvorbisenc2 libvorbisfile3 openal-soft-devel libpthread-stubs-devel libjpeg-turbo-devel libsndfile-devel libXcursor-devel libXinerama-devel -y

echo "SFML Packages Installed!"
