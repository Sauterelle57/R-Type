echo "Building Server using docker... (please wait)"

sleep 1

docker build -t rtype .

sleep 2

echo "Launching server..."

docker run -p 1234:1234 rtype