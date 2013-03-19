#version 130

uniform sampler2D tex;
uniform vec2 bk_texOffset0;
uniform vec2 bk_texSize0;
in vec2 bk_fragTex0;
out vec4 finalColor;

void main() {
    finalColor = texture(tex,  (bk_texSize0 * bk_fragTex0) + bk_texOffset0);
}

