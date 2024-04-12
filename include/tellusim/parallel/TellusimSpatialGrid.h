// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_SPATIAL_GRID_H__
#define __TELLUSIM_PARALLEL_SPATIAL_GRID_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Buffer;
	class Compute;
	class Device;
	class RadixSort;
	
	/**
	 * SpatialGrid class
	 */
	class TS_API SpatialGrid {
			
			TS_DECLARE_PTR(SpatialGrid, 0)
			
		public:
			
			SpatialGrid();
			~SpatialGrid();
			
			/// clear grid
			void clear();
			
			/// check grid
			bool isCreated() const;
			
			/// grid parameters
			uint32_t getGroupSize() const;
			RadixSort getRadixSort() const;
			
			/// create spatial grid
			bool create(const Device &device, RadixSort &sort, uint32_t groups = 256);
			
			/// dispatch spatial grid generation
			/// \param data Spatial grid of uint32_t elements.
			/// \param offset Spatial grid offset index.
			/// \param size Number of spatial elements.
			/// \param bits Number of hash bits to sort.
			bool dispatch(Compute &compute, Buffer &data, uint32_t offset, uint32_t size, uint32_t bits = 32);
			
			/// dispatch spatial tree generation
			/// \param data Spatial grid of uint32_t elements.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of spatial elements.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, uint32_t max_size = Maxu32);
			
			struct DispatchParameters {
				uint32_t offset;			// spatial grid offset index
				uint32_t size;				// number of spatial elements
				uint32_t padding_0;
				uint32_t padding_1;
			};
	};
}

#endif /* __TELLUSIM_PARALLEL_SPATIAL_GRID_H__ */
