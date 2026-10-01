/*!
 * \file    peak_icv_printable.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <type_traits>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace peak
{
namespace icv
{
namespace detail
{

class CommaSeperatedStream
{
public:
    explicit CommaSeperatedStream(std::ostream& os)
        : m_os(os)
    {}

    template <typename Type>
    CommaSeperatedStream& operator<<(const Type& value)
    {
        if (m_addDelimiter)
        {
            m_os << delimiter;
        }
        m_os << value;
        m_addDelimiter = true;
        return *this;
    }

    template <typename Type>
    CommaSeperatedStream& operator<<(const std::vector<Type>& vector)
    {
        if (m_addDelimiter)
        {
            m_os << delimiter;
        }

        m_os << "{ ";
        CommaSeperatedStream innerStream(m_os);
        std::for_each(vector.begin(), vector.end(), [&](const auto& elem) {
            innerStream << elem;
        });
        m_os << " }";

        m_addDelimiter = true;
        return *this;
    }

    CommaSeperatedStream& operator<<(std::ostream& (*manip)(std::ostream&))
    {
        m_addDelimiter = false;
        m_os << delimiter;
        m_os << manip;
        return *this;
    }

private:
    std::ostream& m_os;
    bool m_addDelimiter = false;
    constexpr static const char* delimiter = ", ";
};

// This is not real CRTP
// NOLINTBEGIN(bugprone-crtp-constructor-accessibility)
template <typename Type>
class IPrintable
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Type& obj)
    {
        static_assert(std::is_base_of<IPrintable, Type>::value, "T must derive from IPrintable<T>");

        os << outputBegin;
        CommaSeperatedStream stream(os);

        auto printable = static_cast<const IPrintable<Type>*>(&obj);
        printable->Print(stream);

        os << outputEnd;
        return os;
    }

    virtual ~IPrintable() = default;


protected:
    virtual void Print(CommaSeperatedStream& stream) const = 0;


private:
    constexpr static const char* outputBegin = "{ ";
    constexpr static const char* outputEnd = " }";
};

template <typename BaseType>
class IterablePrinter : public IPrintable<BaseType>
{
protected:
    void Print(CommaSeperatedStream& stream) const override
    {
        PrintInternal(stream);
    }

private:
    template <typename...>
    using void_t = void; // std::void_t not usable before c++17

    template <typename Type, typename = void>
    struct has_begin : std::false_type
    {};

    template <typename Type>
    struct has_begin<Type, void_t<decltype(std::declval<Type>().begin())>> : std::true_type
    {};

    template <typename Type, typename = void>
    struct has_cbegin : std::false_type
    {};

    template <typename Type>
    struct has_cbegin<Type, void_t<decltype(std::declval<Type>().cbegin())>> : std::true_type
    {};

    template <typename Type = BaseType>
    std::enable_if_t<has_begin<Type>::value && !has_cbegin<Type>::value, void> PrintInternal(CommaSeperatedStream& stream) const
    {
        std::for_each(static_cast<const BaseType*>(this)->begin(), static_cast<const BaseType*>(this)->end(), [&](auto elem) {
            stream << elem;
        });
    }

    template <typename Type = BaseType>
    std::enable_if_t<has_cbegin<Type>::value, void> PrintInternal(CommaSeperatedStream& stream) const
    {
        std::for_each(static_cast<const BaseType*>(this)->cbegin(), static_cast<const BaseType*>(this)->cend(), [&](auto elem) {
            stream << elem;
        });
    }
};

// NOLINTEND(bugprone-crtp-constructor-accessibility)

} // namespace detail
} /* namespace icv */
} /* namespace peak */
