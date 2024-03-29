﻿#define _USE_MATH_DEFINES
#include <iostream>
#include "random_generator.h"
#include <vector>
#include <fstream>
//#include <typeinfo>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;
double f(vector <double> x,double ny)
{
	vector<double> d;
	for (int i = 0; i < ny; i++)
	{
		d.push_back(x[i]);
	}
	return (-20 * exp(-0.2*(sqrt(0.5*(pow(d[0],2)+pow(d[1],2))))) - exp(0.5*(cos(2* M_PI * d[0]) + cos(2 * M_PI * d[1]))) + M_E + 20);
}
double alg()
{
	setlocale(0, "");
	//cout << "Число Эпсилон(точность метода) Epsilon > 0 : ";
	//cin >> E;
	double A = 1, B = 0.5, Y = 2, E = 0.01, K = 1;
	double ox = 0;
	double o = E + 1;
	double n = 2;
	double nx = n + 1;
	double ny = n;
	bool vivod = true;
	bool fullvivod = false;
	vector<double> nole;
	vector<double> res;
	vector<double> xl;
	vector<double> xh;
	vector<double> xt;
	vector<double> xs;
	vector<double> xotr;
	vector<double> xras;
	vector<double> xsz;
	vector<vector<double>> x(nx);
	for (auto& r : x)
		r.resize(ny);
	if (n > pow(ny, 11))
	{
	cout << "Внимание! Максимально возможное количество комбинаций различающихся вершин симплекса для " <<
		n << " точек с " << ny << " вершинами: " << pow(ny, 11) << "\nКоличество точек изменено до максимально возможного значения.\n";
	n = pow(ny, 11);
	nx = n + 1;
	ny = n;
	}
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			x[i][j] = round(rand_uniform(-5, 5));
			if (x[i][j] == -0)
				x[i][j] = 0;
		}
		res.push_back(0);
	}
	for (int i = 0; i < nx; i++)
	{
		for (int g = 0; g < nx; g++)
		{
			if (i == g)
				g++;
			if (g >= nx)
				break;
			while (x[i] == x[g])
			{
				for (int j = 0; j < ny; j++)
				{
					x[i][j] = round(rand_uniform(-1, 3));
					if (x[i][j] == -0)
						x[i][j] = 0;
				}
			}
		}
	}
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			if (x[i][j] == -0)
				x[i][j] = 0;
		}
	}
	for (int i = 0; i < nx; i++)
	{
		for (int g = 0; g < nx; g++)
		{
			if (i == g)
				g++;
			if (g >= nx)
				break;
			if (x[i] == x[g])
				cout << "ошибка: одинаковые вершины x[" << i << "] x[" << g << "]\n";

		}
	}
	for (int i = 0; i < nx; i++)
		res[i] = (f(x[i], ny));
	if (vivod)
	{
		for (int i = 0; i < nx; i++)
		{
			cout << "x" << "[" << i << "]" << " = (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << x[i][j];
				else
					cout << ";" << x[i][j];
			}
			cout << ")\t";
			cout << "res" << "[" << i << "]" << " = " << res[i] << endl;
		}
	}
	for (int j = 0; j < ny; j++)
	{
		xl.push_back(0);
		xh.push_back(0);
		xs.push_back(0);
		xt.push_back(0);
		xotr.push_back(0);
		xsz.push_back(0);
		xras.push_back(0);
		nole.push_back(0);
	}
	ifstream number("launch.txt");
	string bufff;
	number >> bufff;
	number.close();
	ofstream results(bufff + ".txt");
	int func = 0;
	bool ok = false;
	string vershini;
	for (int i = 0; i < nx; i++)
	{
		vershini += "(";
		for (int j = 0; j < ny; j++)
		{
			if (j == 0)
				vershini += to_string(x[i][j]);
			else
			{
				vershini += ";";
				vershini += to_string(x[i][j]);
			}
		}
		vershini += "),\t";
		vershini += to_string(res[i]);
		vershini += "\n";
	}
	vershini += "\n";
	double start_time = clock();
	while (o > E)
	{
		cout << "шаг: " << K << endl;
		for (int i = 0; i < nx; i++)
		{
			for (int j = 0; j < ny; j++)
			{
				res[i] = f(x[i], ny);
				func++;
			}
		}
		for (int i = 0; i < nx; i++)
		{
			if (i >= 1)
			{
				if (min(res[i], res[i - 1]) < f(xl, ny))
				{
					xl = x[i];
					func++;
				}
				else if (max(res[i], res[i - 1]) > f(xh, ny))
				{
					xh = x[i];
					func++;
				}
			}
			else
			{
				xl = x[i];
				xh = x[i];
			}
		}
		for (int i = 0; i < nx; i++)
		{
			if (x[i] != xl && x[i] != xh)
				xs = x[i];
		}
		if (xs == nole)
			xs = xh;
		for (int i = 0; i < nx; i++)
		{
			if (res[i] > f(xl, ny) && res[i] < f(xh, ny) && res[i] > f(xs, ny))
			{
				xs = x[i];
				func++;
			}
		}
		if (fullvivod)
		{
			cout << "_______________________2step______________________________________________\n";
			for (int i = 0; i < nx; i++)
			{
				cout << "x" << "[" << i << "]" << " = (";
				for (int j = 0; j < ny; j++)
				{
					if (j == 0)
						cout << x[i][j];
					else
						cout << ";" << x[i][j];
				}
				cout << ")\t";
				cout << "res" << "[" << i << "]" << " = " << res[i] << endl;
			}
			cout << "xh = " << f(xh, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xh[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xs = " << f(xs, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xs[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xl = " << f(xl, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xl[j];
				else
					cout << ";" << xl[j];
			}
			cout << ")\n";

			cout << "xt = " << f(xt, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xt[j];
				else
					cout << ";" << xt[j];
			}
			cout << ")\n";

			if (K == 1)
				cout << "o = " << 0 << "\n";
			else
				cout << "o = " << o << "\n";

			cout << "xotr = " << f(xotr, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xotr[j];
				else
					cout << ";" << xotr[j];
			}
			cout << ")\n";

			cout << "xsz = " << f(xsz, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xsz[j];
				else
					cout << ";" << xsz[j];
			}
			cout << ")\n";

			cout << "xras = " << f(xras, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xras[j];
				else
					cout << ";" << xras[j];
			}
			cout << ")\n";
			cout << "__________________________________________________________________________\n\n";
		}
		vector <double> sum;
		for (int i = 0; i < ny; i++)
			sum.push_back(0);
		int k = 0;
		for (int i = 0; i < nx; i++)
		{
			k = 0;
			for (int j = 0; j < ny; j++)
			{
				if (x[i] != xh)
				{
					sum[k] += x[i][j];
					k++;
				}
			}
		}
		for (int i = 0; i < ny; i++)
			xt[i] = (1 / n) * sum[i];
		if (fullvivod)
		{
			cout << "_______________________3step______________________________________________\n";
			for (int i = 0; i < nx; i++)
			{
				cout << "x" << "[" << i << "]" << " = (";
				for (int j = 0; j < ny; j++)
				{
					if (j == 0)
						cout << x[i][j];
					else
						cout << ";" << x[i][j];
				}
				cout << ")\t";
				cout << "res" << "[" << i << "]" << " = " << res[i] << endl;
			}
			cout << "xh = " << f(xh, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xh[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xs = " << f(xs, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xs[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xl = " << f(xl, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xl[j];
				else
					cout << ";" << xl[j];
			}
			cout << ")\n";

			cout << "xt = " << f(xt, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xt[j];
				else
					cout << ";" << xt[j];
			}
			cout << ")\n";

			if (K == 1)
				cout << "o = " << 0 << "\n";
			else
				cout << "o = " << o << "\n";

			cout << "xotr = " << f(xotr, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xotr[j];
				else
					cout << ";" << xotr[j];
			}
			cout << ")\n";

			cout << "xsz = " << f(xsz, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xsz[j];
				else
					cout << ";" << xsz[j];
			}
			cout << ")\n";

			cout << "xras = " << f(xras, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xras[j];
				else
					cout << ";" << xras[j];
			}
			cout << ")\n";
			cout << "__________________________________________________________________________\n\n";
		}
		ox = 0;
		for (int i = 0; i < nx; i++)
		{
			ox += pow(f(x[i], ny) - f(xt, ny), 2);
			func += 2;
		}
		o = pow((1 / (n + 1)) * ox, 0.5);
		if (ok)
		{
			for (int i = 0; i < nx; i++)
			{
				vershini += "(";
				for (int j = 0; j < ny; j++)
				{
					if (j == 0)
						vershini += to_string(x[i][j]);
					else
					{
						vershini += ";";
						vershini += to_string(x[i][j]);
					}
				}
				vershini += "),\t";
				vershini += to_string(res[i]);
				vershini += "\n";
			}
			vershini += "\n";
		}
		if (o <= E)
		{
			double end_time = clock();
			cout << "o (" << o << ") <= E (" << E << "), следовательно в качестве приближенного\n" <<
				"решения можно взять наилучшую точку текущего многогранника : ";
			cout << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xl[j];
				else
					cout << ";" << xl[j];
			}
			cout << ")\t = " << f(xl,ny) << "\n";
			results << "Число вычислений значений целевой функции до остановки: " << func << "\n"
				<< "Итоговое решение: (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					results << xl[j];
				else
					results << ";" << xl[j];
			}
			results << ") = " << f(xl,ny) << "\n";
			results << "Время работы алгоритма: " << ((end_time - start_time) / CLOCKS_PER_SEC) << " секунд.\n";
			results << "История поиска:\n" << vershini;
			results.close();
			return o;
		}
		else
			cout << "o (" << o << ") > E (" << E << "), следовательно процесс поиска продолжается.\n";
		if (fullvivod)
		{
			cout << "_______________________4step______________________________________________\n";
			for (int i = 0; i < nx; i++)
			{
				cout << "x" << "[" << i << "]" << " = (";
				for (int j = 0; j < ny; j++)
				{
					if (j == 0)
						cout << x[i][j];
					else
						cout << ";" << x[i][j];
				}
				cout << ")\t";
				cout << "res" << "[" << i << "]" << " = " << res[i] << endl;
			}
			cout << "xh = " << f(xh, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xh[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xs = " << f(xs, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xs[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xl = " << f(xl, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xl[j];
				else
					cout << ";" << xl[j];
			}
			cout << ")\n";

			cout << "xt = " << f(xt, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xt[j];
				else
					cout << ";" << xt[j];
			}
			cout << ")\n";

			if (K == 1)
				cout << "o = " << 0 << "\n";
			else
				cout << "o = " << o << "\n";

			cout << "xotr = " << f(xotr, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xotr[j];
				else
					cout << ";" << xotr[j];
			}
			cout << ")\n";

			cout << "xsz = " << f(xsz, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xsz[j];
				else
					cout << ";" << xsz[j];
			}
			cout << ")\n";

			cout << "xras = " << f(xras, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xras[j];
				else
					cout << ";" << xras[j];
			}
			cout << ")\n";
			cout << "__________________________________________________________________________\n\n";
		}
		for (int i = 0; i < ny; i++)
			xotr[i] = xt[i] + A * (xt[i] - xh[i]);
		if (fullvivod)
		{
			cout << "_______________________5step______________________________________________\n";
			for (int i = 0; i < nx; i++)
			{
				cout << "x" << "[" << i << "]" << " = (";
				for (int j = 0; j < ny; j++)
				{
					if (j == 0)
						cout << x[i][j];
					else
						cout << ";" << x[i][j];
				}
				cout << ")\t";
				cout << "res" << "[" << i << "]" << " = " << res[i] << endl;
			}
			cout << "xh = " << f(xh, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xh[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xs = " << f(xs, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xs[j];
				else
					cout << ";" << xh[j];
			}
			cout << ")\n";

			cout << "xl = " << f(xl, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xl[j];
				else
					cout << ";" << xl[j];
			}
			cout << ")\n";

			cout << "xt = " << f(xt, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xt[j];
				else
					cout << ";" << xt[j];
			}
			cout << ")\n";

			if (K == 1)
				cout << "o = " << 0 << "\n";
			else
				cout << "o = " << o << "\n";

			cout << "xotr = " << f(xotr, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xotr[j];
				else
					cout << ";" << xotr[j];
			}
			cout << ")\n";

			cout << "xsz = " << f(xsz, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xsz[j];
				else
					cout << ";" << xsz[j];
			}
			cout << ")\n";

			cout << "xras = " << f(xras, ny) << " (";
			for (int j = 0; j < ny; j++)
			{
				if (j == 0)
					cout << xras[j];
				else
					cout << ";" << xras[j];
			}
			cout << ")\n";
			cout << "__________________________________________________________________________\n\n";
		}
		ok = true;
		if (f(xotr,ny) <= f(xl,ny))
		{
			func += 2;
			if (vivod)
				cout << "1if" << endl;
			for (int i = 0; i < ny; i++)
				xras[i] = xt[i] + Y * (xotr[i] - xt[i]);
			if (f(xras,ny) < f(xl,ny))
			{
				func += 2;
				if (vivod)
					cout << "1ifif" << endl;
				for (int i = 0; i < nx; i++)
				{
					if (x[i] == xh)
						x[i] = xras;
				}
				K++;
			}
			else if (f(xras,ny) >= f(xl,ny))
			{
				func += 2;
				if (vivod)
					cout << "1elseif" << endl;
				for (int i = 0; i < nx; i++)
				{
					if (x[i] == xh)
						x[i] = xotr;
				}
				K++;
			}
		}
		else if (f(xs,ny) < f(xotr,ny) && f(xotr,ny) <= f(xh,ny))
		{
			func += 4;
			if (vivod)
				cout << "2elseif" << endl;
			for (int i = 0; i < ny; i++)
				xsz[i] = xt[i] + B * (xh[i] - xt[i]);
			for (int i = 0; i < nx; i++)
			{
				if (x[i] == xh)
					x[i] = xsz;
			}
			K++;
		}
		else if (f(xl,ny) < f(xotr,ny) && f(xotr,ny) <= f(xs,ny))
		{
			func += 4;
			if (vivod)
				cout << "3elseif" << endl;
			for (int i = 0; i < nx; i++)
			{
				if (x[i] == xh)
					x[i] = xotr;
			}
			K++;
		}
		else if (f(xotr,ny) > f(xh,ny))
		{
			func += 2;
			if (vivod)
				cout << "4elseif" << endl;
			for (int i = 0; i < nx; i++)
			{
				for (int j = 0; j < ny; j++)
					x[i][j] = xl[j] + 0.5 * (x[i][j] - xl[j]);
			}
			K++;
		}
	}
}
void main()
{
	bool multiruns = true;
	if (multiruns)
	{
		setlocale(0, "");
		char buff[3];
		ifstream launchnumber("launch.txt");
		if (!launchnumber.is_open())
		{
			cout << "Ошибка открытия текстового файла launch.txt\n";
			ofstream launchnumbercreate("launch.txt");
			launchnumbercreate.close();
		}
		launchnumber.getline(buff, 3);
		launchnumber.close();
		if (strlen(buff) < 1)
		{
			cout << "Тексовой файл пуст\nЗаписываю 1 в текстовой файл\n";
			ofstream launchnumber("launch.txt");
			launchnumber << "1";
			launchnumber.close();
		}
		else
		{
			cout << "Запуск № " << buff << "\n";
			alg();
			int ibuff = stoi(buff);
			//cout << "buff = " << buff << " типа: " << typeid(buff).name() << " ibuff = " << ibuff << " типа: " << typeid(ibuff).name() << "\n";
			ibuff++;
			if (ibuff > 40)
				ibuff = 1;
			ofstream launchnumber("launch.txt");
			launchnumber << ibuff;
			launchnumber.close();
		}
	}
	if (!multiruns)
		alg();
}
