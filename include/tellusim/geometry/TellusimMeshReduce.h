// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_REDUCE_H__
#define __TELLUSIM_GEOMETRY_MESH_REDUCE_H__

#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * MeshReduce algorithms
	 */
	namespace MeshReduce {
		
		/// progress callback
		using ProgressCallback = Function<bool(uint32_t progress)>;
		
		/// mesh collapse reduction
		/// \param ratio Triangle reduction ratio (use negative ratio for border reduction)
		/// \param threshold Edge collapse threshold
		/// \param position Position attribute index
		TS_API bool collapse(Mesh &dest, const Mesh &src, float32_t ratio, float32_t threshold = 0.0f, const ProgressCallback *func = nullptr);
		TS_API bool collapse(MeshGeometry &dest, const MeshGeometry &src, float32_t ratio, float32_t threshold = 0.0f, const ProgressCallback *func = nullptr, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_REDUCE_H__ */
