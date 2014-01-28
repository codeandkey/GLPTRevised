struct Vertex {
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct Pixel {
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
};

SamplerState linear_sampler {
	Filter=MIN_MAG_MIP_POINT;
	AddressU=Wrap;
	AddressV=Wrap;
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

Pixel RenderVertexShader (Vertex input) {
	Pixel output;

	output.position = mul(float4(input.position,1.0f) , neptune_transform);
	output.texcoord = input.texcoord;

	return output;
}

float4 RenderPixelShader(Pixel input) : SV_Target {
	float4 output = neptune_texture.Sample(linear_sampler,input.texcoord);

	return output;
}

technique10 NeptuneRender {
	pass p0 {
		SetBlendState(blend_normal,float4(0.0f,0.0f,0.0f,0.0f),0xFFFFFFFF);

		SetVertexShader(CompileShader(vs_4_0,RenderVertexShader()));
		SetPixelShader(CompileShader(ps_4_0,RenderPixelShader()));
	}
}