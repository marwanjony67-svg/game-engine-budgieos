#include "budgie/Engine.hpp"
namespace budgie {
std::string Engine::welcome() const {
    return std::string(Name) + " " + std::string(Version) + " — BudgieOS Blue";
}
}
