BEGIN {FS = ","}
{
if (NR == 1){
val[NR] = $6;
}
else{
	zmienna = val[NR-1] + $4;
	#if(zmienna === $6){print val[NR-1],$4,$6;}
	if(zmienna != $6){
	print "\t", zmienna, "!=", $6, "BLAD W LINII:", NR;}
	val[NR] = $6
}}
END{};
