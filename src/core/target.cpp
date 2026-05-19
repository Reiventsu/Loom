#include "loom/target.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace loom
{

struct sInclude
{
    std::string      path;
    eLinkVisibility  visibility;
    sCallSite        declared_at;
};

struct sDependency
{
    Target*         target;
    eLinkVisibility visibility;
    sCallSite       declared_at;
};

struct Target::sTargetData
{
    std::string              name;
    eKind                    kind;
    sCallSite                declared_at;

    std::vector<std::string> source_globs;
    std::vector<std::string> exclude_globs;
    std::vector<sInclude>    includes;
    std::vector<std::string> defines;
    std::vector<std::string> flags;
    std::vector<sDependency> dependencies;
    std::vector<std::string> system_libs;

    eStandard                standard    = eStandard::cpp23;
    eOptimization            optimize    = eOptimization::None;
    std::string              output_name;
    std::string              output_dir;
};

Target::Target(std::string_view _name, eKind _kind, sCallSite _declaredAt)
    : m_impl(std::make_unique<sTargetData>())
{
    m_impl->name        = _name;
    m_impl->kind        = _kind;
    m_impl->declared_at = _declaredAt;
}

Target::~Target() = default;

auto Target::name() const noexcept -> std::string_view { return m_impl->name; }
auto Target::kind() const noexcept -> eKind            { return m_impl->kind; }

auto Target::standard(eStandard _standard, std::source_location _loc) -> Target &
{
    m_impl->standard = _standard;
    return *this;
}

auto Target::sources(std::string_view _glob, std::source_location _loc) -> Target &
{
    m_impl->source_globs.emplace_back(_glob);
    return *this;
}

auto Target::exclude(std::string_view _glob, std::source_location _loc) -> Target &
{
    m_impl->exclude_globs.emplace_back(_glob);
    return *this;
}

auto Target::include(std::string_view _path, std::source_location _loc) -> Target &
{
    m_impl->includes.push_back({ std::string(_path), eLinkVisibility::Private, sCallSite::here(_loc) });
    return *this;
}

auto Target::includePublic(std::string_view _path, std::source_location _loc) -> Target &
{
    m_impl->includes.push_back({ std::string(_path), eLinkVisibility::Public, sCallSite::here(_loc) });
    return *this;
}

auto Target::includePrivate(std::string_view _path, std::source_location _loc) -> Target &
{
    m_impl->includes.push_back({ std::string(_path), eLinkVisibility::Private, sCallSite::here(_loc) });
    return *this;
}

auto Target::define(std::string_view _macro, std::source_location _loc) -> Target &
{
    m_impl->defines.emplace_back(_macro);
    return *this;
}

auto Target::define(std::string_view _macro, std::string_view _value, std::source_location _loc) -> Target &
{
    m_impl->defines.emplace_back(std::string(_macro) + "=" + std::string(_value));
    return *this;
}

auto Target::flag(std::string_view _flag, std::source_location _loc) -> Target &
{
    m_impl->flags.emplace_back(_flag);
    return *this;
}

auto Target::optimize(eOptimization _level, std::source_location _loc) -> Target &
{
    m_impl->optimize = _level;
    return *this;
}

auto Target::dependsOn(Target& _other, eLinkVisibility _visibility, std::source_location _loc) -> Target &
{
    m_impl->dependencies.push_back({ &_other, _visibility, sCallSite::here(_loc) });
    return *this;
}

auto Target::linkTo(std::string_view _lib, std::source_location _loc) -> Target &
{
    m_impl->system_libs.emplace_back(_lib);
    return *this;
}

auto Target::outputName(std::string_view _name, std::source_location _loc) -> Target &
{
    m_impl->output_name = _name;
    return *this;
}

auto Target::outputDir(std::string_view _path, std::source_location _loc) -> Target &
{
    m_impl->output_dir = _path;
    return *this;
}

}