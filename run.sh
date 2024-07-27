#!/bin/bash

while :
do
    read -p "---> " -a command_array

    if [ ${#command_array[@]} -eq 0 ]; then
        echo "No command entered. Please enter a command."
        continue
    fi

    ./file_manager.out "${command_array[@]}" 
done
