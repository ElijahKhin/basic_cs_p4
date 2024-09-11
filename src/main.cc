#include "rootfinder/RootFinder.h"

int main(void) {
	double eps[2] {EPS1, EPS2};
	short coef[2] {1, 10};
	short method[3] {1, 2, 3};


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
//				std::cout << "wtf" << std::endl;
				RootFinder equation(eps[j], coef[k], method[i]);
				equation.SolveEquation();
				if (!i && !j && !k) equation.PrintResult(1);
				else equation.PrintResult(0);
			}
		}
	}
}
