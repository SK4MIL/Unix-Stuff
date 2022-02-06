
zmienna=5

if test "$#" -eq 0 
then
	echo Brak argumentu 
else
	zmienna=$1
fi

while true
do
	clear
	date +'%H:%M:%S'
	sleep $zmienna
done

