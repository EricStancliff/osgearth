// ***DO NOT EDIT THIS FILE - IT IS AUTOMATICALLY GENERATED BY CMAKE***

#include <osgEarthDrivers/engine_rex/Shaders>

using namespace osgEarth::Drivers::RexTerrainEngine;

Shaders::Shaders()
{
    ENGINE_VERT_MODEL = "RexEngine.vert.glsl";
    _sources[ENGINE_VERT_MODEL] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       REX Engine - Vertex%EOL%#pragma vp_entryPoint oe_rexEngine_vert_model%EOL%#pragma vp_location   vertex_model%EOL%#pragma vp_order      0.0%EOL%%EOL%// uniforms%EOL%uniform vec4 oe_terrain_color;%EOL%%EOL%// outputs%EOL%out vec4 vp_Color;%EOL%out vec4 oe_layer_tilec;%EOL%%EOL%out float oe_rex_morphFactor;%EOL%flat out int oe_terrain_vertexMarker;%EOL%%EOL%void oe_rexEngine_vert_model(inout vec4 vertexModel)%EOL%{%EOL%    // Texture coordinate for the tile (always 0..1)%EOL%    oe_layer_tilec = gl_MultiTexCoord0;%EOL%%EOL%    // Color of the underlying map geometry (untextured)%EOL%    vp_Color = oe_terrain_color;%EOL%%EOL%    // initialize:%EOL%    oe_rex_morphFactor = 0.0;%EOL%%EOL%    // Extract the ertex type marker%EOL%    oe_terrain_vertexMarker = int(oe_layer_tilec.z);%EOL%}%EOL%%EOL%%EOL%[break]%EOL%#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       REX Engine - VertexView%EOL%#pragma vp_entryPoint oe_rexEngine_vert_view%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.0%EOL%%EOL%// outputs%EOL%vec3 vp_Normal;%EOL%out vec3 oe_UpVectorView;%EOL%%EOL%void oe_rexEngine_vert_view(inout vec4 vertexView)%EOL%{%EOL%    // %QUOTE%up%QUOTE% vector at this vertex in view space, which we will later%EOL%    // need in order to elevate the terrain. vp_Normal can change later%EOL%    // but UpVectorView will stay the same.%EOL%    oe_UpVectorView = vp_Normal;%EOL%}%EOL%%EOL%";

	ENGINE_ELEVATION_MODEL = "RexEngine.elevation.glsl";
    _sources[ENGINE_ELEVATION_MODEL] = "#version $GLSL_VERSION_STR%EOL%%EOL%#pragma vp_name       REX Engine - Elevation%EOL%#pragma vp_entryPoint oe_rexEngine_elevation%EOL%#pragma vp_location   vertex_model%EOL%#pragma vp_order      0.7%EOL%%EOL%#pragma import_defines(OE_TERRAIN_RENDER_ELEVATION)%EOL%%EOL%// Vertex Markers:%EOL%#define VERTEX_MARKER_DISCARD  1%EOL%#define VERTEX_MARKER_GRID     2%EOL%#define VERTEX_MARKER_PATCH    4%EOL%#define VERTEX_MARKER_BOUNDARY 8%EOL%#define VERTEX_MARKER_SKIRT    16%EOL%%EOL%// stage%EOL%vec3 vp_Normal; // up vector%EOL%vec4 oe_layer_tilec;%EOL%%EOL%flat out int oe_terrain_vertexMarker;%EOL%%EOL%uniform float oe_terrain_altitude;%EOL%%EOL%// SDK functions:%EOL%float oe_terrain_getElevation(in vec2 uv);%EOL%%EOL%void oe_rexEngine_elevation(inout vec4 vertexModel)%EOL%{%EOL%    vec3 up = normalize(vp_Normal);%EOL%%EOL%#ifdef OE_TERRAIN_RENDER_ELEVATION%EOL%%EOL%    bool ignore =%EOL%        ((oe_terrain_vertexMarker & VERTEX_MARKER_BOUNDARY) != 0) ||%EOL%        ((oe_terrain_vertexMarker & VERTEX_MARKER_DISCARD)  != 0);%EOL%%EOL%    float elev = ignore ? 0.0f : oe_terrain_getElevation( oe_layer_tilec.st );%EOL%    %EOL%    vertexModel.xyz += up * elev;%EOL%#endif%EOL%%EOL%    vertexModel.xyz += up * oe_terrain_altitude;%EOL%}%EOL%%EOL%";

    MORPHING_VERT = "RexEngine.Morphing.vert.glsl";
    _sources[MORPHING_VERT] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       REX Engine - Morphing%EOL%#pragma vp_entryPoint oe_rexEngine_morph%EOL%#pragma vp_location   vertex_model%EOL%#pragma vp_order      0.5%EOL%%EOL%#pragma import_defines(OE_TERRAIN_MORPH_GEOMETRY)%EOL%#pragma import_defines(OE_TERRAIN_RENDER_ELEVATION)%EOL%#pragma import_defines(OE_IS_DEPTH_CAMERA)%EOL%%EOL%// stage%EOL%vec3 vp_Normal;%EOL%%EOL%vec4 oe_layer_tilec;%EOL%%EOL%out float oe_rex_morphFactor;%EOL%%EOL%flat out int oe_terrain_vertexMarker;%EOL%%EOL%uniform vec2  oe_tile_morph;%EOL%uniform float oe_tile_size;%EOL%%EOL%#ifdef OE_IS_DEPTH_CAMERA%EOL%uniform mat4 oe_shadowToPrimaryMatrix;%EOL%#endif%EOL%%EOL%// SDK functions:%EOL%float oe_terrain_getElevation(in vec2 uv);%EOL%%EOL%// Vertex Markers:%EOL%#define VERTEX_MARKER_DISCARD  1%EOL%#define VERTEX_MARKER_GRID     2%EOL%#define VERTEX_MARKER_PATCH    4%EOL%#define VERTEX_MARKER_BOUNDARY 8%EOL%#define VERTEX_MARKER_SKIRT    16%EOL%%EOL%%EOL%// Compute a morphing factor based on model-space inputs:%EOL%float oe_rex_ComputeMorphFactor(in vec4 position, in vec3 up)%EOL%{%EOL%    // Find the %QUOTE%would be%QUOTE% position of the vertex (the position the vertex would%EOL%    // assume with no morphing)%EOL%	vec4 wouldBePosition = position;%EOL%%EOL%#ifdef OE_TERRAIN_RENDER_ELEVATION%EOL%        float elev = oe_terrain_getElevation( oe_layer_tilec.st );%EOL%		wouldBePosition.xyz += up*elev;%EOL%#endif%EOL%%EOL%    vec4 wouldBePositionView = gl_ModelViewMatrix * wouldBePosition;%EOL%%EOL%#ifdef OE_IS_DEPTH_CAMERA%EOL%    // For a depth camera, we have to compute the morphed position%EOL%    // from the perspective of the primary camera so they match up:%EOL%    wouldBePositionView = oe_shadowToPrimaryMatrix * wouldBePositionView;%EOL%#endif%EOL%    %EOL%    float fDistanceToEye = length(wouldBePositionView.xyz); // or just -z.%EOL%	float fMorphLerpK  = 1.0f - clamp( oe_tile_morph[0] - fDistanceToEye * oe_tile_morph[1], 0.0, 1.0 );%EOL%    return fMorphLerpK;%EOL%}%EOL%%EOL%%EOL%void oe_rexEngine_morph(inout vec4 vertexModel)%EOL%{    %EOL%    // compute the morphing factor to send down the pipe.%EOL%    // we need this even if vertex-morphing is off since we use it for %EOL%    // other things (like image blending)%EOL%    if ((oe_terrain_vertexMarker & VERTEX_MARKER_GRID) != 0)%EOL%    {%EOL%        oe_rex_morphFactor = oe_rex_ComputeMorphFactor(vertexModel, vp_Normal);    %EOL%%EOL%#ifdef OE_TERRAIN_MORPH_GEOMETRY%EOL%        vec3 neighborVertexModel = gl_MultiTexCoord1.xyz;        %EOL%        vec3 neighborNormal = gl_MultiTexCoord2.xyz;%EOL%        %EOL%        float halfSize        = (0.5*oe_tile_size)-0.5;%EOL%        float twoOverHalfSize = 2.0/(oe_tile_size-1.0);   %EOL%        vec2 fractionalPart = fract(oe_layer_tilec.st * halfSize) * twoOverHalfSize;%EOL%        oe_layer_tilec.st = clamp(oe_layer_tilec.st - (fractionalPart * oe_rex_morphFactor), 0.0, 1.0);%EOL%%EOL%        // morph the vertex:%EOL%        vec3 morphVector = neighborVertexModel.xyz - vertexModel.xyz;%EOL%        vertexModel.xyz = vertexModel.xyz + morphVector*oe_rex_morphFactor;%EOL%%EOL%        // morph the normal:%EOL%        morphVector = neighborNormal - vp_Normal;%EOL%        vp_Normal = normalize(vp_Normal + morphVector*oe_rex_morphFactor);%EOL%#endif%EOL%    }%EOL%    else%EOL%    {%EOL%        oe_rex_morphFactor = 0.0;%EOL%    }%EOL%}%EOL%%EOL%";

    ENGINE_VERT_VIEW = "RexEngine.vert.view.glsl";
    _sources[ENGINE_VERT_VIEW] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       REX Engine - Vertex/View%EOL%#pragma vp_entryPoint oe_rex_setTexCoords%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.4%EOL%%EOL%// Stage globals%EOL%vec4 oe_layer_tilec;%EOL%vec2 oe_layer_texc;%EOL%vec2 oe_layer_texcParent;%EOL%%EOL%uniform mat4 oe_layer_texMatrix;%EOL%uniform mat4 oe_layer_texParentMatrix;%EOL%%EOL%void oe_rex_setTexCoords(inout vec4 vertexView)%EOL%{%EOL%    // calculate the texture coordinates:%EOL%    oe_layer_texc       = (oe_layer_texMatrix * oe_layer_tilec).st;%EOL%	oe_layer_texcParent = (oe_layer_texParentMatrix * oe_layer_tilec).st;%EOL%}%EOL%%EOL%";

    ENGINE_FRAG = "RexEngine.frag.glsl";
    _sources[ENGINE_FRAG] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name       REX Engine - Fragment%EOL%#pragma vp_entryPoint oe_rexEngine_frag%EOL%#pragma vp_location   fragment_coloring%EOL%#pragma vp_order      0.5%EOL%%EOL%#pragma import_defines(OE_TERRAIN_RENDER_IMAGERY)%EOL%#pragma import_defines(OE_TERRAIN_MORPH_IMAGERY)%EOL%#pragma import_defines(OE_TERRAIN_BLEND_IMAGERY)%EOL%#pragma import_defines(OE_TERRAIN_CAST_SHADOWS)%EOL%#pragma import_defines(OE_IS_PICK_CAMERA)%EOL%#pragma import_defines(OE_IS_SHADOW_CAMERA)%EOL%#pragma import_defines(OE_IS_DEPTH_CAMERA)%EOL%%EOL%uniform sampler2D oe_layer_tex;%EOL%uniform int       oe_layer_uid;%EOL%uniform int       oe_layer_order;%EOL%%EOL%#ifdef OE_TERRAIN_MORPH_IMAGERY%EOL%uniform sampler2D oe_layer_texParent;%EOL%uniform float oe_layer_texParentExists;%EOL%in vec2 oe_layer_texcParent;%EOL%in float oe_rex_morphFactor;%EOL%#endif%EOL%%EOL%in vec2 oe_layer_texc;%EOL%in vec4 oe_layer_tilec;%EOL%in float oe_layer_opacity;%EOL%%EOL%//in float oe_layer_rangeOpacity;%EOL%%EOL%// Vertex Markers:%EOL%#define VERTEX_MARKER_DISCARD  1%EOL%#define VERTEX_MARKER_GRID     2%EOL%#define VERTEX_MARKER_PATCH    4%EOL%#define VERTEX_MARKER_BOUNDARY 8%EOL%#define VERTEX_MARKER_SKIRT    16%EOL%flat in int oe_terrain_vertexMarker;%EOL%%EOL%void oe_rexEngine_frag(inout vec4 color)%EOL%{%EOL%    // if the provoking vertex is marked for discard, skip it:%EOL%    if ((oe_terrain_vertexMarker & VERTEX_MARKER_DISCARD) != 0)%EOL%    {%EOL%        discard;%EOL%        return;%EOL%    }%EOL%%EOL%    // If this is a shadow camera and the terrain doesn't cast shadows, no render:%EOL%#if defined(OE_IS_SHADOW_CAMERA) && !defined(OE_TERRAIN_CAST_SHADOWS)%EOL%    discard;%EOL%    return;%EOL%#endif%EOL%%EOL%    // If this is a depth-only camera, skip terrain skirt geometry:%EOL%#if defined(OE_IS_DEPTH_CAMERA)%EOL%    if ((oe_terrain_vertexMarker & VERTEX_MARKER_SKIRT) != 0)%EOL%    {%EOL%        discard;%EOL%        return;%EOL%    }%EOL%#endif // OE_IS_DEPTH_CAMERA%EOL%%EOL%    // if this is a picking camera, reset the color to all zeros:%EOL%#ifdef OE_IS_PICK_CAMERA%EOL%    color = vec4(0);%EOL%#else%EOL%%EOL%    // If imagery rendering is disabled, we're done:%EOL%#ifndef OE_TERRAIN_RENDER_IMAGERY%EOL%    return;%EOL%#endif%EOL%%EOL%    // whether this layer contains texel color (UID<0 means no texture)%EOL%    bool isTexelLayer = oe_layer_uid >= 0;%EOL%%EOL%    // whether this is the first layer to render:%EOL%    bool isFirstLayer = oe_layer_order == 0;%EOL%%EOL%    vec4 texel = color;%EOL%%EOL%    if (isTexelLayer)%EOL%    {%EOL%	    texel = texture(oe_layer_tex, oe_layer_texc);%EOL%%EOL%#ifdef OE_TERRAIN_MORPH_IMAGERY%EOL%        // sample the main texture:%EOL%%EOL%        // sample the parent texture:%EOL%	    vec4 texelParent = texture(oe_layer_texParent, oe_layer_texcParent);%EOL%%EOL%        // if the parent texture does not exist, use the current texture with alpha=0 as the parent%EOL%        // so we can %QUOTE%fade in%QUOTE% an image layer that starts at LOD > 0:%EOL%        texelParent = mix( vec4(texel.rgb, 0.0), texelParent, oe_layer_texParentExists );%EOL%%EOL%        // Resolve the final texel color:%EOL%	    texel = mix(texel, texelParent, oe_rex_morphFactor);%EOL%#endif%EOL%%EOL%        // intergrate thelayer opacity:%EOL%        texel.a = texel.a * oe_layer_opacity;%EOL%        color.a = 1.0;%EOL%    }%EOL%    %EOL%#ifdef OE_TERRAIN_BLEND_IMAGERY%EOL%    // If this is a first image layer, blend with the incoming terrain color.%EOL%    // Otherwise, apply directly and let GL blending do the rest.%EOL%    if (isTexelLayer && isFirstLayer)%EOL%    {%EOL%        color.rgb = texel.rgb*texel.a + color.rgb*(1.0-texel.a);%EOL%    }%EOL%    else%EOL%    {%EOL%        color = texel;%EOL%    }%EOL%#else%EOL%    // No blending? The output is just the texel value.%EOL%    color = texel;%EOL%#endif // OE_TERRAIN_BLEND_IMAGERY%EOL%%EOL%#endif // OE_IS_PICK_CAMERA%EOL%}%EOL%%EOL%";

    NORMAL_MAP_VERT = "RexEngine.NormalMap.vert.glsl";
    _sources[NORMAL_MAP_VERT] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_normalMapVertex%EOL%#pragma vp_location   vertex_view%EOL%#pragma vp_order      0.5%EOL%%EOL%#pragma import_defines(OE_TERRAIN_RENDER_NORMAL_MAP)%EOL%%EOL%uniform mat4 oe_tile_normalTexMatrix;%EOL%uniform vec2 oe_tile_elevTexelCoeff;%EOL%%EOL%// stage globals%EOL%vec4 oe_layer_tilec;%EOL%%EOL%out vec2 oe_normalMapCoords;%EOL%out vec3 oe_normalMapBinormal;%EOL%%EOL%void oe_normalMapVertex(inout vec4 unused)%EOL%{%EOL%#ifndef OE_TERRAIN_RENDER_NORMAL_MAP%EOL%    return;%EOL%#endif%EOL%%EOL%    // calculate the sampling coordinates for the normal texture%EOL%    //oe_normalMapCoords = (oe_tile_normalTexMatrix * oe_layer_tilec).st;%EOL%    %EOL%    oe_normalMapCoords = oe_layer_tilec.st%EOL%        * oe_tile_elevTexelCoeff.x * oe_tile_normalTexMatrix[0][0]%EOL%        + oe_tile_elevTexelCoeff.x * oe_tile_normalTexMatrix[3].st%EOL%        + oe_tile_elevTexelCoeff.y;%EOL%%EOL%    // send the bi-normal to the fragment shader%EOL%    oe_normalMapBinormal = normalize(gl_NormalMatrix * vec3(0,1,0));%EOL%}%EOL%%EOL%";

    NORMAL_MAP_FRAG = "RexEngine.NormalMap.frag.glsl";
    _sources[NORMAL_MAP_FRAG] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_entryPoint oe_normalMapFragment%EOL%#pragma vp_location   fragment_coloring%EOL%#pragma vp_order      0.2%EOL%%EOL%#pragma import_defines(OE_TERRAIN_RENDER_NORMAL_MAP)%EOL%#pragma import_defines(OE_DEBUG_NORMALS)%EOL%#pragma import_defines(OE_COMPRESSED_NORMAL_MAP)%EOL%%EOL%// import terrain SDK%EOL%vec4 oe_terrain_getNormalAndCurvature(in vec2);%EOL%%EOL%uniform sampler2D oe_tile_normalTex;%EOL%%EOL%in vec3 vp_Normal;%EOL%in vec3 oe_UpVectorView;%EOL%in vec2 oe_normalMapCoords;%EOL%in vec3 oe_normalMapBinormal;%EOL%%EOL%void oe_normalMapFragment(inout vec4 color)%EOL%{%EOL%#ifndef OE_TERRAIN_RENDER_NORMAL_MAP%EOL%    return;%EOL%#endif%EOL%%EOL%    vec4 encodedNormal = oe_terrain_getNormalAndCurvature(oe_normalMapCoords);%EOL%#ifdef OE_COMPRESSED_NORMAL_MAP%EOL%	vec2 xymod = encodedNormal.rg*2.0 - 1.0;%EOL%    vec3 normal = vec3(xymod, sqrt(1 - xymod.x*xymod.x - xymod.y*xymod.y));%EOL%#else%EOL%    vec3 normal = normalize(encodedNormal.xyz*2.0-1.0);%EOL%#endif%EOL%%EOL%    vec3 tangent = normalize(cross(oe_normalMapBinormal, oe_UpVectorView));%EOL%    vp_Normal = normalize( mat3(tangent, oe_normalMapBinormal, oe_UpVectorView) * normal );%EOL%%EOL%    // visualize curvature quantized:%EOL%    //color.rgba = vec4(0.0,0,1);%EOL%    //float curvature = 2.0*encodedNormal.w - 1.0;%EOL%    //if (curvature > 0.0) color.r = curvature;%EOL%    //if (curvature < 0.0) color.b = -curvature;%EOL%    //color.a = 1.0;%EOL%    %EOL%#ifdef OE_DEBUG_NORMALS%EOL%    // visualize normals:%EOL%    color.rgb = encodedNormal.xyz;%EOL%#endif%EOL%}%EOL%%EOL%";

    ENGINE_GEOM = "RexEngine.gs.glsl";
    _sources[ENGINE_GEOM] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%%EOL%#if 0 // currently unused - triangle discard implemented on CPU instead%EOL%%EOL%#pragma vp_name       REX Engine - GS%EOL%#pragma vp_entryPoint oe_rexEngine_gs%EOL%#pragma vp_location   geometry%EOL%%EOL%// Vertex Markers:%EOL%#define VERTEX_MARKER_DISCARD  1%EOL%#define VERTEX_MARKER_GRID     2%EOL%#define VERTEX_MARKER_PATCH    4%EOL%#define VERTEX_MARKER_BOUNDARY 8%EOL%#define VERTEX_MARKER_SKIRT    16%EOL%%EOL%layout(triangles)      in;%EOL%layout(triangle_strip) out;%EOL%layout(max_vertices=3) out;%EOL%%EOL%void VP_LoadVertex(in int);%EOL%void VP_EmitModelVertex();%EOL%%EOL%in vec4 oe_layer_tilec;%EOL%%EOL%void oe_rexEngine_gs(void)%EOL%{%EOL%    for(int i=0; i < 3; ++i )%EOL%    {%EOL%        VP_LoadVertex(i);%EOL%        if ( int(oe_layer_tilec.z) == VERTEX_MARKER_DISCARD )%EOL%            return;%EOL%    }%EOL%%EOL%    for(int i=0; i < 3; ++i )%EOL%    {%EOL%        VP_LoadVertex(i);%EOL%        gl_Position = gl_in[i].gl_Position;%EOL%        VP_EmitModelVertex();%EOL%    }%EOL%    EndPrimitive();%EOL%}%EOL%%EOL%#endif%EOL%%EOL%";

    SDK = "RexEngine.SDK.vert.glsl";
    _sources[SDK] = "#version $GLSL_VERSION_STR%EOL%$GLSL_DEFAULT_PRECISION_FLOAT%EOL%%EOL%#pragma vp_name Rex Terrain SDK%EOL%%EOL%/**%EOL% * SDK functions for the Rex engine.%EOL% * Declare and call these from any shader that runs on the terrain.%EOL% */%EOL%%EOL%// uniforms from terrain engine%EOL%uniform sampler2D oe_tile_elevationTex;%EOL%uniform mat4 oe_tile_elevationTexMatrix;%EOL%uniform vec2 oe_tile_elevTexelCoeff;%EOL%%EOL%uniform sampler2D oe_tile_normalTex;%EOL%uniform mat4 oe_tile_normalTexMatrix;%EOL%%EOL%uniform vec4 oe_tile_key;%EOL%%EOL%// Stage global%EOL%vec4 oe_layer_tilec;%EOL%%EOL%%EOL%/**%EOL% * Sample the elevation data at a UV tile coordinate.%EOL% */%EOL%float oe_terrain_getElevationUnscaled(in vec2 uv)%EOL%{%EOL%    // Texel-level scale and bias allow us to sample the elevation texture%EOL%    // on texel center instead of edge.%EOL%    vec2 elevc = uv%EOL%        * oe_tile_elevTexelCoeff.x     // scale%EOL%        + oe_tile_elevTexelCoeff.y;%EOL%%EOL%    return texture(oe_tile_elevationTex, elevc).r;%EOL%}%EOL%%EOL%/**%EOL% * Sample the elevation data at a UV tile coordinate.%EOL% */%EOL%float oe_terrain_getElevation(in vec2 uv)%EOL%{%EOL%    // Texel-level scale and bias allow us to sample the elevation texture%EOL%    // on texel center instead of edge.%EOL%    vec2 elevc = uv%EOL%        * oe_tile_elevTexelCoeff.x * oe_tile_elevationTexMatrix[0][0]     // scale%EOL%        + oe_tile_elevTexelCoeff.x * oe_tile_elevationTexMatrix[3].st     // bias%EOL%        + oe_tile_elevTexelCoeff.y;%EOL%%EOL%    return texture(oe_tile_elevationTex, elevc).r;%EOL%}%EOL%%EOL%/**%EOL% * Read the elevation at the build-in tile coordinates (convenience)%EOL% */%EOL%float oe_terrain_getElevation()%EOL%{%EOL%    return oe_terrain_getElevation(oe_layer_tilec.st);%EOL%}%EOL%%EOL%/**%EOL% * Read the normal vector and curvature at resolved UV tile coordinates.%EOL% */%EOL%vec4 oe_terrain_getNormalAndCurvature(in vec2 uv_scaledBiased)%EOL%{%EOL%    return texture(oe_tile_normalTex, uv_scaledBiased);%EOL%}%EOL%%EOL%vec4 oe_terrain_getNormalAndCurvature()%EOL%{%EOL%    vec2 uv_scaledBiased = oe_layer_tilec.st%EOL%        * oe_tile_elevTexelCoeff.x * oe_tile_normalTexMatrix[0][0]%EOL%        + oe_tile_elevTexelCoeff.x * oe_tile_normalTexMatrix[3].st%EOL%        + oe_tile_elevTexelCoeff.y;%EOL%%EOL%    return texture(oe_tile_normalTex, uv_scaledBiased);%EOL%}%EOL%%EOL%/**%EOL% * Scales repeating texture coordinate such that they are [0..1]%EOL% * at a specific reference tile LOD. %EOL% */%EOL%vec2 oe_terrain_scaleCoordsToRefLOD(in vec2 tc, in float refLOD)%EOL%{%EOL%    float dL = oe_tile_key.z - refLOD;%EOL%    float factor = exp2(dL);%EOL%    float invFactor = 1.0/factor;%EOL%    vec2 result = tc * vec2(invFactor);%EOL%%EOL%    vec2 a = floor(oe_tile_key.xy * invFactor);%EOL%    vec2 b = a * factor;%EOL%    vec2 c = b + factor;%EOL%%EOL%    float m = floor(clamp(factor,0.0,1.0)); // if factor>=1.0%EOL%    result += m*(oe_tile_key.xy-b)/(c-b);%EOL%%EOL%    return result;%EOL%}%EOL%%EOL%";
}
