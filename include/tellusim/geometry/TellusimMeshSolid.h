// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_SOLID_H__
#define __TELLUSIM_GEOMETRY_MESH_SOLID_H__

#include <core/TellusimArray.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * MeshSolid algorithms
	 */
	namespace MeshSolid {
		
		/// progress callback
		using ProgressCallback = Function<bool(uint32_t progress)>;
		
		/// advancing front generation algorithm
		/// \param ratio Tetrahedron height ratio
		/// \param threshold Delaunay radius threshold
		/// \param position Position attribute index
		TS_API bool create(Mesh &dest, const Mesh &src, float32_t ratio = 1.0f, float32_t threshold = 0.9f, const ProgressCallback *func = nullptr);
		TS_API bool create(MeshGeometry &dest, const MeshGeometry &src, float32_t ratio = 1.0f, float32_t threshold = 0.9f, const ProgressCallback *func = nullptr, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_SOLID_H__ */
