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

uam_compiler *uam_create_compiler(DkStage stage) {
    auto pstage = map_pipeline_stage(stage);
    if (pstage == static_cast<pipeline_stage>(-1))
        return NULL;

    return reinterpret_cast<uam_compiler *>(new DekoCompiler(pstage));
}

void uam_free_compiler(uam_compiler *compiler) {
    delete reinterpret_cast<DekoCompiler *>(compiler);
}

bool uam_compile_dksh(uam_compiler *compiler, const char *glsl) {
    return reinterpret_cast<DekoCompiler *>(compiler)->CompileGlsl(glsl);
}

size_t uam_get_code_size(const uam_compiler *compiler) {
    return reinterpret_cast<const DekoCompiler *>(compiler)->CalculateDkshSize();
}

void uam_write_code(const uam_compiler *compiler, void *memory) {
    reinterpret_cast<const DekoCompiler *>(compiler)->OutputDkshToMemory(memory);
}
