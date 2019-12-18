#include <vector>
#include <iostream>

double DerivativeIntercept(std::pair<double, double> pares, double b, double m)
{
	//Squared residuals=(yO-yP)^2
	//where yO is observed data or real data and yP is predicted data and yP=m*xO+b
	//so Squared Residuals=(yO-(m*xO+b))^2 
	//dSum of squared residuals/dIntercept=-2*(y-(b+m*x))
	return -2 * (pares.second - (b + m * pares.first));
}

double DerivativeSlope(std::pair<double, double> pares, double b, double m)
{
	return -2 * pares.first * (pares.second - (b + m * pares.first));
}

std::pair<double, double> Gradient(std::vector<std::pair<double, double>> data)
{
	//y=m*x+b;
	double b = 0;
	double m = 1;
	double sumI = 0.00;
	double sumS = 0.00;
	double stepsizeintercept = 1;
	double stepsizeslope = 1;
	//change the learning rate when the answer is cannot be determined (-nan(ind))
	double learningrate = 0.0001;
	int steps = 0;
	while (abs(stepsizeintercept) > 0.00000000000000001 && abs(stepsizeslope) > 0.0000000000000001)
	{
		sumI = 0.00;
		sumS = 0.00;
		for (int i = 0; i < data.size(); i++)
		{
			sumI += DerivativeIntercept(data.at(i), b, m);
			sumS += DerivativeSlope(data.at(i), b, m);
		}
		stepsizeintercept = sumI * learningrate;
		double oldIntercept = b;
		b = oldIntercept - stepsizeintercept;
		stepsizeslope = sumS * learningrate;
		double oldSlope = m;
		m = oldSlope - stepsizeslope;
		steps++;
	}
	return { steps,m };
}


int main()
{
	std::vector<std::pair<double, double>> i = { {0.5,1.4},{2.3,1.9},{2.9,3.2},{5.5,6.0},{10,6.6},{5,4},{7.7,6.2},{9.0,10.1},{2.3,10.1},{4.5,5.4} };
	std::vector<std::pair<double, double>> j = { {0.5,1.4},{2.3,1.9},{2.9,3.2} };
	std::cout << "Kahabog: " << Gradient(i).second << "	Intersyepto: " << Gradient(i).first << std::endl;
	return 0;
}
