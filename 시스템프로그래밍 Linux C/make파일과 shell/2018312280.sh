 #execute makefile, 
 #make answersheet answer.txt, 
 #run,save output as output.txt,
 #compare answer, output with diff command as result.txt,
 #clean object files and executable file
 #use echo pipe line
 #!/bin/bash
make
./hello.txt > output.txt
touch answer.txt
answerfile="answer.txt"
echo -e "33 11" >> ${answerfile}
diff output.txt answer.txt > result.txt
make clean
