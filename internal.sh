#!/bin/bash

var=10000

for j in Bots/run_my2.sh Bots/run_my3.sh Bots/run.sh Bots/run_my1.sh 
do
    for i in  Bots/run_my3.sh Bots/run.sh Bots/run_my1.sh Bots/run_my2.sh
    do
        echo 5,5 Player 1 = $j, Opp = $i >> Learn/log55.txt
        echo python server.py $var -n 5 -s 5 -NC 2 -TL 120 -LOG server.log
        python server.py $var -n 5 -s 5 -NC 2 -TL 120 -LOG server.log > Learn/log11.txt&
        sleep 0.1s

        python client.py 0.0.0.0 $var $j &

        sleep 0.1s
        python client.py 0.0.0.0 $var $i  
        sleep 1s
        pkill -9 python
        
        let "var++"

        echo $var
        echo Awake
        
        tail -1 Learn/log11.txt | head -1 >> Learn/log55.txt

        echo Next

        echo 6,5 Player 1 = $j, Opp = $i >> Learn/log65.txt
        python server.py $var -n 6 -s 5 -NC 2 -TL 150 -LOG server.log > Learn/log21.txt&
        sleep 0.1s
        python client.py 0.0.0.0 $var $j &
        sleep 0.1s
        python client.py 0.0.0.0 $var $i  
        sleep 1s
        pkill -9 python
        # source kill_python.sh
        
        let "var++"
        echo $var
        echo Awake

        tail -1 Learn/log21.txt | head -1 >> Learn/log65.txt

        echo Next


        echo 6,6 Player 1 = $j, Opp = $i >> Learn/log66.txt
        python server.py $var -n 6 -s 6 -NC 2 -TL 180 -LOG server.log > Learn/log31.txt&
        sleep 0.1s
        python client.py 0.0.0.0 $var $j &
        sleep 0.1s
        python client.py 0.0.0.0 $var $i  
        sleep 1s
        pkill -9 python
        # source kill_python.sh
        
        let "var++"
        echo $var
        echo Awake

        tail -1 Learn/log31.txt | head -1 >> Learn/log66.txt

        echo Next
    done
done