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
    vector<float> m_uri1;
    vector<float> m_uri2;

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
    void capture(const std::string& uri) {
        if (uri.compare("uri1") == 0) {
            
        }
        else if (uri.compare("uri2") == 0) {
            
        }
        else {
            
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
    int a, b;

    DerivedRequest obj = DerivedRequest();    
    
    std::istringstream iss1(argv[2]);
    iss1 >> a;
    for (int i = 0; i < a; i++) {
        obj.capture(argv[1]);
        obj.process(argv[1]);
        
    }

    std::istringstream iss2(argv[4]);
    iss2 >> b;
    for (int j = 0; j < b; j++) {
        obj.capture(argv[3]);
        obj.process(argv[3]);
        
    }
    
    return 0;
}
