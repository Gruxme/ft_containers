/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:24:37 by abiari            #+#    #+#             */
/*   Updated: 2021/10/04 17:05:18 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	// class random_access_iterator_tag {};
	// class input_iterator_tag {};
	// class output_iterator_tag {};
	// class forward_iterator_tag {};
	// class bidirectional_iterator_tag {};
	
	template < class T >
	struct iterator_traits
	{
        typedef typename T::difference_type		difference_type;
		typedef typename T::value_type			value_type;
        typedef typename T::pointer				pointer;
        typedef typename T::reference			reference;
        typedef typename T::iterator_category	iterator_category;
	};
	
	template < class T >
	struct iterator_traits<T*>
	{
        typedef ptrdiff_t						difference_type;
		typedef T										value_type;
        typedef T*										pointer;
        typedef T&										reference;
        typedef typename std::random_access_iterator_tag	iterator_category;
	};
	
	template < class T >
	struct iterator_traits<const T*>
	{
        typedef ptrdiff_t						difference_type;
		typedef T										value_type;
        typedef const T*								pointer;
        typedef const T&								reference;
        typedef typename std::random_access_iterator_tag	iterator_category;
	};
	
	template < class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator
	{
    		typedef Category  iterator_category;
			typedef T         value_type;
    		typedef Distance  difference_type;
    		typedef Pointer   pointer;
    		typedef Reference reference;
	};
}
