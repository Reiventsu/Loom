#pragma once

#include "callsite.hpp"
#include "profile.hpp"

#include <memory>
#include <source_location>
#include <string>

namespace loom {
    class Target {
    public:
        [[nodiscard]] auto name() const noexcept -> std::string_view;

        [[nodiscard]] auto kind() const noexcept -> eKind;

        auto standard( eStandard _standard
                     , std::source_location _loc = std::source_location::current()) -> Target &;

        auto sources( std::string_view _glob
                    , std::source_location _loc = std::source_location::current()) -> Target &;

        auto exclude( std::string_view _glob
                    , std::source_location _loc = std::source_location::current()) -> Target &;

        auto include( std::string_view
                    , std::source_location _loc = std::source_location::current()) -> Target &;

        auto includePublic( std::string_view _path
                          , std::source_location _loc = std::source_location::current()) -> Target &;

        auto includePrivate( std::string_view _path
                           , std::source_location _loc = std::source_location::current()) -> Target &;

        auto define( std::string_view _macro
                   , std::source_location _loc = std::source_location::current()) -> Target &;

        auto define( std::string_view _macro, std::string_view _value
                   , std::source_location _loc = std::source_location::current()) -> Target &;

        auto flag( std::string_view _flag
                 , std::source_location _loc = std::source_location::current()) -> Target &;

        template <typename... Tflags>
        auto flags(Tflags&&... _flags) -> Target & {
            (flag(std::forward<Tflags>(_flags)), ...);
            return *this;
        }

        auto optimize( eOptimization
                     , std::source_location _loc = std::source_location::current()) -> Target &;

        auto dependsOn( Target &_other, eLinkVisibility _visibility = eLinkVisibility::Private
                      , std::source_location _loc = std::source_location::current() ) -> Target &;

        auto linkTo(std::string_view _lib, std::source_location _loc = std::source_location::current()) -> Target &;

        auto outputName( std::string_view _name, std::source_location _loc = std::source_location::current()) -> Target &;

        auto outputDir( std::string_view _path
                      , std::source_location _loc = std::source_location::current()) -> Target &;

        Target(const Target&)                      = delete;
        auto operator=(const Target&) -> Target&   = delete;
        Target(Target&&)                           = default;
        auto operator=(Target&&) -> Target&        = default;
        ~Target();
    private:
        friend class Project;

        Target(std::string_view _name, eKind _kind, sCallSite _declaredAt);

        struct sTargetData;
        std::unique_ptr<sTargetData> m_impl;
    };
}