#ifndef SLOAD_H
#define SLOAD_H
#include "common.h"
struct surface_bumped {
half4 base;
half3 normal;
half gloss;
half height;
};
float4 tbase(float2 tc){
return tex2D(s_base,tc);
}
#if defined(ALLOW_STEEPPARALLAX)&& defined(USE_STEEPPARALLAX)
static const float fParallaxStartFade=8.0f;
static const float fParallaxStopFade=12.0f;
void UpdateTC(inout p_bumped I){
if (I.position.z<fParallaxStopFade){
const float maxSamples=25;
const float minSamples=5;
const float fParallaxOffset=-0.013;
float nNumSteps=lerp(maxSamples,minSamples,normalize(I.eye).z);
float fStepSize=1.0/nNumSteps;
float2 vDelta=normalize(I.eye).xy*fParallaxOffset*1.2;
float2 vTexOffsetPerStep=fStepSize*vDelta;
float2 vTexCurrentOffset=I.tcdh;
float fCurrHeight=0.0;
float fCurrentBound=1.0;
for(;fCurrHeight<fCurrentBound;fCurrentBound-=fStepSize){
vTexCurrentOffset+=vTexOffsetPerStep;
fCurrHeight=tex2Dlod(s_bumpX,float4(vTexCurrentOffset.xy,0,0)).a;
}
vTexCurrentOffset-=vTexOffsetPerStep;
float fPrevHeight=tex2D(s_bumpX,float3(vTexCurrentOffset.xy,0)).a;
float fDelta2=((fCurrentBound+fStepSize)-fPrevHeight);
float fDelta1=(fCurrentBound-fCurrHeight);
float fParallaxAmount=(fCurrentBound*fDelta2-(fCurrentBound+fStepSize)*fDelta1)/(fDelta2-fDelta1);
float fParallaxFade=smoothstep(fParallaxStopFade,fParallaxStartFade,I.position.z);
float2 vParallaxOffset=vDelta*((1-fParallaxAmount)*fParallaxFade);
float2 vTexCoord=I.tcdh+vParallaxOffset;
I.tcdh=vTexCoord;
#if defined(USE_TDETAIL)&& defined(USE_STEEPPARALLAX)
I.tcdbump=vTexCoord*dt_params;
#endif
}
}
#elif defined(USE_PARALLAX)|| defined(USE_STEEPPARALLAX)
void UpdateTC(inout p_bumped I){
half height=tex2D(s_bumpX,I.tcdh).w;
height=height*(parallax.x)+(parallax.y);
float2 new_tc=I.tcdh+height*normalize(I.eye);
I.tcdh.xy=new_tc;
}
#else
void UpdateTC(inout p_bumped I){
;
}
#endif
surface_bumped sload_i(p_bumped I){
surface_bumped S;
UpdateTC(I);
half4 Nu=tex2D(s_bump,I.tcdh);
half4 NuE=tex2D(s_bumpX,I.tcdh);
S.base=tbase(I.tcdh);
S.normal=Nu.wzyx+(NuE.xyz-1.0h);
S.gloss=Nu.x*Nu.x;
S.height=NuE.z;
#ifdef USE_TDETAIL
#ifdef USE_TDETAIL_BUMP
half4 NDetail=tex2D(s_detailBump,I.tcdbump);
half4 NDetailX=tex2D(s_detailBumpX,I.tcdbump);
S.gloss=S.gloss*NDetail.x*2;
S.normal+=NDetail.wzy+NDetailX.xyz-1.0h;
half4 detail=tex2D(s_detail,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
#else
half4 detail=tex2D(s_detail,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
S.gloss=S.gloss*detail.w*2;
#endif
#endif
return S;
}
surface_bumped sload(p_bumped I){
surface_bumped S=sload_i(I);
S.normal.z*=0.5;
return S;
}
#endif