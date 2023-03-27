#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <conio.h>

using namespace std;


vector<char> input_char(char end)
{
	int i;
	vector<char> char_array;
	char_array.clear();

	for (i = 0; i != -1; i++)
	{
		char sim = _getch();
		if (sim != end)
		{
			if (sim == '\b' && char_array.size() != 0)
			{
				cout << sim << ' ' << sim;
				char_array.pop_back();
			}
			if (sim == '-' || sim >= '0' && sim <= '9')
			{
				cout << sim;
				char_array.push_back(sim);
			}
		}
		else
		{
			if (end == '\r')
			{
				cout << endl;
			}
			else
			{
				cout << end;
			}
			i = -2;
		}
	}

	return char_array;
}

string str_check(vector<char> num)
{
	int negat = -1;
	string number(num.begin(), num.end());
	negat = number.find_first_of('-', 1);
	if (negat > 0)
	{
		number = "";
		return number;
	}

	if (number != "0")
	{
		int p = number.find_first_not_of('0', 0);
		if ((p > 0) || (p > 1 && negat == 0))
		{
			number = "";
			return number;
		}
	}
	return number;
}

bool correct_inp(string number)
{
	bool inp;
	int s = size(number);

	if (number == "" || s > 12)
	{
		cout << endl << "Error. Write again: ";
		inp = 1;
	}
	else
	{
		inp = 0;
	}
	return inp;
}

double write_int()
{ 
	int a = 0;
	int max_size = 12;
	bool inp = 1;

	while (inp == 1)
	{
		vector<char> input_int = input_char('\r');
		string number = str_check(input_int);
		inp = correct_inp(number);
		if (inp == 0)
		{
			a = stod(number);
		}
	}
	return a;
}

double input_limit(char end_number)
{
	int a = 0;
	int max_size = 12;
	bool inp = 1;

	while (inp == 1)
	{
		vector<char> input_int = input_char(end_number);
		string number = str_check(input_int);
		inp = correct_inp(number);
		if (inp == 0)
		{
			a = stod(number);
		}
	}

	return a;
}

double sum(const vector<double>& right, const vector<double>& left)
{
	double sum = 0;
	for (int i = 0; i < right.size(); i++)
	{
		sum += (right[i] - left[i]);
	}
	return sum;
}

int main()
{
	bool begin = true;
	while (begin)
	{
		double num_segments;
		bool inp = true;
		cout << "Input the number of segments (>1) = ";

		while (inp == true)
		{
			num_segments = write_int();
			if (num_segments <= 1 || num_segments - (int)num_segments != 0)
			{
				cout << "Error. Write positive integer! ";
			}
			else
			{
				inp = false;
			}
		}

		vector<double> left_limits;
		vector<double> right_limits;

		for (int i = 0; i < num_segments; i++)
		{
			double l, r;
			inp = true;

			while (inp == true)
			{
				cout << "Segmet " << i + 1 << ": ";

				l = input_limit(' ');
				r = input_limit('\r');
				left_limits.push_back(l);
				right_limits.push_back(r);

				if (r <= l)
				{
					cout << "Right limit greater than or equal to left limit" << endl;
					inp = true;
				}
				else
				{
					inp = false;
				}
			}

			for (int k = 0; k < left_limits.size() - 1; k++)
			{
				if (l >= left_limits[k])
				{
					if (l <= right_limits[k])
					{
						if (r > right_limits[k])
						{
							right_limits[k] = r;
							right_limits.pop_back();
							left_limits.pop_back();
						}
						else
						{
							right_limits.pop_back();
							left_limits.pop_back();
						}
					}
				}
				else
				{
					if (r > right_limits[k])
					{
						right_limits[k] = r;
						left_limits[k] = l;
						right_limits.pop_back();
						left_limits.pop_back();
					}
					else
					{
						if (r >= left_limits[k])
						{
							left_limits[k] = l;
							right_limits.pop_back();
							left_limits.pop_back();
						}
					}
				}
			}
		}

		cout << "Result: " << sum(right_limits, left_limits);

		char end = 0;
		cout << endl << "Continue(Y/N)? ";

		while (end != 'y' && end != 'n' && end != 'Y' && end != 'N' && end != 'í' && end != 'Í' && end != 'ò' && end != 'Ò')
		{
			end = _getch();
		}
		cout << end << endl;
		begin = (end == 'y' || end == 'Y' || end == 'Í' || end == 'í');
	}
}