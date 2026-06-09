#include "Rating.h"
#include "InvalidRatingException.h"

Rating::Rating() {
    average_rate = 0.0f;
    rate_sum = 0;
    rate_quant = 0;
}

Rating::Rating(float general_rate) {
    average_rate = general_rate;
    rate_sum = static_cast<int>(general_rate);
    rate_quant = 1;
}

void Rating::calculateAverage() {
    if (rate_quant > 0) {
        average_rate = static_cast<float>(rate_sum) / rate_quant;
    }
    else {
        average_rate = 0.0f;
    }
}

float Rating::getAverage() const {
    return average_rate;
}

Rating& Rating::operator+=(int new_rate) {
    if (new_rate < 1 || new_rate > 5) {
        throw InvalidRatingException(new_rate); 
    }
    rate_sum += new_rate;
    rate_quant++;
    calculateAverage();
    return *this;
}