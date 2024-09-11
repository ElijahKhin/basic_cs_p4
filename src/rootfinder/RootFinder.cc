#include "RootFinder.h"

void RootFinder::CheckArgs() {

	if (!(method_ >= 1 && method_ <= 3))
    throw std::invalid_argument("Error: There is no such method");
	if (eps_ != EPS1 && eps_ != EPS2)
    throw std::invalid_argument("Error: Wrong Epsilon");
	if (!coef_)
    throw std::invalid_argument("Error: Coefficient value can't be 0, it's meaningless");
}

//======================Constructors & Destructors======================

//RootFinder::RootFinder() {
//	method_ = 1, iter_num_ = 0, root_ = 0, eps_ = EPS1, coef_ = 1;
//}
//
//RootFinder::RootFinder(short method_) : method_(method_) {
//	iter_num_ = 0, root_ = 0, eps_ = EPS1, coef_ = 1;
//	CheckArgs();
//}

RootFinder::RootFinder(double eps_, short coef_, short method_)
	: eps_(eps_), coef_(coef_), method_(method_) {
	CheckArgs();
	iter_num_ = 0, root_ = 0;
}

RootFinder::~RootFinder() {}

//======================Accessors And Mutators==========================

double RootFinder::get_root() { return root_; }
double RootFinder::get_eps() { return eps_; }
short RootFinder::get_coef() { return coef_; }
short RootFinder::get_method() { return method_; }

void RootFinder::set_root(double new_value) { root_ = new_value; }

//==========================Private Methods=============================

inline bool RootFinder::isRoot(double value) {
	if (std::abs(value) <= eps_) return true;
	return false;
}

inline static int GetRandom() {
	srand(time(0));
	return rand() % MAX_INT * std::pow(-1, rand() % 2);
}

inline double RootFinder::derivative(double x) {
	return coef_ * sin(x) + 1;
}

inline double RootFinder::func(double x) {
	return x - coef_ * cos(x);
}

inline double RootFinder::GetSecondX(double x_1) {
	double a = func(x_1);
	double b = 0, x_2;

	if (a > 0) {
		while (b >= 0) {
			x_2 = GetRandom();
			b = func(x_2);
		}
	}
	else {
		while (b <= 0) {
			x_2 = GetRandom();
			b = func(x_2);
		}
	} 
	return x_2;
}

void RootFinder::Bisection() {
	double x_1 = GetRandom();
	double x_2 = GetSecondX(x_1);

//	std::cout << "x_1: " << x_1 << " " << "x_2: " << x_2 << std::endl;

	if (isRoot(func(x_1))) root_ = x_1;
	else if (isRoot(func(x_2))) root_ = x_2;
	else {
		for (int i = 0; i < MAX_ITER && !iter_num_; i++) {
			double c = (x_1 + x_2) / 2;
			if (isRoot(func(c))) {
				root_ = c; 
				iter_num_ = i + 1;
			}
			else if (func(x_1) * func(c) < 0) x_2 = c;
			else  x_1 = c;
		}
	}
//	std::cout << "The exact ROOT: " <<  root_ << std::endl;
}

void RootFinder::NewtonRaphson() {
	double x_1 = GetRandom(), x_2;

	if (isRoot(func(x_1))) root_ = x_1;
	else {
		for (int i = 0; i < MAX_ITER && !iter_num_; i++) {
	//		if (derivative(x_1))
			x_2 = x_1 - func(x_1) / derivative(x_1);
			if (isRoot(func(x_2))) {
				root_ = x_2; 
				iter_num_ = i + 1;
			}
			else x_1 = x_2;
		}
	}
//	std::cout << "The exact ROOT: " <<  root_ << std::endl;
}

void RootFinder::GetExecTime(void(RootFinder::*method)()) {
	auto start = std::chrono::high_resolution_clock::now();
	(this->*method)();
	auto end = std::chrono::high_resolution_clock::now();
	exec_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

//===========================Public Methods=============================

void RootFinder::SolveEquation() {
	if (method_ == 1) GetExecTime(&RootFinder::SimpleIterations);
	else if (method_ == 2) GetExecTime(&RootFinder::Bisection);
	else if (method_ == 3) GetExecTime(&RootFinder::NewtonRaphson);
	else 
		throw std::invalid_argument("Error <SolveEquation>: Wrong method index"); 
}

inline static void PrintServiceChar(size_t length, const char serv_ch, const bool nl) {
	while (length--) std::cout << serv_ch;
	if (nl) std::cout << std::endl;
}

static void PrintCell(size_t length, const char* value, short align) {
	short value_length = strlen(value);
	short padding = length - value_length;

	std::cout << std::setprecision(15);
	if (padding < 0) 
		throw std::invalid_argument("Error <PrintCell>: Length of column name exceeds width of cell");
	PrintServiceChar(1, '|', 0);
	if (align == 0) {
		PrintServiceChar(padding, ' ', 0);
		std::cout << value;
	}
	else if (align == 1) {
		int left_padding = padding / 2;
		PrintServiceChar(left_padding, ' ', 0);
		std::cout << value;
		PrintServiceChar(padding - left_padding, ' ', 0);
	}
	else if (align == 2) {
		std::cout << value;
		PrintServiceChar(padding, ' ', 0);
	}
	else
		throw std::invalid_argument("Error <PrintCell>: Wrong 'align' argument");
}

inline static short GetSepLineWidth(char** headers, short cell_width) {
	short num = 0;

	while(headers[num]) num++;
	return num * (cell_width + 1) + 1;
}

inline static void PrintHeader(char** headers, short line_width, short cell_width) {
	PrintServiceChar(line_width, '_', 1);
	for (short i = 0; headers[i]; i++)
		PrintCell(cell_width, headers[i], 1);
	PrintServiceChar(1, '|', 1);
	PrintServiceChar(line_width, '_', 1);
	PrintServiceChar(line_width, '_', 1);
}

inline void RootFinder::PrintMethod(short cell_width) {
	if (method_ == 1) PrintCell(cell_width, "Simple Iterations", 1);
	else if (method_ == 2) PrintCell(cell_width, "Bisection", 1);
	else if (method_ == 3) PrintCell(cell_width, "Newton Raphson", 1);
}

inline void RootFinder::PrintEpsilon(short cell_width) {
	if (eps_ == EPS1)
		PrintCell(cell_width, "10^(-6)", 1);
	else PrintCell(cell_width, "10^(-7)", 1);
}

inline void RootFinder::PrintCoef(short cell_width) {
	if (coef_ == 1)
		PrintCell(cell_width, "1", 1);
	else PrintCell(cell_width, "10", 1);
}

inline void RootFinder::PrintRoot(short cell_width) {
	if (!iter_num_) PrintCell(cell_width, "None", 1);
	else PrintCell(cell_width, std::to_string(root_).c_str(), 1);
}

inline void RootFinder::PrintIter(short cell_width) {
	PrintCell(cell_width, std::to_string(iter_num_).c_str(), 1);
}

inline void RootFinder::PrintExecTime(short cell_width) {
	PrintCell(cell_width, std::to_string(exec_time_.count()).c_str(), 1);
	std::cout << "|" << std::endl;
}

void RootFinder::PrintResult(const bool header) {
	char** headers = ft_split("Method Epsilon Coefficient ROOT Iterations Time(μs)", ' ');
	short cell_width = 20;
	short line_width = GetSepLineWidth(headers, cell_width);

	if (header) PrintHeader(headers, line_width, cell_width);
	PrintMethod(cell_width);
	PrintEpsilon(cell_width);
	PrintCoef(cell_width);
	PrintRoot(cell_width);
	PrintIter(cell_width);
	PrintExecTime(cell_width);
	PrintServiceChar(line_width, '_', 1);
}
