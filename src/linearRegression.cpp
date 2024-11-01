#include "linearRegression.h"


LinearRegression::LinearRegression( const std::vector<std::variant<std::string, double>>& x, const std::vector<std::variant<std::string, double>>& y){


    

    if (x.size() != y.size()){
        throw std::invalid_argument("Input vectors must have the same size");
    }

    // try to change to double vector, if error return error message
    try{
        for (size_t i = 0; i < x.size(); i++){
            this->x.push_back(std::get<double>(x[i]));
            this->y.push_back(std::get<double>(y[i]));
        }
    } catch (const std::bad_variant_access& e){
        throw std::invalid_argument("Input vectors must contain only doubles");
    }
    

    double sumX = 0;
    double sumY = 0;

    for (size_t i = 0; i < x.size(); i++){
        sumX += this->x[i];
        sumY += this->y[i];
    }

    this->meanX = sumX / x.size();
    this->meanY = sumY / y.size();

    sumX = 0;
    sumY = 0;

    for (size_t i = 0; i < x.size(); i++){
        sumX += (this->x[i] - this->meanX);
        sumY += (this->y[i] - this->meanY);
    }

    this->stdDevX = sumX / x.size();
    this->stdDevY = sumY / y.size();


}

void LinearRegression::findCoefficients(){

    double numerator = 0;
    double denominator = 0;

    for (size_t i = 0; i < x.size(); i++){
        numerator += (x[i] - this->meanX) * (y[i] - this->meanY);
        denominator += (x[i] - this->meanX) * (x[i] - this->meanX);
    }

    this->b1 = numerator / denominator;
    this->b0 = this->meanY - (this->b1 * this->meanX);

}

double LinearRegression::predict(double x){

    if (this->b0 == -1 || this->b1 == -1){
        // warn about not finding coefficients first, then run findCoefficients
        throw std::invalid_argument("Coefficients not found. Run findCoefficients first");
        findCoefficients();
    }

    return this->b0 + this->b1 * x;
}