struct VertexShaderOutput {
	float32_t4 position : SV_POSITION;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
	float32_t3 worldPos : WORLDPOSITION0;
	float32_t3 cameraPos : CAMPOSSION0;
};
struct Camera {
	float32_t3 worldPos;
};
struct Material {
	float32_t4 color;
	int32_t enableLighting;
	float32_t4x4 uvTransform;
	float32_t shininess;
};

struct TransformationMatrix {

	float32_t4x4 matWorld;
};
struct ViewProjectionMatrix {
	float32_t4x4 view;
	float32_t4x4 projection;
	float32_t3 camera;
};
struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};
struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
};
struct DirectionalLight {
	float32_t4 color;
	float32_t3 direction;
	float intensity;
};