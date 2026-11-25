#pragma once
#include <string>
#include <string_view>

namespace budgie {
class Engine {
public:
    static constexpr std::string_view Name = "BudgieOS Engine";
    static constexpr std::string_view Version = "1.0.0";
    std::string welcome() const;
};
}
