#ifndef SWILMER_UTILS_HPP
#define SWILMER_UTILS_HPP

namespace ft
{
    template <class T>
    struct remove_const
    {
        typedef T type;
    };

    template <class T>
    struct remove_const<const T>
    {
        typedef T type;
    };

    template <class T>
    struct remove_volatile
    {
        typedef T type;
    };

    template <class T>
    struct remove_volatile<volatile T>
    {
        typedef T type;
    };

    template <class T>
    struct remove_cv
    {
        typedef typename remove_volatile<typename remove_const<T>::type>::type type;
    };

	template <class>     struct _is_integral                     { enum { value = 0 }; };
	template <>          struct _is_integral<bool>               { enum { value = 1 }; };
	template <>          struct _is_integral<char>               { enum { value = 1 }; };
	template <>          struct _is_integral<signed char>        { enum { value = 1 }; };
	template <>          struct _is_integral<unsigned char>      { enum { value = 1 }; };
#ifndef _LIBCPP_HAS_NO_WIDE_CHARACTERS
	template <>          struct _is_integral<wchar_t>            { enum { value = 1 }; };
#endif
#ifndef _LIBCPP_HAS_NO_CHAR8_T
	template <>          struct _is_integral<char8_t>            { enum { value = 1 }; };
#endif
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
	template <>          struct _is_integral<char16_t>           { enum { value = 1 }; };
	template <>          struct _is_integral<char32_t>           { enum { value = 1 }; };
#endif // _LIBCPP_HAS_NO_UNICODE_CHARS
	template <>          struct _is_integral<short>              { enum { value = 1 }; };
	template <>          struct _is_integral<unsigned short>     { enum { value = 1 }; };
	template <>          struct _is_integral<int>                { enum { value = 1 }; };
	template <>          struct _is_integral<unsigned int>       { enum { value = 1 }; };
	template <>          struct _is_integral<long>               { enum { value = 1 }; };
	template <>          struct _is_integral<unsigned long>      { enum { value = 1 }; };
	template <>          struct _is_integral<long long>          { enum { value = 1 }; };
	template <>          struct _is_integral<unsigned long long> { enum { value = 1 }; };
#ifndef _LIBCPP_HAS_NO_INT128
	template <>          struct _is_integral<__int128_t>         { enum { value = 1 }; };
	template <>          struct _is_integral<__uint128_t>        { enum { value = 1 }; };
#endif

    template <bool v>
    struct _bool_constant
    {
        static const bool           value = v;
        typedef bool                value_type;
        typedef _bool_constant      type;
        operator value_type() const { return value; }
    };

    template <class T>   struct is_integral
        : public _bool_constant<_is_integral<typename remove_cv<T>::type>::value> {};

    template<bool, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <class input_iterator1, class input_iterator2>
    bool lexicographical_compare(input_iterator1 first1, input_iterator1 last1,
								 input_iterator2 first2, input_iterator2 last2)
    {
		for (; first2 != last2; ++first1, ++first2)
		{
			if (first1 == last1 || *first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return false;
    }

    template<class input_iterator1, class input_iterator2>
    bool equal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
		{
            if (!(*first1 == *first2))
                return false;
        }
        return true;
    }

	template<class T>
	struct is_const { enum { value = 0 }; };

	template<class T>
	struct is_const<const T> { enum { value = 1 }; };

    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        // default
        pair()
            : first(first_type())
            , second(second_type())
        {}

        // copy
        template<class K, class V>
        pair(const pair<K, V> &pr)
            : first(static_cast<T1>(pr.first))
            , second(static_cast<T2>(pr.second))
        {}

        // initialization
        pair(const first_type &a, const second_type &b)
            : first(a)
            , second(b)
        {}

        template <class T>
        typename enable_if<!is_const<T>::value, pair &>::type
        operator=(const pair &src)
        {
            if (this == &src)
                return *this;
            this->first = src.first;
            this->second = src.second;
            return *this;
        }
    };

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return !(lhs == rhs); }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return !(rhs < lhs); }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return rhs < lhs; }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    { return !(lhs < rhs); }

    template <class T1,class T2>
    pair<T1, T2> make_pair(T1 a, T2 b)
    {
        return pair<T1, T2>(a, b);
    }

    template <class T1,class T2>
    std::ostream &operator<<(std::ostream &o, const pair<T1, T2> &pair)
    {
        o << pair.first << " => " << pair.second;
        return o;
    }

    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T                   value_type;
        typedef integral_constant   type;

        operator value_type() const {return value;}
    };

    typedef integral_constant<bool,(true)>  true_type;
    typedef integral_constant<bool,(false)> false_type;

    template <class T, class U> struct is_same       : public false_type {};
    template <class T>          struct is_same<T, T> : public true_type {};
}

#endif //SWILMER_UTILS_HPP
