struct Vertex {
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct Pixel {
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
};

SamplerState linear_sampler {
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};

BlendState blend_normal {
	BlendEnable[0] = true;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
};

matrix neptune_transform;
Texture2D neptune_texture;

Pixel RenderVertexShader(Vertex input) {
	Pixel output;

	output.position = mul(float4(input.position, 1.0f), neptune_transform);
	output.texcoord = input.texcoord;

	return output;
}

float4 RenderPixelShader(Pixel input) : SV_Target{

	float4 output_color = (float4) 0;
	float4 output_sum = (float4) 0;
	float bloom_distance = 2.0f;
	float bloom_factor = 1.0f;
	float bloom_interval = 0.002f;

	for (float i = -bloom_distance; i <= bloom_distance; i += bloom_factor) {
		for (float y = -bloom_distance; y <= bloom_distance; y += bloom_factor) {
			float2 index_position = input.texcoord + float2(i, y) * bloom_interval;

			if (index_position.x>1.0f || index_position.x < 0.0f) {
				output_sum += neptune_texture.Sample(linear_sampler, input.texcoord) / bloom_distance;
			}
			else if (index_position.y>1.0f || index_position.y < 0.0f) {
				output_sum += neptune_texture.Sample(linear_sampler, input.texcoord) / bloom_distance;
			}
			else {
				output_sum += neptune_texture.Sample(linear_sampler, index_position) / bloom_distance;
			}
		}
	}

	if (neptune_texture.Sample(linear_sampler, input.texcoord).r < 0.5) {
		output_color = output_sum*output_sum*0.012 + neptune_texture.Sample(linear_sampler, input.texcoord);
	}
	else if (neptune_texture.Sample(linear_sampler, input.texcoord).r < 0.8) {
		output_color = output_sum*output_sum*0.0009 + neptune_texture.Sample(linear_sampler, input.texcoord);
	}
	else {
		output_color = output_sum*output_sum*0.00075 + neptune_texture.Sample(linear_sampler, input.texcoord);
	}

	output_color.a = 1.0f;

	return output_color;
}

technique10 NeptuneRender {
	pass p0 {
		SetBlendState(blend_normal, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader(CompileShader(vs_4_0, RenderVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, RenderPixelShader()));
	}
}