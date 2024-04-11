// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__
#define __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__

#include <core/TellusimString.h>
#include <core/TellusimArray.h>
#include <math/TellusimMath.h>
#include <TellusimFormat.h>
#include <TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * SeparableFilter class
	 */
	class TS_API SeparableFilter {
			
			TS_DECLARE_PTR(SeparableFilter, 0)
			
		public:
			
			/// Filter modes
			enum Mode {
				ModeHorizontal = 0,		// horizontal filter
				ModeVertical,			// vertical filter
				NumModes,
			};
			
			/// Filter flags
			enum Flags {
				FlagNone = 0,
				FlagRepeat		= (1 << 0),		// repeat border
				FlagZero		= (1 << 1),		// zero border
				DefaultFlags	= FlagNone,
			};
			
			SeparableFilter();
			~SeparableFilter();
			
			/// clear filter
			void clear();
			
			/// check filter
			bool isCreated(Format format, uint32_t size) const;
			
			/// input shader source
			/// \param src Shader source.
			void setInputSource(Mode mode, const char *src);
			String getInputSource(Mode mode) const;
			
			/// output shader source
			/// \param src Shader source.
			void setOutputSource(Mode mode, const char *src);
			String getOutputSource(Mode mode) const;
			
			/// create filter
			/// \param format Texture format.
			/// \param size Filter size in pixels, the actual filter size is (size * 2 + 1).
			bool create(const Device &device, Format format, uint32_t size, Flags flags = DefaultFlags);
			
			/// filter weights
			void setWeights(Mode mode, const Array<Vector4f> &weights, bool normalize = false);
			void setWeights(Mode mode, const Array<float32_t> &weights, bool normalize = false);
			
			/// Gaussian filter weights
			void setGaussianWeights(uint32_t size, const Vector4f &sigma);
			void setGaussianWeights(uint32_t size, float32_t sigma);
			
			/// Sobel filter weights
			void setSobelXWeights(uint32_t size);
			void setSobelYWeights(uint32_t size);
			
			/// box filter weights
			void setBoxWeights(uint32_t size);
			
			/// dispatch separable filter
			/// \param dest Destination texture.
			/// \param src Source texture.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source texture slice.
			/// \param values Filter parameters available for the source blocks.
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, const Vector4f &values = Vector4f::zero) const;
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Slice &src_slice, const Vector4f &values = Vector4f::zero) const;
			bool dispatch(Compute &compute, Mode mode, uint32_t size, Texture &dest, Texture &src, const Vector4f &values = Vector4f::zero) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(SeparableFilter::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_SEPARABLE_FILTER_H__ */
