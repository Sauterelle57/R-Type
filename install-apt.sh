echo "Installing SFML Packages..."

echo "Updating apt-get..."
sudo apt-get update -y

echo "Installing GIT..."
sudo apt-get install git -y

echo "Installing SFML Packages..."
sudo apt-get install libxi-dev libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev -y
sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev libvorbis-dev libogg-dev libxcursor-dev libxinerama-dev -y

echo "SFML Packages Installed!"