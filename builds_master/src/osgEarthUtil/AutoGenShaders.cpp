// ***DO NOT EDIT THIS FILE - IT IS AUTOMATICALLY GENERATED BY CMAKE***

#include <osgEarthUtil/Shaders>

using namespace osgEarth::Util;

Shaders::Shaders()
{
    ContourMap_Vertex = "ContourMap.vert.glsl";
    _sources[ContourMap_Vertex] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%    // NOTE: This vertex shader is no longer used.%EOL%%EOL%#pragma vp_entryPoint oe_contour_vertex%EOL%#pragma vp_location   vertex_model%EOL%#pragma vp_order      0.5%EOL%%EOL%out vec4 oe_layer_tilec;%EOL%out float oe_contour_lookup;%EOL%uniform float oe_contour_min;%EOL%uniform float oe_contour_range;%EOL%%EOL%float oe_terrain_getElevation(in vec2 uv);%EOL%%EOL%void oe_contour_vertex(inout vec4 VertexModel)%EOL%{%EOL%    float height = oe_terrain_getElevation(oe_layer_tilec.st);%EOL%    float height_normalized = (height-oe_contour_min)/oe_contour_range;%EOL%    oe_contour_lookup = clamp( height_normalized, 0.0, 1.0 );%EOL%}%EOL%%EOL%";

    ContourMap_Fragment = "ContourMap.frag.glsl";
    _sources[ContourMap_Fragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_contour_fragment%EOL%#pragma vp_location   fragment_coloring%EOL%#pragma vp_order      0.2%EOL%%EOL%in vec4 oe_layer_tilec;%EOL%uniform sampler1D oe_contour_xfer;%EOL%uniform float oe_contour_opacity;%EOL%uniform float oe_contour_min;%EOL%uniform float oe_contour_range;%EOL%%EOL%float oe_terrain_getElevation(in vec2 uv);%EOL%%EOL%void oe_contour_fragment( inout vec4 color )%EOL%{%EOL%    float height = oe_terrain_getElevation(oe_layer_tilec.st);%EOL%    float height_normalized = (height-oe_contour_min)/oe_contour_range;%EOL%    float lookup = clamp( height_normalized, 0.0, 1.0 );%EOL%    vec4 texel = texture( oe_contour_xfer, lookup );%EOL%    color.rgb = mix(color.rgb, texel.rgb, texel.a * oe_contour_opacity);%EOL%}%EOL%%EOL%";

    Fog_Vertex = "Fog.vert.glsl";
    _sources[Fog_Vertex] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_fog_vertex%EOL%#pragma vp_location   vertex_view%EOL%%EOL%uniform int oe_fog_algo;%EOL%%EOL%out float oe_fogFactor;%EOL%%EOL%void oe_fog_vertex(inout vec4 vertexVIEW)%EOL%{%EOL%    float z = length( vertexVIEW.xyz );%EOL%%EOL%	// linear fog%EOL%	if (oe_fog_algo == 0)%EOL%	{%EOL%	  oe_fogFactor = clamp((gl_Fog.end - z) / (gl_Fog.end - gl_Fog.start), 0.0, 1.0);%EOL%	}%EOL%	// exp fog%EOL%	else if (oe_fog_algo == 1)%EOL%	{	%EOL%	  oe_fogFactor = clamp(exp( -gl_Fog.density * z ), 0.0, 1.0);%EOL%	}	%EOL%	else%EOL%	// exp2 fog%EOL%	{%EOL%        const float LOG2 = 1.442695;%EOL%        oe_fogFactor = clamp(exp2( -gl_Fog.density * gl_Fog.density * z * z * LOG2 ), 0.0, 1.0);%EOL%	}	%EOL%}%EOL%%EOL%";

    Fog_Fragment = "Fog.frag.glsl";
    _sources[Fog_Fragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_fog_frag%EOL%#pragma vp_location   fragment_lighting%EOL%#pragma vp_order      1.1%EOL%%EOL%in float oe_fogFactor;%EOL%%EOL%void oe_fog_frag(inout vec4 color)%EOL%{        %EOL%    color.rgb = mix( gl_Fog.color.rgb, color.rgb, oe_fogFactor);%EOL%}%EOL%%EOL%";

    LogDepthBuffer_VertFile = "LogDepthBuffer.vert.glsl";
    _sources[LogDepthBuffer_VertFile] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_logDepth_vert%EOL%#pragma vp_location   vertex_clip%EOL%#pragma vp_order      0.99%EOL%%EOL%out float oe_LogDepth_logz;%EOL%%EOL%void oe_logDepth_vert(inout vec4 clip)%EOL%{%EOL%    if (gl_ProjectionMatrix[3][3] == 0) // perspective only%EOL%    {%EOL%        mat4 clip2view = inverse(gl_ProjectionMatrix);%EOL%        vec4 farPoint = clip2view * vec4(0,0,1,1);%EOL%        float FAR = -farPoint.z / farPoint.w;%EOL%%EOL%        const float C = 0.001;%EOL%        float FC = 1.0 / log(FAR*C + 1);%EOL%        oe_LogDepth_logz = log(max(1e-6, clip.w*C + 1.0))*FC;%EOL%        clip.z = (2.0*oe_LogDepth_logz - 1.0)*clip.w;%EOL%    }%EOL%    else%EOL%    {%EOL%        oe_LogDepth_logz = -1.0;%EOL%    }%EOL%}%EOL%%EOL%";

    LogDepthBuffer_FragFile = "LogDepthBuffer.frag.glsl";
    _sources[LogDepthBuffer_FragFile] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_logDepth_frag%EOL%#pragma vp_location   fragment_lighting%EOL%#pragma vp_order      0.99%EOL%%EOL%in float oe_LogDepth_logz;%EOL%%EOL%void oe_logDepth_frag(inout vec4 color)%EOL%{%EOL%    gl_FragDepth = oe_LogDepth_logz >= 0? oe_LogDepth_logz : gl_FragCoord.z;%EOL%}%EOL%%EOL%";

    LogDepthBuffer_VertOnly_VertFile = "LogDepthBuffer.VertOnly.vert.glsl";
    _sources[LogDepthBuffer_VertOnly_VertFile] = "#version $GLSL_VERSION_STR%EOL%%EOL%#pragma vp_entryPoint oe_logDepth_vert%EOL%#pragma vp_location   vertex_clip%EOL%#pragma vp_order      0.99%EOL%%EOL%void oe_logDepth_vert(inout vec4 clip)%EOL%{%EOL%    if (gl_ProjectionMatrix[3][3] == 0.0) // perspective only%EOL%    {%EOL%        mat4 clip2view = inverse(gl_ProjectionMatrix);%EOL%        vec4 farPoint = clip2view * vec4(0,0,1,1);%EOL%        float FAR = -farPoint.z / farPoint.w;%EOL%%EOL%        float FC = 2.0 / log2(FAR + 1);%EOL%        clip.z = (log2(max(1e-6, clip.w+1.0))*FC - 1.0) * clip.w;%EOL%    }%EOL%}%EOL%%EOL%";

    Graticule_Fragment = "Graticule.frag.glsl";
    _sources[Graticule_Fragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_GeodeticGraticule_fragment%EOL%#pragma vp_location   fragment_lighting%EOL%#pragma vp_order      1.1%EOL%%EOL%#pragma import_defines(OE_DISABLE_GRATICULE)%EOL%%EOL%uniform float oe_GeodeticGraticule_lineWidth;%EOL%uniform float oe_GeodeticGraticule_resolution;%EOL%uniform vec4  oe_GeodeticGraticule_color;%EOL%uniform mat4 osg_ViewMatrixInverse;%EOL%%EOL%in vec2 oe_GeodeticGraticule_coord;%EOL%%EOL%void oe_GeodeticGraticule_fragment(inout vec4 color)%EOL%{%EOL%#ifndef OE_DISABLE_GRATICULE%EOL%    // double the effective res for longitude since it has twice the span%EOL%    vec2 gr = vec2(0.5*oe_GeodeticGraticule_resolution, oe_GeodeticGraticule_resolution);%EOL%    vec2 distanceToLine = mod(oe_GeodeticGraticule_coord, gr);%EOL%    vec2 dx = abs(dFdx(oe_GeodeticGraticule_coord));%EOL%    vec2 dy = abs(dFdy(oe_GeodeticGraticule_coord));%EOL%    vec2 dF = vec2(max(dx.s, dy.s), max(dx.t, dy.t)) * oe_GeodeticGraticule_lineWidth;%EOL%%EOL%    if ( any(lessThan(distanceToLine, dF)))%EOL%    {%EOL%        // calculate some anti-aliasing%EOL%        vec2 f = distanceToLine/dF;%EOL%        float antialias = 1.0 - 2.0*abs(0.5 - min(f.x,f.y));%EOL%%EOL%        // Fade out the lines as you get closer to the ground.%EOL%        vec3 eye = osg_ViewMatrixInverse[3].xyz;%EOL%        float hae = length(eye) - 6378137.0;%EOL%        float maxHAE = 2000.0;%EOL%        float alpha = clamp(hae / maxHAE, 0.0, 1.0) * antialias;%EOL%        color.rgb = mix(color.rgb, oe_GeodeticGraticule_color.rgb, oe_GeodeticGraticule_color.a * alpha);%EOL%    }%EOL%#endif%EOL%}%EOL%%EOL%";

    Graticule_Vertex = "Graticule.vert.glsl";
    _sources[Graticule_Vertex] = "#version $GLSL_VERSION_STR%EOL%%EOL%#pragma vp_entryPoint oe_GeodeticGraticule_vertex%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.5%EOL%%EOL%#pragma import_defines(OE_DISABLE_GRATICULE)%EOL%%EOL%uniform vec4 oe_tile_key;%EOL%out vec4 oe_layer_tilec;%EOL%out vec2 oe_GeodeticGraticule_coord;%EOL%%EOL%%EOL%void oe_GeodeticGraticule_vertex(inout vec4 vertex)%EOL%{%EOL%#ifndef OE_DISABLE_GRATICULE%EOL%    // calculate long and lat from [0..1] across the profile:%EOL%    vec2 r = (oe_tile_key.xy + oe_layer_tilec.xy)/exp2(oe_tile_key.z);%EOL%    oe_GeodeticGraticule_coord = vec2(0.5*r.x, r.y);%EOL%#endif%EOL%}%EOL%%EOL%";

    Shadowing_Vertex = "Shadowing.vert.glsl";
    _sources[Shadowing_Vertex] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       Shadowing Vertex Shader%EOL%#pragma vp_entryPoint oe_shadow_vertex%EOL%#pragma vp_location   vertex_view%EOL%%EOL%%EOL%uniform mat4 oe_shadow_matrix[$OE_SHADOW_NUM_SLICES];%EOL%%EOL%out vec4 oe_shadow_coord[$OE_SHADOW_NUM_SLICES];%EOL%%EOL%void oe_shadow_vertex(inout vec4 VertexVIEW)%EOL%{%EOL%    for(int i=0; i < $OE_SHADOW_NUM_SLICES; ++i)%EOL%    {%EOL%        oe_shadow_coord[i] = oe_shadow_matrix[i] * VertexVIEW;%EOL%    }%EOL%}%EOL%%EOL%";

    Shadowing_Fragment = "Shadowing.frag.glsl";
    _sources[Shadowing_Fragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       Shadowing Fragment Shader%EOL%#pragma vp_entryPoint oe_shadow_fragment%EOL%#pragma vp_location   fragment_lighting%EOL%#pragma vp_order      0.9%EOL%%EOL%#pragma import_defines(OE_LIGHTING, OE_NUM_LIGHTS)%EOL%%EOL%uniform sampler2DArray oe_shadow_map;%EOL%uniform float          oe_shadow_color;%EOL%uniform float          oe_shadow_blur;%EOL%%EOL%in vec3 vp_Normal; // stage global%EOL%in vec4 oe_shadow_coord[$OE_SHADOW_NUM_SLICES];%EOL%%EOL%// Parameters of each light:%EOL%struct osg_LightSourceParameters %EOL%{   %EOL%   vec4 ambient;%EOL%   vec4 diffuse;%EOL%   vec4 specular;%EOL%   vec4 position;%EOL%   vec3 spotDirection;%EOL%   float spotExponent;%EOL%   float spotCutoff;%EOL%   float spotCosCutoff;%EOL%   float constantAttenuation;%EOL%   float linearAttenuation;%EOL%   float quadraticAttenuation;%EOL%%EOL%   bool enabled;%EOL%};  %EOL%uniform osg_LightSourceParameters osg_LightSource[OE_NUM_LIGHTS];%EOL%%EOL%%EOL%#define OE_SHADOW_NUM_SAMPLES 16%EOL%%EOL%const vec2 oe_shadow_samples[16] = vec2[](%EOL%    vec2( -0.942016, -0.399062 ), vec2( 0.945586, -0.768907 ), vec2( -0.094184, -0.929389 ), vec2( 0.344959, 0.293878 ),%EOL%    vec2( -0.915886, 0.457714 ), vec2( -0.815442, -0.879125 ), vec2( -0.382775, 0.276768 ), vec2( 0.974844, 0.756484 ),%EOL%    vec2( 0.443233, -0.975116 ), vec2( 0.53743, -0.473734 ), vec2( -0.264969, -0.41893 ), vec2( 0.791975, 0.190909 ),%EOL%    vec2( -0.241888, 0.997065 ), vec2( -0.8141, 0.914376 ), vec2( 0.199841, 0.786414 ), vec2( 0.143832, -0.141008 )%EOL%);%EOL%%EOL%float oe_shadow_rand(vec2 co)%EOL%{%EOL%   return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);%EOL%}%EOL%%EOL%vec2 oe_shadow_rot(vec2 p, float a)%EOL%{%EOL%    vec2 sincos = vec2(sin(a), cos(a));%EOL%    return vec2(dot(p, vec2(sincos.y, -sincos.x)), dot(p, sincos.xy));%EOL%}%EOL%%EOL%// slow PCF sampling.%EOL%float oe_shadow_multisample(in vec3 c, in float refvalue, in float blur)%EOL%{%EOL%    float shadowed = 0.0;%EOL%    float randomAngle = 6.283185 * oe_shadow_rand(c.xy);%EOL%    for(int i=0; i<OE_SHADOW_NUM_SAMPLES; ++i)%EOL%    {%EOL%        vec2 off = oe_shadow_rot(oe_shadow_samples[i], randomAngle);%EOL%        vec3 pc = vec3(c.xy + off*blur, c.z);%EOL%        float depth = texture(oe_shadow_map, pc).r;%EOL%        %EOL%        if (depth < 1.0 && depth < refvalue )%EOL%        {%EOL%           shadowed += 1.0;%EOL%        }%EOL%    }%EOL%    return 1.0-(shadowed/OE_SHADOW_NUM_SAMPLES);%EOL%}%EOL%%EOL%void oe_shadow_fragment(inout vec4 color)%EOL%{%EOL%    float alpha = color.a;%EOL%    float factor = 1.0;%EOL%%EOL%    // pre-pixel biasing to reduce moire/acne%EOL%    const float b0 = 0.001;%EOL%    const float b1 = 0.01;%EOL%    vec3 L = normalize(osg_LightSource[0].position.xyz);%EOL%    vec3 N = normalize(vp_Normal);%EOL%    float costheta = clamp(dot(L,N), 0.0, 1.0);%EOL%    float bias = b0*tan(acos(costheta));%EOL%%EOL%    float depth;%EOL%%EOL%    // loop over the slices:%EOL%    for(int i=0; i<$OE_SHADOW_NUM_SLICES && factor > 0.0; ++i)%EOL%    {%EOL%        vec4 c = oe_shadow_coord[i];%EOL%        vec3 coord = vec3(c.x, c.y, float(i));%EOL%%EOL%        // TODO: This causes an NVIDIA error (DUI_foreachId) - disable for now.%EOL%        if ( oe_shadow_blur > 0.0 )%EOL%        {%EOL%            factor = min(factor, oe_shadow_multisample(coord, c.z-bias, oe_shadow_blur));%EOL%        }%EOL%        else%EOL%        {%EOL%            //float depth = texture(oe_shadow_map, coord).r;%EOL%            depth = texture(oe_shadow_map, coord).r;%EOL%            if ( depth < 1.0 && depth < c.z-bias )%EOL%                factor = 0.0;%EOL%        }%EOL%    }%EOL%%EOL%    vec3 colorInFullShadow = color.rgb * oe_shadow_color;%EOL%    color = vec4( mix(colorInFullShadow, color.rgb, factor), alpha );%EOL%%EOL%    //color = vec4(factor, 1.0);%EOL%}%EOL%%EOL%";

    SimpleOceanLayer_Vertex = "SimpleOceanLayer.vert.glsl";
    _sources[SimpleOceanLayer_Vertex] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint ocean_VS%EOL%#pragma vp_location vertex_view%EOL%%EOL%#pragma import_defines(OE_OCEAN_TEXTURE)%EOL%#pragma import_defines(OE_OCEAN_TEXTURE_LOD)%EOL%#pragma import_defines(OE_OCEAN_MASK_MATRIX)%EOL%%EOL%uniform float ocean_maxAltitude;%EOL%uniform float ocean_seaLevel;%EOL%uniform mat4 osg_ViewMatrixInverse;%EOL%%EOL%vec3 oe_UpVectorView;   // stage global%EOL%%EOL%out float ocean_visibility; // [0..1]%EOL%%EOL%#ifdef OE_OCEAN_TEXTURE%EOL%out vec2 ocean_texCoord;%EOL%vec2 oe_terrain_scaleCoordsToRefLOD(in vec2 tc, in float refLOD); // from SDK%EOL%#endif%EOL%%EOL%#ifdef OE_OCEAN_MASK_MATRIX%EOL%out vec2 ocean_maskCoord;%EOL%uniform mat4 OE_OCEAN_MASK_MATRIX ;%EOL%#endif%EOL%%EOL%vec4 oe_layer_tilec;%EOL%%EOL%void ocean_VS(inout vec4 vertexView)%EOL%{%EOL%    // calculate the visibility based on the max altitude:%EOL%    vec3 eye = osg_ViewMatrixInverse[3].xyz;%EOL%    float eyeAlt = max(length(eye) - 6371000.0, 0.0);%EOL%    float lowAlt = ocean_maxAltitude;%EOL%    float highAlt = lowAlt*1.5;%EOL%    ocean_visibility = clamp((highAlt-eyeAlt) / (highAlt-lowAlt), 0.0, 1.0);%EOL%%EOL%    // move the surface to the new sea level:%EOL%    vertexView.xyz += oe_UpVectorView * ocean_seaLevel;%EOL%%EOL%#ifdef OE_OCEAN_TEXTURE%EOL%    ocean_texCoord = oe_terrain_scaleCoordsToRefLOD(oe_layer_tilec.st, OE_OCEAN_TEXTURE_LOD);%EOL%#endif%EOL%%EOL%    // if masking, calculate the mask coordinates%EOL%#ifdef OE_OCEAN_MASK_MATRIX%EOL%    ocean_maskCoord = (OE_OCEAN_MASK_MATRIX * oe_layer_tilec).st;%EOL%#endif%EOL%}%EOL%%EOL%";

    SimpleOceanLayer_Fragment = "SimpleOceanLayer.frag.glsl";
    _sources[SimpleOceanLayer_Fragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint ocean_FS%EOL%#pragma vp_location fragment_coloring%EOL%%EOL%#pragma import_defines(OE_OCEAN_TEXTURE)%EOL%#pragma import_defines(OE_OCEAN_MASK)%EOL%#pragma import_defines(OE_OCEAN_USE_BATHYMETRY)%EOL%%EOL%float oe_terrain_getElevation();%EOL%%EOL%in float ocean_visibility; // [0..1] => [invisible..visible]%EOL%in float oe_layer_opacity; // from VisibleLayer%EOL%%EOL%uniform vec4 ocean_color;%EOL%uniform float ocean_seaLevel;%EOL%%EOL%#ifdef OE_OCEAN_TEXTURE%EOL%in vec2 ocean_texCoord;%EOL%uniform sampler2D OE_OCEAN_TEXTURE ;%EOL%#endif%EOL%%EOL%#ifdef OE_OCEAN_MASK%EOL%in vec2 ocean_maskCoord;%EOL%uniform sampler2D OE_OCEAN_MASK ;%EOL%#endif%EOL%%EOL%// remaps a value from [vmin..vmax] to [0..1] clamped%EOL%float ocean_remap(float val, float vmin, float vmax, float r0, float r1)%EOL%{%EOL%    float vr = (clamp(val, vmin, vmax)-vmin)/(vmax-vmin);%EOL%    return r0 + vr * (r1-r0);%EOL%}%EOL%%EOL%// entry point.%EOL%void ocean_FS(inout vec4 color)%EOL%{%EOL%    float alpha = 1.0;%EOL%%EOL%#ifdef OE_OCEAN_USE_BATHYMETRY%EOL%    const float lowF = -100.0;%EOL%    const float hiF = -10.0;%EOL%%EOL%    float elevation = oe_terrain_getElevation();%EOL%    alpha = ocean_remap(elevation, ocean_seaLevel+lowF, ocean_seaLevel+hiF, 1.0, 0.0);%EOL%#endif%EOL%%EOL%#ifdef OE_OCEAN_MASK%EOL%    float mask = texture(OE_OCEAN_MASK, ocean_maskCoord).a;%EOL%    alpha *= mask;%EOL%#endif%EOL%%EOL%    color = vec4(ocean_color.rgb, alpha*ocean_visibility*oe_layer_opacity*ocean_color.a);%EOL%%EOL%#ifdef OE_OCEAN_TEXTURE%EOL%    color *= texture(OE_OCEAN_TEXTURE, ocean_texCoord);%EOL%#endif%EOL%}%EOL%%EOL%";
    
    RTTPicker = "RTTPicker.glsl";
    _sources[RTTPicker] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_pick_encodeObjectID%EOL%#pragma vp_location   vertex_clip%EOL%%EOL%//#define USE_BITWISE_MATH%EOL%        %EOL%// Vertex stage global containing the Object ID; set in ObjectIndex shader.%EOL%uint oe_index_objectid;%EOL%%EOL%// output encoded oid to fragment shader%EOL%flat out vec4 oe_pick_encoded_objectid;%EOL%%EOL%// whether color already contains oid (written by another RTT camera)%EOL%flat out int oe_pick_color_contains_objectid;%EOL%%EOL%void oe_pick_encodeObjectID(inout vec4 vertex)%EOL%{%EOL%    // the color will contain an encoded object ID for draped features.%EOL%    oe_pick_color_contains_objectid = (oe_index_objectid == 1u) ? 1 : 0;%EOL%%EOL%    if ( oe_pick_color_contains_objectid == 0 )%EOL%    {%EOL%        // encode the objectID as a vec4 (color)%EOL%#ifdef USE_BITWISE_MATH%EOL%        uint u0 = (oe_index_objectid & 0xff000000u) >> 24u;%EOL%        uint u1 = (oe_index_objectid & 0x00ff0000u) >> 16u;%EOL%        uint u2 = (oe_index_objectid & 0x0000ff00u) >> 8u;%EOL%        uint u3 = (oe_index_objectid & 0x000000ffu);%EOL%#else%EOL%        uint u0 = (oe_index_objectid / 16777216u);%EOL%        uint u1 = (oe_index_objectid / 65536u) - (u0 * 256u);%EOL%        uint u2 = (oe_index_objectid / 256u) - (u1 * 256u) - (u0 * 65536u);%EOL%        uint u3 = (oe_index_objectid) - (u2 * 256u) - (u1 * 65536u) - (u0 * 16777216u);%EOL%#endif%EOL%        oe_pick_encoded_objectid = vec4(float(u0), float(u1), float(u2), float(u3)) / 255.0;%EOL%    }%EOL%}%EOL%%EOL%%EOL%[break]%EOL%%EOL%%EOL%#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_pick_renderEncodedObjectID%EOL%#pragma vp_location   fragment_output%EOL%#pragma vp_order      last%EOL%%EOL%flat in vec4 oe_pick_encoded_objectid;%EOL%flat in int oe_pick_color_contains_objectid;%EOL%        %EOL%out vec4 fragColor;%EOL%%EOL%void oe_pick_renderEncodedObjectID(inout vec4 color)%EOL%{%EOL%    if ( oe_pick_color_contains_objectid == 1 )%EOL%        fragColor = color;%EOL%    else%EOL%        fragColor = oe_pick_encoded_objectid;%EOL%}%EOL%%EOL%";
}
