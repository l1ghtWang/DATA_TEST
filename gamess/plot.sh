#!/bin/bash

javac Restore.java
java Restore $1
Rscript restore_mrc_plot.R $1

javac Restore_rotation.java
java Restore_rotation $1
Rscript restore_mrc_plot_rotation.R $1

Rscript hist_plot.R


#for job in `jobs -p`
#do
#	echo $job
#	    wait $job || let "FAIL+=1"
#done
