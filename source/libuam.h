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

typedef void *uam_compiler;

// Creates/destroys compiler
// Returns NULL on failure
uam_compiler *uam_create_compiler(DkStage stage);
void uam_free_compiler(uam_compiler *compiler);

// Compiles the GLSL codes
// Returns true on success, false otherwise
bool uam_compile_dksh(uam_compiler *compiler, const char *glsl);

// Gets the size of the previously compiled shader, as DKSH file
size_t uam_get_code_size(const uam_compiler *compiler);

// Write the compiled shader as DKSH to the specified location
void uam_write_code(const uam_compiler *compiler, void *memory);

#ifdef __cplusplus
}
#endif // __cplusplus
