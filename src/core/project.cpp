#include "loom/project.hpp"

#include <string>
#include <vector>

namespace loom {
    struct Project::sProjectData {
        std::string name;
        std::string version;
        sToolchain toolchain;

        std::vector<Target> targets;

        eStandard globalStandard = eStandard::cpp23;
        eOptimization globalOptimize = eOptimization::None;
        std::vector<std::string> globalFlags;
        std::vector<std::string> globalDefines;
    };

    Project::Project() : m_impl(std::make_unique<sProjectData>()) {
    }

    Project::~Project() = default;

    auto Project::name(std::string_view _name) -> Project & {
        m_impl->name = _name;
        return *this;
    }

    auto Project::version(std::string_view _version) -> Project & {
        m_impl->version = _version;
        return *this;
    }

    auto Project::toolchain(sToolchain _toolchain) -> Project & {
        m_impl->toolchain = _toolchain;
        return *this;
    }

    auto Project::executable(std::string_view _name, std::source_location _loc) -> Target & {
        return m_impl->targets.emplace_back(Target{_name, eKind::Application, sCallSite::here(_loc)}
        );
    }
}