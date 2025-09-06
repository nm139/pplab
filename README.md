# TO CLONE THE REPO USE THE FOLLOWING COMMAND
git clone https://github.com/nm139/pplab.git

# THEN CHANGE DIRECTORY TO THE INSTALLED REPO
cd pplab

# SELECT THE REQUIRED PROGRAM FILE AND USE IT

# CLI COMMANDS TO RUN THE PROGRAMS
PROGRAM 1,2,3: step1) gcc -fopenmp prg1.c -o prg1
               
               step2) ./prg1
               
PROGRAM 4: step1) gcc -fopenmp prg4.c -o prg4 -lm
           
           step2) ./prg4
           
PROGRAM 5: step1) mpic prg5.c -o prg5
           step2) mpirun -np 2 ./prg5

# TO INSTALL MPICC IF NOT PRESENT
sudo apt install mpich
