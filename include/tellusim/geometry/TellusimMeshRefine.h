// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_MESH_REFINE_H__
#define __TELLUSIM_GEOMETRY_MESH_REFINE_H__

#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Mesh;
	class MeshGeometry;
	
	/**
	 * MeshRefine algorithms
	 */
	namespace MeshRefine {
		
		/// mesh subdivision algorithm
		/// \param steps Number of subdivision steps
		TS_API bool subdiv(Mesh &dest, const Mesh &src, uint32_t steps);
		TS_API bool subdiv(MeshGeometry &dest, const MeshGeometry &src, uint32_t steps, uint32_t position = Maxu32);
	}
}

#endif /* __TELLUSIM_GEOMETRY_MESH_REFINE_H__ */
