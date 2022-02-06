#policz3
flagi='-1'

if test "$#" -eq 0
then
	ls $flagi | wc -l
elif test "$1" = '-a'
then	
	flagi='-1 -a'
fi
for i in "$@"
do
	ls $"$i" $flagi | wc -l
done

 
 

