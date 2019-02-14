//
// Created by RS on 2019/2/13.
//

#ifndef CLION_IDGENERATOR_H
#define CLION_IDGENERATOR_H

#include <string>
#include <sstream>

class IDGenerator {
public:
    IDGenerator() : m_orderID(0), m_executionID(0) {}

    std::string getM_orderID() {
        std::stringstream stream;
        stream << ++m_orderID;
        return stream.str();
    }

    std::string getM_executionID() {
        std::stringstream stringstream;
        stringstream << ++m_executionID;
        return stringstream.str();
    }

private:
    long m_orderID;
    long m_executionID;
};

#endif //CLION_IDGENERATOR_H
