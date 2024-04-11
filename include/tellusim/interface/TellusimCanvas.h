// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_INTERFACE_CANVAS_H__
#define __TELLUSIM_INTERFACE_CANVAS_H__

#include <TellusimTypes.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <core/TellusimFunction.h>
#include <platform/TellusimSampler.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <interface/TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Font;
	class Image;
	class Texture;
	class Device;
	class Target;
	class Canvas;
	
	/**
	 * Canvas vertex
	 */
	struct CanvasVertex {
		Vector3f position;					// vertex position
		Vector2f texcoord;					// texture coordinates
		uint32_t color;						// RGBAu8 color
	};
	
	/**
	 * Canvas shape vertex
	 */
	struct CanvasShapeVertex {
		Vector4f position;					// vertex position
		Vector4f parameters;				// vertex parameters
		Vector2f texcoord;					// texture coordinates
		Vector2u padding;
	};
	
	/**
	 * Canvas strip vertex
	 */
	struct CanvasStripVertex {
		Vector4f position;					// vertex position
		Vector4f parameters;				// vertex parameters
		Vector4f adjacencies;				// vertex adjacencies
	};
	
	/**
	 * CanvasElement base class
	 */
	class TS_API CanvasElement {
			
		protected:
			
			friend class Canvas;
			
			TS_DECLARE_PTR(CanvasElement, 0)
			
		public:
			
			/// Element types
			enum Type {
				TypeUnknown = 0,
				TypeText,
				TypeMesh,
				TypeRect,
				TypeTriangle,
				TypeEllipse,
				TypeShape,
				TypeStrip,
				NumTypes,
			};
			
			/// Element modes
			enum Mode {
				ModeSolid = 0,				// solid color mode
				ModeTexture,				// sample based on texture coordinates
				ModeTextureFetch,			// sample based on fragment coordinates
				ModeTextureClamp,			// discard when texture coordinates out of [0-1] range
				ModeTextureCubic,			// cubic texture filter mode
				ModeTextureCubic3x3,		// cubic texture filter with 3x3 prefiltered area mode
				ModeTextureCubic5x5,		// cubic texture filter with 5x5 prefiltered area mode
				ModeTextureRed,				// red texture channel mode
				ModeTextureGreen,			// green texture channel mode
				ModeTextureBlue,			// blue texture channel mode
				ModeTextureAlpha,			// alpha texture channel mode
				ModeGradient,				// gradient mode
				NumModes,
			};
			
			/// Element alignments
			enum Align {
				AlignNone = 0,
				AlignLeft			= (1 << 0),
				AlignRight			= (1 << 1),
				AlignBottom			= (1 << 2),
				AlignTop			= (1 << 3),
				AlignCenterX		= (1 << 4),
				AlignCenterY		= (1 << 5),
				AlignLeftBottom		= (AlignLeft | AlignBottom),
				AlignLeftTop		= (AlignLeft | AlignTop),
				AlignRightBottom	= (AlignRight | AlignBottom),
				AlignRightTop		= (AlignRight | AlignTop),
				AlignCenter			= (AlignCenterX | AlignCenterY),
				NumAligns = 6,
			};
			
			/// Element stack operations
			enum Stack {
				StackNone = 0,
				StackPush		= (1 << 0),		// push into the stack
				StackPop		= (1 << 1),		// pop from the stack
				StackSet		= (1 << 2),		// replace top of the stack
				StackMul		= (1 << 3),		// multiply top of the stack
				StackGet		= (1 << 4),		// get top of the stack
			};
			
			CanvasElement();
			virtual ~CanvasElement();
			
			/// element type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isText() const { return (getType() == TypeText); }
			TS_INLINE bool isMesh() const { return (getType() == TypeMesh); }
			TS_INLINE bool isRect() const { return (getType() == TypeRect); }
			TS_INLINE bool isTriangle() const { return (getType() == TypeTriangle); }
			TS_INLINE bool isEllipse() const { return (getType() == TypeEllipse); }
			TS_INLINE bool isShape() const { return (getType() == TypeShape); }
			TS_INLINE bool isStrip() const { return (getType() == TypeStrip); }
			
			/// element canvas
			void setCanvas(Canvas &canvas);
			const Canvas getCanvas() const;
			Canvas getCanvas();
			
			/// element mode
			void setMode(Mode mode);
			Mode getMode() const;
			
			/// element align
			void setAlign(Align align);
			Align getAlign() const;
			
			TS_INLINE bool hasAlign(Align align) const { return ((getAlign() & align) != AlignNone); }
			TS_INLINE bool hasAligns(Align aligns) const { return ((getAlign() & aligns) == aligns); }
			
			/// element order
			void setOrder(int32_t order);
			int32_t getOrder() const;
			
			/// element enabled flag
			void setEnabled(bool enabled);
			bool isEnabled() const;
			
			/// element color
			void clearColor();
			void setColor(Stack op);
			void setColor(const Color &color, Stack op = StackNone);
			void setColor(float32_t r, float32_t g, float32_t b, float32_t a, Stack op = StackNone);
			const Color &getColor() const;
			Stack getColorOp() const;
			
			/// element transform
			void clearTransform();
			void setTransform(Stack op);
			void setTransform(const Matrix4x4f &transform, Stack op = StackNone);
			const Matrix4x4f &getTransform() const;
			Stack getTransformOp() const;
			
			/// element scissor
			void clearScissor();
			void setScissor(Stack op);
			void setScissor(const Rect &scissor, Stack op = StackNone);
			const Rect &getScissor() const;
			Stack getScissorOp() const;
			
			/// element mipmap number
			void setMipmap(float32_t mipmap);
			float32_t getMipmap() const;
			
			/// sampler pointer
			void setSampler(Sampler &sampler);
			Sampler getSampler() const;
				
			/// filter mode
			void setFilter(Sampler::Filter filter);
			Sampler::Filter getFilter() const;
			
			void setAnisotropy(uint32_t anisotropy);
			uint32_t getAnisotropy() const;
			
			/// wrapping mode
			void setWrapMode(Sampler::WrapMode mode);
			Sampler::WrapMode getWrapMode() const;
			
			/// texture pointer
			void setTexture(Texture &texture, bool linear = false);
			Texture getTexture() const;
			bool getTextureLinear() const;
			
			/// pipeline pointer
			void setPipeline(Pipeline pipeline);
			Pipeline getPipeline() const;
			
			/// rasterization parameters
			void setPrimitive(Pipeline::Primitive primitive);
			Pipeline::Primitive getPrimitive() const;
			
			void setCullMode(Pipeline::CullMode mode);
			Pipeline::CullMode getCullMode() const;
			
			void setFrontMode(Pipeline::FrontMode mode);
			Pipeline::FrontMode getFrontMode() const;
			
			/// blending parameters
			void setBlend(Pipeline::BlendOp op, Pipeline::BlendFunc src, Pipeline::BlendFunc dest);
			
			Pipeline::BlendOp getBlendOp() const;
			Pipeline::BlendFunc getBlendSrcFunc() const;
			Pipeline::BlendFunc getBlendDestFunc() const;
			
			/// color parameters
			void setColorMask(Pipeline::ColorMask mask);
			Pipeline::ColorMask getColorMask() const;
			
			/// depth parameters
			void setDepthMask(Pipeline::DepthMask mask);
			Pipeline::DepthMask getDepthMask() const;
			
			void setDepthFunc(Pipeline::DepthFunc func);
			Pipeline::DepthFunc getDepthFunc() const;
			
			/// stencil parameters
			void setStencilRef(uint32_t ref);
			void setStencilFunc(Pipeline::StencilFunc func, Pipeline::StencilOp fail_op, Pipeline::StencilOp dfail_op, Pipeline::StencilOp dpass_op);
			
			uint32_t getStencilRef() const;
			Pipeline::StencilFunc getStencilFunc() const;
			Pipeline::StencilOp getStencilFailOp() const;
			Pipeline::StencilOp getStencilDepthFailOp() const;
			Pipeline::StencilOp getStencilDepthPassOp() const;
			
			/// draw callback
			using DrawCallback = Function<bool(Command command, CanvasElement element)>;
			void setDrawCallback(const DrawCallback &func);
			DrawCallback getDrawCallback() const;
			
			/// element rectangle
			const Rect &getRect();
	};
	
	/**
	 * CanvasText class
	 */
	class TS_API CanvasText : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasText, CanvasElement, 0)
			
		public:
			
			CanvasText();
			explicit CanvasText(Canvas &canvas);
			explicit CanvasText(const char *text);
			CanvasText(const char *text, Canvas &canvas);
			virtual ~CanvasText();
			
			/// font name
			void setFontName(const char *name);
			void setFontName(const String &name);
			String getFontName() const;
			
			/// font color
			void setFontColor(const Color &color);
			const Color &getFontColor() const;
			
			/// font style
			bool setFontSize(uint32_t scale);
			uint32_t getFontSize() const;
			
			bool setFontScale(uint32_t scale);
			uint32_t getFontScale() const;
			
			bool setFontStyle(const FontStyle &style);
			const FontStyle &getFontStyleConst() const;
			const FontStyle &getFontStyle() const;
			FontStyle &getFontStyle();
			
			/// font position
			void setPosition(const Vector3f &position);
			void setPosition(float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getPosition() const;
			
			/// font text
			void setText(const char *text);
			void setText(const String &text);
			String getText() const;
			
			/// font batches
			void clearBatches();
			void setBatches(const Array<FontBatch> &batches);
			void setBatches(const FontBatch *batches, uint32_t num_batches);
	};
	
	/**
	 * CanvasMesh class
	 */
	class TS_API CanvasMesh : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasMesh, CanvasElement, 0)
			
		public:
			
			CanvasMesh();
			explicit CanvasMesh(Canvas &canvas);
			explicit CanvasMesh(Mode mode);
			CanvasMesh(Mode mode, Canvas &canvas);
			virtual ~CanvasMesh();
			
			/// texture name
			void setTextureName(const char *name);
			void setTextureName(const String &name);
			String getTextureName() const;
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// mesh vertices
			void clearVertices();
			void setNumVertices(uint32_t num_vertices);
			void reserveVertices(uint32_t num_vertices);
			uint32_t getNumVertices() const;
			
			void setVertices(const CanvasVertex *vertices, uint32_t num_vertices);
			void addVertices(const CanvasVertex *vertices, uint32_t num_vertices);
			const CanvasVertex *getVertices() const;
			CanvasVertex *getVertices();
			
			void setVertex(uint32_t index, const CanvasVertex &vertex);
			const CanvasVertex &getVertex(uint32_t index) const;
			CanvasVertex &getVertex(uint32_t index);
			
			/// vertex positions
			void setVertexPosition(uint32_t index, const Vector3f &position);
			void setVertexPosition(uint32_t index, float32_t x, float32_t y, float32_t z = 0.0f);
			Vector3f getVertexPosition(uint32_t index) const;
			
			/// vertex texture coordinates
			void setVertexTexCoord(uint32_t index, const Vector2f &texcoord);
			void setVertexTexCoord(uint32_t index, float32_t s, float32_t t);
			Vector2f getVertexTexCoord(uint32_t index) const;
			
			/// vertex colors
			void setVertexColor(uint32_t index, const Color &color);
			void setVertexColor(uint32_t index, uint32_t color);
			uint32_t getVertexColor(uint32_t index) const;
			
			/// add mesh vertex
			uint32_t addVertex(const Vector3f &position);
			uint32_t addVertex(const Vector3f &position, uint32_t color);
			uint32_t addVertex(const Vector3f &position, const Vector2f &texcoord);
			uint32_t addVertex(const Vector3f &position, const Vector2f &texcoord, uint32_t color);
			uint32_t addVertex(float32_t x, float32_t y, float32_t z, float32_t s, float32_t t, uint32_t color = 0xffffffffu);
			uint32_t addVertex(float32_t x, float32_t y, float32_t z, uint32_t color = 0xffffffffu);
			uint32_t addVertex(float32_t x, float32_t y, uint32_t color = 0xffffffffu);
			
			/// mesh indices
			void clearIndices();
			void setNumIndices(uint32_t num_indices);
			void reserveIndices(uint32_t num_indices);
			uint32_t getNumIndices() const;
			
			void setIndices(const uint32_t *indices, uint32_t num_indices);
			void addIndices(const uint32_t *indices, uint32_t num_indices);
			const uint32_t *getIndices() const;
			uint32_t *getIndices();
			
			void setIndex(uint32_t index, uint32_t value);
			uint32_t getIndex(uint32_t index) const;
			
			/// add mesh indices
			void addIndex(uint32_t i0);
			void addIndices(uint32_t i0, uint32_t i1);
			void addIndices(uint32_t i0, uint32_t i1, uint32_t i2);
			void addIndices(uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3);
			
			/// mesh rectangle
			void setRect(const Rect &rect);
	};
	
	/**
	 * CanvasRect class
	 */
	class TS_API CanvasRect : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasRect, CanvasElement, 0)
			
		public:
			
			CanvasRect();
			explicit CanvasRect(Canvas &canvas);
			explicit CanvasRect(float32_t radius);
			explicit CanvasRect(const Vector2f &size);
			CanvasRect(float32_t radius, Canvas &canvas);
			CanvasRect(float32_t radius, const Vector2f &size, Canvas &canvas);
			virtual ~CanvasRect();
			
			/// rect radius
			void setRadius(float32_t radius);
			float32_t getRadius() const;
			
			/// texture name
			void setTextureName(const char *name);
			void setTextureName(const String &name);
			String getTextureName() const;
			
			/// stroke color
			void setStrokeColor(const Color &color);
			const Color &getStrokeColor();
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// rect size
			void setSize(const Vector2f &size);
			void setSize(float32_t width, float32_t height);
			const Vector2f &getSize() const;
			float32_t getWidth() const;
			float32_t getHeight() const;
			
			/// rect position
			void setPosition(const Vector3f &position);
			void setPosition(float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getPosition() const;
			
			/// texture coordinates
			void setTexCoord(const Rect &texcoord);
			void setTexCoord(float32_t left, float32_t right, float32_t bottom, float32_t top);
			const Rect &getTexCoord() const;
	};
	
	/**
	 * CanvasTriangle class
	 */
	class TS_API CanvasTriangle : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasTriangle, CanvasElement, 0)
			
		public:
			
			CanvasTriangle();
			explicit CanvasTriangle(Canvas &canvas);
			explicit CanvasTriangle(float32_t radius);
			CanvasTriangle(float32_t radius, Canvas &canvas);
			virtual ~CanvasTriangle();
			
			/// triangle radius
			void setRadius(float32_t radius);
			float32_t getRadius() const;
			
			/// stroke color
			void setStrokeColor(const Color &color);
			const Color &getStrokeColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// triangle positions
			void setPosition0(const Vector3f &position);
			void setPosition1(const Vector3f &position);
			void setPosition2(const Vector3f &position);
			void setPosition0(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition1(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition2(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition(const Vector3f &position_0, const Vector3f &position_1, const Vector3f &position_2);
			const Vector3f &getPosition0() const;
			const Vector3f &getPosition1() const;
			const Vector3f &getPosition2() const;
	};
	
	/**
	 * CanvasEllipse class
	 */
	class TS_API CanvasEllipse : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasEllipse, CanvasElement, 0)
			
		public:
			
			CanvasEllipse();
			explicit CanvasEllipse(Canvas &canvas);
			explicit CanvasEllipse(float32_t radius);
			CanvasEllipse(float32_t radius, Canvas &canvas);
			virtual ~CanvasEllipse();
			
			/// ellipse radius
			void setRadius(float32_t radius);
			float32_t getRadius() const;
			
			/// texture name
			void setTextureName(const char *name);
			void setTextureName(const String &name);
			String getTextureName() const;
			
			/// stroke color
			void setStrokeColor(const Color &color);
			const Color &getStrokeColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// ellipse positions
			void setPosition(const Vector3f &position);
			void setPosition0(const Vector3f &position);
			void setPosition1(const Vector3f &position);
			void setPosition(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition0(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition1(float32_t x, float32_t y, float32_t z = 0.0f);
			void setPosition(const Vector3f &position_0, const Vector3f &position_1);
			const Vector3f &getPosition0() const;
			const Vector3f &getPosition1() const;
			
			/// texture coordinates
			void setTexCoord(const Rect &texcoord);
			void setTexCoord(float32_t left, float32_t right, float32_t bottom, float32_t top);
			const Rect &getTexCoord() const;
	};
	
	/**
	 * CanvasShape class
	 */
	class TS_API CanvasShape : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasShape, CanvasElement, 0)
			
		public:
			
			CanvasShape();
			explicit CanvasShape(Canvas &canvas);
			virtual ~CanvasShape();
			
			/// create shape from SVG path
			bool createSVG(const char *src, float32_t scale = 1.0f);
			
			/// stroke color
			void setStrokeColor(const Color &color);
			const Color &getStrokeColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// shape positions
			void clearPositions();
			void setNumPositions(uint32_t num_positions);
			void reservePositions(uint32_t num_positions);
			uint32_t getNumPositions() const;
			
			void setPositions(const Vector3f *positions, uint32_t num_positions);
			void addPositions(const Vector3f *positions, uint32_t num_positions);
			const Vector3f *getPositions() const;
			Vector3f *getPositions();
			
			void setPosition(uint32_t index, const Vector3f &position);
			void setPosition(uint32_t index, float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getPosition(uint32_t index) const;
			Vector3f &getPosition(uint32_t index);
			
			/// add shape position
			uint32_t addPosition(const Vector2f &position);
			uint32_t addPosition(const Vector3f &position);
			uint32_t addPosition(float32_t x, float32_t y, float32_t z = 0.0f);
	};
	
	/**
	 * CanvasStrip class
	 */
	class TS_API CanvasStrip : public CanvasElement {
			
			TS_DECLARE_PTR_1(CanvasStrip, CanvasElement, 0)
			
		public:
			
			explicit CanvasStrip();
			explicit CanvasStrip(Canvas &canvas);
			explicit CanvasStrip(float32_t width);
			CanvasStrip(float32_t width, Canvas &canvas);
			virtual ~CanvasStrip();
			
			/// strip width
			void setWidth(float32_t width);
			float32_t getWidth() const;
			
			/// strip offset
			void setOffset(float32_t offset);
			float32_t getOffset() const;
			
			/// stroke color
			void setStrokeColor(const Color &color);
			const Color &getStrokeColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// strip positions
			void clearPositions();
			void setNumPositions(uint32_t num_positions);
			void reservePositions(uint32_t num_positions);
			uint32_t getNumPositions() const;
			
			void setPositions(const Vector3f *positions, uint32_t num_positions);
			void addPositions(const Vector3f *positions, uint32_t num_positions);
			const Vector3f *getPositions() const;
			Vector3f *getPositions();
			
			void setPosition(uint32_t index, const Vector3f &position);
			void setPosition(uint32_t index, float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getPosition(uint32_t index) const;
			Vector3f &getPosition(uint32_t index);
			
			/// add strip position
			uint32_t addPosition(const Vector2f &position);
			uint32_t addPosition(const Vector3f &position);
			uint32_t addPosition(float32_t x, float32_t y, float32_t z = 0.0f);
	};
	
	/**
	 * Canvas class
	 */
	class TS_API Canvas {
			
			TS_DECLARE_PTR(Canvas, 0)
			
		public:
			
			Canvas();
			explicit Canvas(Canvas *parent);
			virtual ~Canvas();
			
			/// clear canvas
			void clear();
			
			/// check canvas
			bool isCreated() const;
			
			/// canvas scale
			uint32_t getScale(const Target &target, uint32_t scale = 100) const;
			
			/// create canvas
			bool create(const Device &device, Format color, Format depth, uint32_t multisample = 1, uint32_t scale = 100);
			bool create(const Device &device, const Target &target, uint32_t scale = 100);
			
			/// canvas parameters
			Format getColorFormat() const;
			Format getDepthFormat() const;
			uint32_t getMultisample() const;
			
			/// canvas order
			void setOrder(int32_t order);
			int32_t getOrder() const;
			
			/// canvas enabled flag
			void setEnabled(bool enabled);
			bool isEnabled() const;
			
			/// canvas viewport
			void setViewport(const Viewport &viewport);
			void setViewport(uint32_t width, uint32_t height);
			void setViewport(float32_t width, float32_t height);
			const Viewport &getViewport() const;
			float32_t getWidth() const;
			float32_t getHeight() const;
			
			/// canvas color
			void clearColor();
			void setColor(const Color &color);
			void setColor(float32_t r, float32_t g, float32_t b, float32_t a);
			const Color &getColor() const;
			
			/// canvas scissor
			void clearScissor();
			void setScissor(const Rect &scissor);
			const Rect &getScissor() const;
			
			/// canvas transform
			void clearTransform();
			void setTransform(const Matrix4x4f &transform);
			const Matrix4x4f &getTransform() const;
			
			/// canvas parent
			uint32_t setParent(Canvas &parent);
			const Canvas getParent() const;
			Canvas getParent();
			
			/// canvas children
			uint32_t addChild(Canvas &child);
			bool removeChild(Canvas &child);
			bool raiseChild(Canvas &child);
			bool lowerChild(Canvas &child);
			void releaseChildren();
			
			uint32_t findChild(const Canvas &child) const;
			bool isChild(const Canvas &child) const;
			
			uint32_t getNumChildren() const;
			const Array<Canvas> getChildren() const;
			Array<Canvas> getChildren();
			const Canvas getChild(uint32_t index) const;
			Canvas getChild(uint32_t index);
			
			/// canvas elements
			uint32_t addElement(CanvasElement &element);
			bool removeElement(CanvasElement &element);
			bool raiseElement(CanvasElement &element);
			bool lowerElement(CanvasElement &element);
			
			uint32_t findElement(const CanvasElement &element) const;
			bool isElement(const CanvasElement &element) const;
			
			uint32_t getNumElements() const;
			const Array<CanvasElement> getElements() const;
			Array<CanvasElement> getElements();
			const CanvasElement getElement(uint32_t index) const;
			CanvasElement getElement(uint32_t index);
			
			/// canvas fonts
			bool isFont(const char *name) const;
			bool addFont(const char *name, Stream &stream);
			bool addFont(const char *name, const uint8_t (*blob)[256]);
			void removeFont(const char *name);
			Font getFont(const char *name);
			
			/// canvas textures
			bool isTexture(const char *name) const;
			bool addTexture(const char *name, Stream &stream);
			bool addTexture(const char *name, Texture &texture);
			bool addTexture(const char *name, const uint8_t (*blob)[256]);
			void removeTexture(const char *name);
			Texture getTexture(const char *name);
			
			/// depth parameters
			void setDepthMask(Pipeline::DepthMask mask);
			Pipeline::DepthMask getDepthMask() const;
			
			void setDepthFunc(Pipeline::DepthFunc func);
			Pipeline::DepthFunc getDepthFunc() const;
			
			/// draw canvas
			void draw(Command &command, const Target &target);
			void draw(Command &command);
			
			/// create callback
			using CreateCallback = Function<bool(const Device device, Canvas canvas, uint32_t scale)>;
			void setCreateCallback(const CreateCallback &func);
			CreateCallback getCreateCallback() const;
			
			/// pipeline callback
			using PipelineCallback = Function<bool(Pipeline pipeline, CanvasElement element)>;
			void setPipelineCallback(const PipelineCallback &func);
			PipelineCallback getPipelineCallback() const;
			
			/// begin callback
			using BeginCallback = Function<bool(Command command, Canvas canvas)>;
			void setBeginCallback(const BeginCallback &func);
			BeginCallback getBeginCallback() const;
			
			/// draw callback
			using DrawCallback = Function<bool(Command command, Canvas canvas)>;
			void setDrawCallback(const DrawCallback &func);
			DrawCallback getDrawCallback() const;
			
			/// canvas rectangle
			Rect getRect() const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(CanvasElement::Align)
	TS_DECLARE_ENUM_OP(CanvasElement::Stack)
}

#endif /* __TELLUSIM_INTERFACE_CANVAS_H__ */
