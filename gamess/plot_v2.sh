#!/bin/bash

javac Restore_2.java
java Restore_2 $1 
Rscript restore_2_mrc_plot.R $1
Rscript hist_plot.R



#for job in `jobs -p`
#do
#	echo $job
#	    wait $job || let "FAIL+=1"
#done
