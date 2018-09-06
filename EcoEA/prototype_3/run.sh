#!/bin/bash
date
make
date
./App $1
date
rootFolder=$(pwd)
dt=$(date +"%y-%m-%d_%H-%M_%S")
mkdir results > /dev/null
mkdir results/$dt
mkdir results/$dt/eco_ea
mkdir results/$dt/naive
mkdir results/$dt/src
for i in $(seq $1)
do
  cd $rootFolder/results/$dt
  let j=i-1
  cd eco_ea
  mkdir $j
  cd $j
  mv $rootFolder/trial_eco_ea_score_$j.csv ./Score.csv
  mv $rootFolder/trial_eco_ea_tasks_$j.csv ./TasksOverall.csv
  mv $rootFolder/trial_eco_ea_best_tasks_$j.csv ./TasksBest.csv
  mv $rootFolder/trial_eco_ea_$j.txt ./LastGen.txt
  mv $rootFolder/trial_eco_ea_best_$j.txt ./Best.txt
  cp $rootFolder/viz.py ./viz.py
  R < $rootFolder/viz.r --vanilla $rootFolder/results/$dt/eco_ea/$j > /dev/null
  cd $rootFolder/results/$dt/naive
  mkdir $j
  cd $j
  mv $rootFolder/trial_naive_score_$j.csv ./Score.csv
  mv $rootFolder/trial_naive_tasks_$j.csv ./TasksOverall.csv
  mv $rootFolder/trial_naive_best_tasks_$j.csv ./TasksBest.csv
  mv $rootFolder/trial_naive_$j.txt ./LastGen.txt
  mv $rootFolder/trial_naive_best_$j.txt ./Best.txt
  cp $rootFolder/viz.py ./viz.py
  R < $rootFolder/viz.r --vanilla $rootFolder/results/$dt/naive/$j > /dev/null 
  rm $rootFolder/results/$dt/naive/$j/Rplots.pdf  > /dev/null
  cd $rootFolder/results/$dt
  echo "Visualizations done for trial #$j"
done
cp $rootFolder/*.cpp $rootFolder/results/$dt/src/
cp $rootFolder/*.h $rootFolder/results/$dt/src/
cp $rootFolder/*.r $rootFolder/results/$dt/src/
cp $rootFolder/*.sh $rootFolder/results/$dt/src/
cp $rootFolder/Makefile $rootFolder/results/$dt/src/Makefile
#rm data.png
echo "Done!"
date
