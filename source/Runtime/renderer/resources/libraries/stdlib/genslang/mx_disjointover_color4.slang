void mx_disjointover_color4(float4 fg, float4 bg, float mixval, out float4 result)
{
    float summedAlpha = fg.w + bg.w;

    if (summedAlpha <= 1.0)
    {
        result.xyz = fg.xyz + bg.xyz;
    }
    else
    {
        if (abs(bg.w) < M_FLOAT_EPS)
        {
            result.xyz = float3(0.0);
        }
        else
        {
            float x = (1.0 - fg.w) / bg.w;
            result.xyz = fg.xyz + bg.xyz * x;
        }
    }
    result.w = min(summedAlpha, 1.0);

    result.xyz = result.xyz * mixval + (1.0 - mixval) * bg.xyz;
    result.w = result.w * mixval + (1.0 - mixval) * bg.w;
}
