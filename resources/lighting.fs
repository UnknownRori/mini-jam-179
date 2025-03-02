#version 100

precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0; // light mask
uniform sampler2D current; // scene
uniform vec4 colDiffuse;


void main()
{
    vec4 texture = texture2D(current, fragTexCoord);
    vec4 light_mask = texture2D(texture0, fragTexCoord);

    gl_FragColor = vec4(texture.rgb * light_mask.rgb, texture.a);
}
