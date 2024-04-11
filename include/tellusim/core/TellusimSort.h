// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SORT_H__
#define __TELLUSIM_CORE_SORT_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Elements sort
	 *
	\*****************************************************************************/
	
	/*
	 */
	template <class Type> void sort3(Type &v0, Type &v1, Type &v2) {
		if(v0 > v1) swap(v0, v1);
		if(v1 > v2) swap(v1, v2);
		if(v0 > v1) swap(v0, v1);
	}
	
	/*
	 */
	template <class Type> void sort4(Type &v0, Type &v1, Type &v2, Type &v3) {
		if(v0 > v1) swap(v0, v1);
		if(v2 > v3) swap(v2, v3);
		if(v0 > v2) swap(v0, v2);
		if(v1 > v3) swap(v1, v3);
		if(v1 > v2) swap(v1, v2);
	}
	
	/*****************************************************************************\
	 *
	 * quickSort
	 *
	\*****************************************************************************/
	
	/**
	 * quickSort default compare
	 */
	template <class Type> struct QuickCompare {
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			if(q0 < q1) return -1;
			if(q0 > q1) return 1;
			return 0;
		}
	};
	
	template <class Type> struct QuickInverseCompare {
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			if(q0 > q1) return -1;
			if(q0 < q1) return 1;
			return 0;
		}
	};
	
	/**
	 * quickSort function compare
	 */
	template <class Type, class Func> struct QuickFunctionCompare {
		QuickFunctionCompare(const Func &func) : func(func) { }
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			return func(q0, q1);
		}
		Func func;
	};
	
	/**
	 * quickSort
	 * \brief Sort typed array.
	 */
	template <class Type, class Compare = QuickCompare<Type>, class Index = int32_t, uint32_t StackSize = 512> void quickSort(Type *data, uint32_t size, Compare compare = QuickCompare<Type>()) {
		
		if(size < 2) return;
		
		int32_t depth = 0;
		Index stack[StackSize];
		stack[0] = 0;
		stack[1] = size - 1;
		
		while(depth >= 0) {
			Index left = stack[depth + 0];
			Index right = stack[depth + 1];
			Index l = left;
			Index r = right;
			Type value = data[(l + r) >> 1];
			do {
				while(r > left && compare(value, data[r]) < 0) r--;
				while(l < right && compare(value, data[l]) > 0) l++;
				if(l < r) swap(data[l++], data[r--]);
				else if(l == r) { l++; r--; }
			} while(l <= r);
			if(left < r) {
				if(l < right) {
					TS_ASSERT(depth + 4 < (int32_t)StackSize && "quickSort(): stack overflow");
					if(r - left > right - l) {
						stack[depth + 1] = r;
						stack[depth + 2] = l;
						stack[depth + 3] = right;
					} else {
						stack[depth + 0] = l;
						stack[depth + 2] = left;
						stack[depth + 3] = r;
					}
					depth += 2;
				} else {
					stack[depth + 1] = r;
				}
			} else if(l < right) {
				stack[depth + 0] = l;
			} else {
				depth -= 2;
			}
		}
	}
	
	/**
	 * quickSort
	 * \brief Sort typed array with parameters.
	 */
	template <class Type, class Parameter, class Compare = QuickCompare<Type>, class Index = int32_t, uint32_t StackSize = 512> void quickSort(Type *data, Parameter *parameters, uint32_t size, Compare compare = QuickCompare<Type>()) {
		
		if(size < 2) return;
		
		int32_t depth = 0;
		Index stack[StackSize];
		stack[0] = 0;
		stack[1] = size - 1;
		
		while(depth >= 0) {
			Index left = stack[depth + 0];
			Index right = stack[depth + 1];
			Index l = left;
			Index r = right;
			Type value = data[(l + r) >> 1];
			do {
				while(r > left && compare(value, data[r]) < 0) r--;
				while(l < right && compare(value, data[l]) > 0) l++;
				if(l < r) swap(data[l], data[r]), swap(parameters[l++], parameters[r--]);
				else if(l == r) { l++; r--; }
			} while(l <= r);
			if(left < r) {
				if(l < right) {
					TS_ASSERT(depth + 4 < StackSize && "quickSort(): stack overflow");
					if(r - left > right - l) {
						stack[depth + 1] = r;
						stack[depth + 2] = l;
						stack[depth + 3] = right;
					} else {
						stack[depth + 0] = l;
						stack[depth + 2] = left;
						stack[depth + 3] = r;
					}
					depth += 2;
				} else {
					stack[depth + 1] = r;
				}
			} else if(l < right) {
				stack[depth + 0] = l;
			} else {
				depth -= 2;
			}
		}
	}
}

#endif /* __TELLUSIM_CORE_SORT_H__ */
