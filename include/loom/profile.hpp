#pragma once
#include <string_view>
namespace loom {

    enum class eStandard {
        cpp20,
        cpp23,
        cpp26,
    };

    enum class eOptimization {
        None,       // -O0
        Debug,      // -Og
        Speed,      // -O2
        Aggressive, // -O3
    };

    enum class eKind {
        Application,
        StaticLibrary,
        SharedLibrary,
        ModuleLibrary,
        HeaderOnly,
    };

    enum class ePlatform {
        Windows,
        Linux,
        MacOS,
        Any,
    };

    enum class eArchitecture {
        x86,
        x86_64,
        arm,
        arm64,
    };

    enum class eLinkVisibility {
        Private,
        Public,
        Interface,
    };

    struct sProfile {
        std::string_view name;

        [[nodiscard]]
        auto operator==(const sProfile& _other) const noexcept -> bool {
            return name == _other.name;
        }

        static const sProfile Debug;
        static const sProfile Release;
        static const sProfile MinSizeRel;
        static const sProfile RelWithDebInfo;
        static const sProfile Final;
    };

}