// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_RADIX_SORT_H__
#define __TELLUSIM_PARALLEL_RADIX_SORT_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Buffer;
	class Compute;
	class Device;
	class PrefixScan;
	
	/**
	 * RadixSort class
	 */
	class TS_API RadixSort {
			
			TS_DECLARE_PTR(RadixSort, 0)
			
		public:
			
			/// Sort modes
			enum Mode {
				ModeSingle = 0,		// single array sort
				ModeMultiple,		// multiple arrays sort
				NumModes,
			};
			
			/// Sort flags
			enum Flags {
				FlagNone = 0,
				FlagSingle			= (1 << ModeSingle),
				FlagMultiple		= (1 << ModeMultiple),
				FlagIndirect		= (1 << (NumModes + 0)),
				FlagOrder			= (1 << (NumModes + 1)),
				FlagTracing			= (1 << (NumModes + 2)),
				FlagScratch			= (1 << (NumModes + 3)),
				FlagsAll			= (FlagSingle | FlagMultiple | FlagIndirect | FlagOrder),
			};
			
			RadixSort();
			~RadixSort();
			
			/// clear sort
			void clear();
			
			/// check sort
			bool isCreated(Flags flags) const;
			
			/// sort parameters
			uint32_t getDataSize() const;
			uint32_t getGroupSize() const;
			uint32_t getSortElements() const;
			uint32_t getUpdateElements() const;
			uint32_t getMaxElements() const;
			uint32_t getMaxRegions() const;
			PrefixScan getPrefixScan() const;
			Buffer getDataBuffer() const;
			
			/// create radix sort
			/// \param scan Prefix scan.
			/// \param size Radix sort data size.
			/// \param groups Radix sort group size.
			/// \param regions Maximum number of multiple regions.
			bool create(const Device &device, Mode mode, PrefixScan &scan, uint32_t size, uint32_t groups = 256, uint32_t regions = 1);
			bool create(const Device &device, Flags flags, PrefixScan &scan, uint32_t size, uint32_t groups = 256, uint32_t regions = 1);
			
			/// dispatch inplace single radix sort
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param keys_offset Keys elements offset index (4 aligned).
			/// \param data_offset Data elements offset index (4 aligned).
			/// \param size Number of uint32_t elements to sort.
			/// \param bits Number of key bits to sort.
			bool dispatch(Compute &compute, Buffer &data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, Flags flags = FlagNone, uint32_t bits = 32);
			
			/// dispatch inplace multiple radix sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Number of regions to sort.
			/// \param keys_offsets Keys elements offset index (4 aligned).
			/// \param data_offsets Data elements offset index (4 aligned).
			/// \param sizes Number of uint32_t elements to sort.
			/// \param bits Number of key bits to sort.
			bool dispatch(Compute &compute, Buffer &data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, Flags flags = FlagNone, uint32_t bits = 32);
			
			/// dispatch inplace single indirect radix sort
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param bits Number of key bits to sort.
			/// \param max_size Maximum number of elements to sort.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t bits = 32, uint32_t max_size = Maxu32);
			
			/// dispatch inplace multiple indirect radix sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Number of regions to sort.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param bits Number of key bits to sort.
			/// \param max_size Maximum number of elements to sort.
			bool dispatchIndirect(Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t bits = 32, uint32_t max_size = Maxu32);
			
			/// dispatch inplace multiple indirect radix sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Count indirect buffer.
			/// \param dispatch Dispatch indirect buffer.
			/// \param count_offset Count indirect buffer offset.
			/// \param dispatch_offset Dispatch indirect buffer offset.
			/// \param bits Number of key bits to sort.
			/// \param max_size Maximum number of elements to sort.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, Flags flags = FlagNone, uint32_t bits = 32, uint32_t max_size = Maxu32);
			
			struct DispatchParameters {
				uint32_t keys_offset;		// keys elements offset index (4 aligned)
				uint32_t data_offset;		// data elements offset index (4 aligned)
				uint32_t size;				// number of elements to sort
				uint32_t padding;
			};
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(RadixSort::Flags)
}

#endif /* __TELLUSIM_PARALLEL_RADIX_SORT_H__ */
