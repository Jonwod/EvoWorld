//
// Created by jon on 09/06/19.
//

#ifndef EVOWORLD_BRAIN_H
#define EVOWORLD_BRAIN_H
#include <array>
#include "Math.h"


struct BrainDatum{
    ;
};



class InputNode{
public:

};


/*
 * Inputs:
 *  [0] Self length
 *  [1] Self radius
 *  [2] Self energy
 *  [3] Self tail positions (relative)
 */

/*
 */
template<size_t FIXED_INPUTS, size_t OUTPUTS>
class Brain {
public:
    // Returns outputs
    std::array<float, OUTPUTS> compute(const std::array<float, FIXED_INPUTS>& inputs);
private:
    int _numOutputs = 0;
};


template<size_t FIXED_INPUTS, size_t OUTPUTS>
std::array<float, OUTPUTS> Brain<FIXED_INPUTS, OUTPUTS>::compute(const std::array<float, FIXED_INPUTS>& inputs){
    std::array<float, OUTPUTS> outputs;
    outputs[0] = randFloat(-1.f, 1.f);
    outputs[1] = randFloat(-1.f, 1.f);
    outputs[2] = randFloat(0.f, 1.f);
    outputs[3] = randFloat(0.f, 1.f);
    return outputs;
}

#endif //EVOWORLD_BRAIN_H
