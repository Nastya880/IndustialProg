#include "Header.h"

using namespace std;

string to_str(double val)
{
	char val_str[20] = { 0 };
	snprintf(val_str, sizeof(val_str), "%.0lf", val);
	return val_str;
}

 string AnyX(double y)
{
	string y_str = to_str(y);
	return "4 " + y_str;
}

string AnyY(double x)
{
	string x_str = to_str(x);
	return "3 " + x_str;
}

string EndlessAnswers(double firstArg, double SecondArg, double ThirdArg)
{
	string first_number_str = to_str(-firstArg / SecondArg);
	string second_number_str = to_str(ThirdArg / SecondArg);
	return "1 " + first_number_str + " " + second_number_str;
}

string Solve(double a, double b, double c, double d, double e, double f, string output)
{
	double firstComposition = a * d - c * b;
	double secondComposition = e * d - b * f;
	double thirdComposition = a * f - c * e;

	if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
	{
		output = "5";
	}
	else if ((firstComposition != 0) && ((secondComposition != 0) || (thirdComposition != 0)))
	{
		string y = to_str(thirdComposition / firstComposition);
		string x = to_str(secondComposition / firstComposition);
		output = "2 " + x + " " + y;
	}
	else if (((firstComposition == 0) && ((secondComposition != 0) || (thirdComposition != 0))) ||
		(a == 0 && c == 0 && e / b != f / d) ||
		(b == 0 && d == 0 && e / a != f / c) ||
		(a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
	{
		if ((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
			(c == 0 && d == 0 && f == 0 && b != 0 && a == 0))
		{
			if (b == 0)
				output = AnyX(f / d);
			else if (d == 0)
				output = AnyX(e / b);
			else if (e == 0 || f == 0)
				output = AnyX(0);
		}
		else if ((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
			(c == 0 && d == 0 && f == 0 && a != 0 && b == 0))
		{
			if (a == 0)
				output = AnyY(f / c);
			else if (c == 0)
				output = AnyY(e / a);
			else if (e == 0 || f == 0)
				output = AnyY(0);
		}
		else
			output = "0";
	}
	else if (a == 0 && c == 0)
	{
		if (e == 0)
			output = AnyX(f / d);
		else if (f == 0)
			output = AnyX(e / b);
		else
			output = AnyX(e / b);
	}
	else if (b == 0 && d == 0)
	{
		if (e == 0)
			output = AnyY(f / c);
		else if (f == 0)
			output = AnyY(e / a);
		else
			output = AnyY(e / a);
	}
	else if (b == 0 && e == 0)
	{
		output = EndlessAnswers(c, d, f);
	}
	else if (d == 0 && f == 0)
	{
		output = EndlessAnswers(a, b, e);
	}
	else if (a == 0 && e == 0)
	{
		output = EndlessAnswers(d, c, f);
	}
	else if (c == 0 && f == 0)
	{
		output = EndlessAnswers(b, a, e);
	}
	else if ((a / b == c / d))
	{
		output = EndlessAnswers(c, d, f);
	}
	else
	{
		output = "Are you kidding me?";
	}

	return output;
}

int main()
{
	double a, b, c, d, e, f;
	string output = "";

	cin >> a >> b >> c >> d >> e >> f;

	output = Solve(a, b, c, d, e, f, output);

	cout << output;
	
	return 0;
}
