#zmien1
for i in "$@"
do
	n=`echo "$i" | tr "[A-Z]" "[a-z]"` 
	echo "Zmieniono "$i" na "$n""
	#Mozna zakomentowac ponizsza linijke, zeby skrypt jedynie mowil co robi, ulatwia testowanie. 
	mv "$1" "$n"
done
