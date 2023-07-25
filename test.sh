#!/bin/bash

# Colours
BLUE="\e[1;36m"
YELLOW="\e[1;33m"
GREEN="\e[1;32m"
RED="\e[1;31m"
RESET="\e[0m"


# Create folder for traces
error_dir=traces
rm -rf $error_dir
mkdir -p $error_dir


# Set amount of tests
echo -n "Test values: "
read input
if [ -z $input ]; then
	echo "No input entered, using default \"199 190 60 60 10\""
	input="199 190 60 60 10"
fi
echo -n "How many times should each test be run? Enter value: "
read amount_of_tests
if [ -z $amount_of_tests ]; then
	echo "No value entered, using default value 25"
	amount_of_tests=25
fi
printf "\n\n"


# Big test uneven
amount_of_errors=0

printf "$YELLOW"
printf "Running [./philo $input] $amount_of_tests times $RESET\n"

for ((i = 1; i <= amount_of_tests; i++)); do
	./philo $input > out.txt;
	exit_code=$?

	if [ $exit_code -ne 0 ]; then
		((amount_of_errors++));
		echo -n "🍎"
		cat out.txt > $error_dir/trace_$i.txt;
	else
		echo -n "🍏"
	fi

	if ((i % 10 == 0)); then
		printf "\n"
	fi
done
printf "\nfailed $RED$amount_of_errors$RESET out of $GREEN$amount_of_tests$RESET tests\n\n"
rm -rf out.txt