function normal(shader,t_base,t_second,t_detail)
shader:begin("accum_volumetric","accum_volumetric")
:fog(false)
:zb(true,false)
:blend(true,blend.one,blend.one)
:sorting (2,false)
shader:sampler("s_lmap"):texture(t_base):clamp()
shader:sampler("s_smap"):texture("null")
shader:sampler("s_noise"):texture("fx\\fx_noise"):f_linear ()
end