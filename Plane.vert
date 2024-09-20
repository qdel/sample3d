void MAIN()
{
    vec4 v = vec4(VERTEX, 1.0);
    vec4 pos = MODELVIEWPROJECTION_MATRIX * v;

    POSITION = pos;
}
