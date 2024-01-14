#!/bin/bash

while getopts ":v:" opt; do
  case $opt in
    v)
      version="$OPTARG"
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

if [ -z "$version" ]; then
  echo "Usage: $0 -v <version>"
  exit 1
fi

release_notes="Release $version"

gh release create $version -t "$version" -n "$release_notes"

if [ $? -eq 0 ]; then
  echo "Release $version created successfully!"
else
  echo "Failed to create release. Check the error message above."
fi
