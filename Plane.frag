void MAIN() {
    vec2 uv = vec2(UV0.x, 1.0 - UV0.y);

    vec4 texPixel = texture(textureMap, uv);
    BASE_COLOR = texPixel;
}
