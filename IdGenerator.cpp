//
// Created by trric on 2026-11-14.
//

#include "IdGenerator.h"

#include <stdexcept>

IdGenerator::IdGenerator() {
    GLint bits;
    glGetFramebufferAttachmentParameteriv(
        GL_DRAW_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &bits
    );
    _max = (1 << bits) - 1;
}

GLint IdGenerator::next() {
    if (_id >= _max) {
        throw std::runtime_error("Scene has too many objects");
    }

    return _id++;
}
