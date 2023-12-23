echo "Installing SFML Packages..."

echo "Updating dnf..."
sudo dnf update -y

echo "Installing GIT..."
sudo dnf install git -y

echo "Installing SFML Packages..."
sudo dnf install libXi-devel freetype-devel libX11-devel libXrandr-devel libudev-devel mesa-libGL-devel flac-devel libogg-devel libvorbis-devel libvorbisenc2 libvorbisfile3 openal-soft-devel libpthread-stubs-devel -y
sudo dnf install libpthread-stubs-devel mesa-libGL-devel libX11-devel libXrandr-devel freetype-devel libjpeg-turbo-devel libsndfile-devel openal-soft-devel libudev-devel xcb-util-image-devel libjpeg-turbo-devel flac-devel libvorbis-devel libogg-devel libXcursor-devel libXinerama-devel -y

echo "SFML Packages Installed!"
