#!/bin/bash

ARG1=./champions/zork.cor
ARG2=./champions/Gagnant.cor
ARG3=./champions/bee_gees.cor
ARG4=./champions/bigzork.cor
ARG5=./champions/Car.cor
ARG6=./champions/Gagnant2.cor
ARG7=./champions/new.cor

diff <(./corewar -d $1 $ARG2 $ARG5 $ARG6 $ARG5) <(./vm_champs/corewar -d $1 $ARG2 $ARG5 $ARG6 $ARG5)
