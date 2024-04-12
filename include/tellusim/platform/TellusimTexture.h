// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TEXTURE_H__
#define __TELLUSIM_PLATFORM_TEXTURE_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * Texture class
	 */
	class TS_API Texture {
			
			TS_DECLARE_PTR(Texture, 0)
			
		public:
			
			/// Texture types
			enum Type {
				TypeUnknown = 0,
				Type2D,
				Type3D,
				TypeCube,
				NumTypes,
			};
			
			/// Texture flags
			enum Flags {
				FlagNone = 0,
				FlagRead				= (1 << 0),		// read texture
				FlagWrite				= (1 << 1),		// write texture
				FlagTarget				= (1 << 2),		// target texture
				FlagBuffer				= (1 << 3),		// buffer texture
				FlagSource				= (1 << 4),		// source texture
				FlagSparse				= (1 << 5),		// sparse texture
				FlagShared				= (1 << 6),		// shared texture
				FlagExtern				= (1 << 7),		// extern texture
				FlagInterop				= (1 << 8),		// interop texture
				FlagSurface				= (1 << 9),		// surface texture
				FlagMutable				= (1 << 10),	// mutable texture
				FlagMipmaps				= (1 << 11),	// mipmaps texture
				FlagGenerate			= (1 << 12),	// generate mipmaps
				FlagFormatNorm			= (1 << 13),	// convert to norm format
				FlagFormatSRGB			= (1 << 14),	// convert to sRGB format
				FlagFormatSigned		= (1 << 15),	// convert to signed format
				FlagMultisample2		= (1 << 16),	// 2x multisample texture
				FlagMultisample4		= (1 << 17),	// 4x multisample texture
				FlagMultisample8		= (1 << 18),	// 8x multisample texture
				FlagClearOne			= (1 << 19),	// clear value is one
				FlagClearZero			= (1 << 20),	// clear value is zero
				FlagClearNormal			= (1 << 21),	// clear value is normal
				FlagMultisample			= (FlagMultisample2 | FlagMultisample4 | FlagMultisample8),
				DefaultFlags			= FlagNone,
				NumFlags = 22,
			};
			
			Texture();
			virtual ~Texture();
			
			/// texture platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// texture device index
			uint32_t getIndex() const;
			
			/// clear texture
			void clear();
			
			/// check texture
			bool isCreated() const;
			
			/// texture name
			void setName(const char *name);
			String getName() const;
			
			/// create texture
			bool create(Type type, Format format, const Size &size, uint32_t layers, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t size, Flags flags = DefaultFlags);
			bool create3D(Format format, uint32_t size, Flags flags = DefaultFlags);
			bool createCube(Format format, uint32_t size, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t width, uint32_t height, Flags flags = DefaultFlags);
			bool create3D(Format format, uint32_t width, uint32_t height, uint32_t depth, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t width, uint32_t height, uint32_t layers, Flags flags = DefaultFlags);
			bool createCube(Format format, uint32_t size, uint32_t layers, Flags flags = DefaultFlags);
			
			/// texture type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool is2DType() const { return (getType() == Type2D); }
			TS_INLINE bool is3DType() const { return (getType() == Type3D); }
			TS_INLINE bool isCubeType() const { return (getType() == TypeCube); }
			
			/// texture format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE bool isColorFormat() const { return Tellusim::isColorFormat(getFormat()); }
			TS_INLINE bool isDepthFormat() const { return Tellusim::isDepthFormat(getFormat()); }
			TS_INLINE bool isPixelFormat() const { return Tellusim::isPixelFormat(getFormat()); }
			TS_INLINE bool isPlainFormat() const { return Tellusim::isPlainFormat(getFormat()); }
			TS_INLINE bool isMixedFormat() const { return Tellusim::isMixedFormat(getFormat()); }
			TS_INLINE bool isBlockFormat() const { return Tellusim::isBlockFormat(getFormat()); }
			TS_INLINE bool isStencilFormat() const { return Tellusim::isStencilFormat(getFormat()); }
			
			TS_INLINE bool isNormFormat() const { return Tellusim::isNormFormat(getFormat()); }
			TS_INLINE bool isSRGBFormat() const { return Tellusim::isSRGBFormat(getFormat()); }
			TS_INLINE bool isFloatFormat() const { return Tellusim::isFloatFormat(getFormat()); }
			TS_INLINE bool isSignedFormat() const { return Tellusim::isSignedFormat(getFormat()); }
			TS_INLINE bool isUnsignedFormat() const { return Tellusim::isUnsignedFormat(getFormat()); }
			TS_INLINE bool isIntegerFormat() const { return Tellusim::isIntegerFormat(getFormat()); }
			
			TS_INLINE bool isi8Format() const { return Tellusim::isi8Format(getFormat()); }
			TS_INLINE bool isu8Format() const { return Tellusim::isu8Format(getFormat()); }
			TS_INLINE bool is8BitFormat() const { return Tellusim::is8BitFormat(getFormat()); }
			
			TS_INLINE bool isi16Format() const { return Tellusim::isi16Format(getFormat()); }
			TS_INLINE bool isu16Format() const { return Tellusim::isu16Format(getFormat()); }
			TS_INLINE bool isf16Format() const { return Tellusim::isf16Format(getFormat()); }
			TS_INLINE bool is16BitFormat() const { return Tellusim::is16BitFormat(getFormat()); }
			
			TS_INLINE bool isi32Format() const { return Tellusim::isi32Format(getFormat()); }
			TS_INLINE bool isu32Format() const { return Tellusim::isu32Format(getFormat()); }
			TS_INLINE bool isf32Format() const { return Tellusim::isf32Format(getFormat()); }
			TS_INLINE bool is32BitFormat() const { return Tellusim::is32BitFormat(getFormat()); }
			
			TS_INLINE bool isi64Format() const { return Tellusim::isi64Format(getFormat()); }
			TS_INLINE bool isu64Format() const { return Tellusim::isu64Format(getFormat()); }
			TS_INLINE bool isf64Format() const { return Tellusim::isf64Format(getFormat()); }
			TS_INLINE bool is64BitFormat() const { return Tellusim::is64BitFormat(getFormat()); }
			
			TS_INLINE bool isBC15Format() const { return Tellusim::isBC15Format(getFormat()); }
			TS_INLINE bool isBC67Format() const { return Tellusim::isBC67Format(getFormat()); }
			TS_INLINE bool isETC2Format() const { return Tellusim::isETC2Format(getFormat()); }
			TS_INLINE bool isASTCFormat() const { return Tellusim::isASTCFormat(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			TS_INLINE uint32_t getPixelSize() const { return getFormatPixelSize(getFormat()); }
			TS_INLINE uint32_t getBlockSize() const { return getFormatBlockSize(getFormat()); }
			TS_INLINE uint32_t getBlockWidth() const { return getFormatBlockWidth(getFormat()); }
			TS_INLINE uint32_t getBlockHeight() const { return getFormatBlockHeight(getFormat()); }
			
			/// texture flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// texture multisample
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			
			/// texture dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			uint32_t getLayers() const;
			uint32_t getMipmaps() const;
			uint32_t findMipmap(const Size &size) const;
			uint32_t getWidth(uint32_t mipmap) const;
			uint32_t getHeight(uint32_t mipmap) const;
			uint32_t getDepth(uint32_t mipmap) const;
			
			TS_INLINE bool hasFaces() const { return (getFaces() > 1); }
			TS_INLINE bool hasLayers() const { return (getLayers() > 1); }
			TS_INLINE bool hasMipmaps() const { return (getMipmaps() > 1); }
			
			Size getSize() const;
			Region getRegion() const;
			Slice getSlice() const;
			Size getSize(uint32_t mipmap) const;
			Region getRegion(uint32_t mipmap) const;
			Slice getSlice(uint32_t mipmap) const;
			
			/// sparse texture dimension
			uint32_t getTileWidth() const;
			uint32_t getTileHeight() const;
			uint32_t getTileDepth() const;
			uint32_t getTileMipmaps() const;
			
			Size getTileSize() const;
			
			/// texture description
			String getDescription() const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * TextureTable class
	 */
	class TS_API TextureTable {
			
			TS_DECLARE_PTR(TextureTable, 0)
			
		public:
			
			TextureTable();
			virtual ~TextureTable();
			
			/// table platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// table device index
			uint32_t getIndex() const;
			
			/// clear table
			void clear();
			
			/// check table
			bool isCreated() const;
			
			/// table name
			void setName(const char *name);
			String getName() const;
			
			/// create table
			bool create(uint32_t size);
			
			/// table textures
			uint32_t getSize() const;
			Texture get(uint32_t index) const;
			bool isOwner(uint32_t index) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * D3D12Texture
	 */
	class TS_API D3D12Texture : public Texture {
			
			TS_DECLARE_PTR_1(D3D12Texture, Texture, 0)
			
		public:
			
			D3D12Texture();
			virtual ~D3D12Texture();
			
			/// create external texture
			bool create(Type type, ID3D12Resource *texture, uint32_t state, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			uint32_t getDXGIFormat() const;
			ID3D12Resource *getD3D12Texture() const;
			size_t getShaderResourceView() const;
			size_t getRenderTargetView() const;
			size_t getDepthStencilView() const;
			size_t getUnorderedAccessView() const;
			
			void setTextureState(uint32_t state);
			uint32_t getTextureState() const;
			
			void *getSharedHandle() const;
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * D3D11Texture
	 */
	class TS_API D3D11Texture : public Texture {
			
			TS_DECLARE_PTR_1(D3D11Texture, Texture, 0)
			
		public:
			
			D3D11Texture();
			virtual ~D3D11Texture();
			
			/// create external texture
			bool create(Type type, ID3D11Texture2D *texture, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			uint32_t getDXGIFormat() const;
			ID3D11Texture2D *getD3D11Texture() const;
			ID3D11ShaderResourceView *getShaderResourceView() const;
			ID3D11RenderTargetView *getRenderTargetView() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
			ID3D11UnorderedAccessView *getUnorderedAccessView() const;
			
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * MTLTexture
	 */
	class TS_API MTLTexture : public Texture {
			
			TS_DECLARE_PTR_1(MTLTexture, Texture, 0)
			
		public:
			
			MTLTexture();
			virtual ~MTLTexture();
			
			/// create external texture
			bool create(void *texture, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			uint32_t getPixelFormat() const;
			uint32_t getTextureType() const;
			void *getMTLTexture() const;
			
			void *getMTLBuffer() const;
			
			void *getSharedPtr() const;
			
			using Texture::create;
	};
	
	/**
	 * VKTexture
	 */
	class TS_API VKTexture : public Texture {
			
			TS_DECLARE_PTR_1(VKTexture, Texture, 0)
			
		public:
			
			VKTexture();
			virtual ~VKTexture();
			
			/// create external texture
			bool create(Type type, uint32_t format, VkImage texture, uint32_t layout, Flags flags = DefaultFlags, Format texture_format = FormatUnknown);
			
			uint32_t getPixelFormat() const;
			VkImage getVKTexture() const;
			VkImageView getTextureView() const;
			
			void setTextureLayout(uint32_t layout);
			uint32_t getTextureLayout() const;
			
			void getTextureRange(void *range, const Slice &slice) const;
			
			void *getSharedPtr() const;
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * GLTexture
	 */
	class TS_API GLTexture : public Texture {
			
			TS_DECLARE_PTR_1(GLTexture, Texture, 0)
			
		public:
			
			GLTexture();
			virtual ~GLTexture();
			
			/// create external texture
			bool create(uint32_t target, uint32_t texture_id, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			uint32_t getTarget() const;
			uint32_t getInternalFormat() const;
			uint32_t getTextureID() const;
			
			using Texture::create;
	};
	
	/**
	 * GLESTexture
	 */
	class TS_API GLESTexture : public Texture {
			
			TS_DECLARE_PTR_1(GLESTexture, Texture, 0)
			
		public:
			
			GLESTexture();
			virtual ~GLESTexture();
			
			/// create external texture
			bool create(uint32_t target, uint32_t texture_id, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			uint32_t getTarget() const;
			uint32_t getInternalFormat() const;
			uint32_t getTextureID() const;
			
			using Texture::create;
	};
	
	/**
	 * CUTexture
	 */
	class TS_API CUTexture : public Texture {
			
			TS_DECLARE_PTR_1(CUTexture, Texture, 0)
			
		public:
			
			CUTexture();
			virtual ~CUTexture();
			
			CUmipmappedArray getTextureArray() const;
			CUarray getTextureLevel(uint32_t index) const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			CUexternalMemory getSharedMemory() const;
	};
	
	/**
	 * HIPTexture
	 */
	class TS_API HIPTexture : public Texture {
			
			TS_DECLARE_PTR_1(HIPTexture, Texture, 0)
			
		public:
			
			HIPTexture();
			virtual ~HIPTexture();
			
			void *getTextureArray() const;
			void *getTextureLevel(uint32_t index) const;
			const void *getChannelFormat() const;
	};
	
	/**
	 * FUTexture
	 */
	class TS_API FUTexture : public Texture {
			
			TS_DECLARE_PTR_1(FUTexture, Texture, 0)
			
		public:
			
			FUTexture();
			explicit FUTexture(const Array<Texture> &textures, bool owner = false);
			virtual ~FUTexture();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion textures
			uint32_t getNumTextures() const;
			const Texture getTexture(uint32_t index) const;
			Texture getTexture(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Texture::Flags)
}

#endif /* __TELLUSIM_PLATFORM_TEXTURE_H__ */
