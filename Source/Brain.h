//
// Created by jon on 09/06/19.
//

#ifndef EVOWORLD_BRAIN_H
#define EVOWORLD_BRAIN_H
#include <array>
#include <vector>
#include "Math.h"



class Neuron {
public:
    // float getValue();
    inline void set(float v) {
        value = v;
    }
private:
    float value;
};

class World;
class Snake;



class NeuralNetBase {
protected:
    void setInputLayerNum(size_t n) {
        inputLayer.assign(n, Neuron());
    }

    inline void setInputNeuron(size_t i, float value) {
        inputLayer[i].set(value);
    }
private:
    std::vector<Neuron> inputLayer;
    std::vector<Neuron> otherNeurons;
    std::vector<Neuron> outputLayer{Neuron(), Neuron(), Neuron()};
};


/*
 * self:
 *      col
 *      size
 *      len
 *      energy
 * [own_tail_slots]
 *      valid
 *      x
 *      y
 * [plant_slots]
 *      valid
 *      x
 *      y
 * [snake_slots]
 *      valid
 *      head_x
 *      head_y
 *      col
 *      size
 * [segment_slots]
 *      valid
 *      x
 *      y
 *      col
 *      size
 * [meat_slots]
 *      valid
 *      x
 *      y
 *      col
 *      size
 */

class NeuralNet: public NeuralNetBase {
public:
    NeuralNet() {
        const size_t inputLayerSize = Self::numNodes()
                + TailSlot::numNodes()    * numOwnTailSlots
                + PlantSlot::numNodes()   * numPlantSlots
                + SnakeSlot::numNodes()   * numSnakeSlots
                + SegmentSlot::numNodes() * numSegmentSlots
                + MeatSlot::numNodes()    * numMeatSlots;

        setInputLayerNum(inputLayerSize);
    }

    struct Self {
        float color;
        float size;
        float len;
        float energy;
        static constexpr size_t numNodes() { return 4; };
    };

    void setSelf(const Self& self) {
        const size_t selfIndex = selfStartIndex();
        setInputNeuron(selfIndex + 0, self.color);
        setInputNeuron(selfIndex + 1, self.size);
        setInputNeuron(selfIndex + 2, self.len);
        setInputNeuron(selfIndex + 3, self.energy);
    }

    size_t getNumOwnTailSlots() const {
        return numOwnTailSlots;
    }

    struct Slot {
        float valid;
        static size_t numNodes() { return 1; }
    };

    struct PosSlot: public Slot {
        float x;
        float y;
        static size_t numNodes() { return Slot::numNodes() + 2; }
    };
    typedef PosSlot TailSlot;
    typedef PosSlot PlantSlot;

    struct SnakeSlot: public Slot {
        float head_x;
        float head_y;
        float color;
        float size;
        static size_t numNodes() { return Slot::numNodes() + 4; }
    };

    struct SegmentSlot: public PosSlot {
        float col;
        float size;
        static size_t numNodes() { return PosSlot::numNodes() + 2; }
    };

    typedef SegmentSlot MeatSlot;

    void setOwnTailSlot(size_t i, TailSlot tailSlot) {
        const size_t slotIndex = ownTailSlotStartIndex() + i * TailSlot::numNodes();
        setInputNeuron(slotIndex, tailSlot.valid);
        setInputNeuron(slotIndex + 1, tailSlot.x);
        setInputNeuron(slotIndex + 2, tailSlot.y);
    }

    void setPlantSlot(size_t i, PlantSlot plant) {
        const size_t slotIndex = plantSlotStartIndex() + i * PlantSlot::numNodes();
        setInputNeuron(slotIndex, plant.valid);
        setInputNeuron(slotIndex + 1, plant.x);
        setInputNeuron(slotIndex + 2, plant.y);
    }

    void setSnakeSlot(size_t i, SnakeSlot snake) {
        const size_t slotIndex = snakeSlotStartIndex() + i * SnakeSlot::numNodes();
        setInputNeuron(slotIndex, snake.valid);
        setInputNeuron(slotIndex, snake.head_x);
        setInputNeuron(slotIndex, snake.head_y);
        setInputNeuron(slotIndex, snake.color);
        setInputNeuron(slotIndex, snake.size);
    };

    void setSegmentSlot(size_t i, SegmentSlot segment) {
        const size_t slotIndex = segmentSlotStartIndex() + i * SegmentSlot::numNodes();
        setInputNeuron(slotIndex, segment.valid);
        setInputNeuron(slotIndex, segment.x);
        setInputNeuron(slotIndex, segment.y);
        setInputNeuron(slotIndex, segment.col);
        setInputNeuron(slotIndex, segment.size);
    }

    void setMeatSlot(size_t i, SegmentSlot meat) {
        const size_t slotIndex = meatSlotStartIndex() + i * MeatSlot::numNodes();
        setInputNeuron(slotIndex, meat.valid);
        setInputNeuron(slotIndex, meat.x);
        setInputNeuron(slotIndex, meat.y);
        setInputNeuron(slotIndex, meat.col);
        setInputNeuron(slotIndex, meat.size);
    }

private:
    static constexpr size_t selfStartIndex() { return 0; };
    static size_t ownTailSlotStartIndex() { return Self::numNodes(); }
    size_t plantSlotStartIndex()   const { return ownTailSlotStartIndex() + numOwnTailSlots * TailSlot::numNodes(); }
    size_t snakeSlotStartIndex()   const { return plantSlotStartIndex() + numPlantSlots * PlantSlot::numNodes(); }
    size_t segmentSlotStartIndex() const { return snakeSlotStartIndex() + numSnakeSlots * SnakeSlot::numNodes(); }
    size_t meatSlotStartIndex()    const { return segmentSlotStartIndex() + numSegmentSlots * SegmentSlot::numNodes(); }

    const size_t numOwnTailSlots = 4;
    const size_t numPlantSlots   = 4;
    const size_t numSnakeSlots   = 4;
    const size_t numSegmentSlots = 4;
    const size_t numMeatSlots    = 4;
};


/*
 */
class Brain {
public:
    struct Output {
        // -1 to 1 between local left/right. 0 dead ahead
        float steer;
        // whether to reproduce. >= 1 for yes
        bool split;
        // whether to boost. >= 1 for yes
        bool boost;
    };

    // updates brain output
    void think(float dt, const World& world, const Snake& self);

    const Output& getOutput() const { return output; }
private:
    Output output;
    NeuralNet neural_net;
};




#endif //EVOWORLD_BRAIN_H
