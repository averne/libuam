#include "libuam.h"
#include "compiler_iface.h"

inline pipeline_stage map_pipeline_stage(DkStage stage) {
    switch (stage) {
        case DkStage_Vertex:
            return pipeline_stage_vertex;
        case DkStage_TessCtrl:
            return pipeline_stage_tess_ctrl;
        case DkStage_TessEval:
            return pipeline_stage_tess_eval;
        case DkStage_Geometry:
            return pipeline_stage_geometry;
        case DkStage_Fragment:
            return pipeline_stage_fragment;
        case DkStage_Compute:
            return pipeline_stage_compute;
        default:
            return static_cast<pipeline_stage>(-1);
    }
}

bool uam_compile_dksh(const char *glsl, DkStage stage, void **out, size_t *out_size) {
    *out = NULL, *out_size = 0;

    if (!glsl || !out)
        return false;

    auto pstage = map_pipeline_stage(stage);
    if (pstage == static_cast<pipeline_stage>(-1))
        return false;

    auto compiler = DekoCompiler(pstage);
    if (!compiler.CompileGlsl(glsl))
        return false;

    size_t dksh_size = compiler.CalculateDkshSize();
    *out = aligned_alloc(0x100, dksh_size);
    if (!*out)
        return false;
    *out_size = dksh_size;

    memset(*out, 0, dksh_size);
    compiler.OutputDkshToMemory(*out);

    return true;
}
