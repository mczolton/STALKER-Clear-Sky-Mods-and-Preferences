function normal(shader,t_base,t_second,t_detail)
shader:begin("wmark","simple")
:sorting(1,false)
:blend(true,blend.srcalpha,blend.invsrcalpha)
:aref(true,0)
:zb(true,false)
:fog(false)
:wmark(true)
shader:sampler("s_base"):texture(t_base)
end