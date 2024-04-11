// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_PREFIX_SCAN_H__
#define __TELLUSIM_PARALLEL_PREFIX_SCAN_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Buffer;
	class Compute;
	class Device;
	
	/**
	 * PrefixScan class
	 */
	class TS_API PrefixScan {
			
			TS_DECLARE_PTR(PrefixScan, 0)
			
		public:
			
			/// Scan modes
			enum Mode {
				ModeSingle = 0,		// single array scan
				ModeMultiple,		// multiple arrays scan
				NumModes,
			};
			
			/// Scan flags
			enum Flags {
				FlagNone = 0,
				FlagSingle		= (1 << ModeSingle),
				FlagMultiple	= (1 << ModeMultiple),
				FlagIndirect	= (1 << (NumModes + 0)),
				FlagRepeat		= (1 << (NumModes + 1)),
				FlagsAll		= (FlagSingle | FlagMultiple | FlagIndirect),
			};
			
			PrefixScan();
			~PrefixScan();
			
			/// clear scan
			void clear();
			
			/// check scan
			bool isCreated(Flags flags) const;
			
			/// scan parameters
			uint32_t getGroupSize() const;
			uint32_t getScanElements() const;
			uint32_t getMaxElements() const;
			uint32_t getMaxRegions() const;
			
			/// create prefix scan
			/// \param groups Prefix scan group size.
			/// \param regions Maximum number of multiple regions.
			bool create(const Device &device, Mode mode, uint32_t groups = 256, uint32_t regions = 1);
			bool create(const Device &device, Flags flags, uint32_t groups = 256, uint32_t regions = 1);
			
			/// dispatch inplace single prefix scan
			/// \param data Buffer of uint32_t elements to scan.
			/// \param offset Elements offset index (4 aligned).
			/// \param size Number of uint32_t elements to scan.
			bool dispatch(Compute &compute, Buffer &data, uint32_t offset, uint32_t size);
			
			/// dispatch inplace multiple prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Number of regions to scan.
			/// \param offsets Elements offset index (4 aligned).
			/// \param sizes Number of uint32_t elements to scan.
			bool dispatch(Compute &compute, Buffer &data, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, Flags flags = FlagNone);
			
			/// dispatch inplace single indirect prefix scan
			/// \param data Buffer of uint32_t elements to scan.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param repeat Repeat dispatch with the last parameters.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t max_size = Maxu32);
			
			/// dispatch inplace multiple indirect prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Number of regions to scan.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param repeat Repeat dispatch with the last parameters.
			bool dispatchIndirect(Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t max_size = Maxu32);
			
			/// dispatch inplace multiple indirect prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Count indirect buffer.
			/// \param dispatch Dispatch indirect buffer.
			/// \param count_offset Count indirect buffer offset.
			/// \param dispatch_offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param repeat Repeat dispatch with the last parameters.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, Flags flags = FlagNone, uint32_t max_size = Maxu32);
			
			struct DispatchParameters {
				uint32_t offset;			// elements offset index (4 aligned)
				uint32_t size;				// number of elements to scan
				uint32_t padding_0;
				uint32_t padding_1;
			};
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(PrefixScan::Flags)
}

#endif /* __TELLUSIM_PARALLEL_PREFIX_SCAN_H__ */
