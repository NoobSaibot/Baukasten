#version 130

uniform sampler2D tex;
uniform vec2 bk_texOffset0;
uniform vec2 bk_texSize0;
in vec2 bk_fragTex0;
in vec3 bk_Color;

void main() {
    gl_FragColor = texture(tex,  (bk_texSize0 * bk_fragTex0) + bk_texOffset0);
}

