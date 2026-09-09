#ifndef EMULATOR_INCLUDE_EMULATOR_GRAPHICS_SHADER_RECOMPILER_SHADERINFOCOLLECTION_H_
#define EMULATOR_INCLUDE_EMULATOR_GRAPHICS_SHADER_RECOMPILER_SHADERINFOCOLLECTION_H_

#include "graphics/shader/recompiler/ir/ShaderIR.h"

namespace Libs::Graphics::ShaderRecompiler::IR {

struct ShaderInfoOptions {
	const ShaderVertexInputInfo*  vertex  = nullptr;
	const ShaderPixelInputInfo*   pixel   = nullptr;
	const ShaderComputeInputInfo* compute = nullptr;
	// True when the device supports VK_KHR_fragment_shader_barycentric. When true, pixel inputs
	// that genuinely need per-vertex data (GetInterpolationParameter with a non-flat, non-default
	// mode) are reported as such so the emitter requests real per-vertex barycentric input. When
	// false, every such read is instead treated as reading the already-interpolated value (see
	// CollectPixelInputs), which avoids the extension entirely at the cost of losing the explicit
	// per-vertex delta math for the rare shader that actually relies on it. Defaults to true so
	// existing callers (tests, callers that don't care about older/limited GPUs) keep today's
	// exact behavior.
	bool                           barycentric_supported = true;
};

// Completes the immutable shader interface after resource tracking. On failure Program::info and
// all completion state remain unchanged.
void CollectShaderInfo(Program& program, const ShaderInfoOptions& options);

} // namespace Libs::Graphics::ShaderRecompiler::IR

#endif /* EMULATOR_INCLUDE_EMULATOR_GRAPHICS_SHADER_RECOMPILER_SHADERINFOCOLLECTION_H_ */
