#!/bin/bash

function show_usage {
	echo "Options:"
	echo "    [-h, --help]: show the usage"
	echo "    --group=string: specify the group of tests to be performed."
	echo "        This string must not contain the last slash ('/')"
	echo "        and should not start with 'inputs/'."
}

EXE_FILE="tests-debug/tests"
# test that executable file exists
if [ ! -f $EXE_FILE ]; then
	"\e[1;4;31mError:\e[0m Executable file $EXE_FILE does not exist"
fi

# files for standard and error output
TEST_OUT=.tmp.out
TEST_ERR=.tmp.err
# the group of tests to be executed
GROUP=""
GROUP_READ=0
HELP=0

for i in "$@"; do
	case $i in
		
		--help|-h)
		HELP=1
		shift
		;;
		
		--group=*)
		GROUP="${i#*=}"
		GROUP_READ=1
		shift
		;;
		
		*)
		echo -e "\e[1;4;31mError:\e[0m" "Option $i unknown"
		;;
	esac
done

if [ $HELP = 1 ]; then
	show_usage
	exit
fi
if [ $GROUP_READ = 0 ]; then
	echo -e "\e[1;4;31mError:\e[0m" "Group of tests was not set" 
	echo "    Use ./test.sh --help to see the usage"
	exit
fi

INPUT_GROUP=inputs/$GROUP
OUTPUT_GROUP=outputs/$GROUP

if [ ! -d $INPUT_GROUP ]; then
	exit
fi

echo -e "\e[1;1;33mExecuting tests in \e[0m""\e[1;2;33m$INPUT_GROUP\e[0m"
ALL_TEST_FILES=$(ls $INPUT_GROUP)
for f in $ALL_TEST_FILES; do
	if [ "$f" = "summary.ods" ]; then
		# skip
		echo -n ""
	else
		# retrieve id from input test
		# e.g.: 'test-0010' -> '0010'
		INFILE_LENGTH=${#f}
		ID=${f:5:($INFILE_LENGTH - 4)}
		
		echo -en "    ""\e[1;1;34m$f\e[0m"" "
		PROG_OUT=$(./$EXE_FILE --input $INPUT_GROUP/$f 2> $TEST_ERR)
		
		if [ -s $TEST_ERR ]; then
			echo -e "\e[1;4;31mThe test produced errors\e[0m"
			mv $TEST_ERR $TEST_ERR.$ID
		else
			# test whether the error output produced is empty or not
			BASE_OUT=$OUTPUT_GROUP/$f
			BASE_CONTENTS=$(cat $BASE_OUT)
			
			DIFF=$(diff <(echo "$BASE_CONTENTS") <(echo "$PROG_OUT"))
			if [ ! -z "$DIFF" ]; then
				echo -e "\e[1;4;31mDifferent outputs\e[0m See result in $TEST_OUT.$ID"
				echo "$PROG_OUT" > $TEST_OUT.$ID
			else
				echo -e "\e[1;1;32mOk\e[0m"
			fi
		fi
	fi
done

rm -f $TEST_OUT $TEST_ERR
