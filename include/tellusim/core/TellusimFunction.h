// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_FUNCTION_H__
#define __TELLUSIM_CORE_FUNCTION_H__

#include <core/TellusimType.h>

/*
 */
namespace Tellusim {
	
	/**
	 * FunctionType template
	 */
	template <class Func> struct FunctionType {
		using Ret = typename FunctionType<decltype(&Func::operator())>::Ret;
		using Args = typename FunctionType<decltype(&Func::operator())>::Args;
		using Type = Func;
		using Class = void;
	};
	template <class FuncRet, class... FuncArgs> struct FunctionType<FuncRet(FuncArgs...)> {
		using Ret = FuncRet;
		using Args = TypeList<FuncArgs...>;
		using Type = FuncRet (*)(FuncArgs...);
		using Class = void;
	};
	template <class FuncRet, class... FuncArgs> struct FunctionType<FuncRet (*)(FuncArgs...)> {
		using Ret = FuncRet;
		using Args = TypeList<FuncArgs...>;
		using Type = FuncRet (*)(FuncArgs...);
		using Class = void;
	};
	template <class FuncClass, class FuncRet, class... FuncArgs> struct FunctionType<FuncRet (FuncClass::*)(FuncArgs...)> {
		using Ret = FuncRet;
		using Args = TypeList<FuncArgs...>;
		using Type = FuncRet (FuncClass::*)(FuncArgs...);
		using Class = FuncClass;
	};
	template <class FuncClass, class FuncRet, class... FuncArgs> struct FunctionType<FuncRet (FuncClass::*)(FuncArgs...) const> {
		using Ret = FuncRet;
		using Args = TypeList<FuncArgs...>;
		using Type = FuncRet (FuncClass::*)(FuncArgs...) const;
		using Class = FuncClass;
	};
	
	/**
	 * Function template
	 */
	template <class Type> class Function {
			
		public:
			
			/// function type
			using Ret = typename FunctionType<Type>::Ret;
			using Args = typename FunctionType<Type>::Args;
			using Func = typename FunctionType<Type>::Type;
			using Class = typename FunctionType<Type>::Class;
			
			/// function arguments
			using A0 = typename TypeListAt< 0, Args>::Type;
			using A1 = typename TypeListAt< 1, Args>::Type;
			using A2 = typename TypeListAt< 2, Args>::Type;
			using A3 = typename TypeListAt< 3, Args>::Type;
			using A4 = typename TypeListAt< 4, Args>::Type;
			using A5 = typename TypeListAt< 5, Args>::Type;
			using A6 = typename TypeListAt< 6, Args>::Type;
			using A7 = typename TypeListAt< 7, Args>::Type;
			enum { Length = TypeListLength<Args>::Result };
			
			/// constructors
			Function() : c(nullptr), func(nullptr), lambda(nullptr) { }
			Function(const Function &f) : c(f.c), func(f.func), lambda(nullptr), a0(f.a0), a1(f.a1), a2(f.a2), a3(f.a3), a4(f.a4), a5(f.a5), a6(f.a6), a7(f.a7) { if(f.lambda) lambda = f.lambda->clone(); }
			Function(Function &&f) : c(f.c), func(f.func), lambda(f.lambda), a0(f.a0), a1(f.a1), a2(f.a2), a3(f.a3), a4(f.a4), a5(f.a5), a6(f.a6), a7(f.a7) { f.lambda = nullptr; }
			
			/// function constructors
			Function(const Func &func) : c(nullptr), func(func), lambda(nullptr) { }
			Function(const Func &func, A0 a0) : c(nullptr), func(func), lambda(nullptr), a0(a0) { }
			Function(const Func &func, A0 a0, A1 a1) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			Function(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : c(nullptr), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			
			/// member function constructors
			Function(Class *c, const Func &func) : c(c), func(func), lambda(nullptr) { }
			Function(Class *c, const Func &func, A0 a0) : c(c), func(func), lambda(nullptr), a0(a0) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			Function(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : c(c), func(func), lambda(nullptr), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			
			/// lambda function constructors
			template <class Func> Function(Func func) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)) { }
			template <class Func> Function(Func func, A0 a0) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0) { }
			template <class Func> Function(Func func, A0 a0, A1 a1) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2, A3 a3) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2), a3(a3) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			template <class Func> Function(Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) : c(nullptr), func(nullptr), lambda(new Lambda<Func>(func, &func)), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			
			/// destructor
			~Function() { delete lambda; }
			
			/// assignment operators
			Function &operator=(const Function &f) {
				if(&f == this) return *this;
				c = f.c; func = f.func;
				delete lambda; lambda = nullptr;
				if(f.lambda) lambda = f.lambda->clone();
				a0 = f.a0; a1 = f.a1; a2 = f.a2; a3 = f.a3;
				a4 = f.a4; a5 = f.a5; a6 = f.a6; a7 = f.a7;
				return *this;
			}
			Function &operator=(Function &&f) {
				c = f.c; func = f.func;
				delete lambda; lambda = f.lambda; f.lambda = nullptr;
				a0 = move(f.a0); a1 = move(f.a1); a2 = move(f.a2); a3 = move(f.a3);
				a4 = move(f.a4); a5 = move(f.a5); a6 = move(f.a6); a7 = move(f.a7);
				return *this;
			}
			Function &operator=(Func f) {
				c = nullptr; func = f;
				delete lambda; lambda = nullptr;
				return *this;
			}
			template <class Func> Function &operator=(Func f) {
				c = nullptr; func = nullptr;
				delete lambda; lambda = new Lambda<Func>(f, &f);
				return *this;
			}
			
			/// compare functions
			bool operator==(const Function &f) const {
				if(lambda && f.lambda) return (lambda->ptr == f.lambda->ptr);
				if(!lambda && !f.lambda) return (c == f.c && f.func == f.func);
				return false;
			}
			bool operator!=(const Function &f) const {
				if(lambda && f.lambda) return (lambda->ptr != f.lambda->ptr);
				if(!lambda && !f.lambda) return (c != f.c || f.func != f.func);
				return true;
			}
			
			/// check function
			TS_INLINE bool empty() const {
				return (func == nullptr && lambda == nullptr);
			}
			explicit TS_INLINE operator bool() const {
				return (func != nullptr || lambda != nullptr);
			}
			
			/// clear function
			void clear() {
				c = nullptr;
				func = nullptr;
				delete lambda;
				lambda = nullptr;
			}
			
			/// class pointer
			template <class Class> TS_INLINE void setClass(Class *p) { c = p; }
			template <class Class> TS_INLINE Class *getClass() const { return c; }
			
			/// set function arguments
			template <class Arg> TS_INLINE void setArg0(Arg arg) { a0 = arg; }
			template <class Arg> TS_INLINE void setArg1(Arg arg) { a1 = arg; }
			template <class Arg> TS_INLINE void setArg2(Arg arg) { a2 = arg; }
			template <class Arg> TS_INLINE void setArg3(Arg arg) { a3 = arg; }
			template <class Arg> TS_INLINE void setArg4(Arg arg) { a4 = arg; }
			template <class Arg> TS_INLINE void setArg5(Arg arg) { a5 = arg; }
			template <class Arg> TS_INLINE void setArg6(Arg arg) { a6 = arg; }
			template <class Arg> TS_INLINE void setArg7(Arg arg) { a7 = arg; }
			
			/// get function arguments
			template <class Arg> TS_INLINE const Arg getArg0() const { return a0; }
			template <class Arg> TS_INLINE const Arg getArg1() const { return a1; }
			template <class Arg> TS_INLINE const Arg getArg2() const { return a2; }
			template <class Arg> TS_INLINE const Arg getArg3() const { return a3; }
			template <class Arg> TS_INLINE const Arg getArg4() const { return a4; }
			template <class Arg> TS_INLINE const Arg getArg5() const { return a5; }
			template <class Arg> TS_INLINE const Arg getArg6() const { return a6; }
			template <class Arg> TS_INLINE const Arg getArg7() const { return a7; }
			
			/// run function
			TS_INLINE Ret run() const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2, A3 a3) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			
			/// run functor
			TS_INLINE Ret operator()() const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2, A3 a3) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Ret operator()(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return do_run(c, IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
			
		private:
			
			/// lambda function
			struct LambdaBase {
				LambdaBase(void *ptr) : ptr(ptr) { }
				virtual ~LambdaBase() { }
				virtual Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const = 0;
				virtual LambdaBase *clone() const = 0;
				void *ptr;
			};
			
			template <class Func> struct Lambda final : public LambdaBase {
				Lambda(const Func &func, void *ptr) : LambdaBase(ptr), func(func) { }
				TS_INLINE Ret do_run(IntToType< 0>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(); }
				TS_INLINE Ret do_run(IntToType< 1>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0); }
				TS_INLINE Ret do_run(IntToType< 2>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1); }
				TS_INLINE Ret do_run(IntToType< 3>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2); }
				TS_INLINE Ret do_run(IntToType< 4>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2, a3); }
				TS_INLINE Ret do_run(IntToType< 5>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2, a3, a4); }
				TS_INLINE Ret do_run(IntToType< 6>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2, a3, a4, a5); }
				TS_INLINE Ret do_run(IntToType< 7>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2, a3, a4, a5, a6); }
				TS_INLINE Ret do_run(IntToType< 8>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return func(a0, a1, a2, a3, a4, a5, a6, a7); }
				virtual Ret run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return do_run(IntToType<Length>(), a0, a1, a2, a3, a4, a5, a6, a7); }
				virtual LambdaBase *clone() const { return new Lambda(func, LambdaBase::ptr); }
				Func func;
			};
			
			/// run function
			TS_INLINE Ret do_run(void *c, IntToType< 0>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(); }
			TS_INLINE Ret do_run(void *c, IntToType< 1>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0); }
			TS_INLINE Ret do_run(void *c, IntToType< 2>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1); }
			TS_INLINE Ret do_run(void *c, IntToType< 3>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2); }
			TS_INLINE Ret do_run(void *c, IntToType< 4>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2, a3); }
			TS_INLINE Ret do_run(void *c, IntToType< 5>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2, a3, a4); }
			TS_INLINE Ret do_run(void *c, IntToType< 6>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2, a3, a4, a5); }
			TS_INLINE Ret do_run(void *c, IntToType< 7>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE Ret do_run(void *c, IntToType< 8>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { if(lambda) return lambda->run(a0, a1, a2, a3, a4, a5, a6, a7); return func(a0, a1, a2, a3, a4, a5, a6, a7); }
			
			/// run member function
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 0>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 1>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 2>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 3>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 4>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2, a3); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 5>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2, a3, a4); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 6>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2, a3, a4, a5); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 7>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2, a3, a4, a5, a6); }
			template <class Class> TS_INLINE Ret do_run(Class *c, IntToType< 8>, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const { return (c->*func)(a0, a1, a2, a3, a4, a5, a6, a7); }
			
			Class *c;
			Func func;
			LambdaBase *lambda;
			A0 a0; A1 a1; A2 a2; A3 a3;
			A4 a4; A5 a5; A6 a6; A7 a7;
	};
	
	/**
	 * Make function
	 */
	template <class Func> Function<Func> makeFunction(const Func &func) {
		return Function<Func>(func);
	}
	
	template <class Func, class A0> Function<Func> makeFunction(const Func &func, A0 a0) {
		return Function<Func>(func, a0);
	}
	
	template <class Func, class A0, class A1> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1) {
		return Function<Func>(func, a0, a1);
	}
	
	template <class Func, class A0, class A1, class A2> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2) {
		return Function<Func>(func, a0, a1, a2);
	}
	
	template <class Func, class A0, class A1, class A2, class A3> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
		return Function<Func>(func, a0, a1, a2, a3);
	}
	
	template <class Func, class A0, class A1, class A2, class A3, class A4> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) {
		return Function<Func>(func, a0, a1, a2, a3, a4);
	}
	
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
		return Function<Func>(func, a0, a1, a2, a3, a4, a5);
	}
	
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
		return Function<Func>(func, a0, a1, a2, a3, a4, a5, a6);
	}
	
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7> Function<Func> makeFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
		return Function<Func>(func, a0, a1, a2, a3, a4, a5, a6, a7);
	}
	
	/**
	 * Make class member function
	 */
	template <class Class, class Func> Function<Func> makeClassFunction(Class *c, const Func &func) {
		return Function<Func>(c, func);
	}
	
	template <class Class, class Func, class A0> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0) {
		return Function<Func>(c, func, a0);
	}
	
	template <class Class, class Func, class A0, class A1> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1) {
		return Function<Func>(c, func, a0, a1);
	}
	
	template <class Class, class Func, class A0, class A1, class A2> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2) {
		return Function<Func>(c, func, a0, a1, a2);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
		return Function<Func>(c, func, a0, a1, a2, a3);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3, class A4> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) {
		return Function<Func>(c, func, a0, a1, a2, a3, a4);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3, class A4, class A5> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
		return Function<Func>(c, func, a0, a1, a2, a3, a4, a5);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
		return Function<Func>(c, func, a0, a1, a2, a3, a4, a5, a6);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7> Function<Func> makeClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
		return Function<Func>(c, func, a0, a1, a2, a3, a4, a5, a6, a7);
	}
}

#endif /* __TELLUSIM_CORE_FUNCTION_H__ */
