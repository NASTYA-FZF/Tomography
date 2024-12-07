#include "pch.h"
#define _USE_MATH_DEFINES
#include "Model.h"
using namespace std;

void GetProjection(std::vector<std::vector<double>> matr, std::vector<double>& proj, double angle)
{
	RotateImage(matr, matr, angle);
	InterpolationMatr(matr, matr, w, h);
	proj.resize(matr.size());
	for (int i = 0; i < proj.size(); i++)
		proj[i] = accumulate(matr[i].begin(), matr[i].end(), 0);
}

void sinogramma::Main(std::vector<std::vector<double>> matr, double minAngle, double maxAngle, double stepAngle)
{
	vector<double> proj;
	int iter = (maxAngle - minAngle) / stepAngle;
	sinog.resize(iter);
	angle.resize(iter);
	for (int a = 0; a < iter; a++)
	{
		angle[a] = a * stepAngle;
		GetProjection(matr, proj, angle[a]);
		sinog[a] = proj;
	}
}

std::vector<std::vector<double>> sinogramma::GetSinogramma()
{
	return sinog;
}

std::vector<double> sinogramma::GetAngle()
{
	return angle;
}


void fft(std::vector<base>& a, bool invert)
{
	int n = (int)a.size();
	if (n == 1)  return;

	vector<base> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i < n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i < n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

void fft2D(std::vector<std::vector<base>>& fourea, bool invert, int _h, int _w)
{
	for (int i = 0; i < _h; i++)
		fft(fourea[i], invert);

	vector<base> vec_help(_h);
	for (int j = 0; j < _w; j++)
	{
		get_column(vec_help, fourea, j, _h);
		fft(vec_help, invert);
		set_column(fourea, vec_help, j, _h);
	}
}

void get_column(std::vector<base>& res, std::vector<std::vector<base>> matr, int num, int _h)
{
	for (int row = 0; row < _h; row++)
	{
		res[row] = matr[row][num];
	}
}

void set_column(std::vector<std::vector<base>>& matr, std::vector<base> vec, int num, int _h)
{
	for (int row = 0; row < _h; row++)
	{
		matr[row][num] = vec[row];
	}
}

void restore::Main(sinogramma my_si)
{
	//берем проекцию - фулье проекции 1Д - отражаем - вставляем в 2Д по формулам - получили 2Д - обратное фурье - получили результат
	int num_p = my_si.sinog.size();
	int it_center = w / 2;
	int cur_h = 0;
	int cur_w = 0;
	int center2D = h / 2;
	double an = 0;
	base center = 0;
	vector<base> spec1D;
	spectr = vector<vector<base>>(h, vector<base>(w));
	for (int p = 0; p < num_p; p++)
	{
		spec1D = vector<base>(my_si.sinog[p].begin(), my_si.sinog[p].end());
		swap_ranges(spec1D.begin(), spec1D.begin() + it_center, spec1D.begin() + it_center + 1);
		fft(spec1D, true);
		center += spec1D[0];
		swap_ranges(spec1D.begin(), spec1D.begin() + it_center, spec1D.begin() + it_center + 1);
		an = my_si.angle[p] * M_PI / 180;
		for (int a = 0; a < w; a++)
		{
			cur_h = cos(an) * (a - it_center) + center2D;
			cur_w = sin(an) * (a - it_center) + it_center;
			if (cur_h < 0 || cur_h >= h)
				cur_h = cur_h < center2D ? 0 : (h - 1);
			if (cur_w < 0 || cur_w >= w)
					cur_w = cur_w < it_center ? 0 : (w - 1);
			spectr[cur_h][cur_w] = spec1D[a];
		}
	}
	spectr[center2D][it_center] = center / (double)num_p;

	fft2D(spectr, false, h, w);
	result = vector<vector<double>>(h, vector<double>(w));
	for (int i = 0; i < h / 2; i++)
	{
		for (int j = 0; j < w / 2; j++)
		{
			result[i][j] = sqrt(spectr[i + h / 2][j + w / 2].real() * spectr[i + h / 2][j + w / 2].real() + spectr[i + h / 2][j + w / 2].imag() * spectr[i + h / 2][j + w / 2].imag());
			result[i + h / 2][j + w / 2] = sqrt(spectr[i][j].real() * spectr[i][j].real() + spectr[i][j].imag() * spectr[i][j].imag());
			result[i + h / 2][j] = sqrt(spectr[i][j + w / 2].real() * spectr[i][j + w / 2].real() + spectr[i][j + w / 2].imag() * spectr[i][j + w / 2].imag());
			result[i][j + w / 2] = sqrt(spectr[i + h / 2][j].real() * spectr[i + h / 2][j].real() + spectr[i + h / 2][j].imag() * spectr[i + h / 2][j].imag());
		}
	}
}

std::vector<std::vector<double>> restore::GetRes()
{
	return result;
}
