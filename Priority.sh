#!/bin/bash

echo -n "Enter the number of processes: "
read n

# Arrays to store values
declare -a pid
declare -a burst
declare -a priority
declare -a waiting
declare -a turnaround

# Input burst time and priority
for (( i=0; i<n; i++ ))
do
    echo -n "Enter Burst Time and Priority for Process $i: "
    read burst[$i] priority[$i]
    pid[$i]=$i
done

# Sort processes based on priority (lower number = higher priority)
for (( i=0; i<n; i++ ))
do
    for (( j=i+1; j<n; j++ ))
    do
        if [ ${priority[$i]} -gt ${priority[$j]} ]
        then
            # Swap priority
            temp=${priority[$i]}
            priority[$i]=${priority[$j]}
            priority[$j]=$temp

            # Swap burst
            temp=${burst[$i]}
            burst[$i]=${burst[$j]}
            burst[$j]=$temp

            # Swap pid
            temp=${pid[$i]}
            pid[$i]=${pid[$j]}
            pid[$j]=$temp
        fi
    done
done

# Calculate waiting time and turnaround time
waiting[0]=0
turnaround[0]=${burst[0]}

for (( i=1; i<n; i++ ))
do
    waiting[$i]=${turnaround[$((i-1))]}
    turnaround[$i]=$(( waiting[$i] + burst[$i] ))
done

# Print output
echo
echo "PROCESS  PRIORITY  BURST TIME  WAITING TIME  TURNAROUND TIME"
total_wait=0
total_turn=0
for (( i=0; i<n; i++ ))
do
    echo "${pid[$i]}        ${priority[$i]}         ${burst[$i]}         ${waiting[$i]}            ${turnaround[$i]}"
    total_wait=$(( total_wait + waiting[$i] ))
    total_turn=$(( total_turn + turnaround[$i] ))
done

# Calculate averages
avg_wait=$(echo "scale=2; $total_wait / $n" | bc)
avg_turn=$(echo "scale=2; $total_turn / $n" | bc)

echo
echo "Average Waiting Time is --- $avg_wait"
echo "Average Turnaround Time is --- $avg_turn"
