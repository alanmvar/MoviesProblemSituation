#pragma once

class Rating
{
protected:
	float averageRate;
	int rateSum;
	int rateQuant;
public:
	Rating(float generalRate);
	void setRate(int rated);
	int getRates();
	void calculateAverage();
	float getAverage();
};

