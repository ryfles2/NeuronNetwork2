#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
using namespace std;

double fNet(double x[], double w[], bool bias) 
{
	double net = 0.0;
	for (int i = 0; i < 2; i++)
	{
		net += x[i] * w[i];
	}
	if (bias == true)
	{
		net += w[2];
	}
	return net;
}
void fProgowa(double net, ofstream & out)
{
	if (net >= 0.0) 
	{
		out << ("255 0 0 ");
	}
	else {
		out << ("0 0 255 ");
	}
}
void fLiniowa(double net, ofstream & out)
{
	if (net<-2)
	{
		out << ("0 10 92 ");
	}
	else if (net>-2 && net<-0) 
	{
		out << ("255 115 197 ");
	}
	else if (net >= 0 && net<2) 
	{
		out << ("25 255 25 ");
	}
	else
	{
		out << ("246 255 0 ");
	}
}
void fSigmoidalna(double net, ofstream & out) 
{
	double sign = 1.0 / (1 + exp(-net));

	if (sign>0 && sign <= 0.25)
	{
		out << ("0 10 92 ");
	}
	else if (sign>0.25 && sign <= 0.5)
	{
		out << ("255 115 197 ");
	}
	else if (sign>0.5 && sign <= 0.75)
	{
		out << ("25 255 25 ");
	}
	else 
	{
		out << ("246 255 0 ");
	}
}
void fProgowa2w(double neuron2w[], double x2ww[], bool bias, ofstream & out)
{
	double y[2];
	double wynik = 0.0;
	for (int i = 0; i < 2; i++)
	{
		if (neuron2w[i] >= 0)
		{
			y[i] = 1.0*x2ww[i];
		}
		else
		{
			y[i] = 0.0;
		}
		wynik += y[i];
	}
	if (bias == true)
	{
		wynik += x2ww[2];
	}
	if (wynik >= 0.0)
	{
		out << ("255 0 0 ");
	}
	else
	{
		out << ("0 0 255 ");
	}

}
void fSigmoidalna2w(double neuron2w[], double x2ww[], bool bias, ofstream & out)
{
	double y[2];
	double wynik = 0.0;
	for (int i = 0; i<2; i++) 
	{
		y[i] = neuron2w[i] * x2ww[i];
		wynik += 1.0 / (1 + exp(-y[i]));
	}
	if (bias = true) {
		wynik += 1.0 / (1 + exp(x2ww[2]));
	}
	double sign = 1.0 / (1 + exp(-wynik));
	if (sign>0 && sign <= 0.25) {
		out << ("0 10 92 ");
	}
	else if (sign>0.25 && sign <= 0.5) {
		out << ("255 115 197 ");
	}
	else if (sign>0.5 && sign <= 0.75) {
		out << ("25 255 25 ");
	}
	else {
		out << ("246 255 0 ");;
	}
}
int main()
{
	srand(time(NULL));
	ofstream Progowa;
	ofstream Liniowa;
	ofstream Sigmoidalna;
	ofstream ProgowaBias;
	ofstream LiniowaBia;
	ofstream SigmoidalnaBia;
	ofstream Progowa2w;
	ofstream Liniowa2w;
	ofstream Sigmoidalna2w;
	ofstream ProgowaBias2w;
	ofstream LiniowaBias2w;
	ofstream SigmoidalnaBias2w;

	Progowa.open("Progowa.ppm");
	Progowa << "P3\n400 400\n255\n";
	Liniowa.open("Liniowa.ppm");
	Liniowa << "P3\n400 400\n255\n";
	Sigmoidalna.open("Sigmoidalna.ppm");
	Sigmoidalna << "P3\n400 400\n255\n";
	ProgowaBias.open("ProgowaBias.ppm");
	ProgowaBias << "P3\n400 400\n255\n";
	LiniowaBia.open("LiniowaBia.ppm");
	LiniowaBia << "P3\n400 400\n255\n";
	SigmoidalnaBia.open("SigmoidalnaBia.ppm");
	SigmoidalnaBia << "P3\n400 400\n255\n";
	Progowa2w.open("Progowa2w.ppm");
	Progowa2w << "P3\n400 400\n255\n";
	Liniowa2w.open("Liniowa2w.ppm");
	Liniowa2w << "P3\n400 400\n255\n";
	Sigmoidalna2w.open("Sigmoidalna2w.ppm");
	Sigmoidalna2w << "P3\n400 400\n255\n";
	ProgowaBias2w.open("ProgowaBias2w.ppm");
	ProgowaBias2w << "P3\n400 400\n255\n";
	LiniowaBias2w.open("LiniowaBias2w.ppm");
	LiniowaBias2w << "P3\n400 400\n255\n";
	SigmoidalnaBias2w.open("SigmoidalnaBias2w.ppm");
	SigmoidalnaBias2w << "P3\n400 400\n255\n";

	double x[] = { -2.0, -2.0 };
	double xBias[] = { -2.0,-2.0 };
	double neuron2w[] = { 0.0,0.0 };
	double xw[] = { 0.0,0.0,0.0 };
	double xw2[] = { 0.0,0.0,0.0 };
	double x2ww[] = { 0.0,0.0,0.0 };

	double pixel = 0.01;
	//wagi s¹ od -1 do 1
	for (int i = 0; i<3; i++)
	{
		xw[i] = ((double)rand() / RAND_MAX * 2.0) - 1.0;
		x2ww[i] = ((double)rand() / RAND_MAX * 2.0) - 1.0;
		xw2[i] = ((double)rand() / RAND_MAX * 2.0) - 1.0;
	}
	
	double output = 0.0;        double outputBias = 0.0;
	double output2w = 0.0;
	double output2wBias = 0.0;
	for (int i = 0; i<400; i++) 
	{
		for (int j = 0; j<400; j++)
		{

			//Sieæ jednowarstwowa bez sygna³u bias
			output = fNet(x, xw, false);


			fProgowa(output, Progowa);
			fLiniowa(output, Liniowa);
			fSigmoidalna(output, Sigmoidalna);

			//Sieæ jednowarstwowa z sygna³em bias
			outputBias = fNet(xBias, xw, true);
			

			fProgowa(outputBias, ProgowaBias);
			fLiniowa(outputBias,LiniowaBia);
			fSigmoidalna(outputBias,SigmoidalnaBia);

			//Sieæ dwuwarstwowa bez sygna³u bias
			neuron2w[0] = fNet(x, xw, false);
			neuron2w[1] = fNet(x, xw2, false);
			output2w = fNet(neuron2w, x2ww, false);

			fProgowa2w(neuron2w, x2ww, false, Progowa2w);
			fLiniowa(output2w, Liniowa2w);
			fSigmoidalna2w(neuron2w, x2ww, false, Sigmoidalna2w);

			//Sieæ dwuwarstwowa z sygna³em bias
			neuron2w[0] = fNet(xBias, xw, true);
			neuron2w[1] = fNet(xBias, xw2, true);
			output2wBias = fNet(neuron2w, x2ww, true);

			fProgowa2w(neuron2w, x2ww, true, ProgowaBias2w);
			fLiniowa(output2wBias, LiniowaBias2w);
			fSigmoidalna2w(neuron2w, x2ww, true, SigmoidalnaBias2w);


			x[0] += pixel;
			xBias[0] += pixel;


		}
		x[0] = -2.0;
		xBias[0] = -2.0;
		x[1] += pixel;
		xBias[1] += pixel;

	}
	Progowa.close();
	Liniowa.close();
	Sigmoidalna.close();
	ProgowaBias.close();
	LiniowaBia.close();
	SigmoidalnaBia.close();
	Progowa2w.close();
	Liniowa2w.close();
	Sigmoidalna2w.close();
	ProgowaBias2w.close();
	LiniowaBias2w.close();
	SigmoidalnaBias2w.close();

	return 0;
}


