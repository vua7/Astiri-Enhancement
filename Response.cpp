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
    vector<std::chrono::milliseconds> m_uri1;
    vector<std::chrono::milliseconds> m_uri2;

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
     *
     */
    void capture(const std::string& uri, std::chrono::milliseconds time) {
        // determine which URI was specified
        if (uri.compare("uri1") == 0) {
            m_uri1.push_back(time);
        }
        else if (uri.compare("uri2") == 0) {
            m_uri2.push_back(time);
        }
        else {
            cerr << "Invalid URI\n";
        }	
    }

    /**
     * Calculates and returns the mean response time for each URI
     */
    auto getMean(const std::string& uri) {
        int mean1 = 0, mean2 = 0;
        long long unsigned int i;
        
        if (uri.compare("uri1") == 0) {
            // first URI mean response time
            for (i = 0; i < m_uri1.size(); i++) {
                mean1 += m_uri1.at(i).count();
            }
            mean1 /= m_uri1.size();
            return mean1;
        }
        else if (uri.compare("uri2") == 0) {
            // second URI mean response time
            for (i = 0; i < m_uri2.size(); i++) {
                mean2 += m_uri2.at(i).count();
            }
            mean2 /= m_uri2.size();
            return mean2;
        }
        return 0;
    }

    /**
     * Calculates and returns the standard deviation of the response
     * time for each URI.
     */
    auto getStandardDeviation(const std::string& uri, int size) {
        float temp, standardDeviation;
        
        auto mean = getMean(uri);
        
        if (uri.compare("uri1") == 0) {
            for (int i = 0; i < size; i++) {
                temp += pow((m_uri1.at(i).count() - mean), 2);
            }
        } 
        else if (uri.compare("uri2") == 0) {
            for (int i = 0; i < size; i++) {
                temp += pow((m_uri2.at(i).count() - mean), 2);
            }
        }
        standardDeviation = sqrt(temp / size);
        return standardDeviation;
    }

    /**
     * 
     */
    void getHistogram() {
    
    }
};

/**
 * Instantiates object of child class and has object call class methods to
 * execute several functions such as getting mean response times, standard
 * deviation of response times, and normalized histogram of response times.
 *
 * @param [in] URIs and the number of times to request for each URI
 */
int main(int argc, char *argv[]) {
    int iter1, iter2;

    // object instaniation
    DerivedRequest obj = DerivedRequest();    
    
    // convert command-line argument to integer
    std::istringstream iss1(argv[2]);
    iss1 >> iter1;
    // process first URI
    for (int i = 0; i < iter1; i++) {
        auto start = chrono::steady_clock::now();
        obj.process(argv[1]);
        auto end = chrono::steady_clock::now();
        obj.capture(argv[1], chrono::duration_cast<chrono::milliseconds>(end - start));
    }

    // convert command-line argument to integer
    std::istringstream iss2(argv[4]);
    iss2 >> iter2;
    // process second URI
    for (int j = 0; j < iter2; j++) {
        auto start = chrono::steady_clock::now();
        obj.process(argv[3]);
        auto end = chrono::steady_clock::now();
        obj.capture(argv[3], chrono::duration_cast<chrono::milliseconds>(end - start));
    }
    
    // get mean response times for each URI
    auto mean1 = obj.getMean(argv[1]);
    std::cout << "Mean response time for URI 1: " << mean1 << " ms\n";
    auto mean2 = obj.getMean(argv[3]);
    std::cout << "Mean response time for URI 2: " << mean2 << " ms\n";

    // get standard deviation of response times for each URI
    auto standardDeviation1 = obj.getStandardDeviation(argv[1], iter1);
    std::cout << "Standard deviation of response times for URI 1: " << standardDeviation1 << " ms\n";
    auto standardDeviation2 = obj.getStandardDeviation(argv[3], iter2);
    std::cout << "Standard deviation of response times for URI 2: " << standardDeviation2 << " ms\n";

    return 0;
}
