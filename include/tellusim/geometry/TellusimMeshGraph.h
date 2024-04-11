// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_GRAPH_H__
#define __TELLUSIM_GEOMETRY_MESH_GRAPH_H__

#include <core/TellusimArray.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Mesh;
	class MeshGeometry;
	
	/**
	 * MeshGraph algorithms
	 */
	namespace MeshGraph {
		
		/// progress callback
		using ProgressCallback = Function<bool(uint32_t progress)>;
		
		/// mesh graph reduction
		/// \param max_attributes Maximum number of attributes per geometry
		/// \param max_primitives Maximum number of primitives per geometry
		TS_API bool create(Mesh &dest, Mesh &src, uint32_t max_attributes, uint32_t max_primitives, const ProgressCallback *func = nullptr, Async *async = nullptr);
		TS_API bool create(Array<MeshGeometry> &dest, MeshGeometry &src, uint32_t max_attributes, uint32_t max_primitives, const ProgressCallback *func = nullptr, Async *async = nullptr);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_GRAPH_H__ */
