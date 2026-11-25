#include "budgie/Scene.hpp"
#include <utility>
namespace budgie {
Entity& Scene::createEntity(std::string name) {
    entities_.push_back(Entity{nextId_++, std::move(name), {}});
    return entities_.back();
}
}
