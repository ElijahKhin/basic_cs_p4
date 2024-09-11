#ifndef ROOT_DATA_H
#define ROOT_DATA_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <chrono>

#include "../common/libft.h"

#define MAX_ITER 100000000
#define EPS1 0.0000010
#define EPS2 0.0000001

class RootFinder {
	public:
		/* Constructors & Destructors */  
//  	RootFinder();
//  	RootFinder(short method_);
  	RootFinder(double eps_, short coef_, short method_);
  	~RootFinder();

  	/* Accessors*/  
		double get_root();
		double get_eps();
		short get_coef();
		short get_method();

  	/* Mutators */  
		void set_root(double new_value);

  	//	Main Public Methods
		void SolveEquation();
  	void PrintResult(const bool header);
		
		// Public Attributes
		int iter_num_ = 0;


	private:

		std::chrono::duration<long, std::milli> exec_time_;
		double root_, eps_;
  	short coef_, method_;
		void CheckArgs();

		void SimpleIterations();
		void Bisection();
		void NewtonRaphson();

		inline double func(double x);
		inline double derivative(double x);
		inline double GetSecondX(double x_1);
		bool isRoot(double value);
		void GetExecTime(void(RootFinder::*)());
		inline void PrintMethod(short cell_width);
		inline void PrintEpsilon(short cell_width);
		inline void PrintCoef(short cell_width);
		inline void PrintRoot(short cell_width);
		inline void PrintIter(short cell_width);
		inline void PrintExecTime(short cell_width);

};

#endif
