#include "common.h"
struct vv {
float4 pos:POSITION;
float2 tc0:TEXCOORD0;
float2 tc1:TEXCOORD1;
float4 c:COLOR0;
float4 f:COLOR1;
};
struct vf {
float4 hpos:POSITION;
half2 tc0:TEXCOORD0;
half2 tc1:TEXCOORD1;
half2 tc2:TEXCOORD2;
half2 tc3:TEXCOORD3;
half4 c:COLOR0;
half4 f:COLOR1;
float fog:FOG;
};
vf main (vv v) {
vf o;
o.hpos=mul(m_VP,v.pos);
o.tc0=v.tc0;
o.tc1=v.tc1;
o.tc2=v.tc0;
o.tc3=v.tc1;
o.c=v.c;
o.f=v.f;
o.fog=calc_fogging(v.pos);
return o;
}