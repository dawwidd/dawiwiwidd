#!/bin/bash

function morseHelp {
echo "Usage ./morse.sh [OPTION]... [FILE]... [STDIN]
Translate text to morse code signals.

	-r [FILE]	read text from FILE and output morse code to console
	-w [FILE]	write morse code to file from STDIN text
	-t [FILE]	specify alternative code to translate text to
	-h		display this help text and exit

Examples:
./morse.sh [STDIN]	Output standard input in morse code to standard output
./morse.sh -r [FILE]	Output FILE contents in morse code to standard output
	
	
Code files are sets of characters which are to replace normal text, separated with spaces, in following order:
A-Z 0-9 . , ? ! ( ) \" + - =
Default code file is \"defaultcode.txt\""
}

function translate {
	case ${latin[$i],,} in
		"a") morse[$i]=${table[0]};;
		"b") morse[$i]=${table[1]};;
		"c") morse[$i]=${table[2]};;
		"d") morse[$i]=${table[3]};;
		"e") morse[$i]=${table[4]};;
		"f") morse[$i]=${table[5]};;
		"g") morse[$i]=${table[6]};;
		"h") morse[$i]=${table[7]};;
		"i") morse[$i]=${table[8]};;
		"j") morse[$i]=${table[9]};;
		"k") morse[$i]=${table[10]};;
		"l") morse[$i]=${table[11]};;
		"m") morse[$i]=${table[12]};;
		"n") morse[$i]=${table[13]};;
		"o") morse[$i]=${table[14]};;
		"p") morse[$i]=${table[15]};;
		"q") morse[$i]=${table[16]};;
		"r") morse[$i]=${table[17]};;
		"s") morse[$i]=${table[18]};;
		"t") morse[$i]=${table[19]};;
		"u") morse[$i]=${table[20]};;
		"v") morse[$i]=${table[21]};;
		"w") morse[$i]=${table[22]};;
		"x") morse[$i]=${table[23]};;
		"y") morse[$i]=${table[24]};;
		"z") morse[$i]=${table[25]};;
		"0") morse[$i]=${table[26]};;
		"1") morse[$i]=${table[27]};;
		"2") morse[$i]=${table[28]};;
		"3") morse[$i]=${table[29]};;
		"4") morse[$i]=${table[30]};;
		"5") morse[$i]=${table[31]};;
		"6") morse[$i]=${table[32]};;
		"7") morse[$i]=${table[33]};;
		"8") morse[$i]=${table[34]};;
		"9") morse[$i]=${table[35]};;
		".") morse[$i]=${table[36]};;
		",") morse[$i]=${table[37]};;
		"?") morse[$i]=${table[38]};;
		"!") morse[$i]=${table[39]};;
		"(") morse[$i]=${table[40]};;
		")") morse[$i]=${table[41]};;
		"\"")morse[$i]=${table[42]};;
		"+") morse[$i]=${table[43]};;
		"-") morse[$i]=${table[44]};;
		"=") morse[$i]=${table[45]};;
		" ") morse[$i]=" ";;
		*)   morse[$i]="#"
	esac
}

function loadCodeTable {
	while IFS= read -r line; do
		export table=($line)
	done <"$code"
}

function morsify {

	loadCodeTable

	if [[ $r_flag == 1 ]]; then
		exec 3<&0
		exec 0<$src
	fi

	while IFS= read -r line; do
		for (( i=0; i<${#line}; i++ )); do
			latin[$i]=${line:$i:1}
			translate
		done

		if [[ $w_flag == 0 ]];then
			echo "${morse[@]}"
		elif [[ $w_flag == 2 ]]; then
			echo "${morse[@]}" >> $dest
		else
			echo "${morse[@]}" > $dest
			w_flag=2
		fi

		unset morse

	done
	
	if [[ $r_flag == 1 ]]; then
		exec 0<&3
	fi
}

code="defaultcode.txt"
r_flag=0
w_flag=0

while getopts :r:w:t:h opt; do
	case $opt in
		r)
			src=$OPTARG
			r_flag=1
			;;
		w)
			w_flag=1
			dest=$OPTARG
			;;
		t)
			code=$OPTARG
			;;
		h)
			morseHelp
			exit 0
			;;
		\?)
			echo "Unknown option: -$OPTARG. Use ./morse.sh -h for help"
			exit 1
			;;
		:)
			echo "$OPTARG:- requires a value. Use ./morse.sh -h for help"
			exit 1

	esac
done
shift $((OPTIND-1))

morsify
