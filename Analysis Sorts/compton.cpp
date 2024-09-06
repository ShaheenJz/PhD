#include<iostream>

using namespace std;




double compton(double energy){

double emasskg, emass, ecompton, echarge, c;

emass = 511000;
emasskg = 9.10938356E-31;
echarge = 1.602176634E-19;
c = 299792458;

energy = energy*1000;


ecompton = (2*energy*energy)/(2*energy+emass);

ecompton = ecompton/1000;

return ecompton;

}

int main(int argc, char *argv[])
{
	double E;

	E =  atof(argv[1]);

	cout << "The compton edge for a gamma ray of energy " << E << " keV sits at " << compton(E) << " keV" <<  endl;
  return 0;
}
