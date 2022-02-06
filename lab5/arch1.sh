#brak mozliwosci tworzenia plikow
#mkdir -p "$Home/.arch"

if test "$#" -eq 1
then
 rozsz="$1"
 echo "Szukane rozszerzenie: $rozsz"
 for plik in *$rozsz
 do
	#echo $plik
	cp -p "$plik" ~/.arch/`echo "$plik" | sed s/$rozsz$/_arch$rozsz/`
 done

else
 echo "Zla liczba argumentwo, podaj jeden"
fi

