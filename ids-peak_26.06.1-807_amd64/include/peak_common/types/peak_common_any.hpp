/*!
 * \file    peak_common_any.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <type_traits>
#include <memory>
#include <string>

namespace peak
{
namespace common
{

/*!
 * \ingroup ids_peak_common_types
 * \brief A type-erased container for any copyable value.
 *
 * This class provides a way to store and retrieve a value of arbitrary type
 * using type erasure. It behaves similarly to `std::any` and allows type-safe
 * casting via the `AnyCast<T>()` method.
 *
 * \since ids_peak_common 1.0
 */
class Any
{
    struct Placeholder
    {
        virtual ~Placeholder() = default;

        PEAK_COMMON_NO_DISCARD virtual const std::type_info& Type() const = 0;
        PEAK_COMMON_NO_DISCARD virtual std::unique_ptr<Placeholder> Clone() const = 0;
    };

    template <typename T>
    struct Holder : public Placeholder
    {
        T value;

        explicit Holder(const T& val)
            : value(val)
        {}

        explicit Holder(T&& val)
            : value(std::move(val))
        {}

        PEAK_COMMON_NO_DISCARD const std::type_info& Type() const override
        {
            return typeid(T);
        }

        PEAK_COMMON_NO_DISCARD std::unique_ptr<Placeholder> Clone() const override
        {
            return std::make_unique<Holder<T>>(value);
        }
    };

    std::unique_ptr<Placeholder> m_content;

public:
    /*!
     * \brief Default constructor. Constructs an empty Any object.
     *
     * \since ids_peak_common 1.0
     */
    Any() = default;

    /*!
     * \brief Constructs an Any from a const reference.
     *
     * \tparam T The type of the value to store.
     * \param value The value to store.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    explicit Any(const T& value)
        : m_content(std::make_unique<Holder<typename std::decay_t<T>>>(value))
    {}

    /*!
     * \brief Constructs an Any from a rvalue reference.
     *
     * \tparam T The type of the value to store.
     * \param value The value to store.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    explicit Any(T&& value
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if<!std::is_same<Any, typename std::decay<T>::type>::value>::type* = nullptr
        /// @endcond
        )
        : m_content(std::make_unique<Holder<typename std::decay_t<T>>>(std::forward<T>(value)))
    {}

    /*!
     * \brief Copy constructor.
     *
     * \since ids_peak_common 1.0
     */
    Any(const Any& other)
        : m_content(other.m_content ? other.m_content->Clone() : nullptr)
    {}

    /*!
     * \brief Move constructor.
     *
     * \since ids_peak_common 1.0
     */
    Any(Any&& other) noexcept = default;

    /*!
     * \brief Copy assignment operator.
     *
     * \since ids_peak_common 1.0
     */
    Any& operator=(const Any& other)
    {
        if (this != &other)
        {
            m_content = other.m_content ? other.m_content->Clone() : nullptr;
        }
        return *this;
    }

    /*!
     * \brief Move assignment operator.
     *
     * \since ids_peak_common 1.0
     */
    Any& operator=(Any&& other) noexcept = default;

    /*!
     * \brief Clears the stored value.
     *
     * \since ids_peak_common 1.0
     */
    void Reset()
    {
        m_content.reset();
    }

    /*!
     * \brief Gets the type of the stored value.
     *
     * \return Type info of the stored value, or `typeid(void)` if empty.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD const std::type_info& GetType() const
    {
        return m_content ? m_content->Type() : typeid(void);
    }

    /*!
     * \brief Casts the stored value to the specified type.
     *
     * \tparam T The expected type of the stored value.
     * \return Reference to the value.
     * \throws InvalidCastException if the types do not match.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    T& AnyCast()
    {
        using namespace std::string_literals;

        if (typeid(T) != GetType())
        {
            throw InvalidCastException(
                "Casting from "s + GetType().name() + " to the given type " + typeid(T).name() + " is not supported!");
        }
        return static_cast<Holder<T>*>(m_content.get())->value;
    }

    /*!
     * \brief Const version of AnyCast.
     *
     * \tparam T The expected type of the stored value.
     * \return Const reference to the value.
     * \throws InvalidCastException if the types do not match.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    PEAK_COMMON_NO_DISCARD const T& AnyCast() const
    {
        using namespace std::string_literals;

        if (typeid(T) != GetType())
        {
            throw InvalidCastException(
                "Casting from "s + GetType().name() + " to the given type " + typeid(T).name() + " is not supported!");
        }
        return static_cast<const Holder<T>*>(m_content.get())->value;
    }

    /*!
     * \brief Checks if the Any contains a value.
     *
     * \return True if a value is stored, false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool HasValue() const
    {
        return m_content != nullptr;
    }
};

} // namespace common 
} // namespace peak
