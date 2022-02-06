#zmien2
for i in "$@"
do
	n=`printf "$i" | tr -c "[:alnum:]" [_*]`
	echo "zamieniono "$i" "$n""
	# Ponizsza linijka moze zostac zakomentowana w celu latwiejszego testowania.
	mv "$i" "$n"
	
done


