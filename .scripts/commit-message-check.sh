#!/bin/bash

commit_msg_file=$1
commit_msg=$(cat "$commit_msg_file")

pattern="^(add|fix|feat|delete) \([^\)]+\): .+"

if ! [[ "$commit_msg" =~ $pattern ]]; then
    echo "Invalid commit message format. Please follow the pattern: '(add|fix|feat|delete): commit message'"
    exit 1
fi
