// ***DO NOT EDIT THIS FILE - IT IS AUTOMATICALLY GENERATED BY CMAKE***

#include <osgEarthDrivers/engine_mp/MPShaders>

using namespace osgEarth::Drivers::MPTerrainEngine;

Shaders::Shaders()
{
    EngineVertexModel = "MPEngine.vert.model.glsl";
    _sources[EngineVertexModel] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_mp_vertModel%EOL%#pragma vp_location   vertex_model%EOL%#pragma vp_order      first%EOL%%EOL%out vec4 oe_layer_texc;%EOL%out vec4 oe_layer_tilec;%EOL%%EOL%out vec3 oe_UpVectorView;%EOL%out float oe_mp_terrainElev; // internal%EOL%in vec4 oe_terrain_attr;     // internal%EOL%%EOL%void oe_mp_vertModel(inout vec4 vertexModel)%EOL%{%EOL%    oe_layer_texc  = gl_MultiTexCoord$MP_PRIMARY_UNIT;%EOL%    oe_layer_tilec = gl_MultiTexCoord$MP_SECONDARY_UNIT;%EOL%%EOL%    oe_UpVectorView = normalize(gl_NormalMatrix * oe_terrain_attr.xyz);%EOL%%EOL%    // internal variable to support the oe_terrain_getElevation() SDK method%EOL%    // in the fragment shader stage%EOL%    oe_mp_terrainElev = oe_terrain_attr[3];%EOL%}%EOL%%EOL%";

    EngineVertexView = "MPEngine.vert.view.glsl";
    _sources[EngineVertexView] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_mp_vertView%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.5%EOL%%EOL%uniform float oe_layer_minRange;%EOL%uniform float oe_layer_maxRange;%EOL%uniform float oe_layer_attenuationRange;%EOL%%EOL%out float oe_layer_rangeOpacity;%EOL%%EOL%void oe_mp_vertView(inout vec4 vertexView)%EOL%{%EOL%    float range = max(-vertexView.z, 0.0);%EOL%%EOL%    float attenMin    = oe_layer_minRange - oe_layer_attenuationRange;%EOL%    float attenMax    = oe_layer_maxRange + oe_layer_attenuationRange;%EOL%%EOL%    oe_layer_rangeOpacity =%EOL%        oe_layer_minRange >= oe_layer_maxRange                   ? 1.0 :%EOL%        range >= oe_layer_minRange && range < oe_layer_maxRange  ? 1.0 :%EOL%        range < oe_layer_minRange                                ? clamp((range-attenMin)/oe_layer_attenuationRange, 0.0, 1.0) :%EOL%        range > oe_layer_maxRange                                ? clamp((attenMax-range)/oe_layer_attenuationRange, 0.0, 1.0) :%EOL%        0.0;%EOL%}%EOL%%EOL%";

    EngineFragment = "MPEngine.frag.glsl";
    _sources[EngineFragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_mp_apply_coloring%EOL%#pragma vp_location   fragment_coloring%EOL%#pragma vp_order      0.5%EOL%#pragma vp_define     MP_USE_BLENDING%EOL%%EOL%#pragma import_defines(OE_IS_PICK_CAMERA)%EOL%#pragma import_defines(OE_IS_DEPTH_CAMERA)%EOL%#pragma import_defines(OE_IS_SHADOW_CAMERA)%EOL%#pragma import_defines(OE_TERRAIN_CAST_SHADOWS)%EOL%%EOL%uniform vec4 oe_terrain_color;%EOL%uniform sampler2D oe_layer_tex;%EOL%uniform int oe_layer_uid;%EOL%uniform int oe_layer_order;%EOL%uniform float oe_layer_opacity;%EOL%%EOL%in vec4 oe_layer_texc;%EOL%in float oe_layer_rangeOpacity;%EOL%%EOL%void oe_mp_apply_coloring(inout vec4 color)%EOL%{%EOL%#if defined(OE_IS_DEPTH_CAMERA)%EOL%    #if defined(OE_IS_SHADOW_CAMERA) && !defined(OE_TERRAIN_CAST_SHADOWS)%EOL%        discard;%EOL%    #endif%EOL%    return;%EOL%#endif%EOL%%EOL%#ifdef OE_IS_PICK_CAMERA%EOL%    color = vec4(0);%EOL%#else%EOL%%EOL%    color = oe_terrain_color.a >= 0.0 ? oe_terrain_color : color;%EOL%%EOL%    float applyImagery = oe_layer_uid >= 0 ? 1.0 : 0.0;%EOL%    vec4 texel = mix(color, texture(oe_layer_tex, oe_layer_texc.st), applyImagery);%EOL%    texel.a = mix(texel.a, texel.a*oe_layer_opacity*oe_layer_rangeOpacity, applyImagery);%EOL%%EOL%#ifdef MP_USE_BLENDING%EOL%    float firstLayer = oe_layer_order == 0 ? 1.0 : 0.0;%EOL%    color = mix(texel, texel*texel.a + color*(1.0-texel.a), firstLayer);    %EOL%#else%EOL%    color = texel;%EOL%#endif%EOL%%EOL%#endif // OE_IS_PICK_CAMERA%EOL%}%EOL%%EOL%";

    NormalMapVertex = "MPEngine.NormalMap.vert.glsl";
    _sources[NormalMapVertex] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_mp_NormalMap_vertex%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.5%EOL%%EOL%uniform mat4 oe_tile_normalTexMatrix;%EOL%%EOL%// stage globals%EOL%vec3 vp_Normal;%EOL%vec4 oe_layer_tilec;%EOL%%EOL%out vec2 oe_normalMapCoords;%EOL%out vec3 oe_normalMapBinormal;%EOL%%EOL%void oe_mp_NormalMap_vertex(inout vec4 unused)%EOL%{%EOL%    // calculate the sampling coordinates for the normal texture%EOL%    oe_normalMapCoords = (oe_tile_normalTexMatrix * oe_layer_tilec).st;%EOL%%EOL%    // send the bi-normal vector to the fragment shader.%EOL%    oe_normalMapBinormal = normalize(gl_NormalMatrix * vec3(0,1,0));%EOL%}%EOL%%EOL%";

    NormalMapFragment = "MPEngine.NormalMap.frag.glsl";
    _sources[NormalMapFragment] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_mp_NormalMap_fragment%EOL%#pragma vp_location   fragment_coloring%EOL%#pragma vp_order      0.2%EOL%%EOL%uniform sampler2D oe_tile_normalTex;%EOL%%EOL%in vec3 vp_Normal;%EOL%in vec2 oe_normalMapCoords;%EOL%in vec3 oe_normalMapBinormal;%EOL%%EOL%void oe_mp_NormalMap_fragment(inout vec4 color)%EOL%{%EOL%    //const vec3 B = vec3(0,1,0);%EOL%%EOL%    vec4 encodedNormal = texture(oe_tile_normalTex, oe_normalMapCoords);%EOL%    vec3 normal        = normalize(encodedNormal.xyz*2.0-1.0);%EOL%%EOL%    //vp_Normal = normalize(oe_mp_NormalMap_TBN * normalTangent);%EOL%%EOL%    vec3 tangent = normalize(cross(oe_normalMapBinormal, vp_Normal));%EOL%%EOL%    vp_Normal = normalize(mat3(tangent, oe_normalMapBinormal, vp_Normal) * normal);%EOL%%EOL%    // visualize curvature gradient:%EOL%    //color.rgb = vec3(0,0,0);%EOL%    //color.r = (encodedNormal.a+1.0)/2.0;%EOL%    //color.b = 1.0-color.r;%EOL%%EOL%    // visualize curvature quantized:%EOL%    //if(encodedNormal.a >= 0.4) color.r = 1.0;%EOL%    //if(encodedNormal.a <= -0.4) color.b = 1.0;%EOL%    %EOL%    // visualize normals:%EOL%    //color.rgb = encodedNormal.xyz;%EOL%}%EOL%%EOL%";
}
