uniform sampler2D texture;
uniform float offsetX;

void main()
{
    vec4 pixel = gl_Color;
    pixel.a = offsetX/gl_FragCoord.x;
	gl_FragColor = pixel;
}