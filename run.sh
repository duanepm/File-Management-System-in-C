#!/bin/bash

while :
do
    read -p "---> " -a command_array

    ./a.out "${command_array[@]}" 
done
