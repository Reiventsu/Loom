module;
#include <print>
#include <string_view>
export module Greeting;

export auto PrintText( std::string_view _text ) -> void {
    std::print( "Hello, {}!\n", std::move( _text ) );
}