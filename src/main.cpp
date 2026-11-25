#include "budgie/Engine.hpp"
#include "budgie/Scene.hpp"
#include <iostream>
int main() {
    budgie::Engine engine;
    budgie::Scene scene;
    scene.createEntity("Camera");
    scene.createEntity("Directional Light");
    std::cout << engine.welcome() << '\\n';
    std::cout << "Scene entities: " << scene.entities().size() << '\\n';
    return 0;
}
