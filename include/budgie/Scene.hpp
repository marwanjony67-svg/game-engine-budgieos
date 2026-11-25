#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace budgie {
struct Vec3 { float x{0}, y{0}, z{0}; };
struct Transform { Vec3 position{}; Vec3 rotation{}; Vec3 scale{1,1,1}; };
struct Entity {
    std::uint32_t id{};
    std::string name{"Entity"};
    Transform transform{};
};
class Scene {
public:
    Entity& createEntity(std::string name);
    const std::vector<Entity>& entities() const noexcept { return entities_; }
private:
    std::uint32_t nextId_{1};
    std::vector<Entity> entities_;
};
}
