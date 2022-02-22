#include "transform.h"
#include <glm/gtx/transform.hpp>

namespace gfx{
//default scale is 1
Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) :
    m_pos(pos),
    m_rot(rot),
    m_scale(scale) {}


glm::mat4 Transform::GetModel() const {
    glm::mat4 posMatrix = glm::translate(m_pos);
    glm::mat4 scaleMatrix = glm::scale(m_scale);

    //representing rotations as a vec3 can cause gimbal lock.
    //have to represent rotation for each axis seperately
    glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
    glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
    glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));

    //matrix multiplications are not commutative
    //evaluated from R to L
    glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

    return posMatrix * rotMatrix * scaleMatrix;
}

} //namespace gfx