#pragma once

#include "callsite.hpp"
#include "profile.hpp"
#include "toolchain.hpp"
#include "target.hpp"

#include <functional>
#include <memory>
#include <source_location>
#include <string_view>

namespace loom {
    class Project {
    public:
        auto name(std::string_view _name) -> Project &;
        auto version(std::string_view _version) -> Project &;
        auto toolchain(sToolchain _toolchain) -> Project &;

        [[nodiscard]]
        auto executable( std::string_view _name
                       , std::source_location _loc = std::source_location::current()) -> Target &;

        [[nodiscard]]
        auto staticLibrary( std::string_view _name
                          , std::source_location _loc = std::source_location::current()) -> Target &;

        [[nodiscard]]
        auto sharedLibrary( std::string_view _name
                          , std::source_location _loc = std::source_location::current()) -> Target &;

        [[nodiscard]]
        auto headerOnly( std::string_view _name
                       , std::source_location _loc = std::source_location::current()) -> Target &;

        [[nodiscard]]
        auto moduleLibrary( std::string_view _name
                          , std::source_location _loc = std::source_location::current()) -> Target &;

        auto on( ePlatform _platform, std::function< void() > _configure ) -> Project &;
        auto on( eArchitecture _arch, std::function< void() > _configure ) -> Project &;
        auto on( sProfile _profile,   std::function< void() > _configure ) -> Project &;

        auto on( ePlatform _platform, eArchitecture, std::function< void() > _configure ) -> Project &;

        auto profile( std::string_view _profileName, std::function< void() > _configure
                    , std::source_location _loc = std::source_location::current()) -> Project &;

        auto globalStandard( eStandard _standard
                           , std::source_location _loc = std::source_location::current()) -> Project &;

        auto globalFlag( std::string_view _flag
                       , std::source_location _loc = std::source_location::current()) -> Project &;

        auto globalDefine( std::string_view _macro
                         , std::source_location _loc = std::source_location::current() ) -> Project &;

        auto globalOptimize( eOptimization _level
                           , std::source_location _loc = std::source_location::current() ) -> Project &;

        Project(const Project&)                        = delete;
        auto operator=(const Project&) -> Project&     = delete;
        Project(Project&&)                             = delete;
        auto operator=(Project&&) -> Project&          = delete;

        Project();
        ~Project();

    private:
        friend class DependencyGraph;

        struct sProjectData;
        std::unique_ptr<sProjectData> m_impl;
    };
}