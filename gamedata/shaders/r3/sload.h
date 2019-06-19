#ifndef SLOAD_H
#define SLOAD_H
#include "common.h"
#ifdef MSAA_ALPHATEST_DX10_1
#if MSAA_SAMPLES==2
static const float2 MSAAOffsets[2]={ float2(4,4),float2(-4,-4)};
#endif
#if MSAA_SAMPLES==4
static const float2 MSAAOffsets[4]={ float2(-2,-6),float2(6,-2),float2(-6,2),float2(2,6)};
#endif
#if MSAA_SAMPLES==8
static const float2 MSAAOffsets[8]={ float2(1,-3),float2(-1,3),float2(5,1),float2(-3,-5),
float2(-5,5),float2(-7,-1),float2(3,7),float2(7,-7)};
#endif
#endif
struct surface_bumped {
float4 base;
float3 normal;
float gloss;
float height;
};
float4 tbase(float2 tc){
return s_base.Sample(smp_base,tc);
}
#if defined(ALLOW_STEEPPARALLAX)&& defined(USE_STEEPPARALLAX)
static const float fParallaxStartFade=8.0f;
static const float fParallaxStopFade=12.0f;
void UpdateTC(inout p_bumped I){
if(I.position.z<fParallaxStopFade)
{
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
for(int i=0;i<nNumSteps;++i)
{
if(fCurrHeight<fCurrentBound)
{ 
vTexCurrentOffset+=vTexOffsetPerStep;
fCurrHeight=s_bumpX.SampleLevel(smp_base,vTexCurrentOffset.xy,0).a;
fCurrentBound-=fStepSize;
}
}
vTexCurrentOffset-=vTexOffsetPerStep;
float fPrevHeight=s_bumpX.Sample(smp_base,float3(vTexCurrentOffset.xy,0)).a;
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
void UpdateTC(inout p_bumped I)
{
float height=s_bumpX.Sample(smp_base,I.tcdh).w;
height=height*(parallax.x)+(parallax.y);
float2 new_tc=I.tcdh+height*normalize(I.eye);
I.tcdh=new_tc;
}
#else
void UpdateTC(inout p_bumped I)
{
;
}
#endif
surface_bumped sload_i(p_bumped I){
surface_bumped S;
UpdateTC(I);
float4 Nu=s_bump.Sample(smp_base,I.tcdh);
float4 NuE=s_bumpX.Sample(smp_base,I.tcdh);
S.base=tbase(I.tcdh);
S.normal=Nu.wzyx+(NuE.xyz-1.0h);
S.gloss=Nu.x*Nu.x;
S.height=NuE.z;
#ifdef USE_TDETAIL
#ifdef USE_TDETAIL_BUMP
float4 NDetail=s_detailBump.Sample(smp_base,I.tcdbump);
float4 NDetailX=s_detailBumpX.Sample(smp_base,I.tcdbump);
S.gloss=S.gloss*NDetail.x*2;
S.normal+=NDetail.wzy+NDetailX.xyz-1.0h;
float4 detail=s_detail.Sample(smp_base,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
#else
float4 detail=s_detail.Sample(smp_base,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
S.gloss=S.gloss*detail.w*2;
#endif
#endif
return S;
}
surface_bumped sload_i(p_bumped I,float2 pixeloffset){
surface_bumped S;
UpdateTC(I);
float4 Nu=s_bump.Sample(smp_base,I.tcdh);
float4 NuE=s_bumpX.Sample(smp_base,I.tcdh);
S.base=tbase(I.tcdh);
S.normal=Nu.wzyx+(NuE.xyz-1.0h);
S.gloss=Nu.x*Nu.x;
S.height=NuE.z;
#ifdef USE_TDETAIL
#ifdef USE_TDETAIL_BUMP
float4 NDetail=s_detailBump.Sample(smp_base,I.tcdbump);
float4 NDetailX=s_detailBumpX.Sample(smp_base,I.tcdbump);
S.gloss=S.gloss*NDetail.x*2;
S.normal+=NDetail.wzy+NDetailX.xyz-1.0h;
float4 detail=s_detail.Sample(smp_base,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
#else
float4 detail=s_detail.Sample(smp_base,I.tcdbump);
S.base.rgb=S.base.rgb*detail.rgb*2;
S.gloss=S.gloss*detail.w*2;
#endif
#endif
return S;
}
surface_bumped sload(p_bumped I){
surface_bumped S=sload_i(I);
S.normal.z*=0.5;
#ifdef GBUFFER_OPTIMIZATION
S.height=0;
#endif
return S;
}
surface_bumped sload(p_bumped I,float2 pixeloffset){
surface_bumped S=sload_i(I,pixeloffset);
S.normal.z*=0.5;
#ifdef GBUFFER_OPTIMIZATION
S.height=0;
#endif
return S;
}
#endif