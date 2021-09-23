printf "swedish1.txt\n"
time cat words/swedish.txt tests/swedish1.txt | ./Test_Hash 
printf "\nswedish2.txt\n"
time cat words/swedish.txt tests/swedish2.txt | ./Test_Hash 
printf "\nenglish1.txt\n"
time cat words/english.txt tests/english1.txt | ./Test_Hash 
printf "\nenglish2.txt\n"
time cat words/english.txt tests/english2.txt | ./Test_Hash 
printf "\nFull.txt\n"
time cat words/full.txt tests/full1.txt | ./Test_Hash 
