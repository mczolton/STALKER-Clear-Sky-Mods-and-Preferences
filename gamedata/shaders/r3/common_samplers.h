#ifndef common_samplers_h_included
#define common_samplers_h_included
sampler smp_nofilter;
sampler smp_rtlinear;
sampler smp_linear;
sampler smp_base;
Texture2D s_base;
#ifdef USE_MSAA
Texture2DMS<float4,MSAA_SAMPLES>s_generic;
#else
Texture2D s_generic;
#endif
Texture2D s_bump;
Texture2D s_bumpX;
Texture2D s_detail;
Texture2D s_detailBump;
Texture2D s_detailBumpX;
Texture2D s_hemi;
Texture2D s_mask;
Texture2D s_dt_r;
Texture2D s_dt_g;
Texture2D s_dt_b;
Texture2D s_dt_a;
Texture2D s_dn_r;
Texture2D s_dn_g;
Texture2D s_dn_b;
Texture2D s_dn_a;
sampler smp_material;
#ifdef USE_MSAA
Texture2DMS<float4,MSAA_SAMPLES>s_position;
Texture2DMS<float4,MSAA_SAMPLES>s_normal;
#else
Texture2D s_position;
Texture2D s_normal;
#endif
Texture2D s_lmap;
Texture3D s_material;
#ifdef USE_MSAA
Texture2DMS<float4,MSAA_SAMPLES>s_diffuse;
Texture2DMS<float4,MSAA_SAMPLES>s_accumulator;
#else
Texture2D s_diffuse;
Texture2D s_accumulator;
#endif
Texture2D s_bloom;
Texture2D s_image;
Texture2D s_tonemap;
#endif