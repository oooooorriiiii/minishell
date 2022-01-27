#!/bin/bash

readonly MINISHELL_DIR="../minishell"
readonly MINISHELL_EXE="minishell"

readonly SCRIPT_FILE="$0"
readonly LOG_FILE="result.log"

readonly COLOR_RESET="\033[0m"
readonly COLOR_GREEN="\033[32m"
readonly COLOR_RED="\033[32m"

PROMPUT='minishell\$'

rm -rf ./output
mkdir "./output"

echo -e "${COLOR_GREEN}testing.${COLOR_RESET}
"
echo
while read line ; do
   echo $line | ../minishell >> output/result.txt 2>&1
   echo $? >> output/minishell_status.txt
   echo $line >> output/minishell_status.txt

   echo $line | bash >> output/bash.txt 2>&1
   echo $? >> output/bash_status.txt
   echo $line >> output/bash_status.txt
done < ./cmdline.txt