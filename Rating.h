#pragma once
#include <iostream>
#include <stdexcept>

class Rating{
protected:
	float average_rate;
	int rate_sum;
	int rate_quant;
public:
	Rating();
	Rating(float general_rate);
	void calculateAverage();
	float getAverage() const;

	Rating& operator+=(int new_rate);
};