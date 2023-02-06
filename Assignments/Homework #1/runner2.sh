#!/bin/bash
# Joshua Meharg CS392 2023
# Version 1.1


if [[ ! $PWD = $HOME ]] ; then
    echo "ERROR: script has to be run in $HOME"
    echo "       Also make sure testcases2-txt and junk.sh are in the $HOME"
    exit 1
fi

if [[ ! -a "junk.sh" ]] ; then

echo "ERROR: junk.sh not found in $HOME directory"
exit 1

fi

if [[ ! -a "testcases-2.txt" ]] ; then

echo "ERROR: testcases-2.txt not found in $HOME"
echo "       download testcases-2.txt from canvas/move it to $HOME"
exit 1

fi


if [[ $# > 0 ]] ; then

echo "ERROR: too many arguments"
echo "usage: $0"
exit 1

fi



input="/$HOME/testcases-2.txt"
# input="/$HOME/testdoc.txt"

touch junk0.txt
mkdir -p dir1 2>/dev/null
mkdir -p dir2/dir3 2>/dev/null
touch .hidden1.txt 
mkdir .hideme 2>/dev/null
mkdir .hideme2 2>/dev/null
mkdir -p .hideme2/hide.txt 2>/dev/null

touch dir1/junk1.txt

touch dir2/.hidden2.txt
touch dir2/file3.txt
touch dir2/junk2.txt

touch dir2/dir3/junk3.txt

touch file1.txt
touch file2.txt
touch file4.txt
touch junk0.txt
touch junksol.sh
touch lastone.txt
mkdir yetanother 2>/dev/null






clear >$(tty)
cat <<EOF
==================================PLEASE READ==================================

Info: tested echo $ ? after each command automatically and
      removed tree tests that's why it appears THAT TESTS ARE SKIPPED
 
Info: Despite skipping tests test case numbers still
      allign with the original ones in testcases-2.txt 
      for easy comparison
 
Info: This script simply sets up all the test files and 
      calls all the commands in 
      the testcases-2.txt for you, there is no 
      automatic comparison with expected output
 
IMPORTANT: however don't just rely on this for all your testing
           or think you'll get a 100 if all theses 
           test cases work this is just for your convience :)

EOF

read -sp 'Press enter to continue '
clear >$(tty)
echo

num=0
# holds the test case number
next=0
# flags if the next line is an executable command
expected=0
# flag to signal the expected output is being read
start=0
# flag for the initial start of the expected output to display the expected output title


while read line ; do #removes leading and trailing whitespace

    # conditional statements skip echo and tree commands
    if [ $next = 1 ] && [ "${line:0:4}" = "echo" ] ; then
        num=$(( $num + 1 ))
        next=0
    fi

    if [ $next = 1 ] && [ "${line:0:4}" = "tree" ] ; then
        num=$(( $num + 1 ))
        next=0
    fi
    

    # conditional statement to output the expected output
    if [ "$expected" = 1 ] ; then
        if [ "$start" = 1 ] ; then
            echo "==========================EXPECTED OUTPUT========================="
            start=0
        fi
        

        if [ "${line:0:1}" = "" ] ; then
            expected=0
            usage=0
            echo "=================================================================="
            echo "__________________________________________________________________"
            echo
            echo
            continue
        fi

        if [ "$usage" = 1 ] ; then
            echo -n "   "
        fi

        if [ "${line:0:5}" = "Usage" ] ; then
            usage=1
            # when usage flag is 1 tab the rest of the outputs because front white space is cut out when reading
        fi

        echo $line
        continue
        

    fi
    
    # conditional that finds lines in the file that holds a command and executes them
    if [ $next = 1 ] ; then
        echo
        echo "Test $num"
        echo "running command: $line"
        echo
        echo "==============================OUTPUT=============================="
        eval $line 
        eval exit_value=$(eval echo $?)
        # echo $? has to be run right after $line command to catchthe exit value this is why its saved into
        # a variable and printed later rather than just calling echo $? later
        echo "=================================================================="
        echo
        echo "[NOT PART OF OUTPUT] Command finsihed with exit value: $exit_value"
        echo
        num=$(( $num + 1 ))
        expected=1
        # signalling the expected output lines are next in the file
        start=1
        next=0
    fi

    if [ "${line:0:4}" = "Test" ] ; then
        next=1
    fi
    # flags that the next line is a command

    
    
done < "$input"

# rm -r dir1
# rm -r dir2
# rm -r .hideme2
