#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

#if defined(__has_include) && __has_include("deko3d.h")
#   include "deko3d.h"
#else
typedef enum DkStage
{
	DkStage_Vertex   = 0,
	DkStage_TessCtrl = 1,
	DkStage_TessEval = 2,
	DkStage_Geometry = 3,
	DkStage_Fragment = 4,
	DkStage_Compute  = 5,

	DkStage_MaxGraphics = 5,
} DkStage;
#endif

// Will handle memory allocation
// "out" value should be freed after use
// Returns true on success, false otherwise
bool uam_compile_dksh(const char *glsl, DkStage stage, void **out, size_t *out_size);

#ifdef __cplusplus
}
#endif // __cplusplus
