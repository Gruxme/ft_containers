/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:44 by abiari            #+#    #+#             */
/*   Updated: 2021/10/16 14:50:00 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools.hpp"
#include <memory>
#include <iterator>
#include <stdexcept>
#include <functional>
#include "../iterators/iterator_traits.hpp"

template <	typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> >
>	class	map
{
	typedef				Key												key_type;
	typedef				T												mapped_type;
	typedef	typename	ft::pair<const key_type, mapped_type>			value_type;
	typedef				Compare											key_compare;
	typedef																value_compare;
	typedef				Alloc											allocator_type;
	typedef				allocator_type::reference						reference;
	typedef				allocator_type::const_reference					const_reference;
	typedef				allocator_type::pointer							pointer;
	typedef				allocator_type::const_pointer					const_pointer;
	typedef	typename	ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef				size_t											size_type;
};
