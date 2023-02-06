#!/bin/bash 

# I pledge my honor that I have abided by the Stevens Honor System.
# Haig Emirzian

#readonly
readonly junk_path=~/.junk

#initialize flag count
hFlag=0
lFlag=0
pFlag=0

#usage message heredoc
function usageMessage(){
    cat << EOF 
Usage: $(basename "$0") [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
EOF
} 

#looks for h, l, and p flags
while getopts ":hlp" option; do
    case "$option" in
        h)
            hFlag=$(( hFlag = 1 ))
            ;;
        l)
            lFlag=$(( lFlag = 1 ))
            ;;
        p)
            pFlag=$(( pFlag = 1 ))
            ;;
        *)
            echo "Error: Unknown option" "'-"$OPTARG"'." >&2
            usageMessage
            exit 1
            ;;
    esac
done

shift "$(($OPTIND -1))"

#counts the number of flags
flagCount=$(( hFlag + lFlag + pFlag ))

fileCount=0

#counts the number of files
for files in "$@"; do
    fileCount=$(( fileCount + 1))
done


#Case #1: more than one (valid) flag
if [ $flagCount -gt 1 ]; then
    echo 'Error: Too many options enabled.' >&2
    usageMessage
    exit 1
#Case #2: one or more flags and file
elif ([ $flagCount -gt 0 ] && [ $fileCount -gt 0 ]); then
    echo 'Error: Too many options enabled.' >&2
    usageMessage
    exit 1
fi

#if user inputs h flag or just ./junk.sh
if [ $hFlag = 1 ]; then
    usageMessage
elif [[ $fileCount = 0 && $flagCount = 0 ]]; then
    usageMessage
fi

#checks to see if the junk path exists, otherwise it creates it    
if [[ -d "$junk_path" ]]; then
    true
else
    mkdir "$junk_path"
fi

#-l flag command: lists files in junk path
if [ $lFlag = 1 ]; then
    ls -lAF "$junk_path"
fi

#-p flag command: purges files in junk path
if [ $pFlag = 1 ]; then
    shopt -s dotglob
    rm -rf "$junk_path"/*
fi

#moves files or directories to junk path
for files in "$@"; do
    if [[ -f "$files" || -d "$files" ]]; then
        mv "$files" "$junk_path"
    else
        echo "Warning: '$files' not found." >&2
        exit 1
    fi
done

exit 0
