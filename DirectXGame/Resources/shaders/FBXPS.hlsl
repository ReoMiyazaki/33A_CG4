#include "FBX.hlsli"
// 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex : register(t0);
// 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);
// �G���g���[�|�C���g
float4 main(VSOutPut input) : SV_TARGET
{
    // �e�N�X�`���}�b�s���O
    float4 texcolor = tex.Sample(smp, input.uv);
    // Lambert����
    float3 ligth = normalize(float3(1, -1, 1)); // �E���������̃��C�g
    float diffuse = saturate(dot(-ligth, input.normal));
    float brigthness = diffuse + 0.3f;
    float4 shadecolor = float4(brigthness, brigthness, brigthness, 1.0f);
    // �A�e�ƃe�N�X�`���̐F������
    return shadecolor * texcolor;
}
