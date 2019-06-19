#ifndef LMODEL_H
#define LMODEL_H
#include "common.h"
float4 plight_infinity(float m,float3 pnt,float3 normal,float3 light_direction){
float3 N=normal;
float3 V=-normalize(pnt);
float3 L=-light_direction;
float3 H=normalize(L+V);
#ifndef FLOAT32_BLINN_PHONG
return s_material.Sample(smp_material,float3(dot(L,N),dot(H,N),m)).xxxy;
#else
float R=dot(N,H);
float Reflect=pow(saturate(R),m*0.5f);
return s_material.Sample(smp_material,float3(dot(L,N),Reflect,m)).xxxy;
#endif
}
float4 plight_local(float m,float3 pnt,float3 normal,float3 light_position,float light_range_rsq,out float rsqr){
float3 N=normal;
float3 L2P=pnt-light_position;
float3 V=-normalize(pnt);
float3 L=-normalize((float3)L2P);
float3 H=normalize(L+V);
rsqr=dot(L2P,L2P);
float att=saturate(1-rsqr*light_range_rsq);
#ifndef FLOAT32_BLINN_PHONG
float4 light=s_material.Sample(smp_material,float3(dot(L,N),dot(H,N),m)).xxxy;
#else
float R=dot(N,H);
float R_vector=pow(saturate(R),m*0.5f);
float4 light=s_material.Sample(smp_material,float3(dot(L,N),R_vector,m)).xxxy;
#endif
return att*light;
}
float4 blendp(float4 value,float4 tcp){
return value;
}
float4 blend(float4 value,float2 tc){
return value;
}
#endif