void main(){
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0].st = gl_MultiTexCoord0.st;
	gl_FrontColor = gl_Color;
}