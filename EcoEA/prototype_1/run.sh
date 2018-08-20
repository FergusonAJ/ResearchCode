#!/bin/bash

python3 main.py $1

rootFolder=$(pwd)
dt=$(date +"%d-%m-%y_%H-%M_%S")
mkdir results/$dt
mkdir results/$dt/eco_ea
mkdir results/$dt/naive
for i in $(seq $1)
do
  cd $rootFolder/results/$dt
  let j=i-1
  cd eco_ea
  mkdir $j
  cd $j
  mv $rootFolder/trial_eco_ea_$j.csv ./FullMatches.csv
  mv $rootFolder/trial_eco_ea_resources_$j.csv ./Resources.csv
  mv $rootFolder/trial_eco_ea_char_match_$j.csv ./CharMatches.csv
  mv $rootFolder/trial_eco_ea_$j.txt ./LastGen.txt
  cd $rootFolder/results/$dt/naive
  R < $rootFolder/eco_ea_viz.r --vanilla $rootFolder/results/$dt/eco_ea/$j > /dev/null
  mkdir $j
  cd $j
  mv $rootFolder/trial_naive_$j.csv ./FullMatches.csv
  mv $rootFolder/trial_naive_char_match_$j.csv ./CharMatches.csv
  mv $rootFolder/trial_naive_$j.txt ./LastGen.txt
  R < $rootFolder/naive_viz.r --vanilla $rootFolder/results/$dt/naive/$j > /dev/null 
  rm $rootFolder/results/$dt/naive/$j/Rplots.pdf  > /dev/null
  cd $rootFolder/results/$dt
  echo "Visualizations done for trial #$j"
  rm ./naive/Rplots.pdf > /dev/null 
done
cp $rootFolder/*.py $rootFolder/results/$dt/
cp $rootFolder/*.r $rootFolder/results/$dt/
cp $rootFolder/*.sh $rootFolder/results/$dt/
#rm data.png
echo "Done!"
date
