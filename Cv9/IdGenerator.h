//
// Created by trric on 2026-11-14.
//

#ifndef ZPG_IDGENERATOR_H
#define ZPG_IDGENERATOR_H


#include "glad/gl.h"

class IdGenerator {
public:
    IdGenerator();

    GLint next();

private:
    GLint _id = 1;
    GLint _max{};
};



#endif //ZPG_IDGENERATOR_H
