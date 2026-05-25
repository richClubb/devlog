#!/bin/bash

printf "Testing bash params\n"

DEVICE=""
BUILD_TYPE=""

while getopts d:b:c flag
do
    case "${flag}" in
        d) DEVICE=${OPTARG} ;;
        b) BUILD_TYPE=${OPTARG} ;;
        c) THING=true ;;
    esac
done

printf "Device: $DEVICE\n"
printf "Build Type: $BUILD_TYPE\n"
printf "Thing: $THING\n"


