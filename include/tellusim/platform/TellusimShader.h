// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_SHADER_H__
#define __TELLUSIM_PLATFORM_SHADER_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Stream;
	
	/**
	 * Shader class
	 */
	class TS_API Shader {
			
			TS_DECLARE_PTR(Shader, 0)
			
		public:
			
			/// Shader types
			enum Type {
				TypeUnknown = 0,
				TypeVertex,			// vertex shader
				TypeControl,		// tessellation control shader
				TypeEvaluate,		// tessellation evaluate shader
				TypeGeometry,		// geometry shader
				TypeFragment,		// fragment shader
				TypeCompute,		// compute shader
				TypeTask,			// task shader
				TypeMesh,			// mesh shader
				TypeRayGen,			// ray gen shader
				TypeRayMiss,		// ray miss shader
				TypeClosest,		// ray closest shader
				TypeFirstHit,		// ray first hit shader
				TypeIntersection,	// ray intersection shader
				TypeCallable,		// ray callable shader
				NumTypes,
			};
			
			/// Shader masks
			enum Mask {
				MaskNone = 0,
				MaskVertex			= (1 << TypeVertex),			// vertex shader mask
				MaskControl			= (1 << TypeControl),			// tessellation control shader mask
				MaskEvaluate		= (1 << TypeEvaluate),			// tessellation evaluate shader mask
				MaskGeometry		= (1 << TypeGeometry),			// geometry shader mask
				MaskFragment		= (1 << TypeFragment),			// fragment shader mask
				MaskCompute			= (1 << TypeCompute),			// compute shader mask
				MaskTask			= (1 << TypeTask),				// task shader mask
				MaskMesh			= (1 << TypeMesh),				// mesh shader mask
				MaskRayGen			= (1 << TypeRayGen),			// ray gen shader mask
				MaskRayMiss			= (1 << TypeRayMiss),			// ray miss shader mask
				MaskClosest			= (1 << TypeClosest),			// closest shader mask
				MaskFirstHit		= (1 << TypeFirstHit),			// first hit shader mask
				MaskIntersection	= (1 << TypeIntersection),		// intersection shader mask
				MaskCallable		= (1 << TypeCallable),			// callable shader mask
				MaskVertexFragment	= (MaskVertex | MaskFragment),
				MaskGraphics		= (MaskVertex | MaskControl | MaskEvaluate | MaskGeometry | MaskFragment),
				MaskTracing			= (MaskRayGen | MaskRayMiss | MaskClosest | MaskFirstHit | MaskIntersection | MaskCallable),
				MaskAll				= (MaskGraphics | MaskCompute | MaskTask | MaskMesh | MaskTracing),
			};
			
			Shader();
			virtual ~Shader();
			
			/// shader platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// shader device index
			uint32_t getIndex() const;
			
			/// clear shader
			void clear();
			
			/// check shader
			bool isCreated() const;
			
			/// shader parameters
			bool saveState(Stream &stream) const;
			
			/// shader type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isVertex() const { return (getType() == TypeVertex); }
			TS_INLINE bool isControl() const { return (getType() == TypeControl); }
			TS_INLINE bool isEvaluate() const { return (getType() == TypeEvaluate); }
			TS_INLINE bool isGeometry() const { return (getType() == TypeGeometry); }
			TS_INLINE bool isFragment() const { return (getType() == TypeFragment); }
			TS_INLINE bool isCompute() const { return (getType() == TypeCompute); }
			TS_INLINE bool isTask() const { return (getType() == TypeTask); }
			TS_INLINE bool isMesh() const { return (getType() == TypeMesh); }
			TS_INLINE bool isRayGen() const { return (getType() == TypeRayGen); }
			TS_INLINE bool isRayMiss() const { return (getType() == TypeRayMiss); }
			TS_INLINE bool isClosest() const { return (getType() == TypeClosest); }
			TS_INLINE bool isFirstHit() const { return (getType() == TypeFirstHit); }
			TS_INLINE bool isIntersection() const { return (getType() == TypeIntersection); }
			TS_INLINE bool isCallable() const { return (getType() == TypeCallable); }
			
			TS_INLINE bool isGraphicsType() const { return (getType() >= TypeVertex && getType() <= TypeFragment); }
			TS_INLINE bool isTessellationType() const { return (getType() >= TypeControl && getType() <= TypeEvaluate); }
			TS_INLINE bool isTracingType() const { return (getType() >= TypeRayGen && getType() <= TypeCallable); }
			TS_INLINE bool isMeshType() const { return (getType() >= TypeTask && getType() <= TypeMesh); }
			
			/// shader name
			String getName() const;
			String getMacros() const;
			
			/// shader samplers
			void setSamplerOffset(int32_t offset);
			int32_t getSamplerOffset() const;
			
			/// shader textures
			void setTextureOffset(int32_t offset);
			int32_t getTextureOffset() const;
			
			/// shader surfaces
			void setSurfaceOffset(int32_t offset);
			int32_t getSurfaceOffset() const;
			
			/// shader uniforms
			void setUniformOffset(int32_t offset);
			int32_t getUniformOffset() const;
			
			/// shader storages
			void setStorageOffset(int32_t offset);
			int32_t getStorageOffset() const;
			
			/// shader tracings
			void setTracingOffset(int32_t offset);
			int32_t getTracingOffset() const;
			
			/// shader texels
			void setTexelOffset(int32_t offset);
			int32_t getTexelOffset() const;
			
			/// shader tables
			void setTableOffset(int32_t offset);
			int32_t getTableOffset() const;
			
			/// shader patch size
			void setPatchSize(uint32_t size);
			uint32_t getPatchSize() const;
			
			/// shader input size
			void setInputSize(uint32_t size);
			uint32_t getInputSize() const;
			
			/// shader output size
			void setOutputSize(uint32_t size);
			uint32_t getOutputSize() const;
			
			/// create native shader
			bool load(Type type, const char *name, const char *format, ...) TS_PRINTF(4, 5);
			bool create(Type type, const char *src, const char *format, ...) TS_PRINTF(4, 5);
			bool load(Type type, const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool create(Type type, const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			
			/// create GLSL shader
			bool loadGLSL(Type type, const char *name, const char *format, ...) TS_PRINTF(4, 5);
			bool createGLSL(Type type, const char *src, const char *format, ...) TS_PRINTF(4, 5);
			bool loadGLSL(Type type, const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createGLSL(Type type, const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			
			/// create SPIR-V shader
			bool loadSPIRV(Type type, const char *name);
			bool createSPIRV(Type type, const Array<uint32_t> &data);
			
			/// global shader cache
			static bool hasCache();
			static bool setCache(const char *name);
			static bool loadCache(const String &hash, Stream &stream);
			static bool saveCache(const String &hash, Stream &stream);
			static void clearCache();
			
			/// global macro definitions
			static bool isMacro(const char *name);
			static bool setMacro(const char *name, int32_t value);
			static bool setMacro(const char *name, uint32_t value);
			static bool setMacro(const char *name, const char *value = nullptr);
			static bool setMacros(const char *macros);
			static bool removeMacro(const char *name);
			static void clearMacros();
			
			/// global include definitions
			static bool isInclude(const char *name);
			static bool setInclude(const char *name, const String &src);
			static bool removeInclude(const char *name);
			static void clearIncludes();
			
			/// global macro preprocessor
			static String preprocessor(const char *src, const char *format, ...) TS_PRINTF(2, 3);
			static String preprocessor(const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
	};
	
	/**
	 */
	class TS_API ShaderCompiler : public Shader {
			
			TS_DECLARE_PTR_1(ShaderCompiler, Shader, 0)
				
		public:
			
			ShaderCompiler();
			virtual ~ShaderCompiler();
			
			/// shader binary
			bool getBinary(Stream &stream, Platform platform = PlatformUnknown) const;
			
			/// shader source
			String getSource(Platform platform = PlatformUnknown) const;
	};
	
	/**
	 * D3D12Shader
	 */
	class TS_API D3D12Shader : public Shader {
			
			TS_DECLARE_PTR_1(D3D12Shader, Shader, 0)
			
		public:
			
			D3D12Shader();
			virtual ~D3D12Shader();
			
			void *getShaderBlob() const;
	};
	
	/**
	 * D3D11Shader
	 */
	class TS_API D3D11Shader : public Shader {
			
			TS_DECLARE_PTR_1(D3D11Shader, Shader, 0)
			
		public:
			
			D3D11Shader();
			virtual ~D3D11Shader();
			
			void *getD3D11Shader() const;
			void *getShaderBlob() const;
	};
	
	/**
	 * MTLShader
	 */
	class TS_API MTLShader : public Shader {
			
			TS_DECLARE_PTR_1(MTLShader, Shader, 0)
			
		public:
			
			MTLShader();
			virtual ~MTLShader();
			
			void setIndirect(bool enabled);
			bool isIndirect() const;
			
			void *getLibrary() const;
			void *getFunction() const;
	};
	
	/**
	 * VKShader
	 */
	class TS_API VKShader : public Shader {
			
			TS_DECLARE_PTR_1(VKShader, Shader, 0)
			
		public:
			
			VKShader();
			virtual ~VKShader();
			
			VkShaderModule getModule() const;
	};
	
	/**
	 * GLShader
	 */
	class TS_API GLShader : public Shader {
			
			TS_DECLARE_PTR_1(GLShader, Shader, 0)
			
		public:
			
			GLShader();
			virtual ~GLShader();
			
			bool attachShader(uint32_t program_id);
			
			uint32_t getShaderType() const;
			uint32_t getShaderID() const;
	};
	
	/**
	 * GLESShader
	 */
	class TS_API GLESShader : public Shader {
			
			TS_DECLARE_PTR_1(GLESShader, Shader, 0)
			
		public:
			
			GLESShader();
			virtual ~GLESShader();
			
			bool attachShader(uint32_t program_id);
			
			uint32_t getShaderType() const;
			uint32_t getShaderID() const;
	};
	
	/**
	 * CUShader
	 */
	class TS_API CUShader : public Shader {
			
			TS_DECLARE_PTR_1(CUShader, Shader, 0)
			
		public:
			
			CUShader();
			virtual ~CUShader();
			
			CUmodule getModule() const;
			CUfunction getFunction() const;
	};
	
	/**
	 * HIPShader
	 */
	class TS_API HIPShader : public Shader {
			
			TS_DECLARE_PTR_1(HIPShader, Shader, 0)
			
		public:
			
			HIPShader();
			virtual ~HIPShader();
			
			void *getModule() const;
			void *getFunction() const;
	};
	
	/**
	 * FUShader
	 */
	class TS_API FUShader : public Shader {
			
			TS_DECLARE_PTR_1(FUShader, Shader, 0)
			
		public:
			
			FUShader();
			explicit FUShader(const Array<Shader> &shaders, bool owner = false);
			virtual ~FUShader();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion shaders
			uint32_t getNumShaders() const;
			const Shader getShader(uint32_t index) const;
			Shader getShader(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Shader::Mask)
}

#endif /* __TELLUSIM_PLATFORM_SHADER_H__ */
