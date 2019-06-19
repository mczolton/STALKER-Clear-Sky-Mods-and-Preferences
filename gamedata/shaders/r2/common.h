#ifndef COMMON_H
#define COMMON_H
#include "ShaderSettings.txt"
#include "shared\common.h"
#ifndef SMAP_size
#ifdef CUSTOM_SHADOW_RESOLUTION
#define SMAP_size CUSTOM_SHADOWMAP_RESOLUTION
#else
#define SMAP_size 1024
#endif
#endif
#define PARALLAX_H 0.02
#define parallax float2(PARALLAX_H,-PARALLAX_H/2)
#ifdef USE_R2_STATIC_SUN
#define xmaterial half(1.0h/4.h)
#else
#define xmaterial half(L_material.w)
#endif
uniform half4 hemi_cube_pos_faces;
uniform half4 hemi_cube_neg_faces;
uniform half4 L_material;
uniform half4 Ldynamic_color;
uniform half4 Ldynamic_pos;
uniform half4 Ldynamic_dir;
uniform half4 J_direct [6];
uniform half4 J_spot [6];
half calc_fogging (half4 w_pos){ return dot(w_pos,fog_plane);}
half2 calc_detail (half3 w_pos){
float dtl=distance(w_pos,eye_position)*dt_params.w;
dtl=min(dtl*dtl,1);
half dt_mul=1-dtl;
half dt_add=.5*dtl;
return half2 (dt_mul,dt_add);
}
float3 calc_reflection(float3 pos_w,float3 norm_w){
return reflect(normalize(pos_w-eye_position),norm_w);
}
float3 calc_sun_r1 (float3 norm_w){ return L_sun_color*saturate(dot((norm_w),-L_sun_dir_w));}
float3 calc_model_hemi_r1 (float3 norm_w){ return max(0,norm_w.y)*L_hemi_color;}
float3 calc_model_lq_lighting (float3 norm_w){ return L_material.x*calc_model_hemi_r1(norm_w)+L_ambient+L_material.y*calc_sun_r1(norm_w);}
struct v_static {
float4 P:POSITION;
float4 Nh:NORMAL;
float4 T:TANGENT;
float4 B:BINORMAL;
float2 tc:TEXCOORD0;
float2 lmh:TEXCOORD1;
float4 color:COLOR0;
};
struct v_tree {
float4 P:POSITION;
float4 Nh:NORMAL;
float3 T:TANGENT;
float3 B:BINORMAL;
float4 tc:TEXCOORD0;
};
struct v_model {
float4 P:POSITION;
float3 N:NORMAL;
float3 T:TANGENT;
float3 B:BINORMAL;
float2 tc:TEXCOORD0;
};
struct v_detail {
float4 pos:POSITION;
int4 misc:TEXCOORD0;
};
#ifdef USE_HWSMAP
struct v_shadow_direct_aref {
float4 hpos:POSITION;
float2 tc0:TEXCOORD1;
};
struct v_shadow_direct {
float4 hpos:POSITION;
};
#else
struct v_shadow_direct_aref {
float4 hpos:POSITION;
float depth:TEXCOORD0;
float2 tc0:TEXCOORD1;
};
struct v_shadow_direct {
float4 hpos:POSITION;
float depth:TEXCOORD0;
};
#endif
struct p_bumped {
float4 hpos:POSITION;
#if defined(USE_R2_STATIC_SUN)&& !defined(USE_LM_HEMI)
float4 tcdh:TEXCOORD0;
#else
float2 tcdh:TEXCOORD0;
#endif
float4 position:TEXCOORD1;
half3 M1:TEXCOORD2;
half3 M2:TEXCOORD3;
half3 M3:TEXCOORD4;
#if defined(USE_PARALLAX)|| defined(USE_STEEPPARALLAX)
half3 eye:TEXCOORD5;
#ifdef USE_TDETAIL
float2 tcdbump:TEXCOORD6;
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD7;
#endif
#else
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD6;
#endif
#endif
#else
#ifdef USE_TDETAIL
float2 tcdbump:TEXCOORD5;
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD6;
#endif
#else
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD5;
#endif
#endif
#endif
};
struct p_flat {
float4 hpos:POSITION;
#if defined(USE_R2_STATIC_SUN)&& !defined(USE_LM_HEMI)
float4 tcdh:TEXCOORD0;
#else
float2 tcdh:TEXCOORD0;
#endif
float4 position:TEXCOORD1;
half3 N:TEXCOORD2;
#ifdef USE_TDETAIL
float2 tcdbump:TEXCOORD3;
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD4;
#endif
#else
#ifdef USE_LM_HEMI
float2 lmh:TEXCOORD3;
#endif
#endif
};
struct f_deffer {
half4 position:COLOR0;
half4 Ne:COLOR1;
half4 C:COLOR2;
};
struct p_screen {
float4 hpos:POSITION;
float2 tc0:TEXCOORD0;
};
uniform sampler2D s_base;
uniform sampler2D s_bump;
uniform sampler2D s_bumpX;
uniform sampler2D s_detail;
uniform sampler2D s_detailBump;
uniform sampler2D s_detailBumpX;
uniform sampler2D s_bumpD;
uniform sampler2D s_hemi;
uniform sampler2D s_mask;
uniform sampler2D s_dt_r;
uniform sampler2D s_dt_g;
uniform sampler2D s_dt_b;
uniform sampler2D s_dt_a;
uniform sampler2D s_dn_r;
uniform sampler2D s_dn_g;
uniform sampler2D s_dn_b;
uniform sampler2D s_dn_a;
uniform sampler2D s_depth;
uniform sampler2D s_position;
uniform sampler2D s_normal;
uniform sampler s_lmap;
uniform sampler3D s_material;
uniform sampler1D s_attenuate;
uniform sampler2D s_diffuse;
uniform sampler2D s_accumulator;
uniform sampler2D s_generic;
uniform sampler2D s_bloom;
uniform sampler s_image;
uniform sampler2D s_tonemap;
#define def_gloss half(2.f /255.f)
#define def_aref half(200.f/255.f)
#define def_dbumph half(0.333f)
#define def_virtualh half(0.05f)
#define def_distort half(0.05f)
#ifndef HDR_CUSTOM
#define def_hdr half(9.h)
#else
#define def_hdr half(HDR_CUSTOM)
#endif
#define def_hdr_clip half(0.75h)
#define LUMINANCE_VECTOR half3(0.3f,0.38f,0.22f)
void tonemap (out half4 low,out half4 high,half3 rgb,half scale){
rgb=rgb*scale;
const float fWhiteIntensity=1.7;
const float fWhiteIntensitySQR=fWhiteIntensity*fWhiteIntensity;
#ifdef USE_BRANCHING
low=((rgb*(1+rgb/fWhiteIntensitySQR))/(rgb+1)).xyzz;
high=low/def_hdr;
#else
low=half4 (((rgb*(1+rgb/fWhiteIntensitySQR))/(rgb+1)),0);
high=half4 (rgb/def_hdr,0);
#endif
}
half4 combine_bloom (half3 low,half4 high){
return half4(low+high*high.a,1.h);
}
float3 v_hemi (float3 n){ return L_hemi_color*(.5f+.5f*n.y);}
float3 v_hemi_wrap (float3 n,float w){ return L_hemi_color*(w+(1-w)*n.y);}
float3 v_sun (float3 n){ return L_sun_color*dot(n,-L_sun_dir_w);}
float3 v_sun_wrap (float3 n,float w){ return L_sun_color*(w+(1-w)*dot(n,-L_sun_dir_w));}
half3 p_hemi (float2 tc){
half4 t_lmh=tex2D (s_hemi,tc);
return t_lmh.a;
}
half get_hemi(half4 lmh){
return lmh.a;
}
half get_sun(half4 lmh){
return lmh.g;
}
half Contrast(half Input,half ContrastPower){
bool IsAboveHalf=Input>0.5;
half ToRaise=saturate(2*(IsAboveHalf ? 1-Input:Input));
half Output=0.5*pow(ToRaise,ContrastPower);
Output=IsAboveHalf ? 1-Output:Output;
return Output;
}
#define FXPS technique _render{pass _code{PixelShader=compile ps_3_0 main();}}
#define FXVS technique _render{pass _code{VertexShader=compile vs_3_0 main();}}
#endif