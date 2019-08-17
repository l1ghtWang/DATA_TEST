#!/bin/bash

#javac Restore_2.java
#java Restore_2 $1 
#Rscript restore_2_mrc_plot.R $1
#Rscript hist_plot.R

javac Restore_line.java
java Restore_line $1 
Rscript restore_line_mrc_plot.R $1


#for job in `jobs -p`
#do
#	echo $job
#	    wait $job || let "FAIL+=1"
#done
