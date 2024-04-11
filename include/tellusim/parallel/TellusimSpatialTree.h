// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_SPATIAL_TREE_H__
#define __TELLUSIM_PARALLEL_SPATIAL_TREE_H__

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
	 * SpatialTree class
	 */
	class TS_API SpatialTree {
			
			TS_DECLARE_PTR(SpatialTree, 0)
			
		public:
			
			/// Tree modes
			enum Mode {
				ModeSingle = 0,		// single mode
				ModeMultiple,		// multiple mode
				NumModes,
			};
			
			/// Hash modes
			enum Hash {
				HashXYZ10,			// 10-bit 3D spatial hash
				HashXYZ9,			//  9-bit 3D spatial hash
				HashXYZ8,			//  8-bit 3D spatial hash
				HashXY15,			// 15-bit 2D spatial hash
				HashXY14,			// 14-bit 2D spatial hash
				HashXY12,			// 12-bit 2D spatial hash
				HashXY10,			// 10-bit 2D spatial hash
			};
			
			/// Tree flags
			enum Flags {
				FlagNone = 0,
				FlagSingle				= (1 << ModeSingle),
				FlagMultiple			= (1 << ModeMultiple),
				FlagUpdate				= (1 << (NumModes + 0)),
				FlagOptimize			= (1 << (NumModes + 1)),
				FlagTracing				= (1 << (NumModes + 2)),
				FlagScratch				= (1 << (NumModes + 3)),
				FlagAtomic				= (1 << (NumModes + 4)),
				FlagSingleUpdate		= (FlagSingle | FlagUpdate),
				FlagMultipleUpdate		= (FlagMultiple | FlagUpdate),
				FlagSingleOptimize		= (FlagSingle | FlagOptimize),
				FlagMultipleOptimize	= (FlagMultiple | FlagOptimize),
				FlagsAll				= (FlagSingle | FlagMultiple),
				FlagsAllOptimize		= (FlagsAll | FlagOptimize),
			};
			
			SpatialTree();
			~SpatialTree();
			
			/// clear tree
			void clear();
			
			/// check tree
			bool isCreated(Flags flags) const;
			
			/// tree parameters
			uint32_t getGroupSize() const;
			uint32_t getBoundsNodes() const;
			uint32_t getMaxNodes() const;
			uint32_t getMaxRegions() const;
			RadixSort getRadixSort() const;
			
			/// create spatial tree
			/// \param sort Radix sort.
			/// \param size Spatial tree data size.
			/// \param groups Spatial tree group size.
			/// \param regions Maximum number of multiple regions.
			bool create(const Device &device, Mode mode, RadixSort &sort, uint32_t size, uint32_t groups = 256, uint32_t regions = 1);
			bool create(const Device &device, Flags flags, RadixSort &sort, uint32_t size, uint32_t groups = 256, uint32_t regions = 1);
			
			/// dispatch inplace single spatial tree generation
			/// \param hash Spatial tree hash mode.
			/// \param nodes Buffer of spatial tree nodes.
			/// \param offset Spatial tree nodes offset index.
			/// \param size Number of spatial elements.
			bool dispatch(Compute &compute, Hash hash, Buffer &nodes, uint32_t offset, uint32_t size, Flags flags = FlagNone);
			
			/// dispatch inplace multiple spatial tree generation
			/// \param hash Spatial tree hash mode.
			/// \param nodes Buffer of spatial tree nodes.
			/// \param count Number of regions to create.
			/// \param offsets Spatial tree nodes offset index.
			/// \param sizes Number of spatial elements.
			bool dispatch(Compute &compute, Hash hash, Buffer &nodes, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, Flags flags = FlagNone);
			
			/// dispatch inplace single spatial tree generation
			/// \param hash Spatial tree hash mode.
			/// \param nodes Buffer of spatial tree nodes.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of spatial elements.
			bool dispatchIndirect(Compute &compute, Hash hash, Buffer &nodes, Buffer &dispatch, uint32_t offset, uint32_t max_size = Maxu32);
			
			/// dispatch inplace multiple spatial tree generation
			/// \param hash Spatial tree hash mode.
			/// \param nodes Buffer of spatial tree nodes.
			/// \param count Number of regions to create.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of spatial elements.
			bool dispatchIndirect(Compute &compute, Hash hash, Buffer &nodes, uint32_t count, Buffer &dispatch, uint32_t offset, uint32_t max_size = Maxu32);
			
			struct Node {
				float32_t bound_min[3];		// bound minimum
				float32_t is_enabled;		// enabled flag
				float32_t bound_max[3];		// bound maximum
				uint32_t data;				// leaf-node user data
				uint32_t left;				// left child node index bigger than spatial node index in case of leaf node
				uint32_t right;				// right child node index bigger than spatial node index in case of leaf node
				uint32_t parent;			// parent node index or next node visiting index for optimized tree
				uint32_t spatial;			// spatial node index for leaf node or number of leaf nodes for non-leaf nodes
			};
			
			struct DispatchParameters {
				uint32_t offset;			// spatial tree nodes offset index.
				uint32_t size;				// number of spatial elements.
				uint32_t padding_0;
				uint32_t padding_1;
			};
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(SpatialTree::Flags)
}

#endif /* __TELLUSIM_PARALLEL_SPATIAL_TREE_H__ */
