// Basic vertex shader that just converts the local position to the screen position using given matrices.

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct InputType
{
	float4 localPosition : POSITION;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 screenPosition : SV_POSITION;
};

OutputType main(InputType input)
{
	OutputType output;

	output.screenPosition = mul(input.localPosition, worldMatrix);
	output.screenPosition = mul(output.screenPosition, viewMatrix);
	output.screenPosition = mul(output.screenPosition, projectionMatrix);

	return output;
}