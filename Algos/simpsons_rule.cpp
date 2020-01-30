//############################### SIMPSONS RULE ####################################

double f(double x){	}

//simpsons rule
double integral(double a, double b){
	int n = 10000; //even
	double I = f(a)+f(b), h=(b-a)/n;
	for(int i=1; i<n; i++)
		I += ((i%2==0) ? 2:4) * f(a+h*i);
	return I*h/3;
}
