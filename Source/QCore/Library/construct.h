﻿/********************************************************************
	created:	2012/11/29
	created:	29:11:2012   23:32
	filename: 	\QCore\Library\construct.h
	file path:	\QCore\Library
	file base:	construct
	file ext:	h
	author:		lwch
	
	purpose:	
*********************************************************************/

#ifndef _QLANGUAGE_LIBRARY_CONSTRUCT_H_
#define _QLANGUAGE_LIBRARY_CONSTRUCT_H_

#include <new>
#include "algo.h"
#include "traits.h"

namespace QLanguage
{
    namespace Library
    {
        template <typename T>
        inline void construct(T* p)
        {
            new (p) T();
        }

        template <typename Iterator>
        inline void construct_range(Iterator first, Iterator last)
        {
            while (first != last)
            {
                new (&*first) typename iterator_traits<Iterator>::value_type();
                ++first;
            }
        }

        template <typename T1, typename T2>
        inline void construct(T1* p, const T2& value)
        {
            new (p) T1(value);
        }

        template <typename T1, typename T2, typename T3>
        inline void construct(T1* p, const T2& v1, const T3& v2)
        {
            new (p) T1(v1, v2);
        }

        template <typename T1, typename T2, typename T3, typename T4>
        inline void construct(T1* p, const T2& v1, const T3& v2, const T4& v3)
        {
            new (p) T1(v1, v2, v3);
        }

        template <typename T1, typename T2, typename T3, typename T4, typename T5>
        inline void construct(T1* p, const T2& v1, const T3& v2, const T4& v3, const T5& v4)
        {
            new (p) T1(v1, v2, v3, v4);
        }

        template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        inline void construct(T1* p, const T2& v1, const T3& v2, const T4& v3, const T5& v4, const T6& v5)
        {
            new (p) T1(v1, v2, v3, v4, v5);
        }

        template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        inline void construct(T1* p, const T2& v1, const T3& v2, const T4& v3, const T5& v4, const T6& v5, const T7& v6)
        {
            new (p) T1(v1, v2, v3, v4, v5, v6);
        }

        template <typename T>
        inline void destruct(T* p, __true_type*)
        {
            p->~T();
        }

        template <typename T>
        inline void destruct(T*, __false_type*)
        {
        }

        template <typename Iterator>
        inline void destruct_range(Iterator first, Iterator last)
        {
            while (first != last)
            {
                destruct(&*first, has_destruct(*first));
                ++first;
            }
        }

        template <class InputIterator, class ForwardIterator>
        inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
        {
            while (first != last)
            {
                construct(&*result, *first);
                ++result;
                ++first;
            }
            return result;
        }

        template <class ForwardIterator, class Size, class T>
        inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, const T& x)
        {
            return uninitialized_fill_n_aux(first, count, x, is_POD(x));
        }

        template <class ForwardIterator, class Size, class T>
        inline ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size count, const T& x, __true_type*)
        {
            return fill_n(first, count, x);
        }

        template <class ForwardIterator, class Size, class T>
        inline ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size count, const T& x, __false_type*)
        {
            while(count--)
            {
                construct(&*first, x);
                ++first;
            }
            return first;
        }
    }
}

#endif