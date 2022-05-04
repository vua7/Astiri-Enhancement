#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "Request.hpp"

using namespace std;

/**
 * Derived child class of Request parent class
 *
 * This child class overrides some functions from the Request parent class and
 * includes several new methods relating to captured response time data.
 */
class DerivedRequest: public Request
{
private:
    vector<std::chrono::milliseconds> m_uri;
    int m_bins;

protected:
    /**
     * 
     */
    void start(const std::string& uri) {
    
    }
    
    /**
     * 
     */
    void finish() {
        
    }

public:
    /**
     * Stores the command-line specified number of bins into member variable
     */
    void setBins(int bins) {
        m_bins = bins;
    }

    /**
     * Stores the captured response data into member data structure
     */
    void capture(const std::string& uri, std::chrono::milliseconds time) {
        m_uri.push_back(time);	
    }

    /**
     * Calculates and returns the mean response time for the URI
     */
    auto getMean(int size) {
        int mean = 0;
        
        // URI mean response time
        for (int i = 0; i < size; i++) {
            mean += m_uri.at(i).count();
        }
        mean /= size;
        return mean;
    }

    /**
     * Calculates and returns the standard deviation of the response
     * time for the URI.
     */
    auto getStandardDeviation(int size) {
        float temp, standardDeviation;
        
        // get mean by calling child class method 
        auto mean = getMean(size);
        
        // URI standard deviation
        for (int i = 0; i < size; i++) {
            temp += pow((m_uri.at(i).count() - mean), 2);
        }
        standardDeviation = sqrt(temp / size);
        return standardDeviation;
    }

    /**
     * Builds and returns the normalized histogram of the response
     * times for the URI
     */
    auto getHistogram(int size) {
       int min = 0, max, perBin;
       
       


       perBin = max / m_bins;
       cout << perBin << "\n";
       
       return 0;
    }
};

/**
 * Instantiates object of child class and has object call class methods to
 * execute several functions such as getting mean response time, standard
 * deviation of response times, and normalized histogram of response times.
 *
 * @param [in] number of bins, URI, and the number of times to request for URI
 */
int main(int argc, char *argv[]) {
    int bins, size;

    // check for correct program usage

    // object instaniation
    DerivedRequest obj = DerivedRequest();
    
    // convert command-line argument to integer
    std::istringstream iss1(argv[1]);
    iss1 >> bins;
    // store number of specified bins
    obj.setBins(bins);

    // convert command-line argument to integer
    std::istringstream iss2(argv[3]);
    iss2 >> size;
    // process URI
    for (int i = 0; i < size; i++) {
        auto start = chrono::steady_clock::now();
        obj.process(argv[2]);
        auto end = chrono::steady_clock::now();
        obj.capture(argv[2], chrono::duration_cast<chrono::milliseconds>(end - start));
    }
    
    // get mean response time for URI
    auto mean = obj.getMean(size);
    std::cout << "Mean response time for URI: " << mean << " ms\n";

    // get standard deviation of response times for URI
    auto standardDeviation = obj.getStandardDeviation(size);
    std::cout << "Standard deviation of response times for URI: " << standardDeviation << " ms\n";
    
    // get normalized histogram of response times for URI
    auto histogram = obj.getHistogram(size);

    

    return 0;
}
