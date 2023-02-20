#ifndef SWILMER_ITERATOR_TRAITS_HPP
#define SWILMER_ITERATOR_TRAITS_HPP

#include <type_traits>
#include <iterator>
#include "type_traits.hpp"

namespace ft
{
	template <class Iter, bool>
	struct _iterator_traits_impl
	{};

	template <class Iter>
	struct _iterator_traits_impl<Iter, true>
	{
		typedef typename Iter::difference_type   difference_type;
		typedef typename Iter::value_type        value_type;
		typedef typename Iter::pointer           pointer;
		typedef typename Iter::reference         reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class Iter, bool>
	struct _iterator_traits
	{};

	template <class Iter>
	struct _iterator_traits<Iter, true>
		: _iterator_traits_impl
		<
			Iter,
			std::is_convertible<typename Iter::iterator_category,
									std::input_iterator_tag>::value
				|| std::is_convertible<typename Iter::iterator_category,
											std::output_iterator_tag>::value
		>
	{};

	template <class>
	struct void_t
	{
		typedef void type;
	};

	template <class T>
	struct has_iterator_typedefs
	{
	private:
		struct two
		{
			char lx;
			char lxx;
		};

		template <class U>
		static two test(...);

		template <class U>
		static char test
		(
			typename void_t<typename U::iterator_category>::type* = nullptr,
			typename void_t<typename U::difference_type>::type* = nullptr,
			typename void_t<typename U::value_type>::type* = nullptr,
			typename void_t<typename U::reference>::type* = nullptr,
			typename void_t<typename U::pointer>::type* = nullptr
		);

	public:
		static const bool value = sizeof(test<T>(nullptr, nullptr, nullptr,
												 	nullptr, nullptr)) == 1;
	};

	template <class Iter>
	struct iterator_traits
		: _iterator_traits<Iter, has_iterator_typedefs<Iter>::value>
	{};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef typename remove_cv<T>::type value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct has_iterator_category
	{
	private:
		struct two
		{
			char lx;
			char lxx;
		};

		template <class U>
		static two test(...);

		template <class U>
		static char test(typename U::iterator_category* = nullptr);

	public:
		static const bool value = sizeof(test<T>(nullptr)) == 1;
	};

	template <class T, class U,
		bool = has_iterator_category<iterator_traits<T> >::value>
	struct has_iterator_category_convertible_to
		: std::is_convertible<typename iterator_traits<T>::iterator_category, U>
	{};

	template <class T, class U>
	struct has_iterator_category_convertible_to<T, U, false>
		: std::false_type
	{};

	template <class T>
	struct is_input_iterator
		: public has_iterator_category_convertible_to<T, std::input_iterator_tag>
	{};

	template <class T>
	struct is_random_access_iterator
		: public has_iterator_category_convertible_to<T, std::random_access_iterator_tag>
	{};
}

#endif //SWILMER_ITERATOR_TRAITS_HPP
