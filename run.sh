#!/bin/bash

while :
do
    read -p "---> " -a command_array

    ./file_manager.out "${command_array[@]}" 
done
