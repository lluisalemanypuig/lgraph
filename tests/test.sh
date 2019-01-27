#!/bin/bash

########################################################################
# Functions

function show_usage {
	echo "Options:"
	echo "    [-h, --help]: show the usage"
	echo "    --all: tell the script to execute all groups of tests available."
	echo "        Every new group of tests needs to be added to the list."
	echo "    --group=g: specify the group 'g' of tests to be performed."
	echo "        This string is the path to the directory with all the"
	echo "        input tests. It can not contain the last slash ('/')"
	echo "        and can not start with 'inputs/'."
	echo "    --valgrind : use the memory error detector on every input"
	echo "        test. This option makes the test ignore the output"
	echo "        produced and errors are only reported when valgrind"
	echo "        does so."
}

function exe_valgrind {
	# When using valgrind, we only need to ensure
	# that there were no errors produced.
	if [ -s $TEST_ERR ]; then
		echo -en "\e[1;4;31mThe test produced errors\e[0m "
		echo "See result in $VALG_ERR.$ID"
		mv $TEST_ERR $VALG_ERR.$ID
	else
		# no errors were detected
		echo -e "\e[1;1;32mOk\e[0m"
	fi
}

function exe_no_valgrind {
	# When not using valgrind, we have to make sure that
	# the output produced is correct. If not, copy the
	# contents of the temporary standard output file into
	# a unique file for this test.
	if [ -s $TEST_ERR ]; then
		# why should we check the output if the library
		# produced errors?
		echo -en "\e[1;4;31mThe test produced errors\e[0m "
		echo "See result in $TEST_ERR.$ID"
		mv $TEST_ERR $TEST_ERR.$ID
	else
		# test whether the error output produced is empty or not
		BASE_OUT=$output_group/$f
		BASE_CONTENTS=$(cat $BASE_OUT)
		
		DIFF=$(diff <(echo "$BASE_CONTENTS") <(echo "$PROG_OUT"))
		if [ ! -z "$DIFF" ]; then
			echo -en "\e[1;4;31mDifferent outputs\e[0m"
			echo "See result in $TEST_OUT.$ID"
			echo "$PROG_OUT" > $TEST_OUT.$ID
		else
			# output produced by library is
			# equal to the output made by hand
			echo -e "\e[1;1;32mOk\e[0m"
		fi
	fi
}

function exe_group {
	# make sure that we have something to test
	if [ -z "$group" ]; then
		echo -e "\e[1;4;31mError:\e[0m" "Group of tests was not set" 
		echo "    Use ./test.sh --help to see the usage"
		exit
	fi

	# Make sure the output directory exists
	input_group=inputs/$group
	output_group=outputs/$group
	if [ ! -d $input_group ]; then
		exit
	fi

	# Prepare execution command. If valgrind is
	# requested, make the command appropriately.
	if [ $use_valgrind = 1 ]; then
		EXE_COMMAND="valgrind -q --leak-check=full ./$EXE_FILE"
	else
		EXE_COMMAND="./$EXE_FILE"
	fi

	# ------------------------------------------------
	# Prepare filenames for standard and error outputs
	keys=$(echo $group | tr "/" "\n");
	id=$(echo $keys | tr ' ' '.')
	# TEST_OUT and TEST_ERR are temporary files: a test named, for example,
	# test-0015 will produce a standard output and an error output into
	# $TEST_OUT and $TEST_ERR. Then, in case of errors, each file will be
	# moved to a unique file for this test, namely into the files
	# $TEST_OUT.0015 and $TEST_ERR.0015. In case of valgrind the contents
	# of $TEST_ERR will be moved to $VALG_ERR.0015.
	TEST_OUT=.tmp.$id.out
	TEST_ERR=.tmp.$id.err
	VALG_ERR=.vgd.$id.err

	progress=$1
	echo -e "\e[1;1;33mExecuting tests in \e[0m""\e[1;2;33m$input_group\e[0m ($progress)"

	# execute all tests
	all_test_files=$(ls $input_group)
	for f in $all_test_files; do
		if [ "$f" = "summary.ods" ]; then
			# skip
			echo -n ""
		else
			# retrieve id from input test
			# e.g.: 'test-0010' -> '0010'
			INFILE_LENGTH=${#f}
			ID=${f:5:($INFILE_LENGTH - 4)}
			
			echo -en "    ""\e[1;1;34m$f\e[0m"" "
			PROG_OUT=$($EXE_COMMAND --input $input_group/$f 2> $TEST_ERR)
			
			# parse result of execution command differently,
			# depending on whether we are using valgrind or not.
			if [ $use_valgrind = 1 ]; then
				exe_valgrind
			else
				exe_no_valgrind
			fi
		fi
	done

	# Remove those unnecessary temporary files.
	# File $VALG_ERR is never actually used 'as is'.
	rm -f $TEST_OUT $TEST_ERR
}

########################################################################
# Code starts here

ALL_GROUPS=("unweighted/undirected/paths"		\
			"unweighted/undirected/distances"	\
			"unweighted/directed/paths"			\
			"unweighted/directed/distances"		\
			"weighted/undirected/paths"			\
			"weighted/undirected/distances"		\
			"weighted/directed/paths"			\
			"weighted/directed/distances")

EXE_FILE="tests-debug/tests"
# Make sure that executable file exists.
# Do not continue if it does not.
if [ ! -f $EXE_FILE ]; then
	"\e[1;4;31mError:\e[0m Executable file $EXE_FILE does not exist"
fi

# show usage
usage=0
# the group of tests to be executed
group=""
# use valgrind
use_valgrind=0
# execute all tests?
exe_all=0

for i in "$@"; do
	case $i in
		
		--help|-h)
		usage=1
		shift
		;;
		
		--group=*)
		group="${i#*=}"
		shift
		;;
		
		--all)
		exe_all=1
		shift
		;;
		--valgrind)
		use_valgrind=1
		shift
		;;
		
		*)
		echo -e "\e[1;4;31mError:\e[0m" "Option $i unknown"
		;;
	esac
done

# show usage if indicated
if [ $usage = 1 ]; then
	show_usage
	exit
fi

if [ $exe_all = 1 ] && [ ! -z $group ]; then
	echo -e "\e[1;4;31mError:\e[0m" "Conflicting options '--all' and '--group'"
	exit
fi

if [ $exe_all = 1 ]; then
	echo -e "\e[1;1;36mExecuting all tests\e[0m"
	n_groups="${#ALL_GROUPS[@]}"
	ith_test=1
	for g in "${ALL_GROUPS[@]}"; do
		group=$g
		exe_group "$ith_test/$n_groups"
		ith_test=$(($ith_test + 1))
	done
else
	exe_group "1/1"
fi


