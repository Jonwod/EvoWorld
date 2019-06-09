//
// Created by jon on 08/06/19.
//

#ifndef EVOWORLD_TESTS_H
#define EVOWORLD_TESTS_H
#include "CircleBody.h"
#include <iostream>


bool testAngleOf(float testAngle){
    Vec2 testVec = unitVector(testAngle);
    std::cout<<"unitVector("<<testAngle<<") = "<<str(testVec);
    std::cout<<" angleOf("<<str(testVec)<<") = "<<angleOf(testVec)<<std::endl;
    return testAngle == angleOf(testVec);
}


#endif //EVOWORLD_TESTS_H
