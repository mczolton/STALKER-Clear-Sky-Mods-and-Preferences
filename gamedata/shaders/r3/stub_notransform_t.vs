#include "common_iostructs.h"
uniform float4 screen_res;
v2p_TL main(v_TL_positiont I){
v2p_TL O;
{
I.P.xy+=0.5f;
O.HPos.x=I.P.x*screen_res.z*2-1;
O.HPos.y=(I.P.y*screen_res.w*2-1)*-1;
O.HPos.zw=I.P.zw;
}
O.Tex0=I.Tex0;
O.Color=I.Color.bgra;
return O;
}