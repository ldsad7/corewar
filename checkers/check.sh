#!/bin/bash

ARG1=./champions/zork.cor
ARG2=./champions/Gagnant.cor
ARG3=./champions/bee_gees.cor
ARG4=./champions/bigzork.cor
ARG5=./champions/Car.cor
ARG6=./champions/Gagnant2.cor
ARG7=./champions/new.cor

./vm_champs/corewar -v 31 -a $ARG6 $ARG3 > ./checkers/true_output
./corewar -info -a $ARG6 $ARG3 > ./checkers/my_output

diff ./checkers/my_output ./checkers/true_output > ./checkers/difference

cat ./checkers/difference

