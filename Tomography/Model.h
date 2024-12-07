#pragma once
#include <vector>
#include <numeric>
#include <complex>
#include <algorithm>
typedef std::complex<double> base;

void GetProjection(std::vector<std::vector<double>> matr, std::vector<double>& proj, double angle);

void RotateImage(std::vector<std::vector<double>> matr, std::vector<std::vector<double>>& res, double angle);

void InterpolationMatr(std::vector<std::vector<double>>& result, std::vector<std::vector<double>> _image, double w, double h);

const int h = 512;
const int w = 512;

class sinogramma
{
	friend class restore;
	std::vector<std::vector<double>> sinog;
	std::vector<double> angle;
public:
	void Main(std::vector<std::vector<double>> matr, double minAngle, double maxAngle, double stepAngle);
	std::vector<std::vector<double>> GetSinogramma();
	std::vector<double> GetAngle();
};

void fft(std::vector<base>& a, bool invert);

void fft2D(std::vector<std::vector<base>>& fourea, bool invert, int _h, int _w);

void get_column(std::vector<base>& res, std::vector<std::vector<base>> matr, int num, int _h);

void set_column(std::vector<std::vector<base>>& matr, std::vector<base> vec, int num, int _h);

class restore
{
	std::vector<std::vector<double>> result;
	std::vector<std::vector<base>> spectr;
public:
	void Main(sinogramma my_si);
	std::vector<std::vector<double>> GetRes();
};