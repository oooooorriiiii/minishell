#!/bin/bash

#readonly MINISHELL_DIR="../minishell"
#readonly MINISHELL_EXE="minishell"
#
#readonly SCRIPT_FILE="$0"
#readonly LOG_FILE="result.log"
#
#readonly COLOR_RESET="\033[0m"
#readonly COLOR_GREEN="\033[32m"
#readonly COLOR_RED="\033[32m"
#
#PROMPUT='minishell\$'
#
#rm -rf ./output
#mkdir "./output"
#
#echo -e "${COLOR_GREEN}testing.${COLOR_RESET}
#"
echo
while read line ; do
   echo $line | ../minishell >> output/result.txt 2>&1
   echo $? >> output/minishell_status.txt
   echo $line >> output/minishell_status.txt

   echo $line | bash >> output/bash.txt 2>&1
   echo $? >> output/bash_status.txt
   echo $line >> output/bash_status.txt
done < ./cmdline.txt

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ | ./minishell | sed -e 's/minishell$ //g' | sed -e '1d' 2>&-)
	ES_1=$?
	TEST2=$(echo $@ | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# -------------- ECHO TESTS
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
exec_test 'echo ""'
exec_test 'echo "'
exec_test 'echo "'
exec_test 'echo "   $?   "'
exec_test 'echo $?$?$??'
exec_test 'echo '-n $USER likes an apple''
exec_test 'echo '$USER likes an apple''
exec_test 'echo "$USER likes an apple"'
exec_test 'echo aaaaaaaa$USER++++++++++;'
exec_test 'echo ;;;;;;;;;;;;'
exec_test 'echo ";;;;;;;;;;;;"'
# exec_test 'echo echo echo cd > test.txt'

# -------------- PWD TESTS
exec_test 'pwd "$USER likes an apple"'
exec_test 'pwd '
exec_test '      pwd     '

# -------------- CD TESTS
exec_test 'cd ../'
exec_test 'pwd'
exec_test 'cd'
exec_test 'pwd'
exec_test 'cd . . .'
exec_test 'pwd'
exec_test 'cd . apple'
exec_test 'pwd'
exec_test 'cd > test.txt'
exec_test 'pwd'
exec_test 'cd xxxxxxxx'
exec_test 'pwd'
exec_test 'cd '
exec_test 'pwd'

# -------------- EXPORT TEST
exec_test 'export NINJA'
exec_test 'export APPLE="iPhone"'
exec_test 'echo $APPLE is a phone'
exec_test 'export NUMBER=12345'
exec_test 'export 12345=MATH'
exec_test 'export MICKY==MOUSE'
exec_test 'export $=NUMBER'
exec_test 'export FOOTBALL=FOOTBALL'
exec_test 'export $SAMPLE=``'
exec_test 'export $?=STATUS'
exec_test 'export $CHINA=PANDA'
# exec_test 'export'


# -------------- UNSET TESTS
exec_test 'echo $MICKY'
exec_test 'unset'
exec_test 'unset $$'
exec_test 'unset $?'
exec_test 'echo $?'
exec_test 'unset xxxxxxxxx'
exec_test 'unset $APPLE'
exec_test 'unset NUMBER'
exec_test 'echo $APPLE is a phone'

# -------------- ENV TESTS
# exec_test 'env'
# exec_test 'env apple'


# -------------- INTEGRATED PIPE TESTS
# exec_test 'export | cat'
# exec_test '|||||' #(Syntax Error)
exec_test 'echo I have a dream that one day this nation will rise up | and live out the true meaning of its creed: "We hold these truths to be self-evident, that all men are created equal."'
exec_test 'ls -a | grep 42Tokyo | wc -l'
exec_test 'ls | ls | ls | cat | ls | pwd | cat'
exec_test 'echo apple | cat'
# exec_test 'echo |' #(Syntax Error)
# exec_test 'pwd |' #(Syntax Error)
# exec_test 'cd |' #(Syntax Error)
# exec_test 'pwd' #(Syntax Error)
# exec_test 'unset |' #(Syntax Error)
# exec_test 'export |' #(Syntax Error)

# -------------- SYSTEMCALL


# -------------- MASSY
exec_test '|'
exec_test '$USER'
# exec_test 'echo >' #(Syntax Error)
# exec_test 'echo >|' #(Syntax Error)
exec_test '	'
exec_test 'echo 	'
exec_test 'echo "|"'
exec_test 'echo | apple'
exec_test 'pwd | cat > test.txt'
exec_test 'cd | cd | cd | cd'
exec_test 'pwd'
exec_test 'aaaad    dnlnk aaadpn    dkllkk'
exec_test '\n'
exec_test '\t'
exec_test ''
exec_test '1> file'
# exec_test './minishell'
# exec_test './test'
exec_test 'ls ******* ++++++ +++++'
exec_test 'ls ******* ++++++ | +++++'
# exec_test 'echo Live as if you were to die tomorrow. Learn as if you were to live forever. > test.txt'

# -------------- From minishell-testcase channel
exec_test '2147483647> file'
exec_test '2147483648> file'
exec_test 'export TEST="a=b=c=d"'
exec_test 'env | grep TEST'
exec_test 'echo $TEST'
exec_test 'export TEST="-n hello"'
exec_test 'env | grep TEST'
exec_test 'echo $TEST'
exec_test 'export PIPE="|"'
exec_test 'echo $PIPE'
exec_test 'ps -a $PIPE grep bash'
exec_test 'echo $? | exit 42 | echo $?'
exec_test 'echo hello | cd ..'
exec_test 'export TEST="a" | export TEST="b" | echo $TEST'
exec_test 'export a=" "'
exec_test 'echo $a-a'
exec_test 'mkdir dir'
exec_test 'cd dir'
exec_test 'rmdir ../dir'
exec_test 'pwd'
exec_test 'cd .'
exec_test 'pwd'

exec_test 'ffffffff'

bash --version
