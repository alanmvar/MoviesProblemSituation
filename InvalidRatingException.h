#pragma once
#include <exception>
#include <string>

using namespace std;

class InvalidRatingException : public exception {
    private:
        string message;
    public:
        InvalidRatingException(int rating);
        const char* what() const noexcept override;
    };



