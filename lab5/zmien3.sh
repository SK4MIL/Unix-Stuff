#zmien3
for i in "$@"
do
if expr "$i" : ".*\.txt$" > /dev/null 
then
	mv $i `echo $i | sed s/.txt/_org.txt/`
else
	echo "Brak .txt "$i""
fi 
done
#echo `find ~/Pulpit/lab5/Test/ -name  *.txt -exec basename {} \;` 

#find ~/Pulpit/lab5/Test/ -name *.txt -exec basename {} ;


#find ~/Pulpit/ -type f -iname "lab*" -exec basename {} \;
