// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_INTERFACE_TYPES_H__
#define __TELLUSIM_INTERFACE_TYPES_H__

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * FontStyle
	 *
	\*****************************************************************************/
	
	/**
	 * FontStyle
	 */
	struct FontStyle {
		
		FontStyle() { }
		explicit FontStyle(uint32_t size) : size(size) { }
		explicit FontStyle(const Color &color) : color(color) { }
		FontStyle(uint32_t size, const Color &color) : size(size), color(color) { }
		
		uint32_t size = 16;						// font size
		uint32_t scale = 100;					// font scale
		
		bool fixed = false;						// font width
		bool kerning = true;					// font kerning
		Vector2f spacing = Vector2f::zero;		// font spacing
		Color color = Color::white;				// font color
		
		Vector3f offset = Vector3f::zero;		// shadow offset
		Color shadow = Color::black;			// shadow color
	};
	
	/*****************************************************************************\
	 *
	 * FontBatch
	 *
	\*****************************************************************************/
	
	/*
	 */
	struct FontBatch {
		
		FontBatch() { }
		FontBatch(const Vector3f &position, const char *str) : position(position), str(str) { }
		FontBatch(const Vector3f &position, const FontStyle *style, const char *str) : position(position), style(style), str(str) { }
		
		Vector3f position = Vector3f::zero;		// font position
		Color color = Color::white;				// font color
		
		const FontStyle *style = nullptr;		// font style
		const char *str = nullptr;				// font text
	};
	
	/*
	 */
	struct FontBatch32 {
		
		FontBatch32() { }
		FontBatch32(const Vector3f &position, const uint32_t *str) : position(position), str(str) { }
		FontBatch32(const Vector3f &position, const FontStyle *style, const uint32_t *str) : position(position), style(style), str(str) { }
		
		Vector3f position = Vector3f::zero;		// font position
		Color color = Color::white;				// font color
		
		const FontStyle *style = nullptr;		// font style
		const uint32_t *str = nullptr;			// font text
	};
	
	/*****************************************************************************\
	 *
	 * StrokeStyle
	 *
	\*****************************************************************************/
	
	/**
	 * StokeStyle
	 */
	struct StrokeStyle {
		
		StrokeStyle() { }
		explicit StrokeStyle(float32_t width) : width(width) { }
		explicit StrokeStyle(const Color &color) : color(color) { }
		StrokeStyle(float32_t width, float32_t offset) : width(width), offset(offset) { }
		StrokeStyle(float32_t width, const Color &color) : width(width), color(color) { }
		StrokeStyle(float32_t width, float32_t offset, const Color &color) : width(width), offset(offset), color(color) { }
		
		float32_t width = 0.0f;					// stroke width
		float32_t offset = 0.0f;				// stroke offset
		
		Color color = Color::white;				// stroke color
	};
	
	/*****************************************************************************\
	 *
	 * GradientStyle
	 *
	\*****************************************************************************/
	
	/**
	 * GradientStyle
	 */
	struct GradientStyle {
		
		GradientStyle() { }
		GradientStyle(const Color &c0, const Color &c1) : color_0(c0), color_1(c1) { }
		GradientStyle(float32_t radius, const Vector2f &center) : radius(radius), center(center) { }
		GradientStyle(float32_t length, const Vector2f &center, const Vector2f &axis) : length(length), center(center), axis(axis) { }
		GradientStyle(float32_t radius, const Vector2f &center, const Color &c0, const Color &c1) : radius(radius), center(center), color_0(c0), color_1(c1) { }
		GradientStyle(float32_t length, const Vector2f &center, const Vector2f &axis, const Color &c0, const Color &c1) : length(length), center(center), axis(axis), color_0(c0), color_1(c1) { }
		
		float32_t radius = 0.0f;				// gradient radius
		float32_t length = 0.0f;				// gradient length
		
		Vector2f center = Vector2f::zero;		// gradient center
		Vector2f axis = Vector2f::zero;			// gradient axis
		
		Color color_0 = Color::white;			// first color
		Color color_1 = Color::black;			// second color
	};
	
	/*****************************************************************************\
	 *
	 * Rectangle
	 *
	\*****************************************************************************/
	
	/**
	 * Rect
	 */
	struct Rect {
		
		Rect() : left(Maxf32), right(-Maxf32), bottom(Maxf32), top(-Maxf32) { }
		explicit Rect(float32_t value) : left(value), right(value), bottom(value), top(value) { }
		Rect(float32_t horizontal, float32_t vertical) : left(horizontal), right(horizontal), bottom(vertical), top(vertical) { }
		Rect(float32_t left, float32_t right, float32_t bottom, float32_t top) : left(left), right(right), bottom(bottom), top(top) { }
		
		/// check rectangle
		TS_INLINE bool isValid() const { return (left < right && bottom < top); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// expand by point
		Rect &expand(float32_t x, float32_t y) {
			left = min(left, x);
			right = max(right, x);
			bottom = min(bottom, y);
			top = max(top, y);
			return *this;
		}
		
		/// expand by rectangle
		Rect &expand(const Rect &rect) {
			left = min(left, rect.left);
			right = max(right, rect.right);
			bottom = min(bottom, rect.bottom);
			top = max(top, rect.top);
			return *this;
		}
		
		/// shrink by rectangle
		Rect &shrink(const Rect &rect) {
			left = max(left, rect.left);
			right = min(right, rect.right);
			bottom = max(bottom, rect.bottom);
			top = min(top, rect.top);
			return *this;
		}
		
		/// inside point
		TS_INLINE bool inside(float32_t x, float32_t y) const {
			return (left <= x && x <= right && bottom <= y && y <= top);
		}
		TS_INLINE bool inside(const Vector2f &v) const {
			return (left <= v.x && v.x <= right && bottom <= v.y && v.y <= top);
		}
		TS_INLINE bool inside(const Rect &rect) const {
			return (left <= rect.right && rect.left <= right && bottom <= rect.top && rect.bottom <= top);
		}
		
		/// rectangle size
		TS_INLINE Vector2f getSize() const {
			return Vector2f(right - left, top - bottom);
		}
		TS_INLINE float32_t getWidth() const {
			return right - left;
		}
		TS_INLINE float32_t getHeight() const {
			return top - bottom;
		}
		
		/// center of rectangle
		TS_INLINE Vector2f getCenter() const {
			return Vector2f(left + right, bottom + top) * 0.5f;
		}
		TS_INLINE float32_t getCenterX() const {
			return (left + right) * 0.5f;
		}
		TS_INLINE float32_t getCenterY() const {
			return (bottom + top) * 0.5f;
		}
		
		/// rectangle to vector operators
		TS_INLINE Rect &operator+=(const Vector2f &v) {
			left += v.x; right += v.x; bottom += v.y; top += v.y;
			return *this;
		}
		TS_INLINE Rect &operator-=(const Vector2f &v) {
			left -= v.x; right -= v.x; bottom -= v.y; top -= v.y;
			return *this;
		}
		
		/// rectangle to rectangle operators
		TS_INLINE Rect &operator+=(const Rect &r) {
			left -= r.left; right += r.right; bottom -= r.bottom; top += r.top;
			return *this;
		}
		TS_INLINE Rect &operator-=(const Rect &r) {
			left += r.left; right -= r.right; bottom += r.bottom; top -= r.top;
			return *this;
		}
		
		union {
			struct {
				float32_t left;					// left coordinate
				float32_t right;				// right coordinate
				float32_t bottom;				// bottom coordinate
				float32_t top;					// top coordinate
			};
			float32_t rect[4];
		};
	};
	
	/// rectangle comparison operators
	TS_INLINE bool operator==(const Rect &r0, const Rect &r1) {
		return (r0.left == r1.left && r0.right == r1.right && r0.bottom == r1.bottom && r0.top == r1.top);
	}
	
	TS_INLINE bool operator!=(const Rect &r0, const Rect &r1) {
		return (r0.left != r1.left || r0.right != r1.right || r0.bottom != r1.bottom || r0.top != r1.top);
	}
	
	/// rectangle to vector operators
	TS_INLINE Rect operator*(const Rect &r, const Vector2f &v) {
		return Rect(r.left * v.x, r.right * v.x, r.bottom * v.y, r.top * v.y);
	}
	
	TS_INLINE Rect operator/(const Rect &r, const Vector2f &v) {
		return Rect(r.left / v.x, r.right / v.x, r.bottom / v.y, r.top / v.y);
	}
	
	TS_INLINE Rect operator+(const Rect &r, const Vector2f &v) {
		return Rect(r.left + v.x, r.right + v.x, r.bottom + v.y, r.top + v.y);
	}
	
	TS_INLINE Rect operator-(const Rect &r, const Vector2f &v) {
		return Rect(r.left - v.x, r.right - v.x, r.bottom - v.y, r.top - v.y);
	}
	
	/// rectangle to rectangle operators
	TS_INLINE Rect operator+(const Rect &r0, const Rect &r1) {
		return Rect(r0.left - r1.left, r0.right + r1.right, r0.bottom - r1.bottom, r0.top + r1.top);
	}
	
	TS_INLINE Rect operator-(const Rect &r0, const Rect &r1) {
		return Rect(r0.left + r1.left, r0.right - r1.right, r0.bottom + r1.bottom, r0.top - r1.top);
	}
	
	/// matrix to rectangle multiplication
	template <class Type> Rect operator*(const Matrix4x4<Type> &m, const Rect &r) {
		Vector2f center = Vector2f(r.getCenterX(), r.getCenterY());
		Vector2f radius = Vector2f(r.right, r.top) - center;
		float32_t x = (float32_t)(abs(m.m00) * radius.x + abs(m.m01) * radius.y);
		float32_t y = (float32_t)(abs(m.m10) * radius.x + abs(m.m11) * radius.y);
		center = m * center;
		return Rect(center.x - x, center.x + x, center.y - y, center.y + y);
	}
}

#endif /* __TELLUSIM_INTERFACE_TYPES_H__ */
