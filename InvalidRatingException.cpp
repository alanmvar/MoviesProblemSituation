#include "InvalidRatingException.h"

InvalidRatingException::InvalidRatingException(int rating) {
    message = "Error: " + to_string(rating) + " is not a valid rating. Must be between 1 and 5.";
};
const char* InvalidRatingException::what() const noexcept {
    return message.c_str();
};
