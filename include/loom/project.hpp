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
        Project &name(std::string_view _name);
        Project &version(std::string_view _version);
        Project &toolchain(sToolchain _toolchain);

        [[nodiscard]]
        Target& executable( std::string_view _name
                          , std::source_location _loc = std::source_location::current());

        [[nodiscard]]
        Target& staticLibrary( std::string_view _name
                             , std::source_location _loc = std::source_location::current());

        [[nodiscard]]
        Target& sharedLibrary( std::string_view _name
                             , std::source_location _loc = std::source_location::current());

        [[nodiscard]]
        Target& headerOnly( std::string_view _name
                          , std::source_location _loc = std::source_location::current());

        [[nodiscard]]
        Target& moduleLibrary( std::string_view _name
                             , std::source_location _loc = std::source_location::current());

        Project &on( ePlatform _platform, std::function< void() > _configure );
        Project &on( eArchitecture _arch, std::function< void() > _configure );
        Project &on( sProfile _profile,   std::function< void() > _configure );

        Project &on( ePlatform _platform, eArchitecture, std::function< void() > _configure );

        Project &profile( std::string_view _profileName, std::function< void() > _configure
                        , std::source_location _loc = std::source_location::current());

        Project &globalStandard( eStandard _standard
                               , std::source_location _loc = std::source_location::current());

        Project &globalFlag( std::string_view _flag
                           , std::source_location _loc = std::source_location::current());

        Project &globalDefine( std::string_view _macro
                             , std::source_location _loc = std::source_location::current() );

        Project &globalOptimize( eOptimization _level
                               , std::source_location _loc = std::source_location::current() );

        Project(const Project&)            = delete;
        Project& operator=(const Project&) = delete;
        Project(Project&&)                 = delete;
        Project& operator=(Project&&)      = delete;

        Project();
        ~Project();

    private:
        friend class DependencyGraph;

        struct sProjectData;
        std::unique_ptr<sProjectData> m_impl;
    };
}