echo "Installing SFML Packages..."

echo "Updating apt-get..."
sudo apt-get update -y

echo "Installing SFML Packages..."
sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev libvorbis-dev libogg-dev libxcursor-dev -y

echo "SFML Packages Installed!"
