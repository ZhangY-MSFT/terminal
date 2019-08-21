/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- Utils.h

Abstract:
- Helpers for the TerminalApp project
Author(s):
- Mike Griese - May 2019

--*/
#pragma once

std::wstring GetWstringFromJson(const Json::Value& json);

// Method Description:
// - Create a std::string from a string_view. We do this because we can't look
//   up a key in a Json::Value with a string_view directly, so instead we'll use
//   this helper. Should a string_view lookup ever be added to jsoncpp, we can
//   remove this entirely.
// Arguments:
// - key: the string_view to build a string from
// Return Value:
// - a std::string to use for looking up a value from a Json::Value
inline std::string JsonKey(const std::string_view key)
{
    return static_cast<std::string>(key);
}

winrt::Windows::UI::Xaml::Controls::IconElement GetColoredIcon(const winrt::hstring& path);

namespace TerminalApp
{
    class AppUtils;
};

class TerminalApp::AppUtils final
{
    // using AlignmentPair = std::tuple<winrt::Windows::UI::Xaml::HorizontalAlignment, winrt::Windows::UI::Xaml::VerticalAlignment>;

public:
    static void GetOptionalColor(const Json::Value& json,
                                 std::string_view key,
                                 std::optional<uint32_t>& color);

    static void GetOptionalString(const Json::Value& json,
                                  std::string_view key,
                                  std::optional<std::wstring>& target);

    static void GetOptionalGuid(const Json::Value& json,
                                std::string_view key,
                                std::optional<GUID>& target);

    static void GetOptionalDouble(const Json::Value& json,
                                  std::string_view key,
                                  std::optional<double>& target);

    // private:
    template<typename T, typename F>
    static void GetOptionalValue(const Json::Value& json,
                                 std::string_view key,
                                 std::optional<T>& target,
                                 F&& conversion)
    {
        if (json.isMember(JsonKey(key)))
        {
            if (auto jsonVal{ json[JsonKey(key)] })
            {
                target = conversion(jsonVal);
            }
            else
            {
                target = std::nullopt;
            }
        }
    }
    // template<>
    // static void GetOptionalValue<AlignmentPair,
    //                              std::function<AlignmentPair(const Json::Value&)>>(
    //     const Json::Value& json,
    //     std::string_view key,
    //     std::optional<AlignmentPair>& target,
    //     std::function<AlignmentPair(const Json::Value&)>&& conversion)
    // {
    //     auto conversionfn = [](const Json::Value& value) -> AlignmentPair {
    //         return ParseImageAlignment(value.asString());
    //     };
    //     GetOptionalValue(json,
    //                      key,
    //                      target,
    //                      conversionfn);
    // };
};
