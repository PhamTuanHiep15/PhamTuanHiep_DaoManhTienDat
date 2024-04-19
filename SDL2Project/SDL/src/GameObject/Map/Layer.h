#pragma once
#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include "GameObject/Sprite2D.h" 

class Layer {

public:

    virtual void Render() = 0;
    virtual void Update() = 0;
};

#endif
