#include "FBX.hlsli"
// 0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0);
// 0番スロットに設定されたサンプラー
SamplerState smp : register(s0);
// エントリーポイント
float4 main(VSOutPut input) : SV_TARGET
{
    // テクスチャマッピング
    float4 texcolor = tex.Sample(smp, input.uv);
    // Lambert反射
    float3 ligth = normalize(float3(1, -1, 1)); // 右下奥向きのライト
    float diffuse = saturate(dot(-ligth, input.normal));
    float brigthness = diffuse + 0.3f;
    float4 shadecolor = float4(brigthness, brigthness, brigthness, 1.0f);
    // 陰影とテクスチャの色を合成
    return shadecolor * texcolor;
}
