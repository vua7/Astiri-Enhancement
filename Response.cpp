#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
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
     * 
     */
    float getMean() {
    
    }

    /**
     *
     */
    float getStandardDeviation() {
    
    }

    /**
     * 
     */
    void getHistogram() {
    
    }
};

/**
 *
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
    
    return 0;
}
