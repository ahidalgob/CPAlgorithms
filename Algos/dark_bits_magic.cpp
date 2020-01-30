uint next_mask(uint mask){
	uint t = mask | (mask - 1);
	return  (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(mask) + 1));
}
// Iterar sobre todos las mascaras de tamano N con m bits prendidos
int N=4, m=2;
int mask=(1<<m)-1;
for(int mask=(1<<m)-1; !(mask & (1<<N)); mask=next_mask(mask)){
	
}

//Iterar sobre todas las submascaras de mask de forma creciente (si incluye vacio)
for(int sub = 0 ; sub = sub - mask & mask ;) {
	
}

//Iterar sobre todas las submascaras de mask de forma decreciente (no incluye vacio)
for(int sub = (mask-1) & mask ; sub; sub = (sub-1) & mask )  {
	
}
