#ifndef common_defines_h_included
#define common_defines_h_included
#define def_gloss float(2.f/255.f)
#define def_aref float(200.f/255.f)
#define def_dbumph float(0.333f)
#define def_virtualh float(0.05f)
#define def_distort float(0.05f)
#define def_hdr float(9.h)
#define def_hdr_clip float(0.75h)
#define LUMINANCE_VECTOR float3(0.3f,0.38f,0.22f)
#ifndef SMAP_size
#ifdef CUSTOM_SHADOW_RESOLUTION
#define SMAP_size CUSTOM_SHADOWMAP_RESOLUTION
#else
#define SMAP_size 1024
#endif
#endif
#define PARALLAX_H 0.02
#define parallax float2(PARALLAX_H,-PARALLAX_H/2)
#endif