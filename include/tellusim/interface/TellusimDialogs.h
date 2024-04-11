// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_INTERFACE_DIALOGS_H__
#define __TELLUSIM_INTERFACE_DIALOGS_H__

#include <math/TellusimColor.h>
#include <core/TellusimString.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Image;
	
	/**
	 * DialogMessage
	 */
	class TS_API DialogMessage {
			
		private:
			
			TS_DECLARE_PTR(DialogMessage, 0)
			
		public:
			
			explicit DialogMessage(const char *title = nullptr, const char *message = nullptr);
			explicit DialogMessage(const String &title, const char *message = nullptr);
			DialogMessage(const char *title, const String &message);
			DialogMessage(const String &title, const String &message);
			~DialogMessage();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog message
			void setMessage(const char *message);
			void setMessage(const String &message);
			String getMessage() const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagYes			= (1 << 0),
				FlagNo			= (1 << 1),
				FlagOk			= (1 << 2),
				FlagCancel		= (1 << 3),
				FlagClose		= (1 << 4),
				FlagMessage		= (1 << 5),
				FlagWarning		= (1 << 6),
				FlagQuestion	= (1 << 7),
				FlagError		= (1 << 8),
				FlagMouse		= (1 << 9),
				FlagYesNo		= (FlagYes | FlagNo),
				FlagOkCancel	= (FlagOk | FlagCancel),
				DefaultFlags	= (FlagOk),
				NumFlags = 10,
			};
			
			/// dialog result
			enum Result {
				ResultClose = 0,
				ResultCancel,
				ResultOk,
				ResultNo,
				ResultYes,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogMessage::Flags)
	
	/**
	 * DialogFileOpen
	 */
	class TS_API DialogFileOpen {
			
		private:
			
			TS_DECLARE_PTR(DialogFileOpen, 0)
			
		public:
			
			explicit DialogFileOpen(const char *title = nullptr, const char *name = nullptr);
			explicit DialogFileOpen(const String &title, const char *name = nullptr);
			DialogFileOpen(const char *title, const String &name);
			DialogFileOpen(const String &title, const String &name);
			~DialogFileOpen();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog filter
			void setFilter(const char *filter);
			void setFilter(const String &filter);
			String getFilter() const;
			
			/// dialog file
			void setFile(const char *name);
			void setFile(const String &name);
			String getFile() const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagHidden		= (1 << 0),
				FlagMouse		= (1 << 1),
				DefaultFlags	= FlagNone,
				NumFlags = 2,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultOk,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogFileOpen::Flags)
	
	/**
	 * DialogFileSave
	 */
	class TS_API DialogFileSave {
			
		private:
			
			TS_DECLARE_PTR(DialogFileSave, 0)
			
		public:
			
			explicit DialogFileSave(const char *title = nullptr, const char *name = nullptr);
			explicit DialogFileSave(const String &title, const char *name = nullptr);
			DialogFileSave(const char *title, const String &name);
			DialogFileSave(const String &title, const String &name);
			~DialogFileSave();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog filter
			void setFilter(const char *filter);
			void setFilter(const String &filter);
			String getFilter() const;
			
			/// dialog file
			void setFile(const char *name);
			void setFile(const String &name);
			String getFile() const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagHidden		= (1 << 0),
				FlagOverwrite	= (1 << 1),
				FlagMouse		= (1 << 2),
				DefaultFlags	= (FlagOverwrite),
				NumFlags = 3,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultOk,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogFileSave::Flags)
	
	/**
	 * DialogDirectory
	 */
	class TS_API DialogDirectory {
			
		private:
			
			TS_DECLARE_PTR(DialogDirectory, 0)
			
		public:
			
			explicit DialogDirectory(const char *title = nullptr, const char *name = nullptr);
			explicit DialogDirectory(const String &title, const char *name = nullptr);
			DialogDirectory(const char *title, const String &name);
			DialogDirectory(const String &title, const String &name);
			~DialogDirectory();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog directory
			void setDirectory(const char *name);
			void setDirectory(const String &name);
			String getDirectory() const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagMouse		= (1 << 0),
				DefaultFlags	= FlagNone,
				NumFlags = 1,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultOk,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogDirectory::Flags)
	
	/**
	 * DialogProgress
	 */
	class TS_API DialogProgress {
			
		private:
			
			TS_DECLARE_PTR(DialogProgress, 0)
			
		public:
			
			explicit DialogProgress(const char *title = nullptr, const char *message = nullptr);
			explicit DialogProgress(const String &title, const char *message = nullptr);
			DialogProgress(const char *title, const String &message);
			DialogProgress(const String &title, const String &message);
			~DialogProgress();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog message
			void setMessage(const char *message);
			void setMessage(const String &message);
			String getMessage() const;
			
			/// dialog progress
			void setProgress(uint32_t progress);
			uint32_t getProgress() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagMouse		= (1 << 0),
				DefaultFlags	= FlagNone,
				NumFlags = 1,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultOk,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
			
			/// close dialog
			void close();
	};
	
	TS_DECLARE_ENUM_OP(DialogProgress::Flags)
	
	/**
	 * DialogColor
	 */
	class TS_API DialogColor {
			
		private:
			
			TS_DECLARE_PTR(DialogColor, 0)
			
		public:
			
			explicit DialogColor(const char *title = nullptr, const Color &color = Color::zero);
			explicit DialogColor(const String &title, const Color &color = Color::zero);
			~DialogColor();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// dialog title
			void setTitle(const char *title);
			void setTitle(const String &title);
			String getTitle() const;
			
			/// dialog color
			void setColor(const Color &color, bool callback = false);
			const Color &getColor() const;
			
			/// changed callback
			using ChangedCallback = Function<void(Color)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagAlpha		= (1 << 0),
				FlagMouse		= (1 << 1),
				DefaultFlags	= FlagNone,
				NumFlags = 2,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultOk,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogColor::Flags)
	
	/**
	 * DialogMenu
	 */
	class TS_API DialogMenu {
			
		private:
			
			TS_DECLARE_PTR(DialogMenu, 0)
			
		public:
			
			DialogMenu();
			~DialogMenu();
			
			/// dialog position
			void setPosition(int32_t x, int32_t y);
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			
			/// number of items
			uint32_t getNumItems() const;
			
			/// item text
			void setItemText(uint32_t index, const char *text);
			void setItemText(uint32_t index, const String &text);
			String getItemText(uint32_t index) const;
			
			/// item key
			void setItemKey(uint32_t index, const char *key);
			String getItemKey(uint32_t index) const;
			
			/// item image
			void setItemImage(uint32_t index, const Image &image);
			Image getItemImage(uint32_t index) const;
			
			/// item checked
			void setItemChecked(uint32_t index, bool checked, bool callback = false);
			bool isItemChecked(uint32_t index) const;
			
			/// item enabled
			void setItemEnabled(uint32_t index, bool enabled);
			bool isItemEnabled(uint32_t index) const;
			
			/// item hidden
			void setItemHidden(uint32_t index, bool hidden);
			bool isItemHidden(uint32_t index) const;
			
			/// item group
			void setItemsGroup(uint32_t index, uint32_t size);
			uint32_t getItemGroupIndex(uint32_t index) const;
			uint32_t getItemGroupSize(uint32_t index) const;
			
			/// text item
			uint32_t addItem(const char *text, const char *key = nullptr);
			uint32_t addItem(const String &text, const char *key = nullptr);
			uint32_t addItem(const char *text, const Image &image, const char *key = nullptr);
			uint32_t addItem(const String &text, const Image &image, const char *key = nullptr);
			
			/// click item
			using ClickedCallback = Function<void()>;
			uint32_t addItem(const char *text, const ClickedCallback &func, const char *key = nullptr);
			uint32_t addItem(const char *text, const Image &image, const ClickedCallback &func, const char *key = nullptr);
			ClickedCallback getItemClickedCallback(uint32_t index) const;
			
			/// check item
			using ChangedCallback = Function<void(bool)>;
			uint32_t addItem(const char *text, bool checked, const ChangedCallback &func, const char *key = nullptr);
			uint32_t addItem(const char *text, const Image &image, bool checked, const ChangedCallback &func, const char *key = nullptr);
			ChangedCallback getItemChangedCallback(uint32_t index) const;
			
			/// update callback
			using UpdateCallback = Function<bool()>;
			void setUpdateCallback(const UpdateCallback &func);
			UpdateCallback getUpdateCallback() const;
			
			/// dialog flags
			enum Flags {
				FlagNone = 0,
				FlagMouse		= (1 << 0),
				DefaultFlags	= FlagNone,
				NumFlags = 1,
			};
			
			/// dialog result
			enum Result {
				ResultCancel = 0,
				ResultClick,
				NumResults,
			};
			
			/// run dialog
			Result run(Flags flags = DefaultFlags);
	};
	
	TS_DECLARE_ENUM_OP(DialogMenu::Flags)
}

#endif /* __TELLUSIM_INTERFACE_DIALOGS_H__ */
