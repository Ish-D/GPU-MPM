// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_KERNEL_H__
#define __TELLUSIM_PLATFORM_KERNEL_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	class Stream;
	class Shader;
	
	/**
	 * Kernel class
	 */
	class TS_API Kernel {
			
			TS_DECLARE_PTR(Kernel, 0)
			
		public:
			
			Kernel();
			virtual ~Kernel();
			
			/// kernel platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// kernel device index
			uint32_t getIndex() const;
			
			/// clear kernel
			void clear();
			
			/// check kernel
			bool isCreated() const;
			
			/// kernel name
			void setName(const char *name);
			String getName() const;
			
			/// create kernel
			bool create();
			
			/// kernel parameters
			void setParameters(const Kernel &kernel);
			bool saveState(Stream &stream) const;
			
			/// shader pointer
			void setShader(Shader &shader, bool owner = false);
			
			Shader getComputeShader() const;
			
			/// load shaders
			bool loadShader(const char *name, const char *format, ...) TS_PRINTF(3, 4);
			bool loadShaderGLSL(const char *name, const char *format, ...) TS_PRINTF(3, 4);
			bool loadShader(const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderGLSL(const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderSPIRV(const char *name);
			
			/// create shaders
			bool createShader(const char *src, const char *format, ...) TS_PRINTF(3, 4);
			bool createShaderGLSL(const char *src, const char *format, ...) TS_PRINTF(3, 4);
			bool createShader(const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderGLSL(const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderSPIRV(const Array<uint32_t> &data);
			
			/// sampler parameters
			uint32_t addSampler();
			Kernel &setSamplers(uint32_t num);
			uint32_t getNumSamplers() const;
			
			Kernel &setSamplerOffset(uint32_t offset);
			uint32_t getSamplerOffset() const;
			
			Kernel &setSamplerArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSamplerArray(uint32_t index) const;
			
			/// texture parameters
			uint32_t addTexture();
			Kernel &setTextures(uint32_t num);
			uint32_t getNumTextures() const;
			
			Kernel &setTextureOffset(uint32_t offset);
			uint32_t getTextureOffset() const;
			
			Kernel &setTextureArray(uint32_t index, uint32_t num, bool array);
			uint32_t getTextureArray(uint32_t index) const;
			
			/// surface parameters
			uint32_t addSurface();
			Kernel &setSurfaces(uint32_t num);
			uint32_t getNumSurfaces() const;
			
			Kernel &setSurfaceOffset(uint32_t offset);
			uint32_t getSurfaceOffset() const;
			
			Kernel &setSurfaceArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSurfaceArray(uint32_t index) const;
			
			/// uniform parameters
			uint32_t addUniform(bool dynamic = true);
			Kernel &setUniforms(uint32_t num, bool dynamic = true);
			uint32_t getNumUniforms() const;
			
			Kernel &setUniformOffset(uint32_t offset);
			uint32_t getUniformOffset() const;
			
			Kernel &setUniformDynamic(uint32_t index, bool dynamic);
			bool getUniformDynamic(uint32_t index) const;
			
			Kernel &setUniformDynamics(uint32_t index, uint32_t num, bool dynamic);
			uint32_t getUniformDynamics() const;
			
			/// storage parameters
			uint32_t addStorage(bool dynamic = true);
			Kernel &setStorages(uint32_t num, bool dynamic = true);
			uint32_t getNumStorages() const;
			
			Kernel &setStorageOffset(uint32_t offset);
			uint32_t getStorageOffset() const;
			
			Kernel &setStorageDynamic(uint32_t index, bool dynamic);
			bool getStorageDynamic(uint32_t index) const;
			
			Kernel &setStorageDynamics(uint32_t index, uint32_t num, bool dynamic);
			uint32_t getStorageDynamics() const;
			
			/// tracing parameters
			uint32_t addTracing();
			Kernel &setTracings(uint32_t num);
			uint32_t getNumTracings() const;
			
			Kernel &setTracingOffset(uint32_t offset);
			uint32_t getTracingOffset() const;
			
			/// texel parameters
			uint32_t addTexel();
			Kernel &setTexels(uint32_t num);
			uint32_t getNumTexels() const;
			
			Kernel &setTexelOffset(uint32_t offset);
			uint32_t getTexelOffset() const;
			
			/// table parameters
			uint32_t addTable(uint32_t size);
			uint32_t getNumTables() const;
			
			Kernel &setTableSize(uint32_t index, uint32_t size);
			uint32_t getTableSize(uint32_t index) const;
			
			/// thread group size
			void setGroupSize(uint32_t width, uint32_t height = 1, uint32_t depth = 1);
			
			uint32_t getGroupSizeX() const;
			uint32_t getGroupSizeY() const;
			uint32_t getGroupSizeZ() const;
	};
	
	/**
	 * FUKernel
	 */
	class TS_API FUKernel : public Kernel {
			
			TS_DECLARE_PTR_1(FUKernel, Kernel, 0)
			
		public:
			
			FUKernel();
			explicit FUKernel(const Array<Kernel> &kernels, bool owner = false);
			virtual ~FUKernel();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion kernels
			uint32_t getNumKernels() const;
			const Kernel getKernel(uint32_t index) const;
			Kernel getKernel(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_KERNEL_H__ */
