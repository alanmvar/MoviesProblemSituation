#pragma once

class Rating
{
private:
	int rate;
	float average;
	int rateSum;
	int rateQuant;
public:
	Rating();
	void setRate(int rated);
	int getRates();
	void calculateAverage();
	float getAverage();
};

