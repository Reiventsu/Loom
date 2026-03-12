#pragma once

#include "callsite.hpp"
#include "profile.hpp"

#include <memory>
#include <source_location>
#include <string>

namespace loom {
    class Target {
    public:
        [[nodiscard]] std::string_view name() const noexcept;

        [[nodiscard]] eKind kind() const noexcept;

        Target &standard( eStandard _standard
                        , std::source_location _loc = std::source_location::current());

        Target &sources( std::string_view _glob
                       , std::source_location _loc = std::source_location::current());

        Target &exclude( std::string_view _glob
                       , std::source_location _loc = std::source_location::current());

        Target &include( std::string_view
                       , std::source_location _loc = std::source_location::current());

        Target &includePublic( std::string_view _path
                             , std::source_location _loc = std::source_location::current());

        Target &includePrivate( std::string_view _path
                              , std::source_location _loc = std::source_location::current());

        Target &define( std::string_view _macro
                      , std::source_location _loc = std::source_location::current());

        Target &define( std::string_view _macro, std::string_view _value
                      , std::source_location _loc = std::source_location::current());

        Target &flag( std::string_view _flag
                    , std::source_location _loc = std::source_location::current());

        template <typename... Tflags>
        Target &flags(Tflags&&... _flags) {
            (flag(std::forward<Tflags>(_flags)), ...);
            return *this;
        }

        Target &optimize( eOptimization
                        , std::source_location _loc = std::source_location::current());

        Target &dependsOn( Target &_other, eLinkVisibility _visibility = eLinkVisibility::Private
                          , std::source_location _loc = std::source_location::current() );

        Target &linkTo(std::string_view _lib, std::source_location _loc = std::source_location::current());

        Target &outputName( std::string_view _name, std::source_location _loc = std::source_location::current());

        Target &outputDir( std::string_view _path
                         , std::source_location _loc = std::source_location::current());

        Target(const Target&) = delete;
        Target& operator=(const Target&) = delete;
        Target(Target&&) = default;
        Target& operator=(Target&&) = default;
        ~Target();
    private:
        friend class Project;

        Target(std::string_view _name, eKind _kind, sCallSite _declaredAt);

        struct sTargetData;
        std::unique_ptr<sTargetData> m_impl;
    };
}
