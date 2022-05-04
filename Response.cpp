#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
#include "Request.hpp"

using namespace std;

void usage() {
    std::cerr << "Program usage: ./Response [max number of bins in histogram]" 
        << " [URI] [number of URI requests]";
    exit(EXIT_FAILURE);
}

/**
 * Derived child class of Request parent class
 *
 * This child class includes several new methods that help facilitate the main
 * features of retrieving the mean response time, standard deviation of response
 * times, and normalized histogram of response times.
 */
class DerivedRequest: public Request
{
private:
    vector<std::chrono::milliseconds> m_uri;
    int m_maxBins;

public:
    /**
     * Stores the command-line specified number of bins into member variable.
     *
     * @param [in] maximum number of bins in histogram
     */
    void setBins(int maxBins) {
        m_maxBins = maxBins;
    }

    /**
     * Stores the captured response data into member data structure.
     * 
     * @param [in] response time of URI request
     */
    void capture(const std::string& uri, std::chrono::milliseconds time) {
        m_uri.push_back(time);	
    }

    /**
     * Calculates and returns the mean response time for the URI.
     *
     * @param [in] size of vector aka number of request iterations
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
     *
     * @param [in] size of vector aka number of request iterations
     */
    auto getStandardDeviation(int size) {
        float temp, standardDeviation;
        
        // Get mean by calling child class method 
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
     * times for the URI.
     *
     * @param [in] size of vector aka number of request iterations
     */
    auto getHistogram(int size) {
        int max, perBin, low = 0, high = 0;
        int hist[m_maxBins] = {};
        std::string histogram;

        // Calculate arithmetic variables
        max = (*max_element(m_uri.begin(), m_uri.end())).count();
        perBin = max / m_maxBins;
        if (perBin == 0) {
            perBin = 1;
        }

        // Calculate occurrences in each bin
        // Iterate through each bin
        for (int i = 0; i < m_maxBins; i++) {    
            low = i * perBin;
            high = perBin - 1 + i * perBin;
            
            // Iterate through vector of response times
            for (int j = 0; j < size; j++) {
                int k = m_uri.at(j).count();
                // Increment bin if response time is within bin range
                if (k >= low && k <= high) {
                    hist[i] += 1;
                }
                // Append occurrence to last bin if response time is
                // larger than last bin range
                if (i == m_maxBins - 1 && k > high) {
                    hist[i] += 1;
                }
            }
        }
        
        // Build string to display histogram
        low = 0;
        high = 0;
        // Iterate through array of occurrences
        for (int i = 0; i < m_maxBins; i++) {
            low = i * perBin;
            high = perBin - 1 + i * perBin;
            // Only display non-empty bins
            if (hist[i] != 0) {
                // Add plus symbol to last bin to cover out-of-range
                // response data
                if (i == m_maxBins - 1) {
                    histogram += std::to_string(low) + "-" +
                        std::to_string(high) + "+\t| ";
                }
                else {
                    histogram += std::to_string(low) + "-" + 
                        std::to_string(high) + "\t| ";
                }
                // normalize the histogram by converting the counts
                // to a percentage of total URI requests
                float percentage = (static_cast<float>(hist[i]) / 
                        static_cast<float>(size));
                int normal = percentage / 0.05;
                if (normal == 0) {
                    histogram += std::string(1, '-') + "\n";
                }
                else {
                    histogram += std::string(normal, '*') + "\n";
                }
            }
        }
        
        return histogram;
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
    int maxBins, size;

    // Check for correct number of command-line arguments
    if (argc != 4) {
        usage();
    }

    // Object instaniation
    DerivedRequest obj = DerivedRequest();
    
    // Convert command-line argument to integer
    try {
        std::istringstream iss1(argv[1]);
        iss1 >> maxBins;
    } catch(...) {
        usage();
    }
    
    // Store number of specified bins
    obj.setBins(maxBins);

    // Convert command-line argument to integer
    try {
        std::istringstream iss2(argv[3]);
        iss2 >> size;
    } catch(...) {
        usage();
    }
    
    // Process URI
    try {
        for (int i = 0; i < size; i++) {
            auto start = chrono::steady_clock::now();
            obj.process(argv[2]);
            auto end = chrono::steady_clock::now();
            obj.capture(argv[2], chrono::duration_cast<chrono::milliseconds>(end - start));
        }
    } catch(...) {
        usage();
    }

    // Get mean response time for URI
    auto mean = obj.getMean(size);
    std::cout << "Mean response time for URI: " << mean << " ms\n";

    // Get standard deviation of response times for URI
    auto standardDeviation = obj.getStandardDeviation(size);
    std::cout << "Standard deviation of response times for URI: " 
        << standardDeviation << " ms\n";
    
    // Get normalized histogram of response times for URI
    auto histogram = obj.getHistogram(size);
    std::cout << "Normalized histogram of response times for URI in milliseconds (ms):\n"
        << "* = at least 5% of requests\n- = less than 5% of requests\n"
        << histogram;

    return 0;
}
